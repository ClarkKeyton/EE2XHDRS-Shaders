//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbWidgetStyleDefs.h 13    8/19/04 9:58a Rbradford $
//
// DESCRIPTION:   GDbWidgetStyleDefs.h has widget style def classes.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef GDBWIDGETSTYLEDEFS_H
#define GDBWIDGETSTYLEDEFS_H
#pragma once

#include "hdrmacros.h"
#include "GDbWidgetDefs.h"
#include "LRGBA.h"

//	GDbWidgetFrameStyleDefs are used to control the optional frames which
//	may appear around a widget.

// FrameStylePosition governs how the frame is positioned around its widget;
// either outside the widget screen area, inside the screen area, or in-between
//
// @NOTE currently child widgets will draw over the frame, so if you have widgets 
// close to the edge of a widget (eg. a titlebar) and you specify an inner/middle
// frame, the titlebar will draw in front of the frame where they overlap
//
// @TODO find a good way of addressing this problem...

ENUM eGFrameStylePosition {
	kGFrameStylePosition_Outer,		// default -- outside widget screen area
	kGFrameStylePosition_Middle,	// in between...
	kGFrameStylePosition_Inner,		// inside widget screen area
};

// FrameStyleType determines the graphical appearance of the frame
// for Basic, the default type, the colors specified are interpolated
// for the other types the colors are ignored and a set of one or more sprites is used
// instead; the distinction between tiling and stretching should be clear;
//
// SimpleCornerStretchedEdge, SimpleCornerTiledEdge:
// @IMPORTANT use textures appropriate for UL corner
//
//		ABBBBBA
//		B     B
//		B     B
//		B     B
//		ABBBBBA
//
// ExtendedCornerStretchedEdge, ExtendedCornerTiledEdge:
// @IMPORTANT use textures appropriate for UL corner
//
//		ABCCCBA
//		B     B
//		C     C
//		C     C
//		C     C
//		B     B
//		ABCCCBA
//
// FourCornersFourTiledEdges:
//
//		AEEEEED
//		F     H
//		F	  H
//		F     H
//		BGGGGGC
//
// @IMPORTANT
// if you are tiling your edge texture, the whole tiled extent (either vert or horiz) of the texture is going
// to wrap, meaning you should make the image you want to tile fill the entire tiled dimension

ENUM eGFrameStyleType {
	kGFrameStyleType_Basic,							// default type, just interp. of specified colors
	kGFrameStyleType_SimpleCornerStretchedEdge,		// two sprites (corner, edge)
	kGFrameStyleType_SimpleCornerTiledEdge,			// two sprites (corner, edge)
	kGFrameStyleType_ExtendedCornerStretchedEdge,	// three sprites (corner, corner extension, edge)
	kGFrameStyleType_ExtendedCornerTiledEdge,		// three sprites (corner, corner extension, edge)
	kGFrameStyleType_FourCornersFourTiledEdges,		// eight sprites (4 corners, 4 edges)
};

DATACLASS(GDbWidgetFrameStyleDef)
	int	m_width[6];			// width of frame in pixels, at each of 3 resolutions
	enum eGFrameStylePosition m_position;	// how the frame is positioned on its widget
	enum eGFrameStyleType m_frameStyleType;	// graphical type of frame to use
	DBINDEX(DbSprite) m_sprite;			// first in a set of sprites for non-Basic frame types
	LRGBA m_topOuterColor;		// top outer color
	LRGBA m_topInnerColor;		// top inner color
	LRGBA m_leftOuterColor;		// left outer color
	LRGBA m_leftInnerColor;		// left inner color
	LRGBA m_bottomOuterColor;	// bottom outer color
	LRGBA m_bottomInnerColor;	// bottom inner color
	LRGBA m_rightOuterColor;	// right outer color
	LRGBA m_rightInnerColor;	// right inner color
ENDVARS

	// get ptr to first color to use as an array (const + non-const versions)
	LRGBA *GetColorsArray()
	{
		return &m_topOuterColor;
	}
	const LRGBA *GetColorsArray() const
	{
		return &m_topOuterColor;
	}

ENDCLASS

//	GDbWidgetSoundStyleDefs are used to specify the UI sounds to make when
//	a widget has various events happen to it.  Entries in this table are
//	accessed via "snd=xxxxx" in the argument list.

DATACLASS(GDbWidgetSoundStyleDef)
	DBINDEX(DbSound) m_sndLButtDown;	// sound to play on left button depress
	DBINDEX(DbSound) m_sndLButtUp;		// sound to play on left button depress
	DBINDEX(DbSound) m_sndRButtDown;	// sound to play on left button depress
	DBINDEX(DbSound) m_sndRButtUp;		// sound to play on left button depress
	DBINDEX(DbSound) m_sndLButtSel;		// sound to play on selection, with left button
	DBINDEX(DbSound) m_sndRButtSel;		// sound to play on selection, with right button
	DBINDEX(DbSound) m_sndLButtDblClick;	// sound to play on mouse double-click
	DBINDEX(DbSound) m_sndEnter;		// sound to play on entry of mouse into widget
	DBINDEX(DbSound) m_sndLeave;		// sound to play when mouse leaves widget
	DBINDEX(DbSound) m_sndExtra1;		// extra sound #1, class-specific
	DBINDEX(DbSound) m_sndExtra2;		// extra sound #2, class-specific
ENDCLASS

//	GDbWidgetStyleDefs are used to set default styling behavior for widgets.
//	There is a database for these, and then a "styleset" system for hooking
//	up default styles based on widget class.

DATACLASS(GDbWidgetStyleDef)
	DBINDEX(DbSprite) m_sprite;					// index of sprite to use as background
	enum eGButtonStyle m_buttonStyle;			// button style
	DBINDEX(DbWidgetFrameStyle) m_frameStyle;	// index of frame style
	DBINDEX(DbFontStyle) m_fontStyle;			// font and font style
	enum eGTextJustify m_textJustify;			// text justification enum
	int16 m_xTextOff;							// x text offset from justified pos
	int16 m_yTextOff;							// y text offset from justified pos
	const char *m_argString;	// widgetclass-specific string argument
	USERPTR(LArgSet) m_argSet;	// set of name=value arguments, parsed from m_argString
ENDVARS
	// copy constructor
	GDbWidgetStyleDef(const GDbWidgetStyleDef &in_style);

	// Destructor: clean up argset
	~GDbWidgetStyleDef();

	// BuildArgSet() builds the argset object from the argstr field
	void BuildArgSet();

	// FreeArgSet() frees up the argset object
	void FreeArgSet();
ENDCLASS


//
// simple DC providing style name and style def (used by GDbWidgetStyleSetDef)
//
DATACLASS(GDbWidgetStyleMappingDef)
	const char *m_name;
	DBINDEX(DbWidgetStyle) m_style;
ENDCLASS

//
// simple DC that is an array of style mappings (used by GDbScreenDef)
//
DATACLASS(GDbWidgetStyleSetDef)
	LSizedArray<DC(GDbWidgetStyleMappingDef) *> m_styles;
ENDCLASS



#endif // GDBWIDGETSTYLEDEFS_H
