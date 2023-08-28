//
// Solid_Alt.vsh
// --------------------------------------------------------
//
// author: Daniel Sproul
//
// description:
// Basic shader for a solid (not skinned) object with rainbow vision
//
// input:
// v0 	= PDP_Position
// v3 	= PDP_Normal
//
// constants:
// c3 	= MaterialDiffuse			(color)
// c5	= MiscConstants				(x = 0.0, y = 1.0, z = 0.5, w = 1020.01)
// c6 	= WorldViewProjTranspose	(matrix -- 4 registers)
// c10	= WorldTranspose			(matrix -- 4 registers)
//
// output:
// oPos	= (projected) position
// oD0	= summed lighting
//
// --------------------------------------------------------

// VertexShader Version
vs.1.0

// ----------------------------------------------------------------------------
// Transform the world position
// ----------------------------------------------------------------------------
m4x4    	oPos, v0, c6


// -------------------------------------------
// compute world normal
// -------------------------------------------
// r1	= world normal

// transform normal into world space (and renormalize)
m3x3	r1, v3, c10					// transform into world space
dp3		r8.x, r1.xyz, r1.xyz		// compute magnitude^2
rsq		r8.x, r8.x					// compute 1 / magnitude
mul		r1.xyz, r1.xyz, r8.xxx		// normalize

// normal.w = 1
mov		r1.w, c5.y


// -------------------------------------------
// compute lighting
// rainbow vision! just use surface normal as color
// @TODO expose player color somehow
// -------------------------------------------
// oD0	= color

mul		r8.xyz, r1.xyz, c5.zzz		// N * 0.5 -> [-0.5 to 0.5]
add		oD0.xyz, r8.xyz, c5.zzz		// + 0.5 -> [0.0 to 1.0]
mov     oD0.w, 	c3.w				// pass material alpha