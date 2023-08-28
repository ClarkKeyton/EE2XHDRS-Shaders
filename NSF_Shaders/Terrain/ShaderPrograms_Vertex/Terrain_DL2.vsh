;Enter
;PDP_Position =		v0 = 	PDT_Float3
;PDP_Normal = 		v1 = 	PDT_Float3
;PDP_TexCoord0 = 	v2 = 	PDT_Float2
;
;CM_Defined =	ViewProjTranspose =		c0
;CM_Defined =	MaterialDiffuse	=		c4
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
;Dynamic light 1
;CM_Global =	DL_1_Position = 		c97
;CM_Global =	DL_1_Radius = 			c98.x = reciprocal of squared radius
;CM_Global =	DL_1_Color = 			c99
;
;Dynamic light 2
;CM_Global =	DL_2_Position = 		c100
;CM_Global =	DL_2_Radius = 			c101.x = reciprocal of squared radius
;CM_Global =	DL_2_Color = 			c102
;
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
;mov     r1.xyz, c96.xxx										; r1 = color for directional light -DO NOT MODIFY-
;mov		oD0.w, c4
;-----------------------------
; Lighting - Directional light
;
mov		r0, -c6
;Compute the color (N * L * Color + Ambient)
dp3		r1.xyz, r11, r0
mul		r1.xyz, r1, c7
add     r1.xyz, r1 , c8										; r1 = color for directional light -DO NOT MODIFY-
mov		oD0.w, c4

;-----------------------------
; Lighting - Dynamic light 1
;
; Compute vertex world position
mov		r9, v0												;r9 vertex world position -DO NOT MODIFY-
; Compute light vector (light position - vertex position)
sub		r4, c97, r9											;r4 = vertex - light position
; Normalize light vector
dp3		r3.x, r4, r4
rsq		r2.x, r3.x
mul		r6, r4.xyz, r2.xxx
mul		r7.x, r3.x, c98.x									; r7.x = squared distance from vertex light -DO NOT MODIFY-
; Compute percent of light touching this vertex as directional light + dynamic embiant
dp3		r2.xyz, r11, r6
mov		r10.xyz, c96.xxx
max		r0.xyz, r2, r10
mul		r3.xyz, r0, c99
; falloff the color relativly to the light/vertex distance
mov		r10.x, c96.z
min		r0.x, r7.x, r10.x
sub		r0.x, c96.z, r0.x
mul		r3.xyz, r3.xyz, r0.xxx
add		r1.xyz, r3, r1

;----------------------------
; Lighting - Dynamic light 2
;
; Compute light vector (light position - vertex position)
sub		r4, c100, r9											;r4 = vertex - light position
; Normalize light vector
dp3		r3.x, r4, r4
rsq		r2.x, r3.x
mul		r6, r4.xyz, r2.xxx
mul		r7.x, r3.x, c101.x									; r7.x = squared distance from vertex light -DO NOT MODIFY-
; Compute percent of light touching this vertex as directional light + dynamic embiant
dp3		r2.xyz, r11, r6
mov		r10.xyz, c96.xxx
max		r0.xyz, r2, r10
mul		r3.xyz, r0, c102
; falloff the color relativly to the light/vertex distance
mov		r10.x, c96.z
min		r0.x, r7.x, r10.x
sub		r0.x, c96.z, r0.x
mul		r3.xyz, r3.xyz, r0.xxx

;final color ( 1 directional light + 1 dynamic light )
add		oD0.xyz, r3, r1