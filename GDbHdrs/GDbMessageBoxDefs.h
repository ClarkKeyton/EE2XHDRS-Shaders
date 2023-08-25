//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbMessageBoxDefs.h 2     4/01/04 4:19p Dsproul $
//
// DESCRIPTION:	defines messagebox return values (see GMessageBox.h/.cpp)
//
// AUTHOR:      Daniel Sproul
//
//===========================================================================

#ifndef GDB_MESSAGEBOXDEFS_H
#define GDB_MESSAGEBOXDEFS_H
#pragma once

#include "hdrmacros.h"


//
// possible messagebox return values, listed in the left-to-right order buttons will appear
// (done as an ENUM enum so we have an easy mapping to display strings; keep text db up to
// date with the set and ordering defined here), also listed in reverse order of precedence
// for which message return value is sent in cases where a closebox is clicked or the escape
// key is used to close the messagebox
//
ENUM eMessageBoxReturn {
	kMessageBoxReturn_Yes		= 0x01,
	kMessageBoxReturn_No		= 0x02,
	kMessageBoxReturn_Ok		= 0x04,
	kMessageBoxReturn_Cancel	= 0x08,
	kMessageBoxReturn_Abort		= 0x10,
	kMessageBoxReturn_Ignore	= 0x20,
	kMessageBoxReturn_Retry		= 0x40,
};



#endif // GDB_MESSAGEBOXDEFS_H
