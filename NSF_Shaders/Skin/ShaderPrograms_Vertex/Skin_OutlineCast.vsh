;----------------------------------------------------------------------------
; Vertex shader to perform index palette skinning
;----------------------------------------------------------------------------
; VertexShader Version
; MUST BE 1.1 - since we use the a0 register!
vs.1.1

;----------------------------------------------------------------------------
; Constants specified by the app
;		c0-3	= SkinWorldViewProj
;		c4		= player color
;		c5		= constants - 1,1,1,1020.01
;		c10+	= 20 bone matrices 
;
; Vertex components (as specified in the vertex DECL)
;       v0  = pVertex[i].position
;       v1  = pVertex[i].blendweights
;       v2  = pVertex[i].blendindices
;
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
; Determine the last blending weight
;----------------------------------------------------------------------------
mov		r0.x, v1.x				; r0.xyz = w0,
add		r0.y, -r0.x, c5.x       ; r0.w = 1 - (w0 ) = w1

;----------------------------------------------------------------------------
;   On DX8, use the swizzled input - dues to the usage of D3DCOLOR for 
;       packing the indices...
;----------------------------------------------------------------------------
mul		r1, v2.zyxw, c5.wwww        ; r1 = indices w/ offset (DX8)

;----------------------------------------------------------------------------
; Transform the position and normal for each bone
; v0 = position
; v3 = normal
;----------------------------------------------------------------------------
; Get the index of the bone matrix [0]
mov		a0.x, r1.x
; Transform position 
m4x3	r5, v0, c[a0.x + 10]
; Blend 
mul		r5.xyz, r5.xyz, r0.xxx

; Get the index of the bone matrix [1]
mov		a0.x, r1.y
; Transform position and 
m4x3	r2, v0, c[a0.x + 10]
; Blend them
mad		r5.xyz, r2.xyz, r0.yyy, r5.xyz


;----------------------------------------------------------------------------
; Transform the resulting position for the world
;----------------------------------------------------------------------------
mov		r5.w, c5.x
m4x4	oPos, r5, c0

;----------------------------------------------------------------------------
; no Lighting the player color is outputed directly
;----------------------------------------------------------------------------
mov     oD0.xyz, c4.xyz			; output player color as the color

