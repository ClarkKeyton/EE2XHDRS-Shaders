//
// HDRFinal.vsh
// --------------------------------------------------------
//
// author: Daniel Sproul
//
// description:
// shader which implements final pass of HDR filter
// intended to be applied to a screen polygon textured
// with a rendered texture of the world scene
//
// input:
// v0 	= PDP_Position
// v7 	= PDP_TexCoord0		(base texture)
// v8 	= PDP_TexCoord1		(glare texture)
//
// constants:
// c6 	= WorldViewProjTranspose
//
// output:
// oT0	= base texture coordinates
// oT1	= glare texture coordinates
//
// --------------------------------------------------------

// VertexShader Version
vs.1.0

// ----------------------------------------------------------------------------
// Transform the world position
// ----------------------------------------------------------------------------
m4x4    	oPos, v0, c6

// ----------------------------------------------------------------------------
// Just pass base texture coordinates through
// ----------------------------------------------------------------------------
mov 		oT0.xy, v7
mov 		oT1.xy, v8
