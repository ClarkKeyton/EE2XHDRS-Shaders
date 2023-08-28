; Shader version 1.0
vs.1.0

; Transform position to clip space and output it
;dp4 oPos.x, v0, c0
;dp4 oPos.y, v0, c1
;dp4 oPos.z, v0, c2
;dp4 oPos.w, v0, c3
m4x4 oPos, v0, c0

; set the diffuse color
mov oD0, v3.z
mov oD1, v3.y

; Just copy the texture coords for texture 1 and 2
mov oT0, v7
mov oT1, v8
