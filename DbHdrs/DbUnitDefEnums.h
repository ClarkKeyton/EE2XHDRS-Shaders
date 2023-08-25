//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbUnitDefEnums.h 97    9/29/05 4:24p Dsproul $
//
// DESCRIPTION:	DbUnitDefEnums.h is used to break out some enums that
//				are needed by code, so that UnitType.h doesn't need
//				to include the full definition file (DbUnitDefs.h)
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef DBUNITDEFENUMS_H
#define DBUNITDEFENUMS_H
#pragma once

#include "HdrMacros.h"
#include "LDbText.h"

//	This enum specifies the movement type of the unit, in terms of where
//	it can path.  It is also used as a row index into the movement table
//	for computing speed.

// NOTE: if you change this enum, please go to dbunittypeattributes.ddf and change
//		the MobileUnits attribute correspondingly
ENUM eUnitMoveType {
	kUnitMoveType_Immobile,			// can't move at all

	kUnitMoveType_Foot,				// normal land foot unit (default)
	kUnitMoveType_FootCitizen,		// moves same as Foot, but can traverse certain territory borders
	kUnitMoveType_FootSpy,			// spies can violate border permissions
	kUnitMoveType_Mounted,			// mounted unit
	kUnitMoveType_Wheeled,			// wheeled unit
	kUnitMoveType_WheeledTrade,		// moves same as Wheeled, but can traverse certain territory borders
	kUnitMoveType_Mechanized,		// mechanized unit
	kUnitMoveType_NavalShallow,		// naval unit, shallow water
	kUnitMoveType_NavalDeep,		// naval unit, deep water
	kUnitMoveType_Air,				// air unit (no terrain pathing)
	kUnitMoveType_Projectile,		// projectiles, like arrows
	kNumUnitMoveType,
};

inline bool IsLandMoveType(eUnitMoveType moveType)
{
	return (moveType == kUnitMoveType_Foot || moveType == kUnitMoveType_FootCitizen || moveType == kUnitMoveType_Mounted 
			|| moveType == kUnitMoveType_FootSpy 
			|| moveType == kUnitMoveType_Wheeled || moveType == kUnitMoveType_WheeledTrade || moveType == kUnitMoveType_Mechanized);
}

inline bool IsNavalMoveType(eUnitMoveType moveType)
{
	return (moveType == kUnitMoveType_NavalShallow || moveType == kUnitMoveType_NavalDeep);
}

inline bool IsAirMoveType(eUnitMoveType moveType)
{
	return (moveType == kUnitMoveType_Air);
}

ENUM eProjectileMoveType {
	kProjectileMoveType_Unused,				// to prevent inadvertantly setting
	kProjectileMoveType_RegularProjectile,	// arrow, etc.
	kProjectileMoveType_Bomb,				// bombs dropped from airplanes
	kProjectileMoveType_GuidedMissile,		// self-guided missile
	kProjectileMoveType_ICBM,				// like guided missile, but has a fancy movement path
	kProjectileMoveType_Torpedo,			// Torpedos.  In the water.
};

inline bool IsGuided(eProjectileMoveType projMoveType)
{
	return (projMoveType == kProjectileMoveType_GuidedMissile 
			|| projMoveType == kProjectileMoveType_Torpedo);
}

//	This enum categorizes the unit type in terms of who can instantiate it

ENUM eUnitOwnerType {
	kUnitOwnerType_PlayerOnly = 1,	// only a player can have this unit (default)
									// set to 1 so we don't get it unintentionally
	kUnitOwnerType_WorldOnly,		// only the world can have this unit
	kUnitOwnerType_PlayerOrWorld,	// player or world can have this unit
	kUnitOwnerType_Invalid,			// not a valid unit type, just used for inheritance
};

//	This enum determines how the unit is placed by the UI

ENUM eUnitPlacementType {
	kUnitPlacementType_Default,		// no constraints
	kUnitPlacementType_Building,	// building: rotate 45 degrees, tile bounds, flatten terr
	kUnitPlacementType_Dock,		// like building, but must build on coast
	kUnitPlacementType_NearWater,	// like dock, but rather than overlapping water just needs to be near water (eg for coastal defense)
	kUnitPlacementType_DeepWater,	// deep water only (e.g., fish resource)
	kUnitPlacementType_Airport,		// ???
	kUnitPlacementType_Road,		// road
	kUnitPlacementType_Bridge,		// bridge
	kUnitPlacementType_Wall,		// wall
	kUnitPlacementType_Farm,		// farm
	kUnitPlacementType_OnResource,	// @MRC @EE2X You must place this unit on top of another (resource) unit.  Specify placementTargetType on DbUnitTypeDef
	kUnitPlacementType_Unplaceable,	// cannot be explicitly placed (projectiles, some wall/road units)
};

// Different rally flag locations	
FLAGS(kUnitRallyPlacementFlag)
	const uint32 kUnitRallyPlacementFlag_None			= 0x00000000;	// I'm not sure if this will even be used; but I'll reserve it anyway.  
	
	// terrain
	const uint32 kUnitRallyPlacementFlag_Terrain		= 0x00000001;	// Valid terrain locations
	const uint32 kUnitRallyPlacementFlag_Mountain		= 0x00000002;	// Impassable land terrain
	const uint32 kUnitRallyPlacementFlag_Water			= 0x00000004;	// Water locations
	
	// resource targets
	const uint32 kUnitRallyPlacementFlag_Resources		= 0x00000008;	// Resources.  This also includes oil rigs and uranium mines and farms.  
	const uint32 kUnitRallyPlacementFlag_Fish			= 0x00000010;	// Rally flags on fish
	
	// player-owned targets
	const uint32 kUnitRallyPlacementFlag_Fortress		= 0x00000020;	// Fortress garrisoning
	const uint32 kUnitRallyPlacementFlag_Tower			= 0x00000040;	// tower garrisoning
	const uint32 kUnitRallyPlacementFlag_Dock			= 0x00000080;	// Rally points on docks
	const uint32 kUnitRallyPlacementFlag_Market			= 0x00000100;
	const uint32 kUnitRallyPlacementFlag_Temple			= 0x00000200;
	const uint32 kUnitRallyPlacementFlag_University		= 0x00000400;
	const uint32 kUnitRallyPlacementFlag_Warehouse		= 0x00000800;
	const uint32 kUnitRallyPlacementFlag_CityCenter		= 0x00001000;

	// any (still respects ownership checks)
	const uint32 kUnitRallyPlacementFlag_AnyBuilding	= 0x00002000;	// any building
	const uint32 kUnitRallyPlacementFlag_AnyMobile		= 0x00004000;	// any mobile unit type

	// optionally include units from other players
	const uint32 kUnitRallyPlacementFlag_Allied			= 0x00008000;	// include units from non-self allied players
	const uint32 kUnitRallyPlacementFlag_Neutral		= 0x00010000;	// include units from non-self neutral players
	const uint32 kUnitRallyPlacementFlag_Hostile		= 0x00020000;	// include units from non-self at-war players
	
	// Adding to end so we don't mess up existing stuff - save/load
	// player-owned construction site
	const uint32 kUnitRallyPlacementFlag_ConstructionSite	= 0x00040000;
ENDFLAGS

//	Here are the Rock-Paper-Scissors combat	RPS types
// NOTE THAT THIS MUST EXACTLY MATCH DATACLASS DbCombatDef in DbCombatDefs.h!
// ALSO NOTE THAT YOU MUST UPDATE THE s_rpsTypeNames STRING TABLE RIGHT BELOW THIS ENUM!
ENUM eUnitRPS {
	kUnitRPS_Null,					// invalid entry
	kUnitRPS_LightInfantry,			// land units
	kUnitRPS_HeavyInfantry,
	kUnitRPS_LightArtillery,
	kUnitRPS_AntiAircraft,
	kUnitRPS_HeavyArtillery,
	kUnitRPS_LightMounted,
	kUnitRPS_HeavyMounted,
	kUnitRPS_Citizen,
	kUnitRPS_Priest,
	kUnitRPS_Building,
	kUnitRPS_LandNonCombat,
	kUnitRPS_Ram,
	kUnitRPS_HERC,
	kUnitRPS_Animal,

	// NOTE: see kUnitRPS_LastLand at end of enums, bump this if change the last
	// land-based entry.  I moved these to the end to avoid confusing the parser.

	kUnitRPS_CloseAirSupport,		// air units
	kUnitRPS_AirSuperiority,
	kUnitRPS_Bomber,
	kUnitRPS_AtomicBomber,
	kUnitRPS_Helicopter,
	kUnitRPS_AirNonCombat,

	// NOTE: see kUnitRPS_LastAir at end of enums, bump this if change the last
	// land-based entry.  I moved these to the end to avoid confusing the parser.

	kUnitRPS_Submarine,				// sea units
	kUnitRPS_SubmarineNuclear,	
	kUnitRPS_WarGalley,
	kUnitRPS_FightingSail,
	kUnitRPS_Frigate,
	kUnitRPS_Galleon,
	kUnitRPS_Battleship,
	kUnitRPS_Destroyer,
	kUnitRPS_Carrier,
	kUnitRPS_Transport,
	kUnitRPS_SeaNonCombat,

	// NOTE: see kUnitRPS_LastSea at end of enums, bump this if change the last
	// land-based entry.  I moved these to the end to avoid confusing the parser.

	kUnitRPS_CoastalDefense,
	kUnitRPS_BuildingCombat,
	kUnitRPS_SpecialForces,
	kUnitRPS_NumRPSTypes,			// number of them

	// These appear at the end instead of embedded in the list, because the
	// parser is an idiot and otherwise gets the numbering confused.
	// Keep track of the last land RPS
	kUnitRPS_LastLand = kUnitRPS_Animal,
	// the last air RPS
	kUnitRPS_LastAir = kUnitRPS_AirNonCombat,
	// the last sea RPS
	kUnitRPS_LastSea = kUnitRPS_SeaNonCombat,

};

// PLEASE REMEMBER TO UPDATE THIS IF CHANGING RPS TYPE NAMES
static const char *s_rpsTypeNames[] = {
	"tx_enum_eUnitRPS_0", "tx_enum_eUnitRPS_1", "tx_enum_eUnitRPS_2", "tx_enum_eUnitRPS_3",
	"tx_enum_eUnitRPS_4", "tx_enum_eUnitRPS_5", "tx_enum_eUnitRPS_6", "tx_enum_eUnitRPS_7",
	"tx_enum_eUnitRPS_8", "tx_enum_eUnitRPS_9", "tx_enum_eUnitRPS_10", "tx_enum_eUnitRPS_11",
	"tx_enum_eUnitRPS_12", "tx_enum_eUnitRPS_13", "tx_enum_eUnitRPS_14", "tx_enum_eUnitRPS_15",
	"tx_enum_eUnitRPS_16", "tx_enum_eUnitRPS_17", "tx_enum_eUnitRPS_18", "tx_enum_eUnitRPS_19",	
	"tx_enum_eUnitRPS_20", "tx_enum_eUnitRPS_21", "tx_enum_eUnitRPS_22", "tx_enum_eUnitRPS_23",	
	"tx_enum_eUnitRPS_24", "tx_enum_eUnitRPS_25", "tx_enum_eUnitRPS_26", "tx_enum_eUnitRPS_27",	
	"tx_enum_eUnitRPS_28", "tx_enum_eUnitRPS_29", "tx_enum_eUnitRPS_30", "tx_enum_eUnitRPS_31",
	"tx_enum_eUnitRPS_32", "tx_enum_eUnitRPS_33", "tx_enum_eUnitRPS_34", "tx_enum_eUnitRPS_35",
};

// Convert stance type to a string name
inline const char* GetRpsTypeName(eUnitRPS rps)
{
	ASSERT(rps >= 0 && rps < kUnitRPS_NumRPSTypes);
	return g_pDbTextTable->GetText(s_rpsTypeNames[(int) rps]);
}

//	These specify the ranges of enumerations used in the "super-enumeration"
//	of unit attributes.  Each is assigned a bit position in the class UnitTypeAttribute.

/////////////////////////////
// @EE2X Daniel 03/09/05
// adding hero ab, so _MovementBase, _RPSBase, and _UserBase all had to be bumped
// by one, and a free space got dropped

ENUM eUnitTypeAttr {
	kUnitTypeAttr_Reserved = 0,			// reserved, to make convenient construction from null-term array
	kUnitTypeAttr_AbilityBase = 1,		// the first ability goes here
	kUnitTypeAttr_MovementBase = 26,	// if run out of room, verify func will fail
	kUnitTypeAttr_RPSBase = 38,			// if run out of room, verify func will fail
	kUnitTypeAttr_UserBase = 73,		// we start off with the user-created ones

	// @BM I'm changing this so that the user bits just start at UserBase
	// and then count up automatically, so if we have to reshuffle later,
	// we won't have to change the numerical value of every damn enum member.
	kUnitTypeAttr_RectangularFootprint = kUnitTypeAttr_UserBase,	// set from .ddf - uses tag extents for rect area
	kUnitTypeAttr_HealedByMedic,	// can be healed by medic
	
	kUnitTypeAttr_free_space_1,	 // @NOTE:  need a bit?  make these "free space" bits mean something!
	kUnitTypeAttr_free_space_2,	
	kUnitTypeAttr_free_space_3,
	kUnitTypeAttr_free_space_4,
	kUnitTypeAttr_free_space_5,
	kUnitTypeAttr_free_space_6,

	kUnitTypeAttr_NotInSpatialIndex,		// doesn't go into the spatial index, you cannot get it from a SelectUnits
	
	kUnitTypeAttr_GoesOnAirMissions,						// can go on air missions (must also be able to garrison at airport)

	kUnitTypeAttr_BlockPathing,	// unit CAN block pathing (not necessarily always blocking) 
	kUnitTypeAttr_RangedAttack,	// unit employs ranged attack
	kUnitTypeAttr_MeleeAttack,	// unit attacks with some kind of close range weapon
	kUnitTypeAttr_IsTree,			// unit is a tree
	kUnitTypeAttr_Attackable,		// unit can be attacked (most units are attackable except purely decorative units)
	kUnitTypeAttr_CaptureAttack,	// unit can do capture attack
	kUnitTypeAttr_IsAmmo,
	kUnitTypeAttr_HealedByHERC,	// can be healed by repair herc
	kUnitTypeAttr_IsWonder,		// Is this unit a Wonder?
	kUnitTypeAttr_HasMissileAttack,		// unit attacks with a projectile, not a beam weapon or machine gun
	kUnitTypeAttr_FakeWorldType,	// is this unit a fake world unit type (road, bridge, or farm; not under construction)
//	kUnitTypeAttr_NotAffectedByWeather,	// unit's movement is not affected by weather

	// @EE2X -- Daniel 04/12/05
	// can join hero army!  this bit must be set in order to join a hero army
	kUnitTypeAttr_CanJoinHeroArmy,

	kUnitTypeAttr_NotSelectable,	// This unit is not allowed to be selected.

	// IMPORTANT! Set this to the last 'user' attribute in the list.
	kUnitTypeAttr_UserLast = kUnitTypeAttr_NotSelectable,

	kUnitTypeAttr_Num = 96,			// if run out of room for user bits, bump this up
									// but PLEASE talk to rex first, it is sort of a big deal
									// right now, conveniently fits in 4 words
};

// ---------------------------------------------------------------------
// different types of pieces of composite units -- roads, bridges, walls
// the special repeated cases for labelling are ordered so as to get what we want to
// show up in the debugger

ENUM eComposite {
	kComposite_Invalid			= -1,

	// roads
	kComposite_RoadPiece		= 0,
	kComposite_FirstRoadType	= 0,
	kComposite_RoadElbow		= 1,
	kComposite_LastRoadType		= 1,

	// bridges
	kComposite_Bridge			= 2,

	// walls
	kComposite_WallSegment		= 3,
	kComposite_FirstWallType	= 3,
	kComposite_WallConnector, 
	kComposite_WallFragment,
	kComposite_WallGate,
	kComposite_WallTower		= 7,
	kComposite_LastWallType		= 7,

	kComposite_NumCompositeTypes,
};

// Enumeration of what sides must be left open on a particular building.
// Last 4 bits of each enum dictate what needs to be open or closed.
// Bits are:
//	-y | -x | +y | +x
// So, starting from positive x, ccw around the axes going from low bit to
// high bit.  A one in a bit means that that side MUST be allowed to be open,
// and other buildings cannot be built adjacent to that side.
// X and Y are talking about the sides of the building as if it were placed in
// the world with zero rotation (which never happens).  Note that this does not
// necessarily correspond to the X and Y coordinates of the model.
ENUM eBuildingOpenSides {
	kBuildingOpenSides_None = 0x80,				// 1000 0000
	kBuildingOpenSides_PosX = 0x81,				// 1000 0001
	kBuildingOpenSides_PosY = 0x82,				// 1000 0010
	kBuildingOpenSides_PosXPosY = 0x83,			// 1000 0011
	kBuildingOpenSides_NegX = 0x84,				// 1000 0100
	kBuildingOpenSides_PosXNegX = 0x85,			// 1000 0101
	kBuildingOpenSides_PosYNegX = 0x86,			// 1000 0110	
	kBuildingOpenSides_PosXPosYNegX = 0x87,		// 1000 0111
	kBuildingOpenSides_NegY = 0x88,				// 1000 1000
	kBuildingOpenSides_PosXNegY = 0x89,			// 1000 1001
	kBuildingOpenSides_PosYNegY = 0x8A,			// 1000 1010
	kBuildingOpenSides_PosXPosYNegY = 0x8B,		// 1000 1011
	kBuildingOpenSides_NegXNegY = 0x8C,			// 1000 1100
	kBuildingOpenSides_PosXNegXNegY = 0x8D,		// 1000 1101
	kBuildingOpenSides_PosYNegXNegY = 0x8E,		// 1000 1110
	kBuildingOpenSides_PosXPosYNegXNegY = 0x8F	// 1000 1111
};

// This goes with the above enum.  Doesn't need to be used in .ddfs (that I know of)
// It's for doing bitwise comparisons with the above.
enum eBuildingSides
{
	kBuildingSide_PosX = 0x1,
	kBuildingSide_PosY = 0x2,
	kBuildingSide_NegX = 0x4,
	kBuildingSide_NegY = 0x8,
};

// ---------------------------------------------------------------------
// different unit stance types

// HEY! - if eStanceType changes, so must GetStanceTypeName(stance) (below)...
ENUM eStanceType {
	kStanceType_Invalid = -1,

	kStanceType_Aggressive,
	kStanceType_Defensive,
	kStanceType_HoldPosition,
	kStanceType_HoldFire,
	kStanceType_Cautious,
	kNumStanceTypes,
};

static const char *s_stanceTypeNames[] = {
	"aggressive", "defensive", "holdposition", "holdfire", "cautious"
};

// Convert stance type to a string name
inline const char* GetStanceTypeName(eStanceType stance)
{
	ASSERT(stance >= 0 && stance < kNumStanceTypes);
	return s_stanceTypeNames[(int) stance];
}

// Convert string name to a stance type
inline eStanceType FindStanceTypeByName(const char *in_pName)
{
	for (int stance = 0; stance < kNumStanceTypes; stance++)
	{
		if (stricmp(in_pName, s_stanceTypeNames[stance]) == 0)
			return (eStanceType) stance;
	}
	return kStanceType_Invalid;
}


////////////////////////////////
// @EE2X - Daniel 03/11/05
// the available set of hero classes
// @NOTE this is for the most part just going to end up being a subset
// of RPS I think, but doing things this way allows us a bit more flexibility

ENUM eHeroClass {
	kHeroClass_None = 0,		// let's go ahead and let 0 be None, since that is the default

	kHeroClass_LightInfantry,
	kHeroClass_HeavyInfantry,
	kHeroClass_LightArtillery,
	kHeroClass_HeavyArtillery,
	kHeroClass_LightMounted,
	kHeroClass_HeavyMounted,
	kHeroClass_LightTank,
	kHeroClass_HeavyTank,
	kHeroClass_LightHerc,
	kHeroClass_HeavyHerc,
	kHeroClass_Helicopter,

	// @NOTE Make sure you update these values when you add new Hero Classes.
	kHeroClass_FirstHeroClass	= kHeroClass_LightInfantry,
	kHeroClass_LastHeroClass	= kHeroClass_Helicopter,

	kNumHeroClassTypes,
};

static const char *s_aszHeroClassNames[] = {
	"None",
	"LightInfantry",
	"HeavyInfantry",
	"LightArtillery",
	"HeavyArtillery",
	"LightMounted",
	"HeavyMounted",
	"LightTank",
	"HeavyTank",
	"LightHerc",
	"HeavyHerc",
	"Helicopter"
};


#endif // DBUNITDEFENUMS_H
