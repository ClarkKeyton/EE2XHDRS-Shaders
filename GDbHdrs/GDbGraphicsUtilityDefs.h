//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbGraphicsUtilityDefs.h 5     1/14/05 9:41p Dsproul $
//
// DESCRIPTION:		
//
// AUTHOR:			Daniel Sproul
//
//===========================================================================

#ifndef GDBGRAPHICSUTILITYDEFS_H
#define GDBGRAPHICSUTILITYDEFS_H
#pragma once


#include "hdrmacros.h"


///////////////////////////////////////
// data classes for UI texture packing

//
// a pair of source/target .csv files
//
DATACLASS(GDbSpritePackingCSVPair)
	const char *m_SourceCSV;
	const char *m_TargetCSV;
ENDCLASS

//
// overall configuration for a sprite-packing run
//
DATACLASS(GDbSpritePackingConfigDef)
	// array of sprite sets to use
	// these should be valid database names for GDbPackedTextureSetDef DC's
	LSizedArray<const char *> m_PackedTextureSets;
	USER LDynArray<int> m_aiPackedTextureSets;	// validated db indicies of the above
												// (initialized on PostLoad())

	// array of .csv file source/target pairs
	LSizedArray<DC(GDbSpritePackingCSVPair)*> m_SpriteCSVPairs;

	// set to true if you don't want the temp .csv removed
	bool m_DontRemoveTempCSV;

	// set to true if you want the obsoleted targa files to
	// be left out of the log
	bool m_DontLogObsoleteTargas;
ENDCLASS

//
// packing hint flags
//
FLAGS(kSpritePackingHint)
// force to rotate or to not rotate
const uint32 kSpritePackingHint_Rotate		= 0x0001;	// force do rotate
const uint32 kSpritePackingHint_DontRotate	= 0x0002;	// force do not rotate

// start searching from... 
const uint32 kSpritePackingHint_SearchStartRight	= 0x0004;
const uint32 kSpritePackingHint_SearchStartBottom	= 0x0008;
ENDFLAGS

//
// dataclass for pairing sprite with packing hint flags
//
DATACLASS(GDbSpriteWithPackingHint)
	DBINDEX(DbSprite) m_Sprite;
	FLAGS(kSpritePackingHint) uint32 m_Hints;	// hint flags
ENDCLASS

//
// a single set of sprites for packing into a single texture
//
DATACLASS(GDbPackedTextureDef)
	// .tga target for the created packed image
	const char *m_OutputTarga;

	// image dimensions to use (power-of-two, por favor!)
	int m_Width;
	int m_Height;

	// do we need alpha channel?
	bool m_UseAlpha;

	// min padding between each sprite in the packed texture
	int m_Padding;
	
	// set to true to suppress sorting sprites by size (they will just
	// be processed in the order given)
	bool m_DontSortBySize;

	// array of sprites to pack into this image
	LSizedArray<DBINDEX(DbSprite)> m_Sprites;

	// array of sprites with packing hints
	// the sprites listed here should also be in m_Sprites
	// @NOTE parallel data here, I know its kind of bad but generally speaking I
	// want m_Sprites to be as easy to fill in as possible...
	LSizedArray<DC(GDbSpriteWithPackingHint)*> m_SpriteHints;
ENDCLASS

//
// a set of sprite sets
//
DATACLASS(GDbPackedTextureSetDef)
	// sprite sets to pack
	LSizedArray<DC(GDbPackedTextureDef)*> m_PackedTextures;
ENDCLASS


#endif // GDBGRAPHICSUTILITYDEFS_H
