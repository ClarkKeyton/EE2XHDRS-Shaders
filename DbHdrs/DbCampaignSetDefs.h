//===========================================================================
// Copyright 2003 Mad Doc Software, LLC.  All rights reserved.
// $Header: /src/EE2/DbHdrs/DbCampaignSetDefs.h 2     10/22/03 7:26p Jdunlop $
//
// DESCRIPTION:   Dataclasses used by the campaign sets .ddf file.
//
// AUTHOR:        Jason Dunlop
//
//===========================================================================

#ifndef DBCAMPAIGNSETDEFS_H
#define DBCAMPAIGNSETDEFS_H
#pragma once

#include "HdrMacros.h"

DATACLASS(DbCampaignSetInfo)
	// the names of the campaigns that show up in this campaign set
	LSizedArray<const char *> m_campaigns;
ENDCLASS

#endif // DBCAMPAIGNSETDEFS_H
