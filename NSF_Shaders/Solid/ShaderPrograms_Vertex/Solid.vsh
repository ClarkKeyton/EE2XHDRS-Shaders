//
// Solid.vsh
// --------------------------------------------------------
//
// author: Daniel Sproul
//
// description:
// Basic shader for a solid (not skinned) object with
// no special lighting effects; this essentially just attempts to
// reproduce the fixed-function pipeline, and is probably entirely
// unnescessary...
//
// input:
// v0 	= PDP_Position
// v3 	= PDP_Normal
// v7 	= PDP_TexCoord0
//
// constants:
// c0 	= SunDir
// c1 	= SunColor
// c2 	= SceneAmbient
// c3 	= MaterialDiffuse
// c5	= MiscConstants				(x = 0.0, y = 1.0, z = 0.5, w = 1020.01)
// c6 	= WorldViewProjTranspose
// c14	= InvWorldTranspose
//
// output:
// oD0	= color
// oT0	= base texture coordinates
// oT1	= dark texture coordinates
//
// --------------------------------------------------------

// VertexShader Version
vs.1.0


// ----------------------------------------------------------------------------
// Transform the world position
// ----------------------------------------------------------------------------
mov			r0.xyz, v0.xyz
mov			r0.w, c5.y		// use w=1 for the position.  @NOTE this *shouldn't* be necessary, but on a hunch let's try it out...
m4x4    	oPos, r0, c6
//m4x4    	oPos, v0, c6


// ----------------------------------------------------------
// Lighting - Directional light
// 

// Find light vector in object space
mov			r5, -c0
m3x3		r4, r5, c14

// Normalize light vector.
// (store result in register 0)
dp3			r3.x, r4, r4
rsq			r2.x, r3.x
mul			r0, r4.xyz, r2.xxx

// Compute the color (N dot L * Color + Ambient)
dp3			r1.xyz, v3, r0		// N dot L @TODO clamp to zero?
mul			r1.xyz, r1, c1		// * Color
add			r1.xyz, r1, c2		// + Ambient
mul			oD0.xyz, r1, c3		// modulate by material color
mov			oD0.w, c3			// pass meterial alpha


// ----------------------------------------------------------------------------
// Just pass base and dark texture coordinates through
// ----------------------------------------------------------------------------
mov 		oT0.xy, v7
mov 		oT1.xy, v7
