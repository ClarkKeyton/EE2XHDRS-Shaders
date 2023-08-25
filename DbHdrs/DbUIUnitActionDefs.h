//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbUIUnitActionDefs.h 7     12/15/04 4:44p Dsproul $
//
// DESCRIPTION:	data class for UI unit action button
//				these are found in dbuiunitactions.csv and parsed into DbUIUnitActionsTable
//
// AUTHOR:      Daniel Sproul
//
//===========================================================================

#ifndef DB_UIUNITACTIONDEFS_H
#define DB_UIUNITACTIONDEFS_H
#pragma once

#include "HdrMacros.h"
#include "GDbWidgetDefs.h"	// for eGButtonStyle


//
// enumeration of different button user types
// determines whether a button is shown or hidden based on user type (simple vs. advanced)
//
ENUM eUIUnitActionUserType {
	kUIUnitActionUserType_Default	= 0x00,			// anything left as default will be set to
													// _SimpleAndAdvanced on PostLoad()
	// these should be orthogonal
	kUIUnitActionUserType_Simple	= 0x01,
	kUIUnitActionUserType_Advanced	= 0x02,

	kUIUnitActionUserType_SimpleAndAdvanced = 0x03,	// the true default
};


//
// data class for UI unit action button:
//
DATACLASS(DbUIUnitActionDef)

	const char		   *m_widgetClass;	// widget class to use for the button ("Icon" if unspecified)

	// button appearance:
	DBINDEX(DBSprite)	m_icon;			// icon sprite for the button
	enum eGButtonStyle	m_buttonStyle;	// button style for the icon (see GDbWidgetDefs.h)

	// button user type
	enum eUIUnitActionUserType m_userType;

	// button position:
	// (specify a menu index and a range of rows and columns; the first row (col)
	// can be less than or greater than the last row (col); they are tried in order from
	// first to last
	int16				m_menu;			// which menu the button goes in
	int16				m_firstRow;		// first row the button can go in
	int16				m_lastRow;		// last row the button can go in
	int16				m_firstColumn;	// first column the button can go in
	int16				m_lastColumn;	// last column the button can go in
	
	// tooltips
	DBINDEX(DbText)		m_tooltip;			// tooltip text (index into text db)
	DBINDEX(DbText)		m_verboseTooltip;	// verbose tooltip (index into text db)

	// unit type attribute for the button (if unspecified, special-case code must be used
	// to determine if or not we want to show the button at any given instant)
	DBINDEX(DbUnitTypeAttribute)	m_unitTypeAttributes;
	bool							m_bSpecialCase;		// if true, special case code consideration is needed

	bool				m_bDisableWhenSabotaged;	// if true, this button will be disabled
													// if the unit is sabotaged
	
	// button behaviour:
	const char		   *m_cmdString;			// command string to send when clicked
	const char		   *m_autoCastEffect;		// auto-cast effect name
	const char		   *m_argString;			// additional arg string to add to the widget def
	
ENDCLASS




#endif // DB_UIUNITACTIONDEFS_H
