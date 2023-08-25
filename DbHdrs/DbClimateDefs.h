//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbClimateDefs.h 18    5/24/05 8:59a Dsproul $
//
// DESCRIPTION:   
//
// AUTHOR:        Kevin Wasserman
//
//===========================================================================

#ifndef DBCLIMATEDEFS_H
#define DBCLIMATEDEFS_H
#pragma once

#include "hdrmacros.h"
#include "LRGBA.h"

class DbSeasonalTextureSets;
class DbTerrain;
class DbTerrainTexture;
class LRand;

// Enumeration of the different weather states.  Normal is the default.
ENUM eWeatherState {
	kWeatherState_None = -1,
	kWeatherState_Normal,
	kWeatherState_RainLt,
	kWeatherState_SnowLt,
	kWeatherState_DustLt,
	kWeatherState_RainHv,
	kWeatherState_SnowHv,
	kWeatherState_DustHv, 
	kNumWeatherStates,
	// The first heavy weather value.  This is for quickly determining if a
	// particular state is heavy of light.
	kWeatherState_FirstHv = kWeatherState_RainHv,
};

DATACLASS(DbTerrainTypeWeightPair)
	DBINDEX(DbTerrain_) m_terrainType;
	int					m_weight;
ENDCLASS


DATACLASS(DbTerrainBrush)
	LSizedArray<DC(DbTerrainTypeWeightPair) *> m_terrainTypes;
	USER int m_normalizer;
ENDVARS
	// compute the normalizer
	//Defined in DbClimate.cpp.
	USER void PostLoad();

	//Get a random terrain type, picked by weight from this brush, 
	//using in_rand as the PRNG.  
	//Defined in DbClimate.cpp.
	USER int GetRandomTerrainType(LRand &in_rand) const;
ENDCLASS

// Used by random maps to generate terrain based on the distance to
// a particular feature (river, ocean, forest, etc.)
DATACLASS(DbTerrainDistanceBrush)
	LSizedArray<DC(DbTerrainBrush) *> m_brushes;
ENDVARS
    USER int GetRandomTerrainType(LRand &in_rand, float distance) const;
	USER float GetMaxDist() const;
	USER void PostLoad();
ENDCLASS


DATACLASS(DbTerrainBrushes)
	DC(DbTerrainBrush) *m_grassBrush;
	DC(DbTerrainDistanceBrush) *m_forestBrush;
	DC(DbTerrainDistanceBrush) *m_mountainBrush;
	DC(DbTerrainDistanceBrush) *m_oceanBrush;
	DC(DbTerrainDistanceBrush) *m_riverBrush;
ENDVARS
	//Initialize the USER variables of our sub-classes
	//Defined in DbClimate.cpp.
	USER void PostLoad();
ENDCLASS	

// Data class for defining when different weather can occur during the year.
DATACLASS (DbClimateWeatherInfo)
	int		m_RainySeasonStart;
	int		m_RainySeasonStop;

	int		m_SnowySeasonStart;
	int		m_SnowySeasonStop;
	float				m_SnowRequiredLeadTime;
	int		m_SnowRequiredMonths;

	int		m_DustySeasonStart;
	int		m_DustySeasonStop;
	
	int		m_LeafySeasonStart;
	int		m_LeafySeasonStop;

ENDCLASS

DATACLASS (DbClimateAtmosphericInfo)
	LRGBA m_SunColor;
	LRGBA m_AmbientColor;
	LRGBA m_SpecularColor;
	LRGBA m_SkyColor;			// @EE2X -- sky color (used for hemisphere lighting)
	LRGBA m_TerrainIntensity;	// @EE2X -- terrain intensity (used for hemisphere lighting)
	LRGBA m_FogColor;
	float m_FogStart;
	bool m_FogOn;
	float m_FogIntensity;
ENDCLASS

DATACLASS (DbClimateSkyboxInfo)
	const char* m_TextureRight;
	const char* m_TextureLeft;
	const char* m_TextureFront;
	const char* m_TextureBack;
	const char* m_TextureTop;

	const char* m_NifName;
ENDCLASS

// Data class for defining the settings for a Time of Day
DATACLASS (DbClimateToDInfo)
	LSizedArray<float> m_SunDirectionVec3f;
	DBINDEX(DbClimate) m_SkyBoxSettingsNormal;
	DBINDEX(DbClimate) m_SkyBoxSettingsStormy;
	DBINDEX(DbClimate) m_AtmosphericSettingsNormal;
	DBINDEX(DbClimate) m_AtmosphericSettingsRainLight;
	DBINDEX(DbClimate) m_AtmosphericSettingsRainHeavy;
	DBINDEX(DbClimate) m_AtmosphericSettingsSnowLight;
	DBINDEX(DbClimate) m_AtmosphericSettingsSnowHeavy;
	DBINDEX(DbClimate) m_AtmosphericSettingsDustLight;
	DBINDEX(DbClimate) m_AtmosphericSettingsDustHeavy;
ENDCLASS

DATACLASS (DbAnimalGroupInfo)
	int m_minGroupSize;
	int m_maxGroupSize;
	DBINDEX(DbUnit) m_unitType;
ENDCLASS


DATACLASS(DbClimateInfo)
	char *m_pTerrainDbName;					        // name of the terrain db
	char *m_pSeasonalTexturesDbName;		        // name of the seasonal texture set db
	char *m_pTerrainTextureDbName;                  // name of the terrain texture db
	DC(DbTerrainBrushes) *m_terrainBrushes;

	DBINDEX(DbClimate) m_WeatherInfo;				// What are the weather settings for this climate.
	DBINDEX(DbClimate) m_ToDSettingsMorning;		// Settings for the different times of day.
	DBINDEX(DbClimate) m_ToDSettingsAfternoon;		// Settings for the different times of day.
	DBINDEX(DbClimate) m_ToDSettingsEvening;		// Settings for the different times of day.
	DBINDEX(DbClimate) m_ToDSettingsNight;			// Settings for the different times of day.

	DBINDEX(DbAmbientAudio) m_ambientAudio;			// db entry to use to control ambient audio

	// Native animal info:
	LSizedArray<DC(DbAnimalGroupInfo)*> m_domesticatedAnimals;
	LSizedArray<DC(DbAnimalGroupInfo)*> m_wildAnimals;
	LSizedArray<DC(DbAnimalGroupInfo)*> m_predators;
	LSizedArray<DBINDEX(DbUnit)> m_birds;			// @NOTE: birds don't come in groups
	
	// Food type info:
	LSizedArray<DBINDEX(DbUnit)> m_farms;
	LSizedArray<DBINDEX(DbUnit)> m_forageTrees;

	// Seasonal variant suffixes
	char* m_winterSuffix;
	char* m_springSuffix;
	char* m_summerSuffix;
	char* m_fallSuffix;

	bool m_bSnow;									// does it snow?
	// Actual database pointers. Fixed up on post-load
	USERPTR(DbTerrain)             m_pDbTerrain;
	USERPTR(DbSeasonalTextureSets) m_pDbSeasonalTextures;
	USERPTR(DbTerrainTexture)      m_pDbTerrainTexture;
ENDVARS
	//Initialize the USER variables of our sub-classes
	//Defined in DbClimate.cpp.
	USER void PostLoad();
ENDCLASS

#endif // DBCLIMATEDEFS_H
