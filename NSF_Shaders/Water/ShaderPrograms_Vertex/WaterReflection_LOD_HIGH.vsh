// v0    - Vertex Position
// v5    - Color
// v6    - Reflection texture u,v
// v7    - Bump map u,v 
//
// c0-3	 - world-View-transpose matrix
// c4-7  - Composite World-View-Projection Matrix
// c8    - View vector: it is a constant, for accuracy, use the camera position - vertex position
// c13   - .y = time
// c14   - {basetexcoord distortion x0, y0, x1, y1} (0.031, 0.04, -0.03, 0.02)
// c15   - World Martix
// c19	 - texture uv multiplicator (2, 4, 6, 8)

vs.1.0
//------------------------------------------
// Set the vertex world position
//
//"Object space position" * "World-View-Projection matrix" = screen position
m4x4    oPos, v0, c4

//-----------------------------------------
//Set the water color
//
mov	oD0, v5

//-----------------------------------------
//Set the View vector
//
//Calculate the vertex world position
m4x4    r0, v0, c15

//-----------------------------------------
//distorted tex coord 0
//
mov     r0, c13.x
mul     r0, r0, c14.xyxy
frc     r0.xy, r0             //frc of incoming time
add     r0, v7, r0            //add time to tex coords
//mov r0, v7
mov     oT0, r0               //distorted tex coord 0

//-----------------------------------------
//distorted tex coord 1
//
mov     r0, c13.x
mul     r0, r0, c14.zwzw
frc     r0.xy, r0             //frc of incoming time         
add     r0, v7, r0            //add time to tex coords
//mov r0, v7
mov     oT1, r0.yxzw          //distorted tex coord 1

//Send the original uv
mov	oT2, v6

