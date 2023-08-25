//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbScenarioDefs.h 15    10/14/05 6:13p Dsproul $
//
// DESCRIPTION:   Dataclasses used by the scenario .ddf files.
//
// AUTHOR:        Ben Morse
//
//===========================================================================

#ifndef DBSCENARIODEFS_H
#define DBSCENARIODEFS_H
#pragma once

#include "HdrMacros.h"
#include "LDataObj.h"


// scenario objective types
// if you change this enumeration, please also update GetScenarioObjectiveTypeName()
ENUM eScenarioObjectiveType {
	kScenarioObjectiveType_Primary,
	kScenarioObjectiveType_Secondary,
	kScenarioObjectiveType_Lose,
	kNumScenarioObjectiveTypes,
};

// get programmatic (non-display) name for an objective type
const char *GetScenarioObjectiveTypeName(eScenarioObjectiveType in_eType);

// map programmatic objective name back into objective type
eScenarioObjectiveType GetScenarioObjectiveTypeByName(const char *in_szObjectiveName);


// x/y location for an objective flag
// @TODO probably should have a generalized Db-parsable Vec2f and Vec3f, don't you think?
DATACLASS(DbObjectiveLoc)
	float m_x;	// x location
	float m_y;	// y location
ENDCLASS

//
// dataclass describing a single scenario objective
//
DATACLASS(DbScenarioObjectiveDef)
	// general data
	DBINDEX(DbText)				m_name;			// display name
	DBINDEX(DbText)				m_description;	// description
	enum eScenarioObjectiveType	m_type;
	bool						m_startHidden;

	// optional arrays of targets
	LSizedArray<DC(DbObjectiveLoc) *>	m_targetLocations;
	LSizedArray<const char *>			m_targetUnits;
	LSizedArray<const char *>			m_targetAreas;
	LSizedArray<const char *>			m_targetTerritories;
ENDCLASS

//
// @EE2X - Josh - Reinforcements Screen
// dataclasses for Reinforcements
//
ENUM eReinforcementType {
		kReinforcementType_Unit,
		kReinforcementType_Resource,
		kReinforcementType_Tech,
		kNumReinforcementTypes,
};

DATACLASS(Reinforcement)
	enum eReinforcementType			m_type;			// what type of reinforcement is this?
	int								m_amount;		// number of units or amount of resource (unused for tech)			
	DBINDEX(DbUnit)					m_unitType;		// type of units to place (only used if type is unit)
	enum eResourceType				m_resType;		// type of resource to add (only used if type is resource)
	DBINDEX(DbTechTreeBaseNode)		m_tech;			// which tech to research (only used if type is tech)
ENDCLASS

DATACLASS(ReinforcementGroup)
	LSizedArray<DC(Reinforcement) *> m_members;
ENDCLASS

//
// dataclass describing an entire scenario
//
DATACLASS(DbScenarioInfo)
	DBINDEX(DbText)	m_name;			//the human-visible name of the scenario.
	const char *	m_mapfilename;	//the .scn file to load for this scenario
	DBINDEX(DbText)	m_briefing;		//briefing text.
	DBINDEX(DbText)	m_victory;		//victory text.
	DBINDEX(DbText)	m_loss;			//loss text.
	DBINDEX(DbText)	m_hints;		// hints text
	DBINDEX(DbText)	m_historicalInfo;// historical info text
	DBINDEX(DbText)	m_description;	// very general description of the scenario
	DBINDEX(DbText) m_date;	// date text representing when this scenario takes place
	DBINDEX(DbSprite)	m_sprite;	// sprite displayed on the campaign scenario selection screen
	DBINDEX(DbSprite) m_thumbnail;	// thumbnail image used in the timeline selection area
	LSizedArray<DBINDEX(DbScenarioObjectives)> m_objectives;	//The set of objectives to be completed for this scenario.
	const char *	m_overrideScriptLib;	// override the scenario's script library.  If unspecified, will default to whatever's in the .scn file.
	LSizedArray<int>	m_overrideHumanPlayers;	// override these players in the scenario and make them human.
	// @EE2X - Josh - added m_reinforcementGroups and m_numReinforcements
	LSizedArray<DC(ReinforcementGroup) *> m_reinforcementGroups;	// the groups of reinforcements the player may choose
																	// from at the start of the scenario
	int				m_numReinforcements;	// the number of reinforcement groups the player can select (this is in addition
											// to groups that players earn by completing secondary objectives)	
	// the location to place the reinforcements
	float			m_reinforcementLocX;
	float			m_reinforcementLocY;
	
	// should we suppress reinforcements description msg?
	// @NOTE at the moment, the message I have refers to the next mission, so we
	// would want to suppress it for the last mission of the campaign.  basically
	// I am making this unnescessarily data driven so we don't need to make up our
	// minds about wanting this until later
	bool			m_suppressReinforcementsDescription;
	
	// Should we prevent old heroes from previous scenarios in this campaign
	// from being placed when this scenario starts?
	bool			m_NoOldHeroes;
ENDCLASS

//
// GetScenarioObjectiveTypeName() -- get programmatic (non-display) name for an objective type
//
inline const char *GetScenarioObjectiveTypeName(eScenarioObjectiveType in_eType)
{
	static const char *aszObjectiveTypeNames[] =
	{
		"primary",
		"secondary",
		"lose"
	};

	ASSERT(in_eType >= 0 && in_eType < kNumScenarioObjectiveTypes);
	return aszObjectiveTypeNames[in_eType];
}

//
// GetScenarioObjectiveTypeByName() -- map programmatic objective name back into objective type
//
inline eScenarioObjectiveType GetScenarioObjectiveTypeByName(const char *in_szObjectiveName)
{
	if(in_szObjectiveName != NULL)
	{
		for(int iType=0; iType<kNumScenarioObjectiveTypes; iType++)
		{
			if(!strcmp(in_szObjectiveName, GetScenarioObjectiveTypeName((eScenarioObjectiveType)iType)))
				return (eScenarioObjectiveType)iType;
		}
	}
	
	// not found
	return kNumScenarioObjectiveTypes;
}



#endif // DBSCENARIODEFS_H
