//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/lib/LDbHdrs/LDbHotkeyDefs.h 3     8/09/05 1:21p Dsproul $
//
// DESCRIPTION:		db dataclasses for hotkey databases
//					@NOTE currently this is a bit weird, in that the default hotkeys
//					do not use the database system at all, but the hotkey remapper does...
//
// AUTHOR:			Daniel Sproul
//
//===========================================================================

#ifndef LDBHOTKEYDEFS_H
#define LDBHOTKEYDEFS_H
#pragma once


#include "HdrMacros.h"



//////////////////////////////////////////
//
// eHotkeysMode
// enumerated hotkey default types
//
ENUM eHotkeysMode {
	kHotkeysMode_Advanced,
	kHotkeysMode_Simple,
	kNumHotkeyModes,
};


//////////////////////////////////////////
//
// LDbKeymapDef
// dataclass for keymap
//
DATACLASS(LDbKeymapDef)

	// display name for the keymap
	DBINDEX(DbText) m_DisplayName;

	// keymaps this keymap depends on
	LSizedArray< const char * > m_ParentKeymapNames;
	
	// if true, LKeyMapper will create this keymap even if there are no keys events for it 
	// (this is possible due to remapping)  
	// this is set to true during LDbHotkeys::Postload() -- 
	// if a key in the loaded hotkey DB specifies this keymap it is required, regardless of remapping
	USER bool m_IsRequired;

	// parent keymaps (determined from m_ParentKeymapNames)
	USER LDynArray< int > m_ParentKeymaps;

	// child keymaps (determined from their parents)
	USER LDynArray< int > m_ChildKeymaps;

	// keymaps this keymap overlaps with
	// (determined indirectly from m_ParentKeymapNames)
	// (used to detect conflicts across keymaps when remapping hotkeys)
	USER LDynArray< int > m_OverlappingKeymaps;

ENDCLASS


//////////////////////////////////////////
//
// LDbHotkeyKeyDef
// dataclass for a single hotkey mapping
//
DATACLASS(LDbHotkeyDef)

	// display name for the hotkey
	// (must be specified if we allow remapping for this key)
	DBINDEX(DbText) m_DisplayName;

	// keymap this key belongs to
	DBINDEX(DbKeymap) m_Keymap;

	// named event (required) and argument (optional) bound to this key
	const char *m_EventName;
	const char *m_EventArg;

	// default key names from the DB -- these may be overridden
	const char *m_DefaultKeyName_Advanced;
	const char *m_DefaultKeyName_Simple;

	// key names (indexed by eHotkeysMode)
	USER LDynArray< const char * > m_aszDefaultKeyNames;

	// should the key repeat flag be set for this key's event?
	bool		m_KeyRepeat;

	// the (possibly remapped) actual key name to use
	USER LStr	m_KeyName;

	// actual key event (including repeat flag)
	USER uint32	m_KeyEvent;

	// should we allow this hotkey to be remapped?
	bool		m_AllowRemapping;

	// is this a remapped hotkey?
	USER bool	m_IsRemapped;

ENDCLASS


//////////////////////////////////////////
//
// LDbHotkeyKeyDef
// dataclass for remapping a single hotkey
//
DATACLASS(LDbHotkeyRemapDef)

	// the key to remap
	DBINDEX(DbHotkeys) m_Key;

	// key name for the remapped event (empty string to clear the binding)
	char *m_KeyName;

ENDCLASS



#endif // LDBHOTKEYDEFS_H
