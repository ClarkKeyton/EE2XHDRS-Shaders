//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbWonderDefs.h 2     6/22/04 7:53p Aandkjar $
//
// DESCRIPTION:	DbWonderTrackerDefs.h defines dataclasses used by the wonder tracker
//				primarily to attach/detach area effects to the wonder's owning player.
//
// AUTHOR:		Andrew Andkjar
//
//===========================================================================

#ifndef DBWONDERDEFS_H
#define DBWONDERDEFS_H
#pragma once

#include "hdrmacros.h"

//	IMPORTANT NOTE:  THE USE OF THIS DATACLASS IN MISCGAMESTATE.H PRECLUDES
//	YOU FROM PUTTING ANY POINTERS OR SUCH THINGS INTO IT.  LIMIT THIS TO
//	BOOLS, INTEGERS, FLOATS, ENUMS, AND EMBEDDED ARRAYS OF THESE PRIMITIVES.
//	NO STRINGS, EMBEDDED DATACLASS OBJECTS, OR SIZED ARRAYS.  IF THIS RESTRICTION
//	IS TOO LIMITING, THE AUDIOSETTINGS OBJECT MUST BE MODIFIED TO USE A POINTER
//	TO AN OBJECT OF THIS DATACLASS INSTEAD OF AN ACTUAL INSTANCE OF ONE, AND
//	MUST USE LDATACLASS METHODS TO MANAGE THE PTRS PROPERLY.

DATACLASS(DbWonderPlayerEffect)
	// what wonder does this work for?
	DBINDEX(DbUnit) m_typeName;
	
	// what area effect is to be attached to player that owns the wonder?
	DBINDEX(DbAreaEffects) m_effectName;
ENDCLASS


DATACLASS(DbWonderInfo)
	// collection of all wonder-effect pairs
	LSizedArray<DC(DbWonderPlayerEffect)*> m_playerEffects;
ENDCLASS

#endif // DBWONDERDEFS_H
