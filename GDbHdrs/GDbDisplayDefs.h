//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/gfx/GDbHdrs/GDbDisplayDefs.h 3     8/19/04 9:58a Rbradford $
//
// DESCRIPTION:   GDbDisplayDefs.h has enums for the graphic display.
//
// AUTHOR:        Rex Bradford
//
//===========================================================================

#ifndef GDBDISPLAYDEFS_H
#define GDBDISPLAYDEFS_H
#pragma once

#include "HdrMacros.h"

//	Display resolutions, divorced from color depth

ENUM eDisplayResolution {
	kDisplayResolution_Res800x600,		// 800 x 600 pixels
	kDisplayResolution_Res1024x768,		// 1024 x 768 pixels
	kDisplayResolution_Res1152x864,		// 1152 x 864 pixels
	kDisplayResolution_Res1280x960,		// 1280 x 960 pixels
	kDisplayResolution_Res1280x1024,	// 1280 x 1024 pixels (the bastard aspect-ratio-impaired child)
	kDisplayResolution_Res1600x1200,	// 1600 x 1200 pixels
	kNumDisplayResolutions,
};

//	Color depths

ENUM eDisplayColorDepth {
	kDisplayColorDepth_32,				// 32-bit color depth
	kDisplayColorDepth_16,				// 16-bit color depth
	kNumDisplayColorDepths,
};

//	Display modes: combination of resolution and color depth
//	NOTE: THESE MUST BE DOUBLE THE RESOLUTIONS, AND INTERLEAVED PROPERLY!

ENUM eDisplayMode {
	kDisplayMode_Res800x600x32,			// 800 x 600 pixels, 32-bit color depth
	kDisplayMode_Res800x600x16,			// 800 x 600 pixels, 16-bit color depth
	kDisplayMode_Res1024x768x32,		// 1024 x 768 pixels, 32-bit color depth
	kDisplayMode_Res1024x768x16,		// 1024 x 768 pixels, 16-bit color depth
	kDisplayMode_Res1152x864x32,		// 1152 x 864 pixels, 32-bit color depth
	kDisplayMode_Res1152x864x16,		// 1152 x 864 pixels, 16-bit color depth
	kDisplayMode_Res1280x960x32,		// 1280 x 960 pixels, 32-bit color depth
	kDisplayMode_Res1280x960x16,		// 1280 x 960 pixels, 16-bit color depth
	kDisplayMode_Res1280x1024x32,		// 1280 x 1024 pixels, 32-bit color depth
	kDisplayMode_Res1280x1024x16,		// 1280 x 1024 pixels, 16-bit color depth
	kDisplayMode_Res1600x1200x32,		// 1600 x 1200 pixels, 32-bit color depth
	kDisplayMode_Res1600x1200x16,		// 1600 x 1200 pixels, 16-bit color depth
	kNumDisplayModes,
};

namespace GDisplay
{
	// -------------------------
	// PRIVATE: DO NOT MESS WITH
	// -------------------------

	extern eDisplayMode s_displayMode;		// current display mode

	// NOTE: THESE NUMBERS MUST BE IN SYNC WITH THE ENUMS EARLIER IN THIS .H FILE
	// THEY ARE DEFINED IN GDISPLAY.CPP
	extern int s_resWidth[];
	extern int s_resHeight[];
	extern int s_depth[];

	// ----------------------
	// PUBLIC API
	// -----------------------
	
	// Convert mode to resolution
	inline eDisplayResolution ModeToResolution(enum eDisplayMode in_mode)
	{
		ASSERT(in_mode < kNumDisplayModes);
		return((eDisplayResolution) (int(in_mode) >> 1));
	}

	// Convert mode to color depth
	inline eDisplayColorDepth ModeToColorDepth(enum eDisplayMode in_mode)
	{
		ASSERT(in_mode < kNumDisplayModes);
		return((eDisplayColorDepth) ((int(in_mode) & 1)));
	}

	// Convert resolution & depth to mode
	inline eDisplayMode ResolutionColorDepthToMode(enum eDisplayResolution in_res,
		enum eDisplayColorDepth in_depth)
	{
		ASSERT(in_res < kNumDisplayResolutions);
		ASSERT(in_depth < kNumDisplayColorDepths);
		return ((eDisplayMode) ((int(in_res) << 1) | int(in_depth)));
	};

	// Return info about a mode
	inline void GetModeInfo(enum eDisplayMode in_mode, int &out_width, int &out_height,
		int &out_depth)
	{
		out_width = s_resWidth[ModeToResolution(in_mode)];
		out_height = s_resHeight[ModeToResolution(in_mode)];
		out_depth = s_depth[ModeToColorDepth(in_mode)];
	}

	// Return info about a resolution
	inline void GetResolutionInfo(eDisplayResolution in_res, int &out_width, int &out_height)
	{
		ASSERT(in_res < kNumDisplayResolutions);
		out_width = s_resWidth[in_res];
		out_height = s_resHeight[in_res];
	}

	// Return info about a color depth
	inline int GetColorDepthInfo(eDisplayColorDepth in_depth)
	{
		ASSERT(in_depth < kNumDisplayColorDepths);
		return s_depth[in_depth];
	}
	
	// Set/get the current display mode
	void SetDisplayMode(eDisplayMode in_mode);
	inline eDisplayMode GetDisplayMode()
	{
		return s_displayMode;
	}

	// Get current display resolution
	inline eDisplayResolution GetDisplayResolution()
	{
		return ModeToResolution(s_displayMode);
	}
};

#endif // GDBDISPLAYDEFS_H
