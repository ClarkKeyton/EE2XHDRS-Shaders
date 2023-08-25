//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbScreenDefs.h 4     2/09/05 3:21p Dsproul $
//
// DESCRIPTION:	
//
// AUTHOR:      Daniel Sproul
//
//===========================================================================

#ifndef GDBSCREENDEFS_H
#define GDBSCREENDEFS_H
#pragma once

#include "hdrmacros.h"


//
// simple DC for setting screen parameters
// @TODO extend to add root widget, range of widgets to create, etc.
// @TODO use this to make a GScreenFactory analogous to GWidgetFactory...
//
DATACLASS(GDbScreenDef)
	DBINDEX(DbWidgetStyleSet)	m_styleSet;					// style set for most widgets
	DBINDEX(DbWidgetStyle)		m_conciseTooltipStyle;		// style to use for concise tooltip widget
	DBINDEX(DbWidget)			m_verboseTooltipWidget;		// widget def to use for verbose tooltip widget
	DBINDEX(DbWidget)			m_messageBoxWidget;			// widget def to use for message box
	bool						m_dontAllowUIBinSorter;		// if true, use of UI bin sorter is suppressed for this screen
ENDCLASS



#endif // GDBSCREENDEFS_H
