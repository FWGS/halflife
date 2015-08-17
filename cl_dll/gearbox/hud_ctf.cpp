/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//
// flashlight.cpp
//
// implementation of CHudFlashlight class
//

#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"

#include <string.h>
#include <stdio.h>


/*
item_ctfljump 640 ctf_hud1 128 0  64  64		// Powerup Jump
item_ctfphev 640 ctf_hud1 192 0  64  64			// Powerup hev
item_ctfregen 640 ctf_hud1 0 0  64  64			// Powerup health
item_ctfaccel 640 ctf_hud1 64 0  64  64			// Powerup accel
item_ctfbpack 640 ctf_hud1 0 64  64  64			// Powerup backpack

item_ctfflagh 640 ctf_hud1 67 75  38  42
item_ctfflagc 640 ctf_hud1 105 75  38  42
item_ctfflagd 640 ctf_hud1 143 75  38  42
item_ctfflagg 640 ctf_hud1 181 75  38  42

score_ctfljump 640 ctf_hud1 32 160  16  16
score_ctfphev 640 ctf_hud1 48 160  16  16
score_ctfregen 640 ctf_hud1 0 160  16  16
score_ctfaccel 640 ctf_hud1 16 160  16  16
score_ctfbpack 640 ctf_hud1 64 160  16  16
score_flag 640 ctf_hud1 80 160  16  16

item_ctfscorebm 640 ctf_hud2 48 0  48  48
item_ctfscoreof 640 ctf_hud2 0 0  48  48
*/