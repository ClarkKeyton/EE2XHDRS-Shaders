      //===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbGraphicSettingsDefs.h 25    8/15/05 1:58p Dsproul $
//
// DESCRIPTION:   DbGraphicSettingsDefs defines the format of the graphic settings
//				  database records.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBGRAPHICSETTINGSDEFS_H
#define DBGRAPHICSETTINGSDEFS_H
#pragma once

#include "hdrmacros.h"
#include "GDbDisplayDefs.h"

// keep this order for this enum,
// I say again KEEP 
ENUM eGraphicModelDetail {
	kGraphicModelDetail_Low,		// low-detail models
	kGraphicModelDetail_Medium,		// medium-detail models
	kGraphicModelDetail_High,		// high-detail models
};

ENUM eGraphicAnimDetail {
	kGraphicAnimDetail_Low,
	kGraphicAnimDetail_Medium,
	kGraphicAnimDetail_High,
};

ENUM eGraphicTextureDetail {
	kGraphicTextureDetail_Low,		// low detail textures
	kGraphicTextureDetail_Medium,	// medium detail textures
	kGraphicTextureDetail_High,		// high detail textures
};

ENUM eGraphicEffectDetail {
	kGraphicEffectDetail_Low,
	kGraphicEffectDetail_Medium,
	kGraphicEffectDetail_High,
	kGraphicEffectDetail_VHigh,
};

ENUM eGraphicWeatherDetail {
	kGraphicWeatherDetail_Low,
	kGraphicWeatherDetail_Medium,
	kGraphicWeatherDetail_High,
	kGraphicWeatherDetail_VHigh,
};

ENUM eGraphicWaterDetail {
	kGraphicWaterDetail_Low,
	kGraphicWaterDetail_Medium,
	kGraphicWaterDetail_High,
};

ENUM eGraphicTerrainDetail {
	kGraphicTerrainDetail_Low,
	kGraphicTerrainDetail_Medium,
	kGraphicTerrainDetail_High,
};

ENUM eGraphicShadowDetail {
	kGraphicShadowDetail_Off,		// shadows off
	kGraphicShadowDetail_Low,		// low-quality
	kGraphicShadowDetail_Medium,    // medium-quality
	kGraphicShadowDetail_High,		// high-quality
	kGraphicShadowDetail_VeryHigh,
	kGraphicShadowDetail_Extreme,
};


// @EE2X lighting detail
ENUM eGraphicLightDetail {
	kGraphicLightDetail_Low,
	kGraphicLightDetail_Medium,
	kGraphicLightDetail_High,
	kNumGraphicLightDetailLevels,
};

ENUM eGraphicDefaultSet{
	kGraphicDefaultSet_Default,	// system default
	kGraphicDefaultSet_Fastest,	// fastest
	kGraphicDefaultSet_Quality,	// highest quality
	kGraphicDefaultSet_Custom,	// custom settings
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*
// shadow light detail
ENUM eGraphicShLtDetail {
	kGraphicShLtDetail_Low,		// low quality
	kGraphicShLtDetail_Medium,	// medium quality
	kGraphicShLtDetail_High,		// high quality
	kGraphicShLtDetail_Custom,	// custom quality level
};

// this enum is used in the main video settings screen
ENUM eGraphicAdvFxDetail {
	kGraphicEffectDetail_Low,		// low-detail effects
	kGraphicEffectDetail_Medium,	// medium-detail effects
	kGraphicEffectDetail_High,		// high-detail effects
	kGraphicEffectDetail_Extreme,	// extremely high-detail effects
	kGraphicEffectDetail_Custom,	// custom detail effects level
};
*/

// This one can be used for any setting which is off, main view only, or main view & PIP
ENUM eGraphicViewSelection {
	kGraphicViewSelection_Off,				// off entirely
	kGraphicViewSelection_MainView,			// only on in main view
	kGraphicViewSelection_MainViewAndPIP,	// on in main view and PIP
};


//	IMPORTANT NOTE:  THE USE OF THIS DATACLASS IN GRAPHICSETTINGS.H PRECLUDES
//	YOU FROM PUTTING ANY POINTERS OR SUCH THINGS INTO IT.  LIMIT THIS TO
//	BOOLS, INTEGERS, FLOATS, ENUMS, AND EMBEDDED ARRAYS OF THESE PRIMITIVES.
//	NO STRINGS, EMBEDDED DATACLASS OBJECTS, OR SIZED ARRAYS.  IF THIS RESTRICTION
//	IS TOO LIMITING, THE AUDIOSETTINGS OBJECT MUST BE MODIFIED TO USE A POINTER
//	TO AN OBJECT OF THIS DATACLASS INSTEAD OF AN ACTUAL INSTANCE OF ONE, AND
//	MUST USE LDATACLASS METHODS TO MANAGE THE PTRS PROPERLY.

DATACLASS(DbGraphicSettingsDef)
	enum eGraphicViewSelection		m_waterReflection;	// water reflection enum
//	enum eGraphicShLtDetail			m_shadLightDetail;	// shadow and light detail enum
//	enum eGraphicAdvFxDetail		m_advEffectDetail;	// effects detail enum used in advanced video settings 

	enum eDisplayMode				m_displayMode;		// screen resolution/colordepth
	enum eGraphicModelDetail		m_modelDetail;		// model detail enum
	enum eGraphicAnimDetail			m_animationDetail;	// animation detail enum
	enum eGraphicTextureDetail		m_textureDetail;	// texture detail enum
	enum eGraphicEffectDetail		m_effectDetail;		// effects detail enum
	enum eGraphicWeatherDetail		m_weatherDetail;	// weather detail enum
	enum eGraphicWaterDetail		m_waterDetail;		// water detail enum
	enum eGraphicTerrainDetail		m_terrainDetail;	// terrain detail enum
	enum eGraphicShadowDetail		m_shadowDetail;		// shadow detail enum

	// @EE2X - lighting detail
	enum eGraphicLightDetail		m_lightDetail;

	bool m_pip;								// pip off/on
	bool m_waterShoreWaves;					// shore waves off/on
	bool m_waterRaindrops;					// raindrops on water off/on
	bool m_waterSmoothShore;				// smooth shore off/on
	bool m_weather;							// weather off/on
	bool m_battlefieldAmbients;				// battlefield ambients off/on
	bool m_blood;							// blood off/on
	bool m_streaks;							// streaks off/on
	bool m_particles;						// particles off/on
	bool m_fxVisibleInPip;					// effects visible in pip off/on
ENDCLASS

#endif // DBGRAPHICSETTINGSDEFS_H
