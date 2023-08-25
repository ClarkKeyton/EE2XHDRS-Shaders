
//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbMovieSubtitlesDefs.h 2     12/06/04 6:41p Rbradford $
//
// DESCRIPTION:	GMovieSubtitlesDefs.h holds dataclasses used in movie subtitles
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#include "hdrmacros.h"
#include "LDataObj.h"
#include "LRGBA.h"

//	These dataclasses are steps which may appear in the dynamic array
//	of steps in a subtitle set.

DATACLASS(GDbSubtitleStep_Text)
	float m_time;					// time to display text string at
	DBINDEX(DbText) m_text;			// index of text string to display
ENDCLASS

DATACLASS(GDbSubtitleStep_Blank)
	float m_time;					// time to change text to blank
ENDCLASS

DATACLASS(GDbSubtitleStep_TextColor)
	LRGBA m_color;					// text color
	LRGBA m_fadeColor;				// text color when faded down
ENDCLASS

DATACLASS(GDbSubtitleStep_TextTiming)
	float m_fadeUpTime;				// fade up time
	float m_fadeDownTime;			// fade down time
	float m_autoTimer;				// automatically take down (for streamlining credits)
	float m_blankTime;				// time of blank between text
ENDCLASS

DATACLASS(GDbSubtitleStep_PlaySound)
	float m_time;					// time to play sound
	const char *m_soundfile;		// sound filename
ENDCLASS

//	This is the master dataclass that drives a set of subtitles on a movie

DATACLASS(GDbSubtitles)
	const char *m_widgetName;		// name of widget to display text in
	LSizedArray<VARDC> m_steps;		// array of timed steps
ENDCLASS
