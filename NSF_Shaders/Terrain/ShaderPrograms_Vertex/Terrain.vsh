;Enter
;PDP_Position =		v0 = 	PDT_Float3
;PDP_Normal = 		v1 = 	PDT_Float3
;PDP_TexCoord0 = 	v2 = 	PDT_Float2
;
;CM_Defined =	ViewProjTranspose =		c0
;				
;				//Directional light
;CM_Global = 	SunDir =				c6
;CM_Global = 	SunColor = 				c7
;CM_Global = 	SceneAmbient = 			c8
;
;Start dynamic lighting where we will not brake any previous shader.  This should only
; works on video card that is complient to DirecX9
;CM_Constant=   Const_0_1_0_0			c96  = 0, 0.2, 0, 0
;
; VertexShader Version
vs.1.1

;----------------------------------------------------------------------------
; Transform the position into screen poistion
;
m4x4    oPos, v0, c0

;----------------------------------------------------------------------------
; Just pass texture coordinates through
;
mov		oT0, v2

;-----------------------------------------------------------------------------
; Transform the normal into world
;
mov		r11.xyz, v1											;r11 = world normal -DO NOT MODIFY-

;-----------------------------
; Lighting - Directional light
;
mov		r0, -c6
;Compute the color (N * L * Color + Ambient)
dp3		r1.xyz, r11, r0
mul		r1.xyz, r1, c7
add     oD0.xyz, r1 , c8									; r1 = color for directional light -DO NOT MODIFY-
mov		oD0.w, c4