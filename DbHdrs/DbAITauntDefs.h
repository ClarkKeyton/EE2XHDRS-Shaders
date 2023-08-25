//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbAITauntDefs.h 10    8/10/05 10:37a Dsproul $
//
// DESCRIPTION:   Database headers for the AI Taunt system
//
// AUTHOR:        Tara Teich
//
//===========================================================================

#ifndef DBAITAUNTDEFS_H
#define DBAITAUNTDEFS_H
#pragma once

#include "hdrmacros.h"

// events the AI has something to say about
ENUM eAIResponseEvents {
	kAIResponseEvents_CapturedBuilding,
	kAIResponseEvents_CapturedTerritory,
	kAIResponseEvents_NuclearBomb,
	kAIResponseEvents_AdvancesEpoch,

	// these three are picked in the taunt manager
	//		based on the epoch of the taunter
	kAIResponseEvents_AdvancesEpochPlayerAhead,
	kAIResponseEvents_AdvancesEpochPlayerBehind,
	kAIResponseEvents_AdvancesEpochPlayerEven,

	kAIResponseEvents_WinsCrown,

	kAIResponseEvents_BrokeAlliance,
	
	// taunt when AI decides to betray you
	kAIResponseEvents_BetraysYou,

	// a time tick event, randomly have AI taunts every x seconds
	kAIResponseEvents_RandomTimeTick,

	// used by diplomacy system to handle alliance events
	kAIResponseEvents_RepeatedAllianceRequest,
	kAIResponseEvents_TraitorAllianceRequest,
	kAIResponseEvents_UnneededAllianceRequest,
	kAIResponseEvents_BribedAllianceSuccess,
	kAIResponseEvents_BribedTraitorAllianceSuccess,
	kAIResponseEvents_SuccessfulAllianceRequest,
	kAIResponseEvents_UnsuccessfulAllianceRequest,
	kAIResponseEvents_NoCashAllianceRequestFailure,
	kAIResponseEvents_SurrenderRequest,
	
	// fealty comments
	kAIResponseEvents_RepeatedFealtyDemand,
	kAIResponseEvents_SuccessfulFealtyDemand,
	kAIResponseEvents_UnsuccessfulFealtyDemand,

	// used by diplomacy system for war plan requests
	kAIResponseEvents_AcceptedWarPlan,
	kAIResponseEvents_RejectedWarPlan,
	
	// @EE2X
	// native tribes diplomacy responses
	kAIResponseEvents_NT_Reject_Unfamiliar,
	kAIResponseEvents_NT_Reject_BetterOffer,
	kAIResponseEvents_NT_Reject_Assimilated,
	kAIResponseEvents_NT_Retract_TimeOut,
	kAIResponseEvents_NT_Retract_Assimilated,
	kAIResponseEvents_NT_NowFamiliar,
	kAIResponseEvents_NT_Counter,
	kAIResponseEvents_NT_Accept,
	kAIResponseEvents_NT_Berserk,
	kAIResponseEvents_NT_Unassimilate,

	kNumResponseEvents,
};

// we add this to the weight of personality matches (rather than default)
CONST float kAITaunt_PersonalityMatch_WeightBonus = 10;

// one taunt record
DATACLASS(DbAITauntRecord)
	DBINDEX(DbText)	m_tauntText;		// index into the localized text index of the taunt text
	bool	m_isNonHostile;				// do we play this text when hostile or not?
	const char* m_personalityType;		// if this is for a particular personality, which one, NULL means default
	float m_weight;						// weight of using this particular response, default means 1, really
ENDCLASS

// one complete taunt def for a particular event, the name of the definition
//		is the event name
DATACLASS(DbAITauntDef)
	LSizedArray<DC(DbAITauntRecord)*> m_records;	// all records valid for this event
ENDCLASS


#endif // DBAITAUNTDEFS_H