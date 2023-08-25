  //===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbWidgetDefs.h 56    12/22/04 12:58p Dsproul $
//
// DESCRIPTION:	GDbWidgetDefs.h defines the dataclass defs for widgets.
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef GDBWIDGETDEFS_H
#define GDBWIDGETDEFS_H
#pragma once

#include "hdrmacros.h"

// forward ref
class LArgSet;



// flags for working with eWidgetAnchorType
enum eAnchorFlags {
	kAnchorFlags_IsAnchored   = 0x01,

	kAnchorFlags_SourceBottom = 0x02,
	kAnchorFlags_SourceRight  = 0x04,
	kAnchorFlags_TargetBottom = 0x08,
	kAnchorFlags_TargetRight  = 0x10,
};

// flags specifying anchor relationship between widgets
// target is the widget you are anchoring, source is the widget you
// are anchoring to
//
// you specify which corner for each, then xOff, yOff are the offsets
// between those two corners
//
// if the anchor widget does not exist at the time of creation of target,
// you are kind of screwed
//
// if you specify a second anchor, then the width and/or height of the
// widget are set dynamically in order to satisfy all contraints
ENUM eAnchorType {
	kAnchorType_NoAnchor		 = 0x00,	// default

	// anchor upper-left corner
	kAnchorType_SourceULTargetUL = 0x01,
	kAnchorType_SourceLLTargetUL = 0x03,
	kAnchorType_SourceURTargetUL = 0x05,
	kAnchorType_SourceLRTargetUL = 0x07,

	// anchor lower-left corner
	kAnchorType_SourceULTargetLL = 0x09,
	kAnchorType_SourceLLTargetLL = 0x0B,
	kAnchorType_SourceURTargetLL = 0x0D,
	kAnchorType_SourceLRTargetLL = 0x0F,

	// anchor upper-right corner
	kAnchorType_SourceULTargetUR = 0x11,
	kAnchorType_SourceLLTargetUR = 0x13,
	kAnchorType_SourceURTargetUR = 0x15,
	kAnchorType_SourceLRTargetUR = 0x17,

	// anchor lower-right corner
	kAnchorType_SourceULTargetLR = 0x19,
	kAnchorType_SourceLLTargetLR = 0x1B,
	kAnchorType_SourceURTargetLR = 0x1D,
	kAnchorType_SourceLRTargetLR = 0x1F
};


//	Button styles: determines how many sprite images there are in what layout, so
//	widget state can be translated into proper sprite image.  This is independent
//	of the font style, which also has a "highlight color" used for rollovers.

ENUM eGButtonStyle {
	kGButtonStyle_None		= 0,		// just like Static, but can be overridden by default
	kGButtonStyle_Static	= 0x0001,	// sprite doesn't change
	kGButtonStyle_TwoState	= 0x0002,	// sprite has two states (value 0 and !0)
	kGButtonStyle_Rollover	= 0x0004,	// sprite has rollover pair
	kGButtonStyle_Flash		= 0x0008,	// separate sprite for flashing
	kGButtonStyle_Disabled	= 0x0010,	// sprite has an extra image for disabled

	///////////////////////////////////////////////////////
	// The following are derived from the above
	// @TODO use parser read FLAGS and we won't need this nonsense

	// variants with flashing
	kGButtonStyle_TwoStateFlash	= 0x000A,	// two states of sprites, plus flashing (3 total)
	kGButtonStyle_RolloverFlash	= 0x000C,	// rollver pair plus 3rd for flashing (3 total)
	
	// variants with disabled
	kGButtonStyle_TwoStateDisabled	= 0x0012,	// two states of sprites, plus disabled (3 total)
	kGButtonStyle_RolloverDisabled	= 0x0014,	// rollver pair plus disabled (3 total)

	// variants with flashing and disabled
	kGButtonStyle_TwoStateFlashDisabled	= 0x001A,	// two states of sprites, plus flashing, plus disabled (4 total)
	kGButtonStyle_RolloverFlashDisabled	= 0x001C,	// rollver pair plus 3rd for flashing, plus disabled (4 total)

	// two-state rollover variants
	kGButtonStyle_TwoStateRollover				= 0x0006,	// two states of sprites, each with rollover (4 total)
	kGButtonStyle_TwoStateRolloverFlash			= 0x000E,	// two pairs, plus 5th for flashing (5 total)
	kGButtonStyle_TwoStateRolloverDisabled		= 0x0016,	// two pairs, plus 5th for disabled (5 total)
	kGButtonStyle_TwoStateRolloverFlashDisabled = 0x001E,	// two pairs, plus 5th for flashing, plus disabled (6 total)
};

//
// util func to get the number of sprites for a given button style
//
inline int GetNumSpritesForButtonStyle(eGButtonStyle in_eButtonStyle)
{
	// start with 1 sprite
	int iNumSprites = 1;
	
	// two-state doubles
	if(in_eButtonStyle & kGButtonStyle_TwoState)
		iNumSprites *= 2;
	
	// rollover doubles
	if(in_eButtonStyle & kGButtonStyle_Rollover)
		iNumSprites *= 2;
	
	// disabled adds 1 to the total set
	if(in_eButtonStyle & kGButtonStyle_Disabled)
		iNumSprites++;

	return iNumSprites;
}


//	Text wrap enums

ENUM eGTextWrap {
	kGTextWrap_None,		// no wrap
	kGTextWrap_Char,		// wrap chars
	kGTextWrap_Word,		// wrap words
};

//	Text justification flags

ENUM eGTextJustify {
	kGTextJustify_None			= 0,			// just like Left, but can be overridden by default
	kGTextJustify_Left			= 0x0001,		// left-justify (top)
	kGTextJustify_Center		= 0x0002,		// center x (top)
	kGTextJustify_Right			= 0x0004,		// right-justify (top)
	kGTextJustify_Mid			= 0x0008,		// mid-justify
	kGTextJustify_Bottom		= 0x0010,		// bottom-justify
	// The rest of these are just derived
	kGTextJustify_LeftMid		= 0x0009,		// same as just mid
	kGTextJustify_CenterMid		= 0x000A,		// center- and mid-justify
	kGTextJustify_RightMid		= 0x000C,		// right- and mid-justify
	kGTextJustify_LeftBottom	= 0x0011,		// same as just bottom
	kGTextJustify_CenterBottom	= 0x0012,		// center- and bottom-justify
	kGTextJustify_RightBottom	= 0x0014,		// right- and bottom-justify
};

//	Widget definition dataclass

DATACLASS(GDbWidgetDef)
	//enum eGWidgetClass m_class;		// widget class
	const char *m_className;

	// parenting and positioning info
	const char *m_parentName;		// parent widget's name
	bool  m_IncAccumulationDepth;	// should this widget be flagged to increment the accumulation depth?
	const char *m_anchorName1;		// name of first widget to anchor to (parent if null and anchoring)
	enum eAnchorType m_anchorType1;	// nature of anchoring relationship
	const char *m_anchorName2;		// name of second widget to anchor to (parent if null and anchoring)
	enum eAnchorType m_anchorType2;	// nature of anchoring relationship
	int16 m_xOff;					// x-offset from first anchor
	int16 m_yOff;					// y-offset from first anchor
	int16 m_xOffAnchor2;			// x-offset from second anchor
	int16 m_yOffAnchor2;			// y-offset from second anchor
	int16 m_width;					// width
	int16 m_height;					// height

	// display parameters
	DBINDEX(DbSprite) m_sprite;			// sprite to draw
	DBINDEX(DbWidgetFrameStyle) m_frameStyle;	// style of frame if any
	enum eGButtonStyle m_buttonStyle;	// button style for sprite
	DBINDEX(DbFontStyle) m_fontStyle;	// font and font style
	enum eGTextJustify m_textJustify;	// text justification enum
	int16 m_xTextOff;					// x text offset from justified pos
	int16 m_yTextOff;					// y text offset from justified pos
	DBINDEX(DbText) m_text;				// label text

	// tooltips
	DBINDEX(DbText) m_tooltip;			// tooltip text
	DBINDEX(DbText) m_verboseTooltip;	// verbose tooltip (index into text db)

	// behaviour parameters
	bool m_ignoreMouse;			// ignore the mouse
	const char *m_cmdString;	// command string to send when clicked

	// extra arguments
	const char *m_argString;	// widgetclass-specific string argument
	USERPTR(LArgSet) m_argSet;	// set of name=value arguments, parsed from m_argString
ENDVARS
	// default constructor
	GDbWidgetDef();

	// copy constructor
	GDbWidgetDef(const GDbWidgetDef &in_source);

	// Use this constructor to specify some values
	GDbWidgetDef(const char *in_szClassName, int in_xOff, int in_yOff, int in_width, int in_height, 
		const char *in_szSpriteName = NULL, const char *in_szFontStyleName = NULL, 
		enum eGTextJustify in_justify = kGTextJustify_None,int in_xTextOff = 0, int in_yTextOff = 0);

private:
	void Init();	// fill in with default values, used for construction

public:

	// Destructor: clean up argset
	~GDbWidgetDef();

	//
	// copy -- bit copy is not good enough because of the argset
	//
	// @NOTE there is currently no operator=() here, so if you make an '=' assignment
	// it will bit copy; this can get you into trouble because of the argset, even though
	// sometimes it is what you want
	//
	void Copy(const GDbWidgetDef &in_source);

	// set arg string and build the arg set
	void SetArgString(const char *in_szArgString)
	{
		m_argString = in_szArgString;
		FreeArgSet();
		BuildArgSet();
	}

	// BuildArgSet() builds the argset object from the argstr field
	void BuildArgSet();

	// FreeArgSet() frees up the argset object
	void FreeArgSet();

	// see if this widget def is of a given class...
	bool IsClass(const char *in_szClassName) const;

ENDCLASS

#endif // GDBWIDGETDEFS_H
