//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDBFontDefs.h 14    1/17/05 3:35p Rbradford $
//
// DESCRIPTION:	GDbFontDefs.h declares the dataclasses related to fonts.
//
// AUTHOR:      Rex E. Bradford
//
//===========================================================================

#ifndef GDBFONTDEFS_H
#define GDBFONTDEFS_H
#pragma once

#include "hdrmacros.h"
#include "LRGBA.h"

class GTextureTrueFont;	// forward ref to texture for loaded font

//	These flags are used to control various boolean properties of the font
FLAGS(kFontFlag)
	const uint32 kFontFlag_None		= 0x0000;
	const uint32 kFontFlag_Bold		= 0x0001;	// bold (for Windows CreateFont)
	const uint32 kFontFlag_Italic	= 0x0002;	// italic (for Windows CreateFont)
	const uint32 kFontFlag_Underline = 0x0004;	// underline (for Windows CreateFont)
	const uint32 kFontFlag_Outline	= 0x0008;	// outline (rasterizer does this)
	const uint32 kFontFlag_SmallCaps = 0x0010;	// smallcaps (rasterizer does this)
	const uint32 kFontFlag_AntiAlias = 0x0020;	// anti-alias (rasterizer does this)
	const uint32 kFontFlag_Kern		= 0x0040;	// kerning (rasterizer does this)
	// Remaining bits reserved for future expansion
ENDFLAGS

// This enum is used to categorize fonts by size (for tagged text system)

ENUM eFontSize {
	kFontSize_Tiny,		// tiny font size
	kFontSize_Small,	// small font size
	kFontSize_Medium,	// medium font size
	kFontSize_Large,	// large font size
	kFontSize_Huge,		// huge font size

	kFontSize_Num,
};

//	This enum is used to set the min and max texture sizes (width/height)
//  NOTE: IF YOU FIDDLE WITH THIS LIST, UPDATE THE INLINE METHODS BELOW IT!!
ENUM eFontTextureSize {
	kFontTextureSize_ts64x64,		// 64 x 64 (w x h)
	kFontTextureSize_ts128x64,		// 128 x 64
	kFontTextureSize_ts128x128,		// 128 x 128
	kFontTextureSize_ts256x128,		// 256 x 128
	kFontTextureSize_ts256x256,		// 256 x 256
	kFontTextureSize_ts512x256,		// 512 x 256
	kFontTextureSize_ts512x512,		// 512 x 512
	kFontTextureSize_ts1024x512,	// 1024 x 512
	kFontTextureSize_ts1024x1024,	// 1024 x 1024
	kNumFontTextureSizes,
};

inline GetFontTextureSizeWidth(enum eFontTextureSize in_size)
{
	static int s_width[] = {64,128,128,256,256,512,512,1024,1024};
	ASSERT(in_size < kNumFontTextureSizes);
	return s_width[in_size];
};

inline GetFontTextureSizeHeight(enum eFontTextureSize in_size)
{
	static int s_height[] = {64,64,128,128,256,256,512,512,1024};
	ASSERT(in_size < kNumFontTextureSizes);
	return s_height[in_size];
};

//	This enum is used when setting the initial set of chars to rasterize.

ENUM eFontInitialSet {
	kFontInitialSet_None,		// no initial chars, fully dynamic
	kFontInitialSet_Alnum,		// upper and lowercase letters & digits
	kFontInitialSet_ASCII,		// ASCII chars 32-127
	kFontInitialSet_TextDb,		// all chars in text database (DON'T USE WITH ASIAN FONTS!)
	kNumFontInitialSets,
};

inline const char *GetFontInitialSetString(eFontInitialSet in_set)
{
	static const char *s_setName[] = {"none","alnum","ascii","txdb"};
	ASSERT(in_set < kNumFontInitialSets);
	return s_setName[in_set];
};

//	GDbFontDef describes a truetype font, including all arguments needed
//	to be supplied to the constructor of a GTextureTrueFont.

DATACLASS(GDbFontDef)
	LSizedArray<const char *> m_fontName;		// font name
	LSizedArray<const char *> m_asianFontName;	// font name if Asian language
	int m_pointSize[6];							// point size at 800x600, 1024x768, 1600x1200
	int m_smallCapsPointSize[6];				// point size of small caps (if using small caps)
	FLAGS(kFontFlag) uint32 m_flags;			// font flags
	enum eFontSize m_fontSize;					// the size that this font is
	enum eFontInitialSet m_initialSetWestern;		// char initial set for Western fonts
	enum eFontTextureSize m_minTextureSizeWestern;	// minimum width/height of texture
	enum eFontTextureSize m_maxTextureSizeWestern;	// maximum width/height of texture
	enum eFontInitialSet m_initialSetAsian;			// initial char set for Asian fonts
	enum eFontTextureSize m_minTextureSizeAsian;	// minimum width/height of texture
	enum eFontTextureSize m_maxTextureSizeAsian;	// maximum width/height of texture
	// These are user fields
	USER int m_refCount;		// reference count (user field)
	USERPTR(GTextureTrueFont) m_fontTexture;	// ptr to font texture
ENDCLASS

//	GDbFontStyleDef describes a font style, which consists of a font table index
//	and the colors used to draw the text in.

DATACLASS(GDbFontStyleDef)
	DBINDEX(DbFont) m_font;		// index into DbFont table
	LRGBA m_textColor;			// normal text color
	LRGBA m_disableColor;		// disabled text color
	LRGBA m_linkColor;			// link color (for links, uses hilite color if mouseover)
	LRGBA m_hiTextColor;		// highlighted text color
	bool m_hilite;				// is there a highlight (rollover) color?
	bool m_dropShadow;			// is there a dropshadow?
	int m_dropShadowOffset[6];	// dropshadow offset at 3 resolutions
	LRGBA m_dropColor;			// dropshadow color
	LRGBA m_dropDisableColor;	// disabled dropshadow color
	LRGBA m_hiDropColor;		// highlighted dropshadow color
ENDCLASS

#endif // GDBFONTDEFS_H
