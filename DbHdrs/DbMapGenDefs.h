//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbMapGenDefs.h 11    10/04/05 12:53p Dsproul $
//
// DESCRIPTION:   
//
// AUTHOR:        Kevin Wasserman
//
//===========================================================================

#ifndef DBMAPGENDEFS_H
#define DBMAPGENDEFS_H
#pragma once

#include "hdrmacros.h"

// is the map border arbitrary, always land, or always water?
ENUM eMapBorder {
	kMapBorder_Land,
	kMapBorder_Water,
	kMapBorder_Any,
};

// these are the main classes of maps - used by the AI
//		to determine what to do on this world
ENUM eMapType {
	// everyone on their own landmass
	kMapType_Islands,
	// could share a landmass with someone else, but need boats to get to others
	kMapType_Continents,
	// water around the edge or in the middle
	kMapType_OneLandMass,
	// no water at all
	kMapType_Waterless,

	kNumMapTypes,

};

DATACLASS(DbBitmaskStamp)
	float m_xLoc;			// x position as a fraction of total map width (center = 0.5)
	float m_yLoc;			// y position as a fraction of total map height (center = 0.5)
	float m_radiusFraction;	// radius of the stamp as a fraction of the map size
	float m_minRadius;		// minimum stamp radius regarless of map size
ENDCLASS

DATACLASS(DbMapGeographyInfo)

	///////////////////////////////////////
	// data only used for continents
	// sorry there are so many, this was kind
	// of hacked together at the last moment

	// if 0 or not specified, 1 is used
	// these modifies the min/max radius for our continents
	float m_continentMinRadiusMult;
	float m_continentMaxRadiusMult;

	//float m_continentCenterForcedWaterRadiusMult;
	float m_continentSpecialLocForcedWaterRadiusMult;

	float m_continentStartLocRadiusMult;

	// fraction of map radius used for placing continent centers
	float m_continentSpacingRadiusMult;

	// continent spacing
	float m_continentSpacingArcRandomness;
	float m_continentSpacingRadialRandomness;

	// starting location spacing within a continent
	float m_continentStartLocArcRandomness;
	float m_continentStartLocRadialRandomness;

	// randomness for ratio of semimajor and semiminor axis for a single continent
	float m_continentMaxEccentricity;


	float m_maxWaterDist;	// maximum effective distance from 'forced' water for purposes of water/land determination
							// if less than zero; there is no maximum
	float m_maxLandDist;	// maximum effective distance from 'forced' land
	float m_startLocLandRadius;		// min radius around start locations that must be land 
	float m_landScaleFrac;	// land/water correlation length as fraction of map size
	float m_minLandScale;   // min land/water correlation length
	float m_startLocFlattenRadius;
	float m_landMassMaxRadius; // for islands or continents maps, distance from a land mass seed beyond which must be water
	enum eMapBorder m_border;
	int m_borderWidth;          // width of border area
	enum eMapType m_mapType;	// what kind of map is this?
	LSizedArray<DC(DbBitmaskStamp) *> m_forcedLand;
	LSizedArray<DC(DbBitmaskStamp) *> m_forcedWater;
ENDCLASS


// stupid DC for specifying random geography sets
DATACLASS(DbRandomMapGeographyInfo)

	// displayable name
	DBINDEX(DbText) m_name;	

	// allowable geographies to include
	// should either be "Any" or a valid entry in the MapGeography DB
	LSizedArray<const char *> m_AllowedGeographies;

	// same thing, mapped into DBI's on postload
	USER LDynArray<int> m_aiAllowedGeographies;

ENDCLASS


DATACLASS(DbMapSizeInfo)
	DBINDEX(DbText) m_name;		// displayable map-size name
	int m_width;
	int m_height;
	int m_maxPlayers;				// maximum # players allowable on this map size
	int m_maxPlayersWithTribes;		// max # players+tribes allowable on this map size

	// min/max num continents (2-4)
	// only used if map geo type is continents and num continents is set to random
	int m_minContinents;
	int m_maxContinents;
ENDCLASS


#endif // DBMAPGENDEFS_H
