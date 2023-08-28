// v0    - Vertex Position
// v5    -	Color
//			R = water color intensity
//			G = blending percent in-between ocean and river/coast
//			B = the final color will be substract by this value.  It will only affect cost vertex
//			A = Water alpha
//
// v7    - Vertex Texture Data u,v 
//
// c4-7  - Composite World-View-Projection Matrix
// c8    - water normal
// c13   - c13.xyzw = time
// c14   - Texture 1:  x,y distortion
// c15   - Texture2 : x,y distortion

vs.1.1

//------------------------------------------
// Set the vertex world position
//
//"Object space position" * "World-View-Projection matrix" = screen position
m4x4    oPos, v0, c4

//-----------------------------------------
//Set the water color
//
mov		oD0, v5
mov		oD1, v5.zzzz

//-----------------------------------------
//distorted tex coord 0
//
mov     r0, c13
mad     r0, r0, c14, v7
mov     oT0, r0					//distorted tex coord 0

//-----------------------------------------
//distorted tex coord 1
//
mov     r0, c13
mad     r0, r0, c15, v7
mov     oT1, r0					//distorted tex coord 1

//Normal
mov		oT2, c8

