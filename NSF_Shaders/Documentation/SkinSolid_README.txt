//
// SkinSolid_README.txt
// --------------------
//
// Hi everybody!  Because the Skin and Solid shaders have
// so many variants, and yet have so much in common, but shader
// assembly is obnoxious and inflexible, I think that by
// establishing some conventions about which values go in
// which registers, we can actually have re-usable (ie. copy-
// pasteable) shader code.
//
// please adhere to the following guidelines:
// 
/////////////////////////////////////////////////////////////


/////////////////
// PACKING DEF //
/////////////////

// @NOTE the fixed function pipeline expects position, normal, and tex0
// to be in 0, 3, 7 respectively

Position				v0
BlendWeights			v1	(skin only)
BlendIndicies			v2	(skin only)
Normal					v3	(unused for low LOD skin)
TexCoord0				v7



/////////////////
//  CONSTANTS  //
/////////////////

// general constants
SunDir					c0	(unused for low LOD skin)
SunColor				c1
SceneAmbient			c2	(unused if using hemisphere lighting)
MaterialDiffuse			c3
MaterialSpecular		c4	(only if doing specular lighting)

// misc numeric constants
MiscConstants			c5	(0.0, 1.0, 0.5, 1020.01)

// matrices
// (skin)
ViewProjectionTranspose			c6	(4)
SkinBoneMatrix					c10	(80)
// (solid)
WorldViewProjectionTranspose	c6	(4)
WorldTranspose					c10	(4)
InvWorldTranspose				c24	(4)		(only used for non-hemisphere lighting Solid shader)

// hemisphere lighting constants
SkyColor				c90
TerrIntensity			c91
TerrDir					c92
TerrSizeRecip			c93
CutoffHeightRecip		c94
TerrZ					c95

// specular lighting constants
SunSpecular				c96
EyePoint				c97

// *unused*
c98
c99

// dynamic lighting constants
DynamicAmbient			c100
DL1_PositionAndRadius	c101	// xyz = position, w = 1 / r^2
DL1_Color				c102
DL2_PositionAndRadius	c103	// xyz = position, w = 1 / r^2
DL2_Color				c104
etc.


////////////////////
// REGISTER USAGE //
////////////////////

// vertex transformed into world space
vertex world position				r0
vertex world normal (normalized)	r1

// lighting contributions
sky hemisphere lighting contrib		r2
dynamic light 1 contrib				r3
dynamic light 1 contrib				r4
dynamic light 1 contrib				r5
dynamic light 1 contrib				r6

// *unused*
r7

// scratch
// @NOTE use these scratch registers, not the unused ones!
r8
r9
r10
r11

