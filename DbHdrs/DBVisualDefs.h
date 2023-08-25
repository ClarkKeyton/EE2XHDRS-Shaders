 
//====================================================================
// Copyright 2003 Mad Doc Software, LLC. All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DBVisualDefs.h 234   10/18/05 3:09p Dsproul $
// $Modtime: 10/18/05 1:55p $
//====================================================================

#ifndef _VISUALDBDEFINITION_H__
#define _VISUALDBDEFINITION_H__
#pragma once

#include "HdrMacros.h"
#include "LSizedArray.h"
#include "DBWeaponType.h"
#include "DbGraphicSettingsDefs.h"
#include "LRGBA.h"

//====================================================================
// The folowing classes define the template data to use for visual construction from file.
//====================================================================
ENUM eDeletionMode {
	eUNITDIE,			// Kill unit when the unit die
	eNEVER,				// never auto delete
	eSTATECHANGE,		// kill at first state change
	ePLAYONCE,			// play one loop
	eUNITDIESOFT,		// Kill unit when the unit die, keep the animation playing for a last frame
	ePLAYONCE_AND_HIDE,  // this make it remain onteh model "forever" do not use unless you have good reson, ie you are managing it somehow
}; 

//====================================================================
// a simple visual representation can contain simple loopable ambient animation
// this maps to VisualAttachment
DATACLASS(BaseModel)
char*				ModelFileName;
char*				AnimFilename;
char*				TagPoint;
enum eDeletionMode	DeletionMode;
int					DisableWorldPhysics;			//Only disable the wind for now
float				m_Scale;				// @EE2X -- Daniel 03/14/05 -- optional scale (default 1.0)
bool				m_StartHidden;			// @EE2X -- Daniel 03/14/05 -- optionally start hidden
bool				m_FaceCameraRotateZ;	// @EE2X -- Daniel 04/12/05 -- optionally rotate in Z to face the camera
// @EE2X @MRC
// Use the top of the parent model (like a health bar) instead of the tag point.
bool				m_UseTopOfParent;	
// @EE2X @MRC
// An offset to use from the tag point.  Should contain 3 floats: X Y Z
Vec3f				m_Offset;
// And specify if this offset should be rotated based on the parent's rotation
bool				m_RotateOffsetWithParent;		
ENDCLASS


DATACLASS(DamageEffect)
	char*			ModelFileName;
	char*			TagPoint;
ENDCLASS

//====================================================================
//enum that determines a preset scaling factor assigned by category
ENUM eScaleType {
		kScaleIdentity,		// scale = 1.0f if no parent, otherwise it's parent's scale
		kScaleUnit,			// scale as a unit
		kScaleLandAnimal,	// scale as a land animal (cow, llama, etc)
		kScaleBuilding,		// scale as a building
		kScaleWall,			// walls get their own scale now!
		kScaleVehicle,		// scale for wheeled units
		kScaleMountedUnit,	// scale for units with horses
		kScaleTree,			// scale for trees
		kScaleAmmo,			// scale for ammos
		kScaleHero,				// scale for heroes -- @EE2X - Daniel 03/10/05
		kScaleHeroVehicle,		// scale for hero vehicles -- @EE2X - Daniel 04/13/05
		kScaleHeroMountedUnit,	// scale for hero mounted units -- @EE2X - Daniel 04/13/05
};

//====================================================================
// enum that control outline casting
ENUM eOutlineType {
	kOutlineDefault,		// the default, means take type from parent or none if no parent
	kOutlineReceive,		// model that can receive outline such has building
	kOutlineMake,			// model that can make outline such as humans
};

//====================================================================
// rendering parameters used by UIUnitRenderingBase
DATACLASS(UIUnitRenderingParams)
	// offset the eyepoint from the model center
	float	m_xOffset;
	float	m_yOffset;
	float	m_zOffset;

	// model scale
	float	m_scale;

	// model angle and rotation speed
	float	m_angle;			// starting angle in degrees
	float	m_rotationSpeed;	// rotation speed in degrees per second

	// camera pitch
	float	m_pitch;			// camera pitch in degrees from horizontal (positive points down)
	
	// lighting params
	float	m_lightAngle;		// angle in XY plane from camera
	float	m_lightPitch;		// pitch in degrees from horizontal (positive points down)
	LRGBA	m_lightDiffuse;		// light diffuse color
	LRGBA	m_lightSpecular;	// light specular color
	LRGBA	m_lightAmbient;		// light ambient color
ENDCLASS

//====================================================================
// This class is a simple container class that list a variable sized array of children
// common children are , the main model , a health bar , various individual effects, etc ...
DATACLASS(CompositeModel)
	enum eOutlineType	OutlineType;		// how this unit makes or receives outlines
	enum eScaleType		ScaleType;			// which predetermined scale factor gets applyied
	float				ForceScale;			// override scale
	char *				StateDatabaseName;	// the name of the state DB in the ddf
	LSizedArray<char*>	ChildNames;			// names of child instances in ddf
	char *				DamageDecalsSetName;	// name of the decals used, this should be a dataclass of TYPE DATACLASS(DamageDecalSet)
	DC(UIUnitRenderingParams) *m_UIRenderingParams;	// optional rendering parameters used by UIUnitRenderingBase
ENDCLASS

//====================================================================
// contains the template name to a complete appearance state definition database to use for animating appearance
// one state is active at a time , Ex.: walk , die , attack_01
DATACLASS(StateMachineModel)
	float				XOffset;	// the offset in model space to translate the visual
	float				YOffset;
	float				ZOffset;
	// the template name ( not class name ) of the specific visual DB to use.
	char*	StateDatabaseName;
ENDCLASS

// this clas adjusts over the grount keeping it's Z on the terrain Z
DATACLASS_INHERIT(FarmPlotModel, StateMachineModel)
ENDCLASS


// ---------------------------------
// data class for VisualBridge, specifies
// various models to be used in creating the bridge
DATACLASS_INHERIT(BridgeModel, StateMachineModel)
//DATACLASS(BridgeModel)
	char *				EndModel;		// the piece used for the start/end points
	char *				SpanModel;		// the repeatable middle section
	LSizedArray<char*>	SmokeNifNames;	// smoke particles
										// these two array should have the same nbr of elements
	LSizedArray<char*>	WaveNifNames;	// Waves nif
	LSizedArray<char*>	SplashNifNames;	// Splash nif
	LSizedArray<float>	WaveScales;		// Wave nif force scale
	LSizedArray<float>	SplashScales;	// Splash nif force scale
	LSizedArray<char*>  CollapseSounds;	// Names of sounds choose from during collapse.
	float				DelayBetweenSounds; // Minimum number of seconds to wait before starting another sound.
	char *				DamageDecalsSetName;	// name of the decals used, this should be a dataclass of TYPE DATACLASS(DamageDecalSet)
ENDCLASS


// -----------------------------------
// data class for VisualWall
//
DATACLASS(WallModel)
	// primary model used for most states
	char *		m_DefaultModel;

	// model variants for destroyed neighbors
	char *		m_OneNeighborDestroyedModel;
	char *		m_BothNeighborsDestroyedModel;

	// damage decals
	char *		m_DamageDecalsSetName;
ENDCLASS



//====================================================================
// this is a timed event. The event name and event data actually define what occurs.
ENUM eKeyType {
		HIDE_NODE,
		SHOW_NODE,	
		PLAY_SOUND,
		START_SOUND,
		START_SOUND_UNTIL_ANIM_CHANGE,
		STOP_SOUND,
		START_CONTROLLER,
		STOP_CONTROLLER,
		ATTACH_VISUAL,
		DETACH_VISUAL_BY_NAME,
		HIDE_VISUAL,
		SHOW_VISUAL,
};

DATACLASS(TextKey)
	//char*	Name;
	enum eKeyType	Name; // name makes no sense but is left for preventing to have to change about a million .ddfs
	char*			Data;
	float			KeyTime;
ENDCLASS

//====================================================================
// one single appearance state.
DATACLASS(ModelState)
	// the name of the state as taken by VisualSM::SetVisualState( )
	DBINDEX(DbVisualState) StateName;
	// the name of the model resource for this state
	char*		ModelName;
	// the name of the anim resource for this state
	char*		AnimName;
	// array of random variant names
	LSizedArray<char*>	AnimVariants;
	LSizedArray<float>	AnimVariantsWeights;
	
	float		AnimSpeedScale;
	// the array of text keys used to trigger timed visual events
	LSizedArray<DC(TextKey)*> TextKeys;
ENDCLASS

// @HACK @MRC Boy, howdy, this is really poor.  Soo...
// I need to make a user array of char* in StateDatabase (below).  LDynArray
// causes a memory leak, and I can't seem to create a char**.  (That throws up
// a parse error.)  This is my workaround.  I'm going to create a pointer to
// this new class, which will have a char* inside of it.  It's gross.
DATACLASS(StateDatabaseInternalName)
	USER char* m_ModelName;
ENDCLASS

//====================================================================
// the visual DB contains all possible states for a VisualSM
DATACLASS(StateDatabase)
	// this the parent database to wich all request that fail will e forwarded
	char * Parent;
	// the default state must have a model name
	char * DefaultModel;
	DBINDEX(DbVisualState) DefaultState;
	// array of states the model can be in.
	LSizedArray<DC(ModelState)*> States;
	// A list of models to choose from.  Specify this INSTEAD of DefaultModel
	// to randomly pick a .nif to use.
	LSizedArray<char*> DefaultModelList;

	// UnitModels create their own StateDatabase structures.  They can't modify
	// the LSizedArray model list because it's a fixed array.  We're not using
	// an LDynArray due to some crappy memory problems.  Using a DynArray in the
	// DataClass seems to cause a memory leak.
	USERPTR (StateDatabaseInternalName) m_ModelListInternal;
	USER int m_ModelListInternalLen;
ENDCLASS


//====================================================================
// displays a healthbar
// should be used as a composite child for units needing to diplay hit points  
DATACLASS(HealthBar)
	float m_verticalOffset;			// How high the health bar should be.

	// Colors for blending.
	LRGBA m_colorLow;				// The color to display when low.
	LRGBA m_colorMed;				// The color to display at 50%
	LRGBA m_colorHigh;				// The color to display when high.

	const char* m_UpdateMsg;		// What message do we listen for to update the bar?
	const char* m_FlashMsg;			// What message do we listen for to flash the bar?

	float m_StartingLevel;			// Starting level for this bar.

	// Data pertinent to flashing the health bar.
	bool  m_FlashWhenHealing;		// Should this health bar listen to the flashing messages when the unit is healed?
	const char* m_FlashTexture;		// What texture to play as the bar flashes.
	float m_FlashDuration;			// How long is a flash duration?
	float m_FlashAlphaMax;			// What is the max alpha for the background.
	float m_FlashAlphaMid;			// What is the midpoint.  The alpha goes between this and the max until the end when it fades to zero.
	float m_FlashAlphaRate;			// What is the rate of change of the alpha.  alpha/second.
ENDCLASS

//====================================================================
// displays a timer
DATACLASS(TimerEffect)
	float m_Duration;
	float m_Radius;
	float m_Offset;
ENDCLASS




// =================================================================
//				TerrainLines and related classes
//

// class for displaying patrol path, maps to VisualPatrolPath
// should be used as a composite child for units needing to display patrol paths
DATACLASS(PatrolPath)
	enum eScaleType m_WaypointVisualScaleType;
	const char	    *m_WaypointVisual;
ENDCLASS

// class for displaying queued orders, maps to VisualQueuedOrdersPath
// should be used as a composite child for units for which we wish to display queued orders
DATACLASS(QueuedOrdersPath)
	enum eScaleType m_WaypointVisualScaleType;
	const char		*m_DefaultTargetVisual;
	const char		*m_AttackTargetVisual;
ENDCLASS

// class for displaying a rally point flag or air mission flag, maps to VisualRallyPoint
// should be used as a composite child for units needing to diplay rally point
DATACLASS(RallyPoint)
	enum eScaleType m_FlagVisualScaleType;
	const char	   *m_FlagVisual;
	bool			m_MobileParent;		// set to 1 if parent visual is going to move around	
ENDCLASS

////////////////////////////
// @EE2X -- Daniel 03/14/05 -- changed to inherit from BaseModel
// the actual flag for the rally point, maps to VisualRallyFlag
DATACLASS_INHERIT(RallyFlag, BaseModel)
	char *m_FlagModel;			// which model to use
	char *m_BaseFlagTexture;	// base flag texture
	char *m_DarkFlagTexture;	// dark flag texture
	char *m_FlagTag1;
	char *m_FlagTag2;
	bool  m_VerticalFlag;
	float m_physicalWidth;
	float m_physicalHeight;
	float m_WindMult;
	float m_GravityMult;
	float m_SpringTensionMult;
	float m_SpringDampingMult;
	float m_DragCoefficientMult;
ENDCLASS

// Displays indicators to show the home and target trade buildings for a trade
// unit.
DATACLASS(TradePath)
ENDCLASS

// ==================================================================
//====================================================================
// Flag
DATACLASS(FlagEffect)
	float				FlagWidth;
	float				FlagHeight;
	float				BannerWidth;
	float				BannerHeight;
	bool				BannerWallOn;
	float				PennantWidth;
	float				PennantHeight;
	bool				OnMobileUnit;
ENDCLASS

//====================================================================
// Sail
DATACLASS(OneSail)
	char*						TextureName;
	float						FlagWidth;
	float						FlagHeight;
	int							NbrVertexWidth;				//Default = 6
	int							NbrVertexHeight;			//Deafult = 6
	float						WindDamping;				//Default should be one.  If not initialise in DDf, 
															// the code will initialize it to 1.
	bool						PlaneOn;
	bool						blockTop;
	bool						blockLeft;
	bool						blockBottom;
	bool						blockRight;
	bool						blockCornerTop;
	bool						blockCornerLeft;
	bool						blockCornerBottom;
	bool						blockCornerRight;
ENDCLASS

DATACLASS(SailEffect)	
	LSizedArray<DC(OneSail)*>	Sails;
ENDCLASS

//====================================================================
// a construction effect , using the base object mesh
// add this to a composite if a construction state effect is wanted
DATACLASS(BuildEffect)
	LSizedArray<char*>			Scaffolding;
	LSizedArray<char*>			Fence;
ENDCLASS
DATACLASS(BuildEffectStep)
	LSizedArray<char*>			ConstructionModels;
ENDCLASS
DATACLASS(ScaffoldBuildEffectStep)
	char* ScaffoldModel;
ENDCLASS



//====================================================================
// for SelectCircle, an enum that tells it how to determine its radius
ENUM eRadiusMode {
	kRadiusMode_UnitRadius,		//the selectioncircle radius should be based on the unit's radius
	kRadiusMode_EffectArea,		//the selectioncircle radius should be based on the widest area effect attached to the unit
	kNumRadiusModes,
};

//====================================================================
// a circle that appears at the base of the unit if the unit is selectable and selected

DATACLASS(SelectCircle)
	char*	TextureFilename;				// The texture to draw for this selection circle.  
	float	m_TextureScale;					// Scale to modify the size of the primary selection circle.
											// This does not modify any secondary texture.
	float	m_TextureScaleWidth;			// Scale the width of the texture.  For changing the shape

	char*	m_SecondaryTextureFilename;		// A secondary texture that may be drawn.  It's not drawn by default.
	float	m_SecondaryTextureScale;		// How much to scale the secondary texture, after being scaled to the
											// unit radius.
	float	m_SecondaryTextureScaleWidth;	// Scale the width of the secondary texture

	enum eRadiusMode	RadiusMode;			// The radius mode, to use the unit radius or that of an area effect.
	bool	UseGeometry;					// Whether or not to project the circle onto the terrain, or use a piece
											// of geometry instead.
	float	m_VerticalOffset;				// When using geometry, how how much do we offset the circle?
ENDCLASS

//====================================================================
// Manages a terrain shadow, updating as necessary when the composite location changes

DATACLASS(FlatBillboardShadow)
	char *  m_TextureFilename;
	float   m_WidthScale;
	float	m_LengthScale;
	float   m_HeightScale;
ENDCLASS

DATACLASS(UprightBillboardShadow)
	char *  m_TextureFilename;
	float   m_RadiusScale;
	float   m_HeightScale;
ENDCLASS

FLAGS(kShadowFlag)
const uint32 kShadowFlag_UseStencil      = 0x0001; // If stencil shadows enabled, should we create one?
const uint32 kShadowFlag_IsMobile        = 0x0002; // Is the visual's position expected to change frequently?
												   // @NOTE: this is distinct from _animation_, which is detected 
												   // automatically (I hope)
const uint32 kShadowFlag_HasTurret       = 0x0004; // @HACK: for units with turrets
const uint32 kShadowFlag_SkipAlpha       = 0x0008; // when specified, skip geometry that uses alpha textures 
										           // when generating stencil shadows
const uint32 kShadowFlag_AutoGenerated   = 0x0010; // automatically generate a projected shadow texture.
                                                   // DO NOT USE WITH GEOMETRY THAT CHANGES FREQUENTLY
const uint32 kShadowFlag_ImmutableBounds = 0x0020; // don't update projected shadow bounds after creation
ENDFLAGS

DATACLASS(ShadowData)
	FLAGS(kShadowFlag) uint32 m_Flags;             // a combination of one or more kShadowFlags

	// @NOTE: these are incompatible with the use of kShadowFlag_AutoGenerated
	DC(FlatBillboardShadow)*    m_FlatBillboard;   // project a specified texture as a horizontal billboard
	// Or
	DC(UprightBillboardShadow)* m_UprightBillboard;// project a specified texture as a vertical billboard
ENDCLASS


//====================================================================
// a decal state is one frame of a decal animation, the state name must be one that is set 
// by on a visual SM so that the event is catched in the decal
// The AnimFPS is how many texture flips in a second, if there is multiple textures. 0 means no flip.
// The fadeout time is how long to fade out the complete decals. 0 for never.
DATACLASS(DecalState)
	DBINDEX(DbVisualState)			StateName;
	// these arrays are the same size, they contain the epoch number and the corresponding sprite to use
	LSizedArray<DBINDEX(DbSprite)>	RuralSpriteNames;		
	LSizedArray<DBINDEX(DbSprite)>	UrbanSpriteNames;		
	float							StartFadeDelay;
	float							FadeOutTime;	// time to fade out
	float							WorldSize;
ENDCLASS


//====================================================================
// a decal applyed under units that gets rotated with the unit and scaled accordingly
DATACLASS(Decal)
	LSizedArray<DC(DecalState)*> States;
	DBINDEX(DbVisualState)		 m_DefaultState;	// default state ("Idle" if unspecified)
	float                        m_Scale;           // scale factor for decals that want 
													// to be significantly smaller than 
													// their parent's footprint.
ENDCLASS


//======================================================
// road decal -- done as a separate class just to get the right creation func. called
//				(maps to VisualRoadDecal)
DATACLASS_INHERIT(RoadDecal, Decal)
ENDCLASS

// road elbow decal -- done as a separate class just to get the right creation func. called
//				(maps to VisualRoadElbowDecal)
DATACLASS_INHERIT(RoadElbowDecal, Decal)
ENDCLASS


DATACLASS(SinkAnim)
	float	LifeSpan;
	float	StartDelay;
	float	SinkSpeed;
	bool	HideWhenFinished;
ENDCLASS

DATACLASS(MuzzleSmokeEffect)
LSizedArray<char*>		EffectModel;
char *					ExplosionName;
float					m_EffectScale;
ENDCLASS

//====================================================================
// Damage effects for buildings and ships.  It is expected for buildings to 
// have tags defined where the damage effects can be applied.  The tags should 
// be named some variant of "Tag_Fire_####_1", where the #### is some keyword 
// that is used to sync up with our data structure below.
//
// Example:
// Building has three tag points: "Tag_Fire_Front_1", "Tag_Fire_Front_2",
//	"Tag_Fire_Top_1"
// Data defined as follows:
// BldDamageEffect		TheBldDamageEffect 
// { 
//	   TagDefs = [
//             {
//	               TagName = "front"
//                     Models = [ { ModelName = fx_damage_fire_1.NIF ModelScale = 0.05 }
//                                { ModelName = fx_damage_fire_2.NIF ModelScale = 0.05 }
//                              ]
//             }
//             {
//	               TagName = "top"
//                     Models = [ { ModelName = fx_damage_fire_1.NIF ModelScale = 0.05 }
//                                { ModelName = fx_damage_fire_2.NIF ModelScale = 0.05 }
//                              ]
//             }
//         ]
// }
// 
// As damage is done to the building, the effect will choose a tag point
// randomly to show a fire effect.  If it chooses Tag_Fire_Front_1, it will 
// then pick one of the "front" fire effects to apply at that position.

DATACLASS(BldgDamageModel)
	const char* m_ModelName;
	float m_ModelScale;
ENDCLASS

DATACLASS(BldgDamageTagDef)
	const char*				m_TagName;
	LSizedArray<DC(BldgDamageModel)*> m_Models;
ENDCLASS

DATACLASS(BldDamageEffect)
	LSizedArray<DC(BldgDamageTagDef)*>	m_TagDefs;
	char*								FireDataClassName;
	char*								SmokeDataClassName;
	bool								UseHitPointThreshold;
	float								HitPointThreshold;

	// visual defs to use for fire dynamic lights
	// these should specify legit. DbDynamicLightEmitterDef DC's
	LSizedArray<const char *> m_FireLights;
ENDCLASS

//Boat wakes
DATACLASS(BoatWake)
	char*					WakeModelsName;
	char*					WakeVshapeName;
	char*					WakeIdleName;
	float					Scales;
	float					WakeMovedTimer;
	float					WakeIdleTimer;
	LSizedArray<char*>		WakeSinkName;
	bool					StopUnderWater;
ENDCLASS

DATACLASS(UnitTracks)
	int						m_NumFeet;					// The number of feet of this unit.  This is used in processing
														// the list of decal names to lay down the appropriate decal.
	
	LSizedArray<char*>		m_TrackDecalNames;			// Array of decals to use for the tracks.  The length of this
	LSizedArray<char*>		m_TrackDecalNamesLod2;		// list should be a multiple of m_NumFeet.  For example, for 
	LSizedArray<char*>		m_TrackDecalNamesLod3;		// humans with two feet, it should contain an even number of
														// decal names.  Also, the decal names should be ordered:
														// leftfoot01, rightfoot01, leftfoot02, rightfoot02, etc.
	float					m_TrackSpacing;

	float					m_JitterPositional;			// Amount to randomly shift the track in a positional sense.
														// Randomly shifts both X and Y an amount between 
														// -m_JitterPositional and m_JitterPositional.
	float					m_JitterRotational;			// Amount to randomly shift the track in a rotational sense.
														// Randomly shifts the orientation an amount between
														// -m_JitterRotational and m_JitterRotational.

	bool					m_ShowTurns;				// Draw tracks when turning?
	const char*				m_TrackDecalTurnL;			// The name of the decal for left turns.
	const char*				m_TrackDecalTurnR;			// The name of the decal for right turns.
	float					m_TrackTurnSpacing;			// The space to put between tracks.  Useful for footprints.		

ENDCLASS

//Water Splash
DATACLASS(WaterSplash)
	char*					SplashInModelsName;
	char*					SplashOutModelsName;
ENDCLASS

//Boat death
DATACLASS(BoatDeath)
	char*					boatDeathModelOpaque;
	char*					boatDeathModelTransparent;
ENDCLASS

//Waves
DATACLASS(WavesArray)
ENDCLASS

//Storm
DATACLASS(StormDC)
LSizedArray<char*>			SandGroundNifNames;
LSizedArray<char*>			SandAirNifNames;
LSizedArray<char*>			SnowGroundNifNames;
LSizedArray<char*>			SnowAirNifNames;
ENDCLASS

// Enumeration of ways to fade between two values.
ENUM eFadeType{
	kFadeType_Linear,				// Straight linear fade
	kFadeType_QuadFastStart,		// Quadratic fade starting fast and decelerating toward second value
	kFadeType_QuadSlowStart,		// Quadratic fade starting slow and accelerating toward second value
};

DATACLASS(WorldLightFlash)
	LRGBA m_FlashPeakColor;			// Color of the light at peak of the flash.  Ignores alpha, only uses RGB.

	float m_TimeIn;
	float m_TimeDur;
	float m_TimeOut;

	enum eFadeType m_FadeInType;
	enum eFadeType m_FadeOutType;
ENDCLASS

// Definition for thunder and lightning.
DATACLASS(ThunderLightningDef)
	LSizedArray<char*>					m_FlashNames;				// Possible flashes to use.
	
	float								m_DelayBetweenLightningMin;	// The min time to wait for another bolt.
	float								m_DelayBetweenLightningMax;	// The max time to wait for another bolt

	float								m_DelayBetweenFlashMin;		// The min time to wait between flashes within a bolt
	float								m_DelayBetweenFlashMax;		// The max time to wait between flashes within a bolt

	// This is for distant thunder
	LSizedArray<char*>					m_ThunderFarNames;		// Sounds to play for the thunder.
	float								m_ThunderDelay;
	
	// This is for closer, louder cracks when we can see the lightning bolt.  These
	// don't have a delay because they happen with the crack.
	LSizedArray<char*>					m_ThunderNearNames;
ENDCLASS

DATACLASS(ScreenFlash)
	LRGBA m_PeakColor;								// The peak color of the flash.

	// Fade in, duration, and fade out.
	float m_TimeIn;
	float m_TimeDur;
	float m_TimeOut;

	// How do we fade in and out.
	enum eFadeType m_FadeInType;
	enum eFadeType m_FadeOutType;

ENDCLASS

DATACLASS(DestinationIndicator)
	const char* m_ClickIndicator;					// The indicator to use to show where the actual mouse click happened.
	LRGBA m_ClickColor;								// The color of the mouse click
	float m_ClickIndicatorScale;					// The scale for the mouse click indicator
	const char* m_UnitIndicator;					// The texture for the unit location indicator (will be scaled by unit radius)
	LRGBA m_UnitColor;								// The color of the unit indicator
	float m_TimeDur;								// The length before fade
	float m_TimeFade;								// The time to fade.  (Fade is a shrink to nothing, in this case)
	
	const char* m_OrientIndicator;					// The indicator to use to show orientation.
	float m_OrientIndicatorScale;					// Scale for the orient indicator.
ENDCLASS

DATACLASS(AnimatedTerrainTexture)
	const char* m_Texture;							// Name of the texture to animate.

	LRGBA m_StartColor;								// The start color of the texture
	LRGBA m_MidColor;								// Mid-level color
	LRGBA m_EndColor;								// Ending color

	float m_TimeColorUp;							// Time to go from start to mid color
	float m_TimeColorPeak;							// Time to stay at mid color
	float m_TimeColorDown;							// Time to go from mid to end color

	// How do we fade color up and down
	enum eFadeType m_ColorUpType;
	enum eFadeType m_ColorDownType;

	float m_StartScale;								// start scale
	float m_MidScale;								// mid scale
	float m_EndScale;								// ending scale 

	float m_TimeScaleUp;							// Time to go from start to mid scale
	float m_TimeScalePeak;							// Time to stay at mid scale
	float m_TimeScaleDown;							// Time to go from mid to end scale

	// How do we fade scale up and down
	enum eFadeType m_ScaleUpType;
	enum eFadeType m_ScaleDownType;

ENDCLASS

//====================================================================
// Streaks
//
DATACLASS(StreaksEffect)
	float					BoundingSphereRadius;
	char*					TagName;				
	DBINDEX(DbVisualState)  StateToStart;			//Any game states (Death, attack....)  OR
													// "WaitForMessage" (it will wait to receive a message to start) OR
													// Not assigning anyting will force it to start at creation
	bool					NeverKillEffect;
	float					RotationSpeed;
	float					Red;
	float					Green;
	float					Blue;
	float					Alpha;
	float					ModifiedAlpha;
	char*					TextureName;
	int						MamimumWidthVertices;
ENDCLASS

//====================================================================
// this class makes a named node point at another node along it's z axis

DATACLASS(VisualTurretData)
	// nada
ENDCLASS


DATACLASS(UnitModel)
	// this the model of which any unspecified feature is taken from
	char *				Parent;	
	enum eOutlineType	OutlineType;		// how this unit makes or receives outlines
	enum eScaleType		ScaleType;			// which predetermined scale factor gets applyied
	float				ForceScale;			//  scale override
	LSizedArray<char*>	ChildNames;			// names of child instances in ddf
	char *				DefaultModel;		// model that is used if none is specified in a state
	// A list of models to choose from.  Specify this INSTEAD of DefaultModel
	// to randomly pick a .nif to use.
	LSizedArray<char*>		DefaultModelList;
	DBINDEX(DbVisualState)	DefaultState;		// initial state, if none parent is used
	char *					DamageDecalsSetName;	// name of the decals used, this should be a dataclass of TYPE DATACLASS(DamageDecalSet)
	char *					DamageTerrainDecalSetName;	// Name of decals used to damage the underlay texture.
	float					DamageTerrainDecalFadeTime;	// How long should it take the damage decals to fade after unit death.
	LSizedArray<DC(ModelState)*> States;			// array of states the model can be in.
	DC(UIUnitRenderingParams) *m_UIRenderingParams;	// optional rendering parameters used by UIUnitRenderingBase
ENDCLASS

DATACLASS(DamageDecalSet) 
	// array of textures to apply on the model
	// they are ordered from 0 dmg ot dead. they will be spaced evenly at health/texturecount+1
	//  so 9 textures mean every 10% additionnal dmg starting 90% health
	// the 100% health state has no decal
	LSizedArray<char*> Decals;	
ENDCLASS

// one single attachement set.
// the tag root is the first letters of the named tag points.
// all tag points starting with those letters will have a random item from the set attached to it.
// the name of the set is used to activate deactivate the set, Ex.: Temperate, Jungle , etc.
DATACLASS(AttachmentSet)
	char*				TagNameRoot;
	char*				SetName;
	LSizedArray<char*>	AmbientList;
ENDCLASS

// this class links set of possible attachment to sets of possible tag points
// the startup set's naem should be valid and entered in "DefaultSet"
// the scaletype param determines the world scale of the attachement indepently of the parents.
// if left to default it will be caried over from the parent.
DATACLASS(AttachmentPlacerData)
	enum eScaleType					ScaleType;
	char*							DefaultSet;
	LSizedArray<DC(AttachmentSet)*> Ambients;
ENDCLASS

//====================================================================
// Explosion class
//
ENUM eExplosionSequenceType {
	kExplosionSequenceType_Nif,				// Nif name
	kExplosionSequenceType_ShockWave,		// Nif specificly 
	kExplosionSequenceType_Explosion,		// Explosion DC name
	kExplosionSequenceType_Message,			// Message name
	kExplosionSequenceType_Visual,			// Visual name
	kExplosionSequenceType_Decal,			// Project a texture onto the terrain.
	kExplosionSequenceType_ModelSwap,		// Swap the main model on which this explosion is happening.
	kExplosionSequenceType_FlashWorldLight, // Flash the world light
	kExplosionSequenceType_FlashScreenPanel,// Flash a panel in front of the screen.
	kExplosionSequenceType_Wake,			// Play a .nif on the water.
	kExplosionSequenceType_DynamicLight,	//Add a dynamic light
	kNumExplosionSequenceType,
};

ENUM eCauseOfDeathPower {
	kCauseOfDeath_Low,
	kCauseOfDeath_Medium,
	kCauseOfDeath_High,
	kNumCauseOfDeathPower,
};

ENUM eCauseOfTrigger {
	kCauseOfTrigger_StaticMessage,
	kCauseOfTrigger_DynamicMessage,
	kNumCauseOfTrigger,
};

ENUM eTypeOfCollision {
	kTypeOfCollision_Hit,
	kTypeOfCollision_Final,
	kNumTypeOfCollision,
};

// Weapon type flags.  These match the enum eWeaponType found in
// DbWeaponType.h
FLAGS(kWeaponTypeFlag)
// No weapon type... works with units that don't have weapon types.
const uint32 kWeaponTypeFlag_None = 0;
// The specific weapon types
const uint32 kWeaponTypeFlag_Melee = 1;
const uint32 kWeaponTypeFlag_LightProjectile = 2;	
const uint32 kWeaponTypeFlag_MediumProjectile = 4;
const uint32 kWeaponTypeFlag_Missile = 8;
const uint32 kWeaponTypeFlag_Beam = 16;
const uint32 kWeaponTypeFlag_Nuke = 32;
// Weapon types specifically for projectiles.  These control the type
// of explosion based upon what the projectile hits.
const uint32 kWeaponTypeFlag_Building = 64;
const uint32 kWeaponTypeFlag_MobileUnit = 128;
const uint32 kWeaponTypeFlag_Terrain = 256;
// Any weapon type.  Use this if you want to be able to explode with ANY
// weapon.
const uint32 kWeaponTypeFlag_Any = 512;
// Any weapon except nukes.
const uint32 kWeaponTypeFlag_NotNuke = 479;
ENDFLAGS

DATACLASS(ExplosionSequence)
	float								BoundingSphereRadius;
	float								TimeA;
	float								TimeB;
	float								DelayBeforeDie;					// This is the amount of time after each time the sequence
																		// starts before it is marked deleted.
	float								StartingPositionMinX;
	float								StartingPositionMaxX;
	float								StartingPositionMinY;
	float								StartingPositionMaxY;
	float								StartingPositionMinZ;
	float								StartingPositionMaxZ;
	bool								StartFromMainModel;
	int									Replay;
	float								FiringProbability;
	enum eExplosionSequenceType			SequenceType;
	bool								PlayAll;
	LSizedArray<char*>					SequenceNames;
	LSizedArray<float>					SequenceWorldScales;
	LSizedArray<char*>					SequenceSoundsNames;
	LSizedArray<int>					SequenceDrawingOrderLayer;		// 0, 1, or 2.
	LSizedArray<int>					SequenceMessageParameterInt;
	LSizedArray<char*>					SequenceMessageParameterString;
	float								m_MaxHeightForDecal;			// Maximum allowable height above the terrain
																		// for a decal to be drawn.
	bool								m_DisableWorldPhysics;			// For explosions, you can disable the world physics from affecting the particles
																		// in a nif
	float								m_WakeMaxRadius;				// For wake effects, the max radius.
	float								m_WakeAnimTime;					// For wake effects, the animation time.
	bool								ContainsBlood;
ENDCLASS

DATACLASS(Explosion)
	float								BoundingSphereRadius;
	LSizedArray<DBINDEX(DbVisual)>		ExplosionSequences;
	bool								VelocityOn;
	float								VelocityAngle;			//[0 - 180]. 0 = 1 Zaxis, 180 = -1 Zaxis
	float								SpeedMin;
	float								SpeedMax;
	bool								GravityOn;
	bool								AttachToParent;
	bool								ForceToGround;			// If this is true, then the explosion will occur at
																// ground (or water) level.  This also forces the
																// parent visual to the ground, so be careful.  This
																// should mostly only be used on ammo explosions when
																// the ammo is going to disappear anyway.
ENDCLASS

DATACLASS(ExplosionSelectorEntry)
	float								BoundingSphereRadius;
	enum eCauseOfTrigger				Trigger;
	enum eTypeOfCollision				Collision;
	FLAGS(kWeaponTypeFlag) uint32		Weapon;
	//Member for the message type
	char*								MessageName;
	//General for all type
	char*								ExplosionName;
	float								HitPoint;
	bool								Hide;					//If explosion not visible, play anyway if true
ENDCLASS

DATACLASS(ExplosionSelector)
	LSizedArray<DC(ExplosionSelectorEntry)*> ExplosionDescriptors;
ENDCLASS


//====================================================================
// Visual related to the explosion effect
//
DATACLASS(FlyingPartEntry)
	char*										NifName;
	float										WorldScale;
	float										VelocityAngle;			//[0 - 180]. 0 = 1 Zaxis, 180 = -1 Zaxis
	float										VelocityAngleMin;		// Just like velocity angle, but this is a minimum value.
	float										SpeedMin;
	float										SpeedMax;
	float										StartingPositionMinX;
	float										StartingPositionMaxX;
	float										StartingPositionMinY;
	float										StartingPositionMaxY;
	float										StartingPositionMinZ;
	float										StartingPositionMaxZ;
	float										Mass;
	float										BouncingEnergyKeep;		//[0 - 1] percentage of velocity to keep when bouncing
	float										RotationSpeedMin;		//Speed at wich the part should rotate
	float										RotationSpeedMax;
	char*										DeathExplosionName;		//if an explosion name is set, the object will not
																		// not bounce but will explode
	char*										DeathExplosionNameWater;// Explosion to use if it dies on water.
	bool										NoRandom_ForceToPlay;
	float										TimeBeforeVanish;
	bool										m_UseRandomOrientation; // If true, object is randomly oriented when the explosion starts.
	bool										m_floatOnWater;
ENDCLASS

DATACLASS(FlyingPart)
	LSizedArray<DC(FlyingPartEntry)*>			Parts;
	int											NbrPartToSpawnMin;
	int											NbrPartToSpawnMax;
	bool										RenderAtAllLOD;
ENDCLASS

//====================================================================
//Laser
//
ENUM eLaserTypeOfDeath {
	eLaserTypeOfDeath_All,
	eLaserTypeOfDeath_Message_BegginingToEnd,
	eLaserTypeOfDeath_Message_BegginingToEnd2,
	eLaserTypeOfDeath_Message_Catchup,			// The tail of the beam catches up with the head.
};
//DATACLASS(BeamEntry)
//ENDCLASS
DATACLASS(BeamEffect)
	char*										StartLaserName;
	char*										MiddleLaserName;
	char*										EndLaserName;
	char*										StartEffect;
	char*										SplashEffect;
	float										Life;						//This is the laser life from : visualcreation+DelayBeforeStartLaser.
	float										SplashEffectLife;
	float										StartEffectLife;
	float										DelayBeforeStartLaser;		//This is a delay for the laser, not for the "StartEffect"
	float										DelayBeforeStartMiddleLaser;
	float										TravelSpeed;
	float										DeathLife;					//How long it takes for the laser to die from : visualcreation+DelayBeforeStartLaser+Life
	enum eLaserTypeOfDeath						TypeOfDeath;	
	int											RepeatEffect;
	bool										m_FireAndForget;			// Should we remember and continue to use the initial muzzle position forever.	
ENDCLASS

//====================================================================
// @EE2X ligthing
//
ENUM eDynamicLightingAttenuation {
	eDynamicLighting_Linear,
	eDynamicLighting_Quadratic,
};
ENUM eDynamicLightingType {
	eDynamicLightingType_OneColor_PlayOnce,								// Light always face the center of the object eing lit			
	eDynamicLightingType_TwoColors_PlayOnce,							// Light always face the center of the object eing lit			
	eDynamicLightingType_TwoColors_Loop,
	eDynamicLightingType_Fire,				// fire, plays continuously
};
DATACLASS(DbDynamicLightEmitterDef)
	enum eDynamicLightingType					Type;
	enum eDynamicLightingAttenuation			TypeOfAttenuation;
	float										Life;					// Full light life (second) or how many time to loop
																		// for Fire lights, this is the length of the period to go from color 1 to color 2 and back
	float										LifeFadeOut;			// Fade out life (second)
																		// for Fire lights, this is the time taken to fade-in when first added
	float										LifeFadeOut2;			// Fade out life (second)
																		// for Fire lights, this is the time taken to fade-out when removed
	LSizedArray<float>							DirectionalColor;		// RGB [0,1] (directional and spot color)
	LSizedArray<float>							DirectionalColor2;		// RGB [0,1] (directional and spot color)
	float										Radius;					// light radius in world unit
ENDCLASS

//
// attach this visual as a child to make a model receive dynamic lighting
//
DATACLASS(DbDynamicLightingReceiverDef)
	float	m_Radius;
	int		m_MaxLightCount[kNumGraphicLightDetailLevels];	// max light count (per lighting detail level)
ENDCLASS

//
// attach this visual as a child to make a model receive hemisphere lighting
//
DATACLASS(DbHemisphereLightingReceiverDef)
	// lowest detail level at which to use hemisphere lighting
	enum eGraphicLightDetail m_LowestDetailLevel;
ENDCLASS

//
// attach this visual as a child to make a model receive specular lighting
//
DATACLASS(DbSpecularLightingReceiverDef)
	// lowest detail level at which to use specular lighting
	enum eGraphicLightDetail m_LowestDetailLevel;

	// specular material override color (if black, override is not applied)
	LRGBA m_MaterialSpecularColor;
ENDCLASS


//====================================================================
//Dust
//
DATACLASS(DustEffect)
	LSizedArray<char*>							DustTerrainNifName;
	char*										WaterDust;
	LSizedArray<char*>							DustRoadNifName;
	//For flying units
	float										MaxHeight;
	bool										AlwaysPlay;
	bool										KeepDustOnGround;
ENDCLASS

//====================================================================
// a geometry collapse effect , using the default object mesh
// add this to a composite if a destruction state effect is wanted
DATACLASS(CollapseEffect)
	LSizedArray <float>		Weight;
	LSizedArray <float>		Translation;
ENDCLASS

//====================================================================
// Glow
// Shows if good stuff or bad stuff are affecting the unit.  Not
// necessarily a "glow", but that's the working name.
DATACLASS(GlowEffect)
	bool			m_UseGeometry;

	const char*		m_GoodGlowName;		
	float			m_GoodGlowScale;		

	const char*		m_BadGlowName;		
	float			m_BadGlowScale;		

	const char*		m_MixedGlowName;		
	float			m_MixedGlowScale;
	
	const char*		m_NeutralGlowName;		
	float			m_NeutralGlowScale;
	
	const char*		m_KingGlowName;		
	float			m_KingGlowScale;
	
	const char*		m_HeroArmyGlowName;		
	float			m_HeroArmyGlowScale;
	
	const char*		m_HeroArmyLeaderGlowName;		
	float			m_HeroArmyLeaderGlowScale;

	const char*		m_SupremeLeaderGlowName;
	float			m_SupremeLeaderGlowScale;

	float			m_PulseMaxMult;
	float			m_PulseMinMult;

	int				m_PulseMaxAlpha;
	int				m_PulseMinAlpha;
ENDCLASS


//===================================================================
// @EE2X -- Daniel 03/15/05
// Glow3D -> VisualGlow3D
// a 3D glow (halo) effect
DATACLASS(Glow3D)

	// texture to use
	const char *m_TextureName;

	// num texture slices (1 is used if not specified)
	int			m_NumSlices;

	// texture slice geometry will be scaled to model radius and
	// height, adjusted by these multipliers
	float		m_RadiusFrac;
	float		m_HeightFrac;
	
	// min/max intenstiy mult for pulse (0.0 to 2.0)
	float		m_PulseMinIntensity;		
	float		m_PulseMaxIntensity;

	// min/max alpha for pulse (0.0 to 1.0)
	float		m_PulseMinAlpha;
	float		m_PulseMaxAlpha;

ENDCLASS


//===================================================================
//WORLD VISUAL
//Waves
DATACLASS(WorldVisual)
ENDCLASS


//===================================================================
// EMP EFFECT
//
ENUM eEmpAnimationType {
	kEmpAnimationType_Random,
	kEmpAnimationType_RandomSmooth,
	kEmpAnimationType,
};

DATACLASS(VisualEmpDC)
float					SparkLife;
float					TimeToDie;
float					FirstSparkLife;
float					EffectDelay;
float					LinkDelay;
float					GeometryWidth;
bool					CrossGeometry;
enum eEmpAnimationType	AnimationType;
bool					AnimationOn;
float					AnimationSpeed;
float					SmoothValue;
float					PercentChanceToSmooth;
bool					StopAnimationwhenDie;
float					PoleSegmentLenght;
int						PoleNbrMax;
float					PoleLenght;
char*					TextureName;
bool					DynamicUv;
ENDCLASS

DATACLASS(VisualLightningDC)
float					SparkLife;
float					TimeToDie;
float					FirstSparkLife;
float					EffectDelay;
float					LinkDelay;
float					GeometryWidth;
bool					CrossGeometry;
enum eEmpAnimationType	AnimationType;
bool					AnimationOn;
float					AnimationSpeed;
float					SmoothValue;
float					PercentChanceToSmooth;
bool					StopAnimationwhenDie;
float					PoleSegmentLenght;
int						PoleNbrMax;
float					PoleLenght;
char*					TextureName;
bool					DynamicUv;
//Branches
char*					TextureNameBranch;
float					NbrBranchesMin;
float					NbrBranchesMax;
float					PositionMinRadius;
float					PositionMaxRadius;
ENDCLASS

DATACLASS(VisualUnitElecSpark)
int						NbrSpark;
float					SparkMinLife;
float					SparkMaxLife;
float					TimeToDie;
float					SmoothValue;
float					PercentChanceToSmooth;
bool					StopAnimationwhenDie;
float					MinLifeBeforeSwitchingBone;
float					MaxLifeBeforeSwitchingBone;
float					GeometryWidth;
bool					CrossGeometry;
enum eEmpAnimationType	AnimationType;
bool					AnimationOn;
float					AnimationSpeed;
float					PoleSegmentLenght;
int						PoleNbrMax;
float					PoleLenght;
char*					TextureName;
bool					DynamicUv;
ENDCLASS


ENUM eAnimExploStartDistance {
	eAnimExploStartDistance_VTiny,
	eAnimExploStartDistance_Tiny,
	eAnimExploStartDistance_VSmall,
	eAnimExploStartDistance_Small,
	eAnimExploStartDistance_Medium,
	eAnimExploStartDistance_Large,
	eAnimExploStartDistance_VLarge,
	eAnimExploStartDistance_Huge,
	eAnimExploStartDistance_VHuge,
	kAnimExploStartDistanceType,
};

ENUM eAnimExploDepth {
	eAnimExploDepth_None,
	eAnimExploDepth_VTiny,
	eAnimExploDepth_Tiny,
	eAnimExploDepth_VSmall,
	eAnimExploDepth_Small,
	eAnimExploDepth_Medium,
	eAnimExploDepth_Large,
	eAnimExploDepth_VLarge,
	eAnimExploDepth_Huge,
	eAnimExploDepth_VHuge,
	eAnimExploDepthType,
};

ENUM eAnimExploSlowDown {
	eAnimExploSlowDown_None,
	eAnimExploSlowDown_Slow,
	eAnimExploSlowDown_Medium,
	eAnimExploSlowDown_Fast,
	kAnimExploSlowDownType,
};


//-------------------------------------------------
// Individual particle parameters
//												
DATACLASS(AnimatedExplosionParticle)
bool					PixelShader1_4_and_more;	//render this polygon only if pixel shader 1.4 or more
													// is supported
//Effect duration condition
float					BornAtTime;					// Delay before creating this particle
float					Life;						// How long the partile will live (in second).

//Velocity
float					VelocityAngle;				//[0 - 180]. 0 = 1 Zaxis, 180 = -1 Zaxis.  Ex.; 0 = Right up.
float					Speed;						// How fast the particle travel along the velovity axis 
float					SpeedMin;					

//Size
float					OriginalSize;				//Size of the particle at creation time
float					EndSize;					// How big the particle should be when the life reach "TimeToGrow" parameter
float					TimeToGrow;					// How long it takes (second) before the particle reach "EndSize" size
enum eAnimExploStartDistance	startingDistance;	//[VTiny, Tiny, VSmall, Small, Medium, Large, VLarge, Huge, VHuge]
													// How far this particle will be spawn from the explosion center.
bool					UseDefinedTranslate;		//This will overwrite the startingDistance
float					TranslateX;
float					TranslateY;
float					TranslateZ;
//Color
LSizedArray<float>		Color1;						//4 set of color to modify the particle color over its life.  The RGB will be
LSizedArray<float>		Color2;						// added to the texture color.  The Alpha will be multiply with texture alpha.
float					TimeToColor2;
LSizedArray<float>		Color3;
float					TimeToColor3;
LSizedArray<float>		Color4;
float					TimeToColor4;
ENDCLASS

//------------------------------------------------
// General explosion parameters
//
DATACLASS(AnimatedExplosionDC)
//Drawing options
char*					ShaderName;					//Shader name to use with this explosion: 
													// AnimatedExplosion_Add_Add = Additive blending
													// AnimatedExplosion_Add_Molulate = normal blending
enum eAnimExploDepth	ShaderDepth;				//Value that determine how deap it the explosion (thikness 
													// from pixel shade)
char*					TextureName;				//Name of the targa
bool					TextureRandomUv;			//[false, true]
													// false = create particle with the first sub-bitmap (uv = 0,0)
bool					FlipUvOff;
													// true = create particle with a random sub-bitmap (uv = random)
int						WidthNbrBitmapInTexture;	// Number of sub-bitmap in a row.  The row number must equal the number of column.
int						HeightNbrBitmapInTexture;
bool					ClampTexture;				// Always true
int						DrawingLayer;				//[0 - 11].  0 Will be draw before 1, 1 will be draw before 2......
float					TimeToPlayAllAnimation;		//How long it takes to play all sub-bitmap in second.
bool					StaticBitmap;				//[false, true]
													// false = no sub-bitmap animation, Uvs use the whole bitmap (0,0 - 1,1).
													// true = play all sub-bitmap in "TimeToPlayAllAnimation" seconds.
enum eAnimExploSlowDown	SlowDownAnimation;			// The choice are: [None, Slow, Medium, Fast]
													//Slow down the sub-bitmap animation along the particle life.  Ex.; TimeToPlayAllAnimation get
													// higher over the particle life.
//RandomSeed
float					RandomSeed;					//Number that will change random number use in the code.  That will affect velocity, life,
													// and particle location.  The user could set-up two animated explosion with the same number to
													// make sure that these two animation play their particle at the same location and with the 
													// same velocity.
//Wind
bool					WindOn;						//[false, true] : wind affecting the particle physics or not.
float					WindPercentInUse;			//[0, 1].  Only use if the wind affect the particle physics (WindOn). This parameter 
													// is a percentage of how much wind will be taking into consideratrion (0 = 0%, 0.25 = 25%, 
													// 1 = 100%)
float					DeltaZ;						//This value will be added to the unit z location.  This is usefull
													// for having a ground explosion not clipping on the ground
//Condition to start effect
char*					MessageToStartEffect;		//Not use yet
//Array of particles
LSizedArray<DC(AnimatedExplosionParticle)*>	Particle;
ENDCLASS

//===================================================================
// SmokeTrail
//
DATACLASS(SmokeTrailDC)
//Shader
char*					ShaderName;
//Tag
char*					TagName;
//Texture
char*					TextureSet1;
char*					TextureSet2;
int						TexturesNbrOfSubPart;
bool					ExpandTexture;					//Loose detail over time but give a feeeling of expension
//Effect manager
bool					LiveFrombornToDeath;
float					EffectMinLife;
float					EffectMaxLife;
//Particle parameter
float					MinLife;
float					MaxLife;
//Geometry
int						MaximumParticle;
LRGBA					ColorStart;						//Array of 4 float
LRGBA					ColorMiddle;					//Array of 4 float
LRGBA					ColorEnd;						//Array of 4 float
float					MiddleColorFor;
float					OriginalSizeMin;
float					OriginalSizeMax;
float					SizeGrowMin;
float					SizeGrowMax;
float					GrowFor;
float					PositionRadiusRandom;
float					ParticleDensity;
//Physics
bool					WindOn;
float					WindPercentInUse;
float					VelocityRandom;
bool					BounceOnTerrain;
//Blending mode
bool					AdditiveBlending;
bool					DrawUnderWater;
int						DrawingLayer;
ENDCLASS


//Smoke trail exposion
DATACLASS(ExplosionSmokeTrailDC)
//File containing object to draw
char*					NifName;

//Message to start the effect.  By default: "StartSmokeTrailExplosion"
char*					MessageToStartEffect;

//Drawing options
char*					ShaderName;
char*					Texture1;
char*					Texture2;
bool					AdditiveBlending;
bool					DrawUnderWater;
int						DrawingLayer;					//[0 - 2]

//Node options
bool					NodePhysicsOn;					//If off, do not apply any physics on the nodes
bool					NodeGravityOn;
bool					NodeBounceOnTerrain;			//check for terrain collosion
bool					NodeStopOnGroundCollision;
bool					NodeWindOn;
float					NodeMinLife;
float					NodeMaxLife;
float					NodeMinSpeed;
float					NodeMaxSpeed;
float					NodeVelocityRotation;			//0 degree, straight up, 90 degree = left or right
bool					NodeStopSpeed;
float					NodeSlowDown;					//percent at wich the node stop moving. 1 = 1 second, 2 = 0.5 second
LSizedArray<float>		NodeColorStart;					//Array of 4 floats.  This will be multiply with the particle color
LSizedArray<float>		NodeColorEnd;
float					NodeProbabilityToPlay;
bool					NodeRandomizerotation;

//Particle options
bool					PhysicsOn;
bool					GravityOn;
bool					WindOn;
float					WindPercentInUse;
int						MaximumParticle;				//DirectX buffer size
float					MinLife;
float					MaxLife;
float					MinSpeed;
float					MaxSpeed;
bool					StopSpeed;
LSizedArray<float>		ColorStart;
LSizedArray<float>		ColorMiddle;
LSizedArray<float>		ColorEnd;
float					MiddleColorFor;
bool					BounceOnTerrain;
float					OriginalSizeMin;
float					OriginalSizeMax;
float					SizeGrowMin;
float					SizeGrowMax;
float					GrowFor;
float					PositionRadiusRandom;
float					ParticleDensity;
ENDCLASS

//===================================================================
// Particles animated
//
DATACLASS(AnimatedParticleDC)

//Drawing options
char*					ShaderName;
enum eAnimExploDepth	ShaderDepth;				//Value that determine how deap it the explosion (thikness 
													// from pixel shade)
char*					TextureName;
int						WidthNbrBitmapInTexture;	//Need to be a square texture, EX. 4bitmaps X 4bitmpas
int						HeightNbrBitmapInTexture;
int						DrawingLayer;				//[0 - 11]
float					PlayAllBitmapsSecond;

//Condition to start effect
char*					MessageToStartEffect;
bool					StartEffectAtCreation;

//Effect duration condition
bool					LiveForEver;
float					EffectLifeMin;
float					EffectLifeMax;
float					NbrParticleToSpawnSecond;

//Node parameters
bool					NodeAnimated;				//Smotly move the nodes inside of defined radius
bool					NodeAnimatedMinRadius;		//Distance maximum at which the tag can be animated
bool					NodeAnimatedMaxRadius;
float					NodeSpeedMin;				//Distance in a second at wich the node should be animated
float					NodeSpeedMax;
char*					NodeName;					//Name without the number at the end
													//			Ex. Virtual name = Tag_Name
													//				Physical name: Tag_Name_01, Tag_Name_02...
//Particles parameters
bool					GravityOn;
float					VelocityAngle;				//[0 - 180]. 0 = 1 Zaxis, 180 = -1 Zaxis
float					RadiusMinX;
float					RadiusMaxX;
float					RadiusMinY;
float					RadiusMaxY;
float					RadiusMinZ;
float					RadiusMaxZ;
bool					WindOn;
float					WindPercentInUse;
int						MaximumParticle;			//DirectX buffer size
float					MinLife;
float					MaxLife;
float					MinSpeed;
float					MaxSpeed;
LSizedArray<float>		ColorStart;
LSizedArray<float>		ColorMiddle;
LSizedArray<float>		ColorEnd;
float					MiddleColorFor;
float					OriginalSizeMin;
float					OriginalSizeMax;
float					SizeGrowMin;
float					SizeGrowMax;
float					GrowFor;
bool					ZOrderingOn;
ENDCLASS


//===================================================================
// Vaporizer
//
DATACLASS(VaporizerDef)
	LRGBA m_SpecularTargetColor;
	float m_ShininessTarget;
	float m_SpecularFadeTime;
	enum eFadeType m_SpecularFadeType;

	float m_PeakTime;

	float m_AlphaFadeTime;
	enum eFadeType m_AlphaFadeType;
	float m_FadeTargetAlpha;
	LRGBA m_FadeTargetColor;

ENDCLASS

//===================================================================
// Camera shake
//
DATACLASS(CameraShakeDef)
	// When started from an explosion, the camera shake will "expand" from the
	// point of the explosion to a maximum distance.  When the outside edge reaches
	// a camera, it will shake the camera.  The outside edge expands according
	// to expandType.
	float m_ExpandTime;
	float m_ExpandDistance;
	enum eFadeType m_ExpandType;

	// The affect of the shake is attenuated by the distance from the point of
	// impact.  The far multiplier is the multiplier at the far edge of the camera
	// shake volume.  The multiplier at the center of the volume is 1.  The multiplier
	// type allows for different interpolation when determining how the multiplier
	// changes as the volume expands.
	float m_FarMultiplier;
	enum eFadeType m_MultiplierType;

	// How long with the camera shake?
	float m_Duration;

	// What's the starting amplitude for shaking the camera in X,Y,Z.  These will
	// all ramp down to zero over the duration.
	float m_StartAmplitudeX;
	float m_StartAmplitudeY;
	float m_StartAmplitudeZ;

	// How the amplitudes ramp to zero.
	enum eFadeType m_XFadeType;
	enum eFadeType m_YFadeType;
	enum eFadeType m_ZFadeType;
ENDCLASS

//Force field
DATACLASS(VisualForceFieldDC)
	//Shield born
	float			m_fadeInSecond;
	bool			m_fadeInScale;
	bool			m_fadeInTransparency;
	//Shield death
	float			m_fadeOutSecond;
	bool			m_fadeOutScale;
	bool			m_fadeOutTransparency;
	//Geometry
	//Geometry
	char*			m_shieldNameVHigh;
	char*			m_shieldNameHigh;
	char*			m_shieldNameMedium;
	char*			m_shieldNameLow;	
	char*			m_impactNameVHigh;
	char*			m_impactNameHigh;
	char*			m_impactNameMedium;
	char*			m_impactNameLow;
	float			m_shieldRadius;
	//Message
	char*			m_msgStartEffect;
	char*			m_msgStopEffect;
	char*			m_msgImpact;
ENDCLASS


// VisualShimmer
DATACLASS(VisualShimmerDC)
	// how opaque does unit appear when shimmer is disabled
	float m_disabledOpacity;
	// how opaque does unit appear to friendly eyes (when in disguise)
	float m_friendlyOpacity;
	// how opaque does unit appear to enemy eyes (when in disguise)
	float m_enemyOpacity;
	// what is the  opacity pulse amplitude?
	float m_opacityPulseAmplitude;
	// what is the  opacity pulse wavelength?
	float m_opacityPulseWavelength;
	
	// how fast does  opacity blend?
	float m_opacityBlendRate;
	// how fast does  pulse amplitude blend?
	float m_amplitudeBlendRate;
	//  emissive color is driven by opacity for friendly eyes
	float m_friendlyEmissiveFactor;
	
	// if true, alters the behavior of the visual's update function
	bool m_lostCityMode;
ENDCLASS


// For creating a singleton thick line definition.
DATACLASS(ThickLine)
ENDCLASS

// Define a visual for some 3D text.
DATACLASS(Text3DDef)
	char* m_WidgetDef;			// The name of the widget definition to use for this text
	bool m_UseParentForOffset;	// Whether or not to use the parent's model's volume for the offset.
	float m_ZOffset;			// The vertical offset to shift the text if not using the parents.
ENDCLASS

// @EE2X - Josh - 03/10/05
// Visual for thrown units
DATACLASS(ThrownUnit)
	float	SpeedMin;
	float	SpeedMax;
	float	Mass;
	float	RotationSpeedXMin;
	float	RotationSpeedXMax;
	float	RotationSpeedZMin;
	float	RotationSpeedZMax;
	float	InitialVelocityZMin;
	float	InitialVelocityZMax;
	float	SinkDelay;			// amount of time between unit hitting the ground and unit starting to sink
	float	TimeBeforeVanish;	// amount of time after hitting the ground before unit vanishes
ENDCLASS

#endif  // _VISUALDBDEFINITION_H__