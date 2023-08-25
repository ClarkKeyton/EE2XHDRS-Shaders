  //===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbTooltipDefs.h 1     9/24/04 11:10a Jdunlop $
//
// DESCRIPTION:	GDbWidgetDefs.h defines the dataclass defs for widgets.
//
// AUTHOR:      Jason Dunlop
//
//===========================================================================

#ifndef GDBTOOLTIPDEFS_H
#define GDBTOOLTIPDEFS_H
#pragma once

#include "hdrmacros.h"


// Tooltips mode
ENUM eTooltipsMode {
	kTooltipsMode_Off,			// no tooltips
	kTooltipsMode_Concise,		// just concise tooltips
	kTooltipsMode_Verbose,		// just verbose tooltips
	kTooltipsMode_Both,			// concise and verbose
};

#endif // GDBTOOLTIPDEFS_H
