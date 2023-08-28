// v0    - Vertex Position
// v1    - Color
// v2    - Vertex Texture Data u,v 
//
// c0-3  - Composite World-View-Projection Matrix
// c13   - .x = time
// c14   - {basetexcoord distortion x0, y0, x1, y1} (0.031, 0.04, -0.03, 0.02)

vs.1.1
//------------------------------------------
// Set the vertex world position
//
//"Object space position" * "World-View-Projection matrix" = screen position
m4x4    oPos, v0, c0

//-----------------------------------------
//Set the water color
//
mov	oD0, v1.rrra

//-----------------------------------------
//distorted tex coord 0
//
mov     r0, c13
mad     r0, r0, c14, v2
mov     oT0, r0					//distorted tex coord 0

//-----------------------------------------
//distorted tex coord 1
//
mov     r0, c13
mad     r0, r0, c15, v2
mov     oT1, r0					//distorted tex coord 1





