//
// Gaussian_6Samp.vsh
// --------------------------------------------------------
//
// author: Daniel Sproul
//
// description:
// vertex shader which implements a 6-sample 3x3 gaussian blur filter for
// post-processing a rendered scene.
//
// note that this is being applied to a single screen poly.  what
// is going on in the vertex shader is we are offsetting texture coordinates
// by the same texel amounts for each vertex, so that when the tex coords
// are interpolated, the same offsets are achieved per-pixel
//
// input:
// v0 	= PDP_Position
// v7 	= PDP_TexCoord0
//
// constants:
// c6 	= WorldViewProjTranspose
// c10	= TexelSize (Point2)
//
// output:
// oT0	= upper-left tex coords
// oT1	= upper tex coords
// oT2	= left tex coords
// oT3	= right tex coords
// oT4	= bottom tex coords
// oT5	= bottom-right tex coords
//
// --------------------------------------------------------

// VertexShader Version
vs.1.0

// ----------------------------------------------------------------------------
// Transform the world position
// ----------------------------------------------------------------------------
m4x4    	oPos, v0, c6

// ----------------------------------------------------------------------------
// Compute texture coordinates for the six samples
// ----------------------------------------------------------------------------

// upper-left
sub			oT0.xy, v7.xy, c10.xy

// upper
mov			oT1.x, v7.x
sub			oT1.y, v7.y, c10.y

// left
sub			oT2.x, v7.x, c10.x
mov			oT2.y, v7.y

// right
add			oT3.x, v7.x, c10.x
mov			oT3.y, v7.y

// bottom
mov			oT4.x, v7.x
add			oT4.y, v7.y, c10.y

// bottom-right
add			oT5.xy, v7.xy, c10.xy
