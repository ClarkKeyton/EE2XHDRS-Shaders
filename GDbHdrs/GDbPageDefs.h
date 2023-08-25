//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbPageDefs.h 8     4/20/04 4:39p Jdunlop $
//
// DESCRIPTION:   GDbPageDefs.h has db definitions for the Page system.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef GDBPAGEDEFS_H
#define GDBPAGEDEFS_H
#pragma once

#include "hdrmacros.h"
#include "LDataObj.h"

// a page element's anchoring type
ENUM ePageElemAnchorType {
	kPageElemAnchorType_Default,		// use whatever is specified in csv file
	kPageElemAnchorType_PrevName,		// anchor to the widget last created with the same name
	kPageElemAnchorType_PrevCreated,	// anchor to the widget that was last created
};

//	The GDbPageLayout dataclass describes a page layout

DATACLASS(GDbPageLayout)
	DBINDEX(DbWidget) m_firstWidget;	// index of first widget in layout
	DBINDEX(DbWidget) m_lastWidget;		// index of last widget in layout
ENDCLASS

//	The GDbPageElem dataclass describes a page element customization record

DATACLASS(GDbPageElem)
	const char *m_widgetName;			// which widget are we customizing?
	uint16 m_indexCopy;					// if copy, incrementing index of that copy (or 0)
	enum ePageElemAnchorType m_anchorToPrev;// how this widget should anchor to its siblings
	uint16 m_width;						// width override (or 0)
	uint16 m_height;					// height override (or 0)
	DBINDEX(DbSprite) m_sprite;			// sprite override (or 0)
	DBINDEX(DbText) m_text;				// text replacement (or 0)
	DBINDEX(GDbFontStyle) m_fontStyle;	// font style override index (or 0)
	DBINDEX(DbText) m_tooltip;			// tooltip (or 0)
	DBINDEX(DbText) m_verboseTooltip;	// verbose tooltip (or 0)
	const char *m_argString;			// string argument (add, not override) or NULL
ENDCLASS

//	The GDbPageContents dataclass describes an instantiation of a page

DATACLASS(GDbPageContents)
	DBINDEX(DbPage) m_pageLayout;		// index of page layout to use
	DBINDEX(DbPage) m_pageTOC;			// page which goes in TOC sidebar
	DBINDEX(DbText) m_pageTitle;		// page title
	bool m_retainOnArgChange;			// retain page if only arg changes
	LSizedArray<DC(GDbPageElem)*> m_elems;	// array of page elements
ENDCLASS

#endif // GDBPAGEDEFS_H
