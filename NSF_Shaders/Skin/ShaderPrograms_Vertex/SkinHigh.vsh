//
// SkinHigh.vsh
// --------------------------------------------------------
//
// author: Shanti Gaudreault and Daniel Sproul
//
// description:
// Vertex shader to perform index palette skinning,
// no special lighting effects
//
// input:
// v0 	= PDP_Position
// v1	= PDP_BlendWeights
// v2	= PDP_BlendIndicies
// v3 	= PDP_Normal
// v7 	= PDP_TexCoord0
//
// constants:
// c0 	= SunDir				(Point3)
// c1 	= SunColor				(color)
// c3 	= MaterialDiffuse		(color)
// c5	= MiscConstants			(x = 0.0, y = 1.0, z = 0.5, w = 1020.01)
// c6 	= ViewProjTranspose		(matrix -- 4 registers)
// c10	= SkinBoneMatrix4		(80 registers!)
//
// output:
// oPos	= (projected) position
// oD0	= color
// oT0	= base texture coordinates
//
// --------------------------------------------------------

// VertexShader Version
// MUST BE 1.1 - since we use the a0 register!
vs.1.1


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
// oPos	= (projected) position

// @NOTE there are actually 4 matrices affecting a given vertex,
// to be more thorough we would, I think, get weights and apply
// transforms for each, but apparently we aren't doing that anymore...

// compute blend weight
mov		r8.x, v1.x				// w0
sub		r8.y, c5.y, r8.x    	// 1 - w0

// swizzle the input indicies, scaling by 1020.01
// @NOTE On DX8, we must use the swizzled input due to the usage of D3DCOLOR for 
// packing the indices...
mul		r9, v2.zyxw, c5.wwww

// Get the index of the bone matrix [0]
mov		a0.x, r9.x

// transform position and normal
m4x3	r0, v0, c[a0.x + 10]
m3x3	r1, v3, c[a0.x + 10]

// Get the index of the bone matrix [1]
mov		a0.x, r9.y

// transform position only
// @NOTE we are going to blend the position but not the normal
m4x3	r10, v0, c[a0.x + 10]

// blend positions
mul		r10.xyz, r10.xyz, r8.yyy
mad		r0.xyz, r0.xyz, r8.xxx, r10.xyz

// renormalize the normal
dp3		r8.x, r1.xyz, r1.xyz		// compute magnitude^2
rsq		r8.x, r8.x					// compute 1 / magnitude
mul		r1.xyz, r1.xyz, r8.xxx		// normalize

// pos.w = 1
// normal.w = 1
mov		r0.w, c5.y
mov		r1.w, c5.y

// output projected position
m4x4	oPos, r0, c6


// -------------------------------------------
// compute lighting
// -------------------------------------------
// oD0	= color

// Compute the color (N dot L * Color + Ambient)
dp3		r8.x, r1.xyz, -c0.xyz			// N dot -L
max		r8.xyz, r8.xxx, c5.xxx			// clamp to zero
mul		r8.xyz, r8.xyz, c1.xyz      	// * SunColor
add     oD0.xyz, r8.xyz, c2.xyz    		// + Ambient
mov     oD0.w, 	c3.w					// pass material alpha
