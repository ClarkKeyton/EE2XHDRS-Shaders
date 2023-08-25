//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbGraphicConvertDefs.h 5     9/20/04 1:10p Shanti $
//
// DESCRIPTION:   DbGraphicConvertDefs.h holds the dataclasses for records
//				  which control conversion of textures and models.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBGRAPHICCONVERTDEFS_H
#define DBGRAPHICCONVERTDEFS_H
#pragma once

#include "hdrmacros.h"

//	Texture conversion:
//
//	This dataclass is used to represent entries specifying which folders of
//	textures get non-default conversion options.  The defaults are:
//
//		noconvert	= off		// if on, means don't create DX version at all
//		compression	= on		// if off, don't apply DX compression
//		mipmaps		= on		// if off, don't generate mipmaps
//		genalpha	= off		// if on, generate alpha bits
//		binaryalpha = on		// if on uses one bit for alpha, Dxt1 texture format

DATACLASS(DbTextureConvertDef)
	const char *m_pFolderName;				// folder name
	bool m_bNestedFolders;					// do nested folders too?
	bool m_bNoConvert;						// don't even create a cached converted version
	bool m_bCompress;						// compress?
	bool m_bMipMaps;						// mipmaps?
	bool m_bGenAlpha;						// generate alpha?
	bool m_bBinaryAlpha;					// use binary alpha ?
ENDCLASS

//	Model conversion:
//
//	This dataclass is used to represent entries specifying which folders of
//	textures get non-default conversion options.
//
//	For defaults, see DbModelConvert.cpp
//
//	IMPORTANT NOTE:  IF YOU ADD TO THIS, GO TO DbModelConvert.cpp AND
//	MAKE SURE TO SET THE DEFAULT VALUE PROPERLY.  THERE IS A COMMENT
//	NEAR THE TOP OF THE FILE.

DATACLASS(DbModelConvertDef)
	const char*	m_pFolderName;				// folder name
	bool		m_bNestedFolders;			// do nested folders too?
	bool		m_bNoConvert;				// if true, don't convert this folder
	bool		m_bRemoveDynamicLights;		// remove lights from the model
	bool		m_bApplyLightingSaturation;	// apply modulate 4X to give a "outdoors" look
	int32		m_maxVerts;					// maximum vertices allowed
	int			m_numLods;					// number of lods to generate
	int			m_numBoneLods;				// number of bone lod levels
	int			m_maxTextureWidth;			// width x height gives max res. of all textures
	int			m_maxTextureHeight;			// used with above
	float		m_scaleX;					// non-uniform scaling
	float		m_scaleY;					//
	float		m_scaleZ;					//
ENDCLASS

#endif // DBGRAPHICCONVERTDEFS_H
