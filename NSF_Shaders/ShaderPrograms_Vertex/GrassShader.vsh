;--- INPUT
; V0 :	world vertex position
; V3 :	world vertex normal
; V7 :	texture uv
; V8 :	x = random number that will be use in conjonction with the game timer to get a radian degree
;		y = world vertex position distortion : 0 if the vertex is on the ground, n if vertex affect by wind
; V9:   x = v of the second uv coordinate.  To be use in conjonction with the first set u
;		y = Blending percentage of two textures blending
;
; C0 :	WorldViewProjTranspose
; C6 :	Lighting: Sun direction
; C7 :	Lighting: Sun color
; C8 :	Lighting: Ambient color
; C9 :  Constant: x = 4 (modulate4X), y = 1.07 to minimize taylor innacuracy, z = 0.5, w = 2Pi
; C10:	Taylor constant for Cos: (-0.16161616, 0.0083333, -0.00019841, 0.000002755731)
; C11:	x = Game timer (total time)
; C12:	x = wind speed
;		w = const 1.0
; C13:	x = y = 1 / far clipping 

; Shader version 1.0
vs.1.0

;--------------------------------------------------------------------------------
; Calculate how much distortion the wind apply to the top part of the grass blade
;
; r0 = radian degree = Random number + game timer * wind speed
mov		r0.x, c12.x						; create the total random number
mad		r0, r0.x, c11.x, v8.x			;
frc		r0.xy, r0						; keep the fraction and adjust for error that will be added from Taylor serie
mul		r0.x, r0.x, c9.y
sub		r0.x, r0.x, c9.z				; range from: [-pi to pi]
mul		r0.x, r0.x, c9.w
										; r1 = Taylor serie approximation
mul		r2, r0, r0						; radian^2
mul		r3, r2, r0						; radian^3 
mul		r5, r3, r2						; radian^5
mul		r7, r5, r2						; radian^7 
mul		r9, r7, r2						; radian^9
mad		r1, r3, c10.x, r0				; radian - (radian^3)/3! 
mad		r1, r5, c10.y, r1				; + (radian^5)/5! 
mad		r1, r7, c10.z, r1				; - (radian^7)/7! 
mad		r1, r9, c10.w, r1				; - (radian^9)/9! 

mul		r1, r1, v8.y					; World position += cos(degree) * blade distortion factor
mov		r0, v0
add		r0.x, r0.x, r1.x
add		r0.y, r0.y, -r1.x
m4x4	r2, r0, c0
mov		oPos, r2						;Kep r2 for future use

;---------------------------
; Lighting
;
dp3		r1.xyz, v3.xyz, -c6.xyz
mul		r1.xyz, r1.xyz, c7.xyz
add		r1.xyz, r1.xyz, c8.xyz
mul		oD0.xyz, r1.xyz, c9.x
mov		oD0.w, v9.y

;----------------------------
; Uv texture set 1
;
;mul		r2.z, r2.z, c13.x
;sub		r2.z, c12.w, r2.z
;mov		r1, v7
;mul		r1.x, r1.x, r2.z
;mov oT0, r1
mov oT0, v7

;----------------------------
; Uv texture set 2
;
mov oT1.y, v9.x
mov oT1.x, v7.x




;vs.1.0

;Compute the final output position in screen space
;It is not output directly to oPos because it is
;still needed to compute the depth and oPos is
;write only.
;dp4 r1.x, v0, c0
;dp4 r1.y, v0, c1
;dp4 r1.z, v0, c2
;dp4 r1.w, v0, c3

;emit the position
;mov oPos, r1

;compute the fog
;sub r1.z, r1.z, c4.x
;mul r1.z, r1.z, c4.y
;sub oFog.x, c4.z, r1.z
;mov oD0, c4.z

;texture UV
;mov oT0, v6 ; set texture coor.


