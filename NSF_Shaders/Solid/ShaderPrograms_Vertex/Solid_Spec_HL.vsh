//
// Solid_Spec_HL.vsh
// --------------------------------------------------------
//
// author: Daniel Sproul
//
// description:
// Vertex shader which implements hemisphere lighting effect for
// a solid (not skinned) object, no dynamic lights,
// with specular lighting
//
// input:
// v0 	= PDP_Position
// v3 	= PDP_Normal
// v7 	= PDP_TexCoord0
//
// constants:
// c0 	= SunDir					(Point3)
// c1 	= SunColor					(color)
// c3 	= MaterialDiffuse			(color)
// c4	= MaterialSpecular			(color)
// c5	= MiscConstants				(x = 0.0, y = 1.0, z = 0.5, w = 1020.01)
// c6 	= WorldViewProjTranspose	(matrix -- 4 registers)
// c10	= WorldTranspose			(matrix -- 4 registers)
// c90	= SkyColor					(color)
// c91	= TerrIntensity				(color)
// c92	= TerrDir					(Point3)
// c93	= TerrSizeRecip				(Point2)
// c94	= CutoffHeightRecip			(float)
// c95	= TerrZ						(float)
// c96	= SunSpecular				(color)
// c97	= EyePoint					(Point3)
//
// output:
// oPos	= (projected) position
// oD0	= summed lighting, minus terrain contribution
// oD1	= intensity with which to sample terrain texture to get terrain lighting contribution
// oT0	= base texture coordinates
// oT1	= terrain texture coordinates 
// oT2	= specular lighting (passed in texture coord, because we ran out of color
// 							 output registers; not to be modulated with base texture, so it must be passed separately)
//
// --------------------------------------------------------

// VertexShader Version
vs.1.0

// -------------------------------------------
// Transform vertex pos model -> view
// -------------------------------------------
// oPos	= (projected) position
m4x4    oPos, v0, c6

// -------------------------------------------
// Just pass base texture coordinates through
// -------------------------------------------
// oT0	= base texture coordinates
mov 	oT0.xy, v7


// -------------------------------------------
// compute world position and world normal
// -------------------------------------------
// r0	= world position
// r1	= world normal

// transform position into world space
m4x4	r0, v0, c10

// transform normal into world space (and renormalize)
m3x3	r1, v3, c10					// transform into world space
dp3		r8.x, r1.xyz, r1.xyz		// compute magnitude^2
rsq		r8.x, r8.x					// compute 1 / magnitude
mul		r1.xyz, r1.xyz, r8.xxx		// normalize

// pos.w = 1
// normal.w = 1
mov		r0.w, c5.y
mov		r1.w, c5.y


// -------------------------------------------
// hemisphere lighting
// -------------------------------------------
// r2	= sky lighting contribution
// oD1	= intensity with which to sample terrain texture to get terrain lighting contribution
// oT1	= terrain texture coordinates 

// Compute blending fractions

// normal-based terrain:
dp3		r8.x, r1.xyz, -c92.xyz		// normal-based terr blend contrib. = (N_vert dot N_terrain) [-1 to 1]
mad		r8.x, r8.x, c5.z, c5.z		// * 1/2 ==> [-1/2 to 1/2], + 1/2 ==> [0 to 1]
// height-based terrain:
sub		r9.x, r0.z, c95.x			// subtract out terrain Z from vertex Z
mul		r9.x, r9.x, c94.x			// divide Z (in world space) by model cutoff height (mul by reciprocal)
min		r9.x, r9.x, c5.y			// pick the smaller of that or 1.0 (@NOTE we get gt. 1 for verts above the cutoff height)
sub		r9.x, c5.y, r9.x			// invert (r11 = 1 - r11)
// combine the two components:
add		r8.x, r8.x, r9.x			// sum the normal- and height-based components @NOTE this puts us in [0 to 2], we could weight or sum them differently...
min		r8.x, r8.x, c5.y			// pick the smaller of that or 1.0
sub		r9.x, c5.y, r8.x			// blend contrib. of the sky = 1 - blend contrib. of the terrain

// Compute the terrain contribution
// (to be used in texture lookup in the pixel shader, the result added to the color in oD0)
// (store result in second output color register)
mul		r8.xyz, r8.xxx, c91.xyz		// modulate by terrain intensity
mul		oD1.xyz, r8.xyz, c3.xyz		// modulate by material color

// texture coords for the terrain lookup
// (store result in second texture coord output register)
add		r8.xy, r0.xy, r1.xy			// offset using the x and y of the surface normal (in world space) @TODO scale by some amount...
mul		r8.xy, r8.xy, c93.xy		// divide world position by terrain dims (mul by recip of terrain dims)
sub		r8.y, c5.y, r8.y			// invert y coord (pos.y = 1.0 - pos.y)
mov		oT1.xy, r8.xy				// copy to output register
		
// @TEST pass terrain texture coords in color 0
//mov	oD0.xy, r8.xy
//mov	oD0.zw, c5.yy

// compute sky lighting contribution
mul		r2.xyz, r9.xxx, c90.xyz		// just modulate sky blend contrib. by sky color


// -------------------------------------------
// specular lighting
// -------------------------------------------
// oT2	= specular lighting contribution
// r8.x	= N dot -L

// compute vector from vertex to eye point (and normalize)
sub		r9.xyz, c97.xyz, r0.xyz			// EyePoint - WorldLoc
dp3		r10.x, r9.xyz, r9.xyz			// compute magnitude^2
rsq		r10.x, r10.x					// compute 1 / magnitude
mul		r9.xyz, r9.xyz, r10.xxx			// normalize

// compute N dot -L
// leave this in r8.x for use by the combined lighting (below)
dp3		r8.x, r1.xyz, -c0.xyz			// N dot -L

// reflect light vector about the normal
// (@NOTE that while the light vector points toward the surface,
// resulting vector points away from the surface)
// L' = 2 * (N dot -L) * N + L
mul		r10.xyz, r1.xyz, r8.xxx			// N * (N dot -L)
add		r10.xyz, r10.xyz, r10.xyz		// * 2
add		r10.xyz, r10.xyz, c0.xyz		// + L

// compute specular lighting
dp3		r7.x, r9.xyz, r10.xyz			// VEye dot L'
max		r7.x, r7.x, c5.x				// clamp to 0
mul		r7.x, r7.x, r7.x				// ^2
mul		r7.x, r7.x, r7.x				// ^4
mul		r7.x, r7.x, r7.x				// ^8
//mul	r7.x, r7.x, r7.x				// ^16
//mul	r7.x, r7.x, r7.x				// ^32
mul		r7.xyz, r7.xxx, c96.xyz			// modulate by sun specular color
mul		oT2.xyz, r7.xyz, c4.xyz			// modulate by material specular color


// -------------------------------------------
// combined lighting
// -------------------------------------------
// oD0	= summed lighting, minus terrain contribution

// Compute the color ((N dot -L) * Color + SkyColor)
// we can re-use the N dot -L result from the specular lighting
//dp3	r8.x, r1.xyz, -c0.xyz			// N dot -L
max		r8.xyz, r8.xxx, c5.xxx			// clamp to zero
mad		r8.xyz, r8.xxx, c1.xyz, r2.xyz	// modulate by sun color, add sky illumination
mul		oD0.xyz, r8.xyz, c3.xyz			// modulate by material color
mov		oD0.w, c3.w						// pass meterial alpha

