; Shader version 1.0
vs.1.0

def c4,	1.0,0.0,0.0,1.0

; Transform position to clip space and output it
;dp4 oPos.x, v0, c0
;dp4 oPos.y, v0, c1
;dp4 oPos.z, v0, c2
;dp4 oPos.w, v0, c3
m4x4 oPos, v0, c0

; set the diffuse color
mov r0.x, c4.x
mul r0.y, r0.x, c5.x
frc r0.y, r0.y
mov oD0.w, r0.y
;mov oD0.w, c7.x

mov r0.x, c6.x
mul r0.x, r0.x, c4.x
sub oD1.w, c7.x, r0.x


; Just copy the texture coords for texture 1 and 2
mov oT0, v7
mov oT1, v7
