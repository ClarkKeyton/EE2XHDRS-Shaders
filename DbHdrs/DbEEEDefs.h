//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbEEEDefs.h 1     4/19/04 1:39p Jdunlop $
//
// DESCRIPTION:   Empire Earth Encyclopedia DB defs
//
// AUTHOR:        Jason Dunlop
//
//===========================================================================

#ifndef DBEEEDEFS_H
#define DBEEEDEFS_H
#pragma once

#include "hdrmacros.h"

DATACLASS(DbEEESidebarInfo)
	DBINDEX(DbText)	m_displayName;
	const char*		m_parentFolder;
	bool			m_isFolder;
	const char*		m_pageLink;
	const char*		m_args;
ENDCLASS

#endif // DBEEEDEFS_H
