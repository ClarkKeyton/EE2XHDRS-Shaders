// Shader version 1.1
// @NOTE this is identical to FireAdd_Modulate_Depth.vsh!
vs.1.1

// Transform position to clip space and output it
m4x4	r0, v0, c0
mov		oPos, r0

// set the diffuse color
mov oD0, v2

// Just copy the texture coords for texture 1
mov oT0, v3

// Send the z location
// @HACK changing this to normalize based on the greater of the
// z and w components, so that we don't have to worry about
// register clamping in the pixel shader
max	r1.x, r0.z, r0.w		// the greater...
rcp r1.x, r1.x
mul	oT1.xy, r1.xx, r0.zw	// normalized z,w output as tex coord 1
mov	oT1.z, r1.x				// also output the mult we used
