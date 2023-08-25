//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbTechTreeDefs.h 69    10/05/05 2:53p Tteich $
//
// DESCRIPTION:	DbTechTreeDef.h holds the enum and dataclass defs
//				related to the tech tree
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef DBTECHTREEDEF_H
#define DBTECHTREEDEF_H
#pragma once

#include "HdrMacros.h"
#include "LSizedArray.h"
#include "DbResourceDefs.h"
#include "DbPlayerDefs.h"
#include "LDbText.h"

class LDataObj;		// forward refs
class LStrUTF8;
class Player;

//	-------------------------------------------------------------------
//		TECH TREE EPOCHS
//	-------------------------------------------------------------------

//Epoch Name enumeration table
ENUM eTechTreeEpoch{
	kTechTreeEpoch_None = 0,

	kTechTreeEpoch_Stone = 1,
	kTechTreeEpoch_Copper,
	kTechTreeEpoch_Bronze,
	kTechTreeEpoch_Iron,
	kTechTreeEpoch_Dark,
	kTechTreeEpoch_Middle,
	kTechTreeEpoch_Renaissance,
	kTechTreeEpoch_Imperial,
	kTechTreeEpoch_Enlightenment,
	kTechTreeEpoch_Industrial,
	kTechTreeEpoch_Modern,
	kTechTreeEpoch_Atomic,
	kTechTreeEpoch_Digital,
	kTechTreeEpoch_Genetic,
	kTechTreeEpoch_Synthetic = 15,

	kNumTechTreeEpochs = 15,
	
	kTechTreeEpoch_Random = -1,
};

// meta epochs
const int kMetaEpoch_1 = 5;
const int kMetaEpoch_2 = 10;

//
// EpochToMetaEpoch() -- stupid helper func maps epoch to meta-epoch
//
inline int EpochToMetaEpoch(int in_iEpoch)
{
	ASSERT(in_iEpoch >= 1 && in_iEpoch <= 15);

	if(in_iEpoch <= kMetaEpoch_1)
	{
		return 1;
	}
	else if(in_iEpoch <= kMetaEpoch_2)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

//Epoch Names
static const char *s_EpochNames[] = { "", "tx_enum_eTechTreeEpoch_1", "tx_enum_eTechTreeEpoch_2",
										"tx_enum_eTechTreeEpoch_3",	"tx_enum_eTechTreeEpoch_4",
										"tx_enum_eTechTreeEpoch_5",	"tx_enum_eTechTreeEpoch_6",
										"tx_enum_eTechTreeEpoch_7",	"tx_enum_eTechTreeEpoch_8",
										"tx_enum_eTechTreeEpoch_9",	"tx_enum_eTechTreeEpoch_10",
										"tx_enum_eTechTreeEpoch_11",	"tx_enum_eTechTreeEpoch_12",
										"tx_enum_eTechTreeEpoch_13",	"tx_enum_eTechTreeEpoch_14",
										"tx_enum_eTechTreeEpoch_15"};


inline const char *GetEpochName(eTechTreeEpoch inEpoch)
{
	ASSERT(inEpoch >= 0 && inEpoch <= kNumTechTreeEpochs);
	if(inEpoch >= 0 && inEpoch <= kNumTechTreeEpochs)
		return g_pDbTextTable->GetText(s_EpochNames[inEpoch]);
	else
		return NULL;
}

//	-------------------------------------------------------------------
//		TECH TREE NODES
//	-------------------------------------------------------------------

// Tech Tree branch
ENUM eTechTreeBranch {
	kTechTreeBranch_None,			// none, shouldn't be used in visible tech tree
	kTechTreeBranch_Main,			// main trunk
	kTechTreeBranch_Military,		// military branch
	kTechTreeBranch_Economic,		// economic branch
	kTechTreeBranch_Imperial,		// imperial branch
	kTechTreeBranch_Improvement,	// unit type improvement
	kNumTechTreeBranches,
};

//EE2X
//Enum table to designate civ specific tech tree nodes
//@NOTE: THIS MUST TO CORESPOND TO THE GAME'S CIV ENUM IN DBPLAYERDEFS.H, BUT HAVE THE "ALL" CIV 
//  ENUM IN THE 0 SPACE!
ENUM eTechTreeCiv {
	kTechTreeCiv_All,	//0
	kTechTreeCiv_German,	//1
	kTechTreeCiv_English,
	kTechTreeCiv_Roman,
	kTechTreeCiv_American,
	kTechTreeCiv_Greek,
	kTechTreeCiv_Chinese,
	kTechTreeCiv_Korean,
	kTechTreeCiv_Japanese,
	kTechTreeCiv_Egyptian,
	kTechTreeCiv_Turkish,
	kTechTreeCiv_Babylonian,
	kTechTreeCiv_Inca,
	kTechTreeCiv_Aztec,
	kTechTreeCiv_Mayan,
	kTechTreeCiv_Maasai,
	kTechTreeCiv_Zulu,
	kTechTreeCiv_French,
	kTechTreeCiv_Russian, // 18

	kTechTreeCiv_Western, //19
	kTechTreeCiv_FarEast,
	kTechTreeCiv_MiddleEast,
	kTechTreeCiv_MesoAmer,
	kTechTreeCiv_African,  //23

	kTechTreeCiv_Regions = 19,		//The value of the first region enum
};

//The following two inline function are used for converting from this tech tree enum
//to the play civ enum and regions
inline int TechTreeCivToRegion(int inTTCiv)
{
	ASSERT(inTTCiv >= kTechTreeCiv_Western && inTTCiv <= kTechTreeCiv_African);
	return inTTCiv - kTechTreeCiv_Regions;
}
inline int TechTreeCivToPlayerCiv(int inTTCiv)
{
	ASSERT(inTTCiv >= 0 && inTTCiv < kTechTreeCiv_Regions);
	return inTTCiv - 1;
}

//flags for special units
FLAGS(kSpecialFlag)
	const uint32 kSpecialFlag_None = 0x0000;
//The leader flags use the three right most bits
	const uint32 kSpecialFlag_Leader = 0x0001;	//rightmost bit if the node is a leader
	const uint32 kSpecialFlag_LeaderMilitary = 0x0001;	//001
	const uint32 kSpecialFlag_LeaderEconomic = 0x0003;	//011
	const uint32 kSpecialFlag_LeaderImperial = 0x0005;	//101
	
	// the unit with "ScriptUnlock" flag is normally "locked" and can only be made unlocked through scripting
	const uint32 kSpecialFlag_ScriptUnlock = 0x0008;		//      1000

	//These nodes should be researched when bringing a player up to their starting epoch
	const uint32 kSpecialFlag_FlagForResearch = 0x0010;		//0001 0000

	// unique unit (civ-specific)
	const uint32 kSpecialFlag_UniqueUnit = 0x0020;

	// improvement for unique unit (civ-specific)
	const uint32 kSpecialFlag_UniqueUnitImprovement = 0x0040;

	// civ attribute
	const uint32 kSpecialFlag_CivAttribute = 0x0080;

ENDFLAGS

// Base Tech Tree node
DATACLASS(DbTechTreeBaseNodeDef)
	DBINDEX(DbText)	m_displayName;	// name to display to user
	DBINDEX(DbText) m_tooltip;		// tooltip.  @NOTE for most techs this is not used
									// currently only the civ/regional traits use it
	int16 m_epoch;					// epoch this node is available at
	int16 m_slot;					// slot this node is at in visible tree
	enum eTechTreeBranch m_branch;	// branch this node is on
	DBINDEX(DbSprite) m_icon;		// icon to display

	// button position:
	int16 m_menu;					// menu the button goes in (-1 to hide button)
	int16 m_row;					// row to put icon in (on host)
	int16 m_column;					// column to put icon in (on host)

	DBINDEX(DbUnit) m_host;			// what unit can this be researched/produced at?
	DBINDEX(DbUnit) m_produce;		// unit to produce (if <=0, this is research node)
	DBINDEX(DbUpgrade) m_upgrade;	// upgrade to invoke (often an upgrade set)
	float m_time;					// (nominal) time to produce or research
	uint16 m_costFood;				// cost (food)
	uint16 m_costWood;				// cost (wood)
	uint16 m_costStone;				// cost (stone)
	uint16 m_costGold;				// cost (gold)
	uint16 m_costTin;				// cost (tin)
	uint16 m_costIron;				// cost (iron)
	uint16 m_costSaltpeter;			// cost (saltpeter)
	uint16 m_costOil;				// cost (oil)
	uint16 m_costUranium;			// cost (uranium)
	uint16 m_costTech;				// cost (techpoints)
	enum eTechTreeCiv m_techTreeCiv;	//if this node is civ specific

	// array of prerequisite node indicies
	LSizedArray<DBINDEX(DbTechTreeBaseNode)> m_aiPrerequisiteNodes;
	
	// array of nodes which depend on us (corollary to m_aiPrerequisiteNodes)
	USER LDynArray<int> m_aiDependentNodes;

	FLAGS(kSpecialFlag) uint32 m_specFlags;	// to easily distinguish special tech tree nodes
ENDCLASS


/////////////////////////////////////////////////////////////////////
//
// Tech tree player node (built on the fly, not by parsing)


/////////////////////////
// Tech Tree node flags
const int kTechTreeNodeFlag_Revealed		= 0x0001;	// has this node been revealed 
														// (we used to have support for revealing techs before they could actually be researched)
const int kTechTreeNodeFlag_Unlocked		= 0x0002;	// has this node been unlocked 
														// (once unlocked, a node may be researched/produced)
														// (should not be unlocked until prereqs satisfied)
const int kTechTreeNodeFlag_Researched		= 0x0004;	// has this node been researched?
const int kTechTreeNodeFlag_Production		= 0x0008;	// is this a production node?
const int kTechTreeNodeFlag_Obsolete		= 0x0010;	// has this node been obsoleted?
const int kTechTreeNodeFlag_BeingResearched	= 0x0020;	// is this node currently being researched?
const int kTechTreeNodeFlag_ScriptDisabled	= 0x0040;	// has this node been disabled from script?
const int kTechTreeNodeFlag_Leader			= 0x0080;	// Does this node build a leader?

DATACLASS(DbTechTreeNodeDef)
	USERPTR(DbTechTreeBaseNodeDef) m_baseNode;			// ptr to base node
	USER uint16 m_cost[ENUMVAL(eResourceType,kResourceType_Pop)];	// cost array (modifiable)
	USER float m_timeResearch;							// time to research (modifiable)
	USER uint32 m_flags;								// flags (see above)
	USER int m_host;									// the host so it can be changed on some levels

	// index, it comes in handy cometimes!
	USER int m_iIndex;
	
	// array of unresearched prerequisite node indicies
	// (initially copied from base node's m_aiPrerequisiteNodes)
	USER LDynArray<int> m_aiUnresearchedPrerequisiteNodes;
	
ENDVARS
	const DbTechTreeBaseNodeDef *GetBaseNode() const
	{
		return m_baseNode;				// get ptr to base node
	}
	int GetHost() const
	{
		return m_host;		// get host unittype index
	}
	int GetEpoch() const
	{
		return m_baseNode->m_epoch;
	}

	// research time with handicap, difficulty and tournament mode modifiers applied.
	// this is in essence the "base" value
	// @NOTE that at this point in-game modifiers will not have been applied.
	float GetTimeToResearch(Player *in_pPlayer) const;


	//////////////////////////////////////
	// query node state

	// is this node available for research/production?
	// only available if:
	// 1.) revealed
	// 2.) unlocked (and thus, presumably, prerequisites satisfied)
	// 3.) not obsolete
	// 4.) not script disabled
	bool IsAvailable(bool in_bIgnoreScriptStatus = false) const
	{
		return (IsRevealed() &&
				IsUnlocked() &&
				!IsObsolete() &&
				(in_bIgnoreScriptStatus || !IsScriptDisabled()));
	}
	
	// has this node been revealed?
	bool IsRevealed() const
	{
		return (m_flags & kTechTreeNodeFlag_Revealed) != 0;
	}
	
	// has this node been revealed?
	bool IsUnlocked() const
	{
		return (m_flags & kTechTreeNodeFlag_Unlocked) != 0;
	}

	// has this node been disabled for scripting reasons?
	bool IsScriptDisabled() const
	{
		return (m_flags & kTechTreeNodeFlag_ScriptDisabled) != 0;
	}

	// has this node been researched?
	bool IsResearched() const
	{
		return (m_flags & kTechTreeNodeFlag_Researched) != 0;
	}
	
	// is this node being researched?
	// (@NOTE also returns true if node is queued to be researched)
	bool IsBeingResearched() const
	{
		return (m_flags & kTechTreeNodeFlag_BeingResearched) != 0;
	}

	// has this node been obsoleted?
	bool IsObsolete() const
	{
		return (m_flags & kTechTreeNodeFlag_Obsolete) != 0;
	}

	// have our prereqs been satisfied?
	// @NOTE in general, you should not call this directly; 
	//		instead, use DbTechTreeNode::AreAllPrereqsSatisfied()
	bool AllPrerequisitesSatisfied() const
	{
		return (m_aiUnresearchedPrerequisiteNodes.GetSize() == 0);
	}


	///////////////////////////////////
	// query node type

	// is this a production node?
	bool IsProductionNode() const
	{
		return (m_flags & kTechTreeNodeFlag_Production) != 0;
	}

	// is this a research node? (includes improvement nodes)
	bool IsResearchNode() const
	{
		return !IsProductionNode();
	}

	// is this a non-improvement research node?
	bool IsNonImprovementResearchNode() const
	{
		return (IsResearchNode() && !IsImprovementNode());
	}

	// is this an improvement node?
	bool IsImprovementNode() const
	{
		return m_baseNode->m_branch == kTechTreeBranch_Improvement;
	}
	
	// Is this an epoch-advancing techtree node?
	// (main branch techs are epoch-advancers)
	bool IsEpochAdvancerNode() const
	{
		return m_baseNode->m_branch == kTechTreeBranch_Main;
	}

	// is this node okay for this player? (civ, region, and custom civ checks abound!)
	bool IsNodeForPlayer(const Player *in_pPlayer) const;

	// should this node be script-disabled by default?
	bool IsScriptDisabledByDefault() const
	{
		return (m_baseNode->m_specFlags & kSpecialFlag_ScriptUnlock) != 0;
	}

	// is this node flagged to be insta-researched when starting in a future epoch
	bool IsFlaggedForStartingEpochResearch() const
	{
		return (m_baseNode->m_specFlags & kSpecialFlag_FlagForResearch) != 0;
	}	
	
	// Do we produce a leader?
	bool IsLeaderNode() const
	{
		return (m_flags & kTechTreeNodeFlag_Leader) != 0;
	}

	// what kind of leader do we produce?
	eTechTreeBranch GetLeaderType() const
	{
		//First makesure it's a leader
		if((m_baseNode->m_specFlags & kSpecialFlag_Leader) == 0)
		{
			return kTechTreeBranch_None;
		}
		else
		{
			//return the branch type based on the special flag of the TTNode
			//Leader special flags only use the last three bits.  Mask out everything
			//else and compare
			switch(m_baseNode->m_specFlags & 0x07)
			{
				case kSpecialFlag_LeaderMilitary:
					return kTechTreeBranch_Military;		// military branch
				case kSpecialFlag_LeaderEconomic:
					return kTechTreeBranch_Economic;		// economic branch
				case kSpecialFlag_LeaderImperial:
					return kTechTreeBranch_Imperial;
				default:
					return kTechTreeBranch_None;
			}	
		}	
	}


	/////////////////////////////////////
	// modify node state
	
	// set/unset revealed
	void SetRevealed(bool in_bSet)
	{
		if(in_bSet)
			m_flags |= kTechTreeNodeFlag_Revealed;
		else
			m_flags &= ~kTechTreeNodeFlag_Revealed;
	}
	
	// mark unlocked
	// @NOTE in general, do not call this directly,
	//		instead, use DbTechTreeNode::SetUnlocked()
	void MarkUnlocked()
	{
		ASSERT(IsRevealed());					// should be revealed before being unlocked
		ASSERT(AllPrerequisitesSatisfied());	// all prereqs should be satisfied before being unlocked
		m_flags |= kTechTreeNodeFlag_Unlocked;
	}

	// mark researched
	// @NOTE in general, do not call this directly,
	//		instead, use DbTechTreeNode::SetResearched()
	void MarkResearched()
	{
		ASSERT(IsUnlocked());		// should be unlocked before being researched
		ASSERT(IsResearchNode());	// should be a research node
		if(IsResearchNode())
			m_flags |= kTechTreeNodeFlag_Researched;
	}

	// mark a node obsolete
	// @NOTE this also makes it locked and unrevealed
	void MarkObsolete()
	{
		m_flags |= kTechTreeNodeFlag_Obsolete;
		m_flags &= ~(kTechTreeNodeFlag_Revealed | kTechTreeNodeFlag_Unlocked);
	}

	// set disabled state for script
	// @NOTE in general, do not call this directly
	//		instead, use DbTechTreeNode::SetScriptDisabled() and DbTechTreeNode::SetScriptEnabled()
	void SetScriptDisabled(bool in_bDisable)
	{
		if(in_bDisable)
			m_flags |= kTechTreeNodeFlag_ScriptDisabled;
		else
			m_flags &= ~kTechTreeNodeFlag_ScriptDisabled;	
	}

	// set being-researched state
	void SetBeingResearched(bool in_bSet)
	{
		if(in_bSet)
			m_flags |= kTechTreeNodeFlag_BeingResearched;
		else
			m_flags &= ~kTechTreeNodeFlag_BeingResearched;
	}


	/////////////////////////////////
	// methods for cost

	// query cost for a resource type
	float GetCost(eResourceType resType) const
	{
		ASSERT((resType >= kResourceType_Food) && (resType <= kResourceType_Tech));
		return m_cost[resType];
	}

	// set cost for a resource type
	void SetCost(eResourceType resType, uint16 cost)
	{
		ASSERT((resType >= kResourceType_Food) && (resType <= kResourceType_Tech));
		m_cost[resType] = cost;			// set new cost of a resource
	}


	/////////////////////////////
	// misc utility methods
	
	// Get if this node is hosted by a citizen, i.e. a citizen builds it
	bool IsHostedByCitizen() const;

ENDCLASS


#endif // DBTECHTREEDEF_H
