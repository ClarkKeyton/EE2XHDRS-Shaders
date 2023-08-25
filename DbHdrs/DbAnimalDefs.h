//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbAnimalDefs.h 4     6/16/04 4:50p Kwasserman $
//
// DESCRIPTION:   
//
// AUTHOR:        Ben Morse
//
//===========================================================================

#ifndef DBANIMALDEFS_H
#define DBANIMALDEFS_H
#pragma once

#include "HdrMacros.h"

// Seems like there should be a set of 'utility' dataclasses, but hey.
DATACLASS(DbIntegerInterval)
	int m_min;
	int m_max;
ENDCLASS

ENUM eAnimalType {
	kAnimalType_Predator,
	kAnimalType_Domesticated,
	kAnimalType_Wild,
	kNumAnimalTypes,
};

// A DbAnimalDef entry must have the same name as the UnitType it's an
// entry foor.
DATACLASS(DbAnimalDef)
	// When it's dead (food resource), it turns into:
	DBINDEX(DbUnit) m_DeadUnitType;

	// is it a predator, a wild animal, or a domesticated one?
	enum eAnimalType m_AnimalType;

	// Roughly how far this will wander from its (or its herds) original
	// placement point.  They don't migrate.  They'll flee temporarily
	// when fired upon, but they always come back to within this radius
	// of their home point.
	float m_WanderRadius;

	// Every approximately m_TimeBetweenWandering seconds, they'll get a
	// new move order.
	float m_TimeBetweenWandering;

	// If it's a Wild animal, all the 'herd' stuff should be nonzero.
	// Otherwise it can be omitted since it doesn't apply.

	// At creation time, a max herd size is calculated and stored
	// with the herd, and they should never exceed this.
	DC(DbIntegerInterval) *m_MaxHerdSize;

	// If there are X animals in the herd, a new one will be created
	// every ReproPeriod/X seconds, up to MaxHerdSize.
	float m_ReproPeriod;

	// This will be set in postload - it's the DBINDEX(DbUnit) of the
	// unit type this entry is for.  We get it by looking up the unit
	// type of the same name as this def.
	USER int m_iUnitDBIndex;
ENDCLASS

#endif // DBANIMALDEFS_H
