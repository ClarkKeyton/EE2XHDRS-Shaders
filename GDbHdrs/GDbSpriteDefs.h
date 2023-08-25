//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbSpriteDefs.h 17    2/19/05 5:55p Jwyman $
//
// DESCRIPTION:	GDbSpriteDef.h holds the parser-read class defs
//				for sprites.
//
// AUTHOR:		Rex Bradford
//
//===========================================================================

#ifndef GDBSPRITEDEF_H
#define GDBSPRITEDEF_H
#pragma once

#include "hdrmacros.h"

class GTexture;		// forward ref

FLAGS(kSpriteFlag)
// if set, generate mipmaps on load
const uint32 kSpriteFlag_MipMap		= 0x01;

// texture address flags; default means 'wrap'; 'mirror' and 'clamp' are exclusive
// these flags affect how a texture tiles and will not affect a basic (non-tiled) 
// application of the texture
const uint32 kSpriteFlag_MirrorU	= 0x0002;	
const uint32 kSpriteFlag_MirrorV	= 0x0004;
const uint32 kSpriteFlag_ClampU		= 0x0008;	
const uint32 kSpriteFlag_ClampV		= 0x0010;

// these flags flip u/v for a basic (non-tiled) application of the texture
const uint32 kSpriteFlag_FlipU		= 0x0020;
const uint32 kSpriteFlag_FlipV		= 0x0040;

// for a basic (non-tiled) application of the texture,
// this rotates the texture 90 degrees clockwise
// @NOTE rotation is applied *after* flipping
// @NOTE width/height should refer to the *unrotated* piece of texture
const uint32 kSpriteFlag_Rotate		= 0x0080;

// alpha modification flag for fading overlays
const uint32 kSpriteFlag_SubtractAlpha = 0x0100;

// sprite contains alpha
const uint32 kSpriteFlag_HasAlpha	= 0x0200;
ENDFLAGS

DATACLASS(GDbSpriteDef)
	char *m_filename;			// texture filename

	USERPTR(GTexture) m_texture; // ptr to loaded texture or NULL
	USER int m_refCount;		// reference count for loading
	USER bool m_bAnimated;		// keeps track if its a seasonal texture or not

	//These value are retrieve from the ddf.  They are pixel accurate for only the highest texture LOD.
	// That means if you change texture LOD, these uvs are not accurate anymore.
	int16		m_uInt;				// u-coord in pixels
	int16		m_vInt;				// v-coord in pixels
	int16		m_wInt;				// width in pixels
	int16		m_hInt;				// height in pixels									

	//Always accurate uv, infependent of the texture LOD.
	USER float  m_u;				// u-coord as float (computed at runtime, after db load)
	USER float  m_v;				// v-coord as float (computed at runtime)
	USER float  m_w;				// width as float (computed at runtime)
	USER float  m_h;				// height as float (computed at runtime)
	
	FLAGS(kSpriteFlag) uint32 m_flags;// should we generate mipmaps on load, etc
ENDVARS
	// These methods are implement in GDbSprite.cpp
	GTexture *Load();			// acquire sprite, return texture ptr (reference counts!)
	void Unload();				// release sprite, decr. refcount & drop if 0
	void CalcFloats();			// calculate float vars from int sizes and texture
ENDCLASS


#endif // GDBSPRITEDEF_H
