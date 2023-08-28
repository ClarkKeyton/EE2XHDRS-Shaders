;--- INPUT
; V0 :	world vertex position
; V3 :	world vertex normal
; V7 :	texture uv
;
; C0 :	WorldViewProjTranspose
; C4 :  Player color

; Shader version 1.0
vs.1.0

m4x4 oPos, v0, c0

; set the diffuse color
mov oD0, c4