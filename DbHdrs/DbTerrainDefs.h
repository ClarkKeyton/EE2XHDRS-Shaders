// Copyright 2002 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbTerrainDefs.h 24    11/29/04 2:18p Kwasserman $
// $Modtime: 11/29/04 11:02a $
//
//	The DbTerrainDefs DATACLASS tells you the layout of terrain .csv
//	spreadsheets.

#ifndef DBTERRAINDEFS_H
#define DBTERRAINDEFS_H

#include "hdrmacros.h"
#include "LRgba.h"

//	Terrain types live here

// the basic move type each terrain type can be classified into
// WARNING: if you modify this, you must also update eMovementSpeedType
ENUM eTerrainMoveType {
	kTerrainMoveType_Land,			// normal (grass) land
	kTerrainMoveType_Swamp,			// swamp or marsh
	kTerrainMoveType_Cliff,			// cliff (impassable -- use for cliff faces)
	kTerrainMoveType_Mountain,		// mountain (impassable)
	kTerrainMoveType_Forest,		// forested
	kTerrainMoveType_Coast,			// coast/beach
	kTerrainMoveType_River,			// river (shallow water)
	kTerrainMoveType_Ocean,			// ocean (deep water)
	kNumTerrainMoveType,
};
// WARNING: if you modify this, you must also update eMovementSpeedType

// WARNING: eMovementSpeedType must be kept in sync with eTerrainMoveType
ENUM eMovementSpeedType {
	// the first part of the following is must match eTerrainMoveType
	kMovementSpeedType_Land,		// normal (grass) land
	kMovementSpeedType_Swamp,		// swamp or marsh
	kMovementSpeedType_Cliff,		// cliff (impassable -- use for cliff faces)
	kMovementSpeedType_Mountain,	// mountain (impassable)
	kMovementSpeedType_Forest,		// forested
	kMovementSpeedType_Coast,		// coast/beach
	kMovementSpeedType_River,		// river (shallow water)
	kMovementSpeedType_Ocean,		// ocean (deep water)

	// second part of this enum are special
	kMovementSpeedType_Bridge,		// this should be equal to last valid eTerrainMoveType + 1
	kMovementSpeedType_Road,

	kNumMovementSpeedType,
};
// WARNING: eMovementSpeedType must be kept in sync with eTerrainMoveType

ENUM eTerrainSeasons {
    kNumTerrSeasons = 12,
};

// Type of dust to be associated to a terrain texture, road or water
ENUM eTerrainDustType {
	kTerrainDustType_Snow,
	kTerrainDustType_Sand,
	kTerrainDustType_Dirt,
	kTerrainDustType_Mud,
	kTerrainDustType_None,			//This one must always be last
	kNumTerrainDustType,
};

//this enumeration is not part of the terrain data base but is is close enough to have it here.
ENUM eRoadDustType {
	kRoadDustType_Sand,
	kRoadDustType_Pavement,		
	kRoadDustType_None,				//This one must always be last
	kNumRoadDustType,
};


typedef int TerrType;	//TerrainType

// this class represents one row of the seasonal texture database
// it contains an order dependent texture list to be interpolated
// the more texture the finer the interpolation
// the number of textures in the list are interpolated evenly over the years
// Ex.: 12 textures would be interpolated evenly spread out over the year as one per month
DATACLASS(DbTextureSetinfo)
	LSizedArray<char*>	    SeasonTextures;
ENDCLASS

// Rendering info for a terrain type, including seasonal texture, alpha mask, and tinting information
DATACLASS(DbTerrainTextureDef)
    // index into seasonal textures database
	DBINDEX(DbSeasonalTextureSets_) m_seasonalTexture;
	// name of alpha mask texture
	const char*                     m_maskTextureName;						
	// tint fraction: 1.0 = apply terrain tint; 0.0 = ignore terrain tint
	float					        m_tintFrac[ENUMVAL(eTerrainSeasons,kNumTerrSeasons)];	
ENDCLASS

//	DbTerrainDbInfo is the class which maps onto the .csv file in which terrain
//	sets are located.  The parser reads this structure and so knows how to interpret
//	the .csv information.  Note that the entries must be ordered by TerrType.
DATACLASS(DbTerrainDbInfo)
	DBINDEX(DbTerrainTexture_) m_HighDetailTexture; // index of texture in the terrain texture DB
	DBINDEX(DbTerrainTexture_) m_MediumDetailTexture;
	DBINDEX(DbTerrainTexture_) m_LowDetailTexture;
	enum eTerrainDustType	m_dustType[ENUMVAL(eTerrainSeasons,kNumTerrSeasons)];	// Type of dust to use for a given
													// texture for each month of the year
	char*					m_mapFileName;			//Bitmap file name of each type of terrain 
													//	(to create the mini map and full map).
	float					m_minElev;				//Minimum elevation for autopainter
	float					m_maxElev;				//Maximum elevation for autopainter
	enum eTerrainMoveType	m_terrMoveType;			//Basic move type
	int						m_grassLayer;			//Uuse by the grass manager
ENDCLASS

// These are the valid enumeration levels for water level for the random map generator
ENUM eWaterLevel {
	kWaterLevel_None,		// no water
	kWaterLevel_Low,		// little water
	kWaterLevel_Medium,		// half water
	kWaterLevel_High,		// mostly water
	kNumWaterLevels,
};


#endif
