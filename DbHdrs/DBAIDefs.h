//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DBAIDefs.h 1     8/06/04 2:11p Tteich $
//
// DESCRIPTION:   Database headers for general AI stuff
//
// AUTHOR:        Tara Teich
//
//===========================================================================

#ifndef DBAIDEFS_H
#define DBAIDEFS_H
#pragma once

#include "hdrmacros.h"

// we have one of these for every personality dll we create, then we can specify
//		which regions and difficulties that personalities is good for
DATACLASS(DbAIPersonalityDef)
	LSizedArray<enum eCivilizationRegion> m_regions;		// which regions this personality is good for
	LSizedArray<enum eDifficultySetting> m_difficulties;	// which difficulties this is good for
ENDCLASS

#endif // DBAIDEFS_H