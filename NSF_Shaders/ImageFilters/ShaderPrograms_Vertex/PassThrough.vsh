//
// PassThrough.vsh
// --------------------------------------------------------
//
// author: Daniel Sproul
//
// description:
// stupid shader that just transforms verts and passes through tex coords
//
// input:
// v0 	= PDP_Position
// v7 	= PDP_TexCoord0
//
// constants:
// c6 	= WorldViewProjTranspose
//
// output:
// oT0	= base texture coordinates
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
