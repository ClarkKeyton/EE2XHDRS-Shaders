//----------------------------------------------------------------------------
// Vertex shader to perform index palette skinning
//----------------------------------------------------------------------------
// VertexShader Version
// MUST BE 1.1 - since we use the a0 register!
vs.1.1

//----------------------------------------------------------------------------
//
// input:
// v0 	= PDP_Position
// v1	= PDP_BlendWeights
// v2	= PDP_BlendIndicies
// v7 	= PDP_TexCoord0
//
// constants:
// c1 	= SunColor				(color)
// c2 	= SceneAmbient			(color)
// c3 	= MaterialDiffuse		(color)
// c5	= MiscConstants			(x = 0.0, y = 1.0, z = 0.5, w = 1020.01)
// c6 	= ViewProjTranspose		(matrix -- 4 registers)
// c10	= SkinBoneMatrix4		(80 registers!)
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Determine the last blending weight
//----------------------------------------------------------------------------
mov		r0.x, v1.x				// r0.xyz = w0,
add		r0.y, -r0.x, c5.y       // r0.w = 1 - (w0 ) = w1

//----------------------------------------------------------------------------
//   On DX8, use the swizzled input - dues to the usage of D3DCOLOR for 
//       packing the indices...
//----------------------------------------------------------------------------
mul		r1, v2.zyxw, c5.wwww        // r1 = indices w/ offset (DX8)

//----------------------------------------------------------------------------
// Transform the position for each bone
// v0 = position
//----------------------------------------------------------------------------
// Get the index of the bone matrix [0]
mov		a0.x, r1.x
// Transform position 
m4x3	r5, v0, c[a0.x + 10]
// Blend 
mul		r5.xyz, r5.xyz, r0.xxx

// Get the index of the bone matrix [1]
mov		a0.x, r1.y
// Transform position and 
m4x3	r2, v0, c[a0.x + 10]
// Blend them
mad		r5.xyz, r2.xyz, r0.yyy, r5.xyz


//----------------------------------------------------------------------------
// Transform the resulting position for the world
//----------------------------------------------------------------------------
mov		r5.w, c5.y
m4x4	oPos, r5, c6

//----------------------------------------------------------------------------
// Lighting based on a single directionnal light ignoring direction
//----------------------------------------------------------------------------
mov	r4.xyz, c5.zzz
mul	r4.xyz, r4.xyz, c1.xyz				// modulate ligth color by .5 to approximate the dir intensity
add     oD0.xyz, r4.xyz, c2.xyz			// add light ambient 
// pass alpha thru to the pixel shader
mov     oD0.w, 	c3.w

//----------------------------------------------------------------------------
// Just pass texture coordinates through
//----------------------------------------------------------------------------
mov oT0.xy, v7.xy
