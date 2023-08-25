//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbVisualLodDefs.h 3     6/29/04 10:50a Hstpierre $
//
// DESCRIPTION:	DbSound.h contains database header info for the sound system.
//
// AUTHOR:		Rex Bradford
//
//===========================================================================

#ifndef DBVISUALLODDEFS_H
#define DBVISUALLODDEFS_H
#pragma once

#include "hdrmacros.h"

DATACLASS(DbVisualLodInfo)
	float	m_Low;			
	float	m_Medium;		
	float	m_High;
	float	m_VeryHigh;
	int		m_CheckBox;		
ENDCLASS

#endif //DBVISUALLODDEFS_H
