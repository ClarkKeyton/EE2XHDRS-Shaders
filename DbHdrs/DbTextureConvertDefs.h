//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbTextureConvertDefs.h 3     6/08/04 4:59p Rbradford $
//
// DESCRIPTION:   DbTextureConvertDefs.h holds settings for which folders and
//				  files get which special options when converted for load
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef DBTEXTURECONVERTDEFS_H
#define DBTEXTURECONVERTDEFS_H
#pragma once

#include "hdrmacros.h"

//	This dataclass is used to represent entries specifying which folders of
//	textures get non-default conversion options.  The defaults are:
//
//		noconvert	= off		// if on, means don't create DX version at all
//		compression	= on		// if off, don't apply DX compression
//		mipmaps		= on		// if off, don't generate mipmaps
//		genalpha	= off		// if on, generate alpha bits

DATACLASS(DbTextureConvertDef)
	const char *m_pFolderName;				// folder name
	bool m_bNestedFolders;					// do nested folders too?
	bool m_bNoConvert;						// don't even create a cached converted version
	bool m_bCompress;						// compress?
	bool m_bMipMaps;						// mipmaps?
	bool m_bGenAlpha;						// generate alpha?
ENDCLASS

#endif // DBTEXTURECONVERTDEFS_H
