// Copyright 2002 Mad Doc Software, LLC.  All rights reserved.
// $Header: /EE2X/src/EE2/DbHdrs/DbUnitDefs.h 187   9/07/05 12:43p Tteich $
// $Modtime: 9/07/05 12:01p $
//
//	DbUnitDefs has definitions related to Unit Types which need to be
//	read by the parser.

#pragma once
#ifndef DBUNITDEFS_H
#define DBUNITDEFS_H

#include "HdrMacros.h"

#include "DbResourceDefs.h"
#include "DbUnitDefEnums.h"
#include "LDataObj.h"
#include "LSizedArray.h"
#include "LRGBA.h"

//	-------------------------------------------------------------------
//		UNIT TYPE DATA DEFINITION CLASSES
//	-------------------------------------------------------------------

//	IMPORTANT NOTE:  IF YOU ADD NEW ABILITY TYPES, YOU MUST ADD THEM TO
//	THE s_dcTranslationTable TABLE IN DbUnit.cpp!

// used to define the type of bound the unit gets
// for building rectangle should be used, for mobile units, ellipse should be used

// different places units can garrison
ENUM eGarrisonType {
	kGarrisonType_Tower,							// can garrison at tower
	kGarrisonType_Temple,							// can garrison at temple
	kGarrisonType_Fortress,							// can garrison at fortress
	kGarrisonType_UniWarehouseOilDerrickCityCenter,	// can garrison at university, warehouse, oil derrick, city center (basically, resource drop off site)
	kGarrisonType_NavalTransport,					// can enter naval transport
	kGarrisonType_AirTransport,						// can enter air transport
	kGarrisonType_AirportOrAircraftCarrier,			// can garrison at airport/aircraft carrier
	kGarrisonType_Dock,								// can garrison at dock
	kGarrisonType_SpyShip,							// can garrison at spy ship
	kGarrisonType_SeigeTower,						// can garrison at seige tower (all human units)
	kGarrisonType_Heliport,							// can garrison at heliport

	//
	// WOO - put your new garrison types here!
	//

	kNumGarrisonTypes,
};

ENUM eFootprintType {
	kFootprintType_None,
	kFootprintType_Ellipse,
	kFootprintType_Rectangle,
};

// DbUnitTypeProperites are basic properties on a unit
DATACLASS(DbUnitTypeProperties)
	DBINDEX(DbText) displayName;			// name to display to user
	DBINDEX(DbText) displayNamePlural;		// name to display to user (plural version)
	DBINDEX(DbText) displayNameTTTooltip;	// override display name for techtree upgrade tooltips
	DBINDEX(DbText) displayNameScenEdit;	// override display name in scenario editor
	DBINDEX(DbText) verboseTooltip;		// index to tooltip text
	float mass;					// mass of unit (for collision)

	// for rectangular footprint, size is impassable area and footprint size
	//   is the total area for placement and undertexture.
	// for elliptical footprint, SizeX is radius along the major axis (middle
	//   to front) and SizeY is radius along the minor axis (middle to right).
	// the FootprintType enum determines what type of shape this unit occupies.
	enum eFootprintType FootprintType;
	float	Diameter;			// used with the circle type radius*2
	float	FootprintSizeX;		// depending on the type of footprint this is interpreted differently
	float	FootprintSizeY;		// they are ignored for ellipse and are the size of the rectangle if rectangle type
	float	SizeX;				// used by both rectangle and circle
	float	SizeY;				// used by both rectangle and circle
	// those two values determine where the upper left corner of the impassable area
	// is placed relative to the upper left corner of the footprint, default is both corner are aligned
	float	OffsetX;
	float	OffsetY;
	float	UndertextureSizeX;		// size of the unit's undertexture
	float	UndertextureSizeY;
	float	UndertextureOffsetX;	// offset of the unit's undertexture
	float	UndertextureOffsetY;

	float	UnitHeight;				// by default, this is 1.0 - which is the same old behavior we've always had!

	enum eBuildingOpenSides m_requiredOpenSides;	// For buildings, which sides must remain open and cannot
													// be adjacent to other buildings.

	int hitpoints;				// max hitpoints
	enum eUnitMoveType moveType;	// movement type (eUMT_xxx)
	enum eUnitRPS rps;			// rps enum
	enum eStanceType stance;	// default stance for this unit type
	LRGBA mmColor;				// minimap color (if all 0's use player color)
	int m_popCount;				// How much population does this unit take up?
	int m_popCapacity;			// How much population does this unit grant to the player?
	bool m_inForest;			// This unit type should go into forests for optimization

	FLAGS(kUnitRallyPlacementFlag) uint32 m_RallyPlacementFlags;	// Where are we allowed to place rally flags?
ENDCLASS

DATACLASS(DbUnitTypeSounds)
	LSizedArray<const char *> sndSelection;	// selection sounds
	LSizedArray<const char *> sndCmdMove;	// move command sound
	LSizedArray<const char *> sndCmdAttack;	// attack command sound
	LSizedArray<const char *> sndDeath;		// death sounds
ENDCLASS


//
// DbUnitFullmapOverlay -- for creating overlay sprites representing this unit type
//							on the fullmap

DATACLASS(DbUnitFullmapOverlay)
	DBINDEX(DbSprite) m_sprite;		// sprite to use when representing unit as an overlay on fullmap (upgradeable)
	float m_scale;					// scale relative to actual real-world footprint size;
									// if 0 this is set to 1 (so that 1.0 is the default;
									// at 1.0, the sprite is rendered on the fullmap with footprint
									// exactly matching real-world footprint size)
	bool m_ignoreOrientation;		// if true, sprite is rendered at 0 rotation regardless of unit orientation
ENDCLASS


// DbUnitTypeDef is the highest-level dataclass which every unit
// is defined in terms of
DATACLASS(DbUnitTypeDef)
    char *parent;								// parent unit type if any
	char *visualName;							// visual name if not just unit name
	const char *m_UIVisualName;					// alternate visual name to use for UI rendering
	const char *m_icon;							// sprite name for production/selection icon
												// this is a char * and not a sprite index because
												// we do some processing to get regional variants...
	DC(DbUnitFullmapOverlay) *m_fullmapOverlay;	// data for fullmap overlay sprite
	DBINDEX(DbSprite) m_citizenManagerCursorSprite;	// sprite to use in placement in citizen manager
	enum eUnitOwnerType ownerType;				// owner type (eUOT_xxxx)
	USER enum eUnitOwnerType inheritedOwnerType; // computed post-load
	enum eUnitPlacementType placementType;		// placement type (eUPT_xxxx)
	USER enum eUnitPlacementType inheritedPlacementType;	// computed post-load
	DC(DbUnitTypeProperties) *properties;		// properties (see above)
	DC(DbUnitTypeSounds) *sounds;				// unit type UI sounds
	LSizedArray<VARDC> abilities;				// array of variable abilities

	// Arrays of attribute bits to set and clear.  For each ancestor, bits are
	// first set, and then cleared from the attributes and nonAttributes arrays,
	// respectively.  You can override ancestors attributes.
	LSizedArray<enum eUnitTypeAttr> attributes;
	LSizedArray<enum eUnitTypeAttr> nonAttributes;


	//for inheritance tracking:
	USERPTR(DbUnitTypeDef) m_pParent;				// the parent of this DbUnitTypeDef, or NULL if root (?)
	USER LDynArray<uint16> m_aiChildren;		// an array of the DBINDEXes of all the unit types descended
											// from this DbUnitTypeDef.
	
	// @EE2X @MRC
	// If a unit needs to be placed on top of another unit of a particular type,
	// this value names the appropriate type.
	const char* m_placementTargetType;
	USER const char* m_inheritedPlacementTargetType;

ENDVARS
	enum eUnitOwnerType GetOwnerType()			// get owner type via inheritance
	{
		return inheritedOwnerType;
	}
	enum eUnitPlacementType GetPlacementType()	// get placement type via inheritance
	{
		return inheritedPlacementType;
	}
	const char* GetPlacementTargetType()
	{
		return m_inheritedPlacementTargetType;
	}
	//is this a unit that must be placed when created in game
	bool IsPlaceableUnit()
	{
		switch(inheritedPlacementType)
		{
			case kUnitPlacementType_Building:
			case kUnitPlacementType_Dock:
			case kUnitPlacementType_NearWater:
			case kUnitPlacementType_Airport:
			case kUnitPlacementType_Road:
			case kUnitPlacementType_Bridge:
			case kUnitPlacementType_Wall:
			case kUnitPlacementType_Farm:
			case kUnitPlacementType_OnResource:
				return true;
				break;
			default:
				return false;
		}
	}
ENDCLASS

// This dataclass is used to translate obsolete unit type names into good ones
DATACLASS(DbUnitTypeTranslation)
	const char *m_newUnitTypeName;	// name of entry is old name, this is new name
ENDCLASS

// There are a host of ability dataclasses

DATACLASS(ABCD_Move)
	float speed;		// maximum speed
	float accel;		// acceleration, usually derived from speed
	float angSpeed;		// maximum angular speed
	float angAccel;		// angular acceleration, usually derived from speed

	// the following are usually for vehicle-type of units (tanks, cars, chariots, etc.)
	bool mustMoveToTurn;		// if true, this unit can not turn without moving (i.e., vehicles)
	// does weather not affect this unit type's speed
	// (this is expressed this way so we can exploit the fact that the DB reader
	//  will initialize all dataclass data to 0)
	bool speedNotAffectedByWeather;
ENDCLASS

// a very simple move ability
DATACLASS_INHERIT(ABCD_MoveFreeFall, ABCD_Move)
ENDCLASS

DATACLASS_INHERIT(ABCD_VehicleMove, ABCD_Move)
	bool followTerrainSlope;	// if true (usually true for most vehicles), rotate to follow terrain slope so that all corners are on ground
	float bounce;	// >0, determines how "bouncy" the vehicle is, if 0, will use a default value, the higher the value, the bouncier the vehicle will be
					// if you don't want any bounce, just set followTerrainSlope to false
ENDCLASS

DATACLASS_INHERIT(ABCD_ProjectileMissileMove, ABCD_Move)
	enum eProjectileMoveType m_Type;	// what kind of projectile movement
ENDCLASS

DATACLASS_INHERIT(ABCD_AircraftMove, ABCD_Move)
	float m_CruisingHeight;		// how much above terrain level does this airplane flies while cruising (not taking off or landing)
	float m_ElevChangeRate;		// when flying over uneven terrain, how much elevation change per second
	float m_CargoHeight;		// the height above terrain when loading/unloading garrisoned units/cargo
	float m_OnGroundScale;		// the RELATIVE scale when the airplanes are on the ground (airport runway)
	bool  m_CanHover;			// if true, this unit can hover (hang) in the air without moving
ENDCLASS

DATACLASS_INHERIT(ABCD_NavalMove, ABCD_Move)
	float m_CruisingDepth;		// only submarine needs this, specifies how much under the sea level should the boat travels
ENDCLASS

DATACLASS_INHERIT(ABCD_AnimalMove, ABCD_Move)
	float m_wanderDist;		// how far away can the animal wander off its initial position
	float m_timeBetweenWandering;	// average time between the completion of the last wandering and the start of the next wandering
ENDCLASS

DATACLASS_INHERIT(ABCD_AirAnimalMove, ABCD_AircraftMove)
	float m_flyDist;		// how far away can the animal fly off its initial position
	float m_timeBetweenFlying;	// average time between the completion of the last flying and the start of the next flying
ENDCLASS

DATACLASS(ABCD_PowerReserve)
	// this class's data member
	//float powerUseRate;		// NOT CURRENTLY USED, power used per second while performing the conversion
	float timeToRecharge;	// time in seconds to recharge to full power  (or rechargeRate - how much power will be gained/recharged per second)
	//int maxPower;			// NOT CURRENTLY USED, how much power (maximum) can we have
ENDCLASS

//
// BEGIN TURRET CONTROLLER DATACLASS
//
DATACLASS(MuzzleSet)
	// list of tag names that fire together
	LSizedArray<char*> m_tags;
ENDCLASS

DATACLASS(FiringPattern)
	// name of turret bank this pattern belongs to
	char *m_bankName;
	// ordered listof muzzle sets that defines firing sequence
	LSizedArray<DC(MuzzleSet)*> m_sequence;
ENDCLASS

DATACLASS(TurretControllerData)
	// list of patterns, at most one for each bank,
	// if a bank has no pattern, then all muzzles in bank fire at once.
	LSizedArray<DC(FiringPattern)*> m_patterns;
ENDCLASS
//
// END TURRET CONTROLLER DATACLASS
//

DATACLASS(ABCD_Attack)
	// this class's data member
	char *m_missileName;		// if not NULL, this is a missile attack
	float m_range;				// this is the maximum range
	float m_minRangeMobile;		// this is the minimum range against mobile target
	float m_minRangeImmobile;	// this is the minimum range against immobile target
	float m_angularRange;		// the angle between the left-most line and right-most line of attackable area
	float m_reloadTime;		// how long does a "round" of attack take
	float m_unpackTime;		// if >0, the time it takes to unpack before attacking
	float m_packTime;			// if >0, the time it takes to pack up after attacking is finished
	float m_applyDamageTime;	// at what point of the "round" should the damage be applied
	float m_damage;				// damage (hit points reduction of enemy) per ROUND of attack
	float m_areaDamageRadius;	// if >0, has area damage
	float m_areaDamageFriendlyRatio;	// 0-1, how much of the area damage is applied to friendly units
	bool m_ignoreBlocking;	// is firing blocked by buildings, wall, etc.
							// for missile attack, if this is true, then missiles will be fired using high projectile
							// rather than low projectile
	bool m_attackOnTheMove;		// can we attack while moving (for airplanes)

	bool m_latent;				// is this ability latent (inactive until ?

	bool m_startWithNoOrdnance;	// only to be used when m_ordnance > 0
								// should the unit start with no ordnance?

	int  m_ordnance;			// amount of supply, 0 means infinite supply
								// if non-0, it is the number of attack rounds (for missile attack, it is
								// equal to the number of missiles; for non-missile (direct) attack, it is
								// number of reloads. and the total time doing attack will always be equal to
								// m_reloadTime * m_ordnance)
	enum eWeaponType m_weaponType;		// the type of weapon, needed to determine explosion effect

	bool m_disableAutoTarget;	// can stop UnitAI's from auto targeting this attack ability

	// if not NULL, then this is a turreted unit
	char *m_turretControllerName;
	int m_ICBMTargetingProbability;	// > 0 if this unit can attack ICBMs, in range [0,100]

	// @EE2X - Josh - 03/09/05 - added m_throwUnits
	bool m_throwUnits;		// if true, units within this blast radius will flinch or be thrown by the attack
ENDCLASS

DATACLASS(ABCD_AreaEffect)
	// what effects does this ability give me?
	LSizedArray< DBINDEX(DbAreaEffects) > m_effects;
ENDCLASS

DATACLASS_INHERIT(ABCD_SpecialPower, ABCD_AreaEffect)
	// does this ability let me disguise?
	bool	m_canDisguise;

	// text to print (to both the spotter and spotted player's screens)
	//when disguised unit is discovered
	DBINDEX(DbText) m_spotterTextDBI;
	DBINDEX(DbText) m_spottedTextDBI;

	// special power range
	float	m_range;
	// if greater than zero,
	// then this much tech points will be yielded when spy gathers intelligence.
	float m_techOnGatherIntel;

	// set to true if this spoecial power ability does not require
	// a power reserve
	bool m_doesNotRequirePowerReserve;
ENDCLASS

// convert enemy (into own unit) instead of killing enemy
DATACLASS_INHERIT(ABCD_ConvertAttack, ABCD_Attack)	// inherit from ABCD_Attack
	bool m_capture; // convert or capture?
	float m_convertTimeModifier;
ENDCLASS

DATACLASS(ABCD_PayloadAttack)
	enum eWeaponType m_weaponType;		// the type of weapon, needed to determine explosion effect

	// this effect, if nonzero, well be attached to all
	// units within range (areaDamageRadius) of this payload attack
	// see UnitAbilityPayloadAttack for details.
	// @NOTE: this implies that only unit attached area effects are allowed.
	LSizedArray< DBINDEX(DbAreaEffects) > m_damageEffects;
ENDCLASS

DATACLASS(ConvertableResourceTransfer)
	// the resource type (Tech and AllNaturalResource are valid)
	enum eResourceType m_resource;

	// percent transferred if capturing from a normal player
	float m_percentTransferred;

	// min/max fixed amount if capturing from a native tribe
	float m_NativeTribesAmountTransferredMin;
	float m_NativeTribesAmountTransferredMax;
ENDCLASS

DATACLASS(ABCD_Convertable)
	float m_damageRate;			// number of current hitpoints to decrement on each capture step
	float m_convertTimeModifier;// 'm_ConvertTimeModifier' x "base time to be converted" gives the actual time to get converted
	//int powerRequired;		// NOT CURRENTLY USED, power required to convert this unit, time to convert is equal to powerRequired / powerUseRate of ConvertAttack ability
	bool m_capture;				// convert or capture?

	// the following parameters are strictly capture related
	float m_garrisonedUnitModifier; // how much does each garrisoned unit decrement the conversion rate?
	float m_garrisonedUnitDamage;	// damage provided by each garrisioned unit each round of conversion.

	// resources you get from capturing
	LSizedArray< DC(ConvertableResourceTransfer) * > m_resourcesTransferred;
ENDCLASS

DATACLASS(ABCD_LOS)
	float range;		// radius for LOS, how many tiles out can we see. @TODO should this be a int or a float?
ENDCLASS

DATACLASS(ABCD_Construction)	// no invariant data for this ability
ENDCLASS

DATACLASS(ABCD_Build)
	float repairRate;	// hit points repaired per second
ENDCLASS

DATACLASS(ABCD_Produce)
	bool m_NoRallyFlag;			// don't use rally flag for this unit
	bool m_ProduceOrdnance;		// what is produced is just turning into our ordnance (rather than an actual unit)
ENDCLASS

DATACLASS(ABCD_Research)	// no invariant data for this ability
ENDCLASS

DATACLASS(ABCD_Connect)
	enum eComposite m_type;
	bool m_aidsPathing;			// does this unit aid pathing?
ENDCLASS


DATACLASS(StateTransition)
	// play this transient visual state,
	DBINDEX(DbVisualState) m_trans;

	// for this long
	float m_duration;

	// names of from and to state names
	DBINDEX(DbVisualState) m_from;
	DBINDEX(DbVisualState) m_to;

ENDVARS
	// two state transitions are considered equal
	// iff they have matching 'from' and 'to' state names
	//
	// you may be wondering why we care about StateTransition equality,
	// for the time being we want to ensure that there is only a single
	// transition for each directed edge.  maybe someday in the future
	// we may want to allow multiple transitions wich would be selected
	// by some weighted random function.  see DbUnit::PostLoad() for more on this.
	bool operator==(const StateTransition &in_rhs) const
	{
		return (m_from == in_rhs.m_from &&
			    m_to   == in_rhs.m_to);
	}
ENDCLASS

DATACLASS(ABCD_TemporaryAnimation)
	LSizedArray<DC(StateTransition)*> m_transitions;
ENDCLASS



// variants for terrain texture overlays
ENUM eOverlayVariant {
	kOverlayVariant_Invalid = -1,

	kOverlayVariant_NormalRural,
	kOverlayVariant_DamagedRural,
	kOverlayVariant_DestroyedRural,
	kOverlayVariant_NormalUrban,
	kOverlayVariant_DamagedUrban,
	kOverlayVariant_DestroyedUrban,

	kNumOverlayVariants,
};

DATACLASS(ABCD_TerrainOverlay)
	// this should be the first in a set of kNumOverlayVariants sprites
	// the sprited should be arranged in the sprite table in the order given
	// by eOverlayVariant
	DBINDEX(DbSprite) m_baseSprite;

	// variants for straight-piece endcaps:
	DBINDEX(DbSprite) m_baseSprite_capStart;
	DBINDEX(DbSprite) m_baseSprite_capEnd;
	DBINDEX(DbSprite) m_baseSprite_capBoth;
ENDCLASS

DATACLASS(ABCD_Resource)
	enum eResourceType type;		// type of resource
	int amount;	// amount of resource contained
	int maxNumOfWorkers;	// limits how many units can gather from it at any one time
	bool alwaysExhaustible;		// is this resource unit always exhaustible regardless of game setting?
ENDCLASS

DATACLASS_INHERIT(ABCD_ResourceFarm, ABCD_Resource)
	// no extra data of its own
ENDCLASS

DATACLASS(ABCD_ResourceDropoff)
	enum eResourceType type;		// what type of resource can be dropped off here, kResourceType_AllNaturalResource for all types.
	// @EE2X @MRC
	// Bonus to give to players when a unit drops off at this unit.
	// 1.0 = 100%
	float m_BonusPercentFood;
	float m_BonusPercentWood;
	float m_BonusPercentStone;
	float m_BonusPercentGold;
	float m_BonusPercentTin;
	float m_BonusPercentIron;
	float m_BonusPercentSaltpeter;
	// @NOTE No Oil and Uranium, because they're never dropped off.
ENDCLASS

DATACLASS(ABCD_GatherFarm)
	float foodRate;		// the gather rate MUST appear in the same order as in enum eResourceType
	float woodRate;
	float stoneRate;
	float goldRate;
	float tinRate;
	float ironRate;
	float saltpeterRate;
	float oilRate;
	float uraniumRate;

	float idleTechRate;		// while idle, can gather tech points

	float treeCuttingRange;	// how close to get to tree when cutting trees
	float otherRange;		// how close to get to other resource to gather
	float dropoffRange;		// how close to get to resource dropoff site when dropping off
	int carryLimit;			// maximum amount resource that can be carried (therefore, a citizen must drop it off once this limit is reached)

	// the following 2 members are for farming
	float farmRate;	// the amount of farm food gathered per second
	int farmCarryLimit;		// how much farm food can the unit carry (citezen will drop it off when this much food has been gathered)

	// For the special Forage unit ability, that lets a unit gather food to heal
	// itself.
	float m_LifePerFood;	// How much life to regain per unit of food foraged.

	float m_forageTreeRate;		// rate to gather food from (fruit?) trees
	float m_animalRate;			// rate to gather food from animals
ENDCLASS

// Explore Ability invariant data
DATACLASS(ABCD_Explore)
	//float dirDist;		// distance to travel in each randomly chosen direction
ENDCLASS


DATACLASS(ABCD_Heal)
	float healRate;		// healing rate: number of hit points regenerated per second
	float range;		// healing range: how close to the healee does the healer has to be
	float healRadius;	// Units within this radius of the target healee will also be healed.
	enum eUnitTypeAttr healType;		// what type of units can be healed
	
	// @EE2X @MRC
	// Some units can only give themselves heal goals if heal auto-cast is turned on.
	// Other units can always give themselves heal goals.
	bool m_requireAutoCastToSelfGoal;
ENDCLASS


//////////////////////////////
// @EE2X - DANIEL - 03/09/05
// created ABCD_Hero

DATACLASS(ABCD_Hero)
	// unit type this is a hero for
	DBINDEX(DbUnit) m_HeroForUnit;

	// class this is a hero for
	enum eHeroClass m_HeroClass;
ENDCLASS


DATACLASS(ABCD_Garrisonable)
	// places unit with this ability can garrison
	LSizedArray<enum eGarrisonType> m_garrisonTypes;
ENDCLASS

// simple dataclass - intended to be used to store unit type name and count pairs.
DATACLASS(TypeCountPair)
	char	*m_typeName;
	int		m_count;
ENDCLASS

DATACLASS(ABCD_Garrison)
	int numOfSlots;		// how many slots (1-2 slots per unit) are available
	enum eGarrisonType garrisonType;	// what type of units can be garrisoned here
	float attackBonus;		// how much percent more attack (for the unit holding the garrisoned units) per garrisoned slot
	float resourceBonus;			// for each resource dropoff/gathering, muliply by 1 + (resourceBonus * garrisoned slots)
	float healPoints;		// every second, hit points of garrisoned unit will increase by this much (up to maximum)

	// Some units gather resources when garrisoned.
	float gatherRate;					// Each second, gather the rate * garrisoned slots of the specified resource.
	enum eResourceType gatherType;		// What type of resource to gather.

	// ui parameters
	bool m_dontShowGarrisonButton;	// if true, the garrison button in the UI unit info area is not shown
	bool m_rightClickToGarrison;	// if true, you get the garrison cursor when mousing over the structure

	// load with the named unit upon creation (i.e. paratrooper plane)
	LSizedArray<DC(TypeCountPair)*> m_initialContents;
	int m_extraCapacity;	// extra capacity for units with initialContents (not the same as numOfSlots)

	// Some units, like oil derricks, switch to a different visual state
	// when garrisoned.
	DBINDEX(DbVisualState) m_GarrisonedVisualState;

	// The name of the garrison flag to use, if any.
	const char* m_GarrisonFlagModelName;
ENDCLASS

DATACLASS_INHERIT(ABCD_GarrisonParatrooper, ABCD_Garrison)
ENDCLASS

DATACLASS_INHERIT(ABCD_GarrisonTrade, ABCD_Garrison)
ENDCLASS

DATACLASS_INHERIT(ABCD_GarrisonAircraft, ABCD_Garrison)
ENDCLASS
//DATACLASS_INHERIT(ABCD_GarrisonAircraft, ABCD_Garrison)
//	int m_numStrikeMissions;	// how many strike missions can we have?
//	int m_numCAPMissions;		// how many combat air patrol missions can we have?
//ENDCLASS

DATACLASS(ABCD_Gate)
	// width of the gate door opening
	// @NOTE .ddf value will be multiplied by sqrt(2) to get world dims; this is
	// done in the UnitAbilityGate ctor
	float m_DoorWidth;
ENDCLASS

// city-specific area effect
DATACLASS_INHERIT(ABCD_AreaEffectCity, ABCD_AreaEffect)
	float m_CityRadius;
	float m_CityHealRate;
	float m_CityCaptureResistance;
ENDCLASS

DATACLASS(ABCD_Trade)
	DBINDEX(DbUnitTypeAttribute) m_MarketType;		// unit attribute of type of markets
	float  m_GoldPerTile;		// number of golds per tile distance between market
	float  m_TechPerTile;		// number of tech points per tile distance between market
	float m_TechBonusEpochDiff;			// // for each epoch difference, the tech points bonus for player BEHIND in epoch during trading
	LSizedArray<float> m_TechBonusLikelyhood;  //Based on the epoch difference, the likelyhood of gaining tech from this trade.
	bool m_ForeignTradeAllowed;	// Am I allowed to trade with other players?
	float m_timeToLoad;			// How long does this unit take to 'load' at a trade building.
ENDCLASS

#endif



