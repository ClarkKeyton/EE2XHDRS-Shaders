//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbResourceDefs.h 11    2/26/05 12:46p Mcorthell $
//
// DESCRIPTION:   Types of resource available in the games
//
//					@IMPORTANT NOTE -- DbResourceLevelDefs has a constant int array
//									whose size needs to be updated if you change eResourceType
//
// AUTHOR:        Xinbo Kan
//
//===========================================================================

#ifndef DBRESOURCEDEFS_H
#define DBRESOURCEDEFS_H
#pragma once

#include "HdrMacros.h"

// the basic move type each terrain type can be classified into
// @NOTE: If you change this enum, please update the corresponding text entries in 
// dbtext_enums.utf8!!!
ENUM eResourceType {
	kResourceType_AllNaturalResource = -1,	// special enum to signify all natural resources
		
	// natural resources start here
	kResourceType_Food = 0,
	kResourceType_FirstNaturalResource = 0,	// this must be equal to 0,
											// and the first natural resource should be equal to it
											// entry appear AFTER food so that 0 shows up as 'food'
											// in the debugger
	kResourceType_Wood,
	kResourceType_Stone,
	kResourceType_Gold,
	
	// special natural resources start here
	kResourceType_Tin,
	kResourceType_FirstSpecialNaturalResource = 4,	// set to the same as first special natural resource
													// this demarcates the standard natural resources
													// entry appears AFTER tin so that 4 shows up as 'tin'
													// in the debugger

	kResourceType_Iron,
	kResourceType_Saltpeter,
	kResourceType_Oil,
	kResourceType_Uranium,
	// natural resources end here

	kResourceType_LastNaturalResource = 8, // this must be equal to the last natural resource

	kResourceType_Tech = 9,	// tech points, not an actual natural resource to be gathered
	kResourceType_Pop,		// population, not an actual natural resource to be gathered 

	kNumResourceType, // this must be the last item in the enum def
};


// derive some constants -- how many natural resources of various kinds?
const int kNumNaturalResourceTypes = 1 + kResourceType_LastNaturalResource - kResourceType_FirstNaturalResource;
const int kNumSpecialNaturalResourceTypes = 1 + kResourceType_LastNaturalResource - kResourceType_FirstSpecialNaturalResource;
const int kNumBasicNaturalResources = kNumNaturalResourceTypes - kNumSpecialNaturalResourceTypes;



//
// resource names (used for programmatically constructing related names, not to be used
//					for display names)
// 
static const char *s_resourceNames[] = 
{
	"Food", 
	"Wood", 
	"Stone", 
	"Gold", 
	"Tin", 
	"Iron", 
	"Saltpeter", 
	"Oil", 
	"Uranium",

	"TechPoints", 
	"PopCap"
};



#endif // DBRESOURCEDEFS_H
