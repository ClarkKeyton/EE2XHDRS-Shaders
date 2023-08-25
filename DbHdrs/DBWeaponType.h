//====================================================================
// Copyright 2003 Mad Doc Software, LLC. All rights reserved.
// $Header: /src/EE2/DbHdrs/DBWeaponType.h 5     1/23/04 4:37p Mcorthell $
// $Modtime: 1/23/04 3:45p $
//====================================================================
#ifndef DBWeaponType_H
#define DBWeaponType_H
#pragma once

// @NOTE When you change this enum, you should probably also update
// kWeaponTypeFlag in DbVisualDefs.h.

ENUM eWeaponType {
	kWeaponType_None				= 0,		// not a meaningful category, just serving as a default value
	kWeaponType_Melee				= 1,
	kWeaponType_LightProjectile		= 2,
	kWeaponType_MediumProjectile	= 4,
	kWeaponType_Missile				= 8,
	kWeaponType_Beam				= 16,
	kWeaponType_Nuke				= 32,

	// This is kind of confusing.
	// These weapon types pertain to the death of ammo units.  Ammo units unclude
	// arrows, trebuchet stones, artillery shells, bombs, etc.  These weapo types
	// are used to indicate what kind of object the ammo collided with when it
	// died.  The explosion system (VisualExplosionMapper) makes use of the weapon
	// type to determine which explosions to tie to the death of the unit.  This
	// is not so important for arrows, but it is important for any bombs and
	// artillery shells.
	// If you want to try and rationalize it, a bomb dies when it hits something.
	// The bomb is, therefore, killed by whatever it hit.  So, if a bomb hits a
	// building, then the building is the weapon that killed the bomb.
	// If you want to yell at someone about this, talk to Matt Corthell.
	kWeaponType_Building			= 64,
	kWeaponType_MobileUnit			= 128,
	kWeaponType_Terrain				= 256,

	kWeaponType_Any					= 512,

	// This is really, really the number of weapon types.  For use in integer
	// iteration, and stuff.
	kNumWeaponType					= 11,
};

#endif  // DBWeaponType_H