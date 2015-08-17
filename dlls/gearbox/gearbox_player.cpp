/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
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
/*

===== player.cpp ========================================================

functions dealing with the player

*/

#include "extdll.h"
#include "util.h"

#include "cbase.h"
#include "player.h"
#include "trains.h"
#include "nodes.h"
#include "weapons.h"
#include "soundent.h"
#include "monsters.h"
#include "shake.h"
#include "decals.h"
#include "gamerules.h"
#include "game.h"
#include "pm_shared.h"
#include "hltv.h"

#include "gearbox_player.h"

#define	FLASH_DRAIN_TIME	 1.2 //100 units/3 minutes
#define	FLASH_CHARGE_TIME	 0.2 // 100 units/20 seconds  (seconds per unit)

extern DLL_GLOBAL ULONG		g_ulModelIndexPlayer;
extern int gmsgFlashlight;

extern edict_t *EntSelectSpawnPoint(CBaseEntity *pPlayer);

int gmsgSelAmmo_Op4 = 0;
int gmsgNightvision = 0;

#if defined ( GEARBOX_CTF )
int gmsgCTFMsgs = 0;
int gmsgFlagStatus = 0;
int gmsgRuneStatus = 0;
int gmsgFlagCarrier = 0;

#endif

LINK_ENTITY_TO_CLASS( player, CGearboxPlayer );

// Global Savedata for player
TYPEDESCRIPTION	CGearboxPlayer::m_playerSaveData[] =
{
	DEFINE_FIELD(CGearboxPlayer, m_fInXen, FIELD_BOOLEAN),
	DEFINE_FIELD(CGearboxPlayer, m_fIsFrozen, FIELD_BOOLEAN),
};

void LinkUserMessages_Op4(void)
{
	// Already taken care of?
	if (gmsgSelAmmo_Op4)
	{
		return;
	}
	
	gmsgSelAmmo_Op4		= 1; // Use this as a placeholder to ensure Op4 messages
							 // only get registered once.

	gmsgNightvision		= REG_USER_MSG("Nightvision", 1);

#if defined ( GEARBOX_CTF )
	gmsgCTFMsgs			= REG_USER_MSG("CTFMsg", 1);
	gmsgFlagStatus		= REG_USER_MSG("FlagStatus", 5);
	gmsgRuneStatus		= REG_USER_MSG("RuneStatus", 1);
	gmsgFlagCarrier		= REG_USER_MSG("FlagCarrier", 2);
#endif

}

int CGearboxPlayer::Save(CSave &save)
{
	if (!CBaseMonster::Save(save))
		return 0;

	return save.WriteFields("PLAYER", this, m_playerSaveData, ARRAYSIZE(m_playerSaveData));
}


int CGearboxPlayer::Restore(CRestore &restore)
{
	if (!CBaseMonster::Restore(restore))
		return 0;

	int status = restore.ReadFields("PLAYER", this, m_playerSaveData, ARRAYSIZE(m_playerSaveData));

	SAVERESTOREDATA *pSaveData = (SAVERESTOREDATA *)gpGlobals->pSaveData;
	// landmark isn't present.
	if (!pSaveData->fUseLandmark)
	{
		ALERT(at_console, "No Landmark:%s\n", pSaveData->szLandmarkName);

		// default to normal spawn
		edict_t* pentSpawnSpot = EntSelectSpawnPoint(this);
		pev->origin = VARS(pentSpawnSpot)->origin + Vector(0, 0, 1);
		pev->angles = VARS(pentSpawnSpot)->angles;
	}
	pev->v_angle.z = 0;	// Clear out roll
	pev->angles = pev->v_angle;

	pev->fixangle = TRUE;           // turn this way immediately

	// Copied from spawn() for now
	m_bloodColor = BLOOD_COLOR_RED;

	g_ulModelIndexPlayer = pev->modelindex;

	if (FBitSet(pev->flags, FL_DUCKING))
	{
		// Use the crouch HACK
		//FixPlayerCrouchStuck( edict() );
		// Don't need to do this with new player prediction code.
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
	}
	else
	{
		UTIL_SetSize(pev, VEC_HULL_MIN, VEC_HULL_MAX);
	}

	g_engfuncs.pfnSetPhysicsKeyValue(edict(), "hl", "1");

	if (m_fLongJump)
	{
		g_engfuncs.pfnSetPhysicsKeyValue(edict(), "slj", "1");
	}
	else
	{
		g_engfuncs.pfnSetPhysicsKeyValue(edict(), "slj", "0");
	}

	RenewItems();

#if defined( CLIENT_WEAPONS )
	// HACK:	This variable is saved/restored in CBaseMonster as a time variable, but we're using it
	//			as just a counter.  Ideally, this needs its own variable that's saved as a plain float.
	//			Barring that, we clear it out here instead of using the incorrect restored time value.
	m_flNextAttack = UTIL_WeaponTimeBase();
#endif

	return status;
}





BOOL CGearboxPlayer::FlashlightIsOn(void)
{
	return FBitSet(pev->effects, EF_BRIGHTLIGHT);
}

void CGearboxPlayer::FlashlightTurnOn(void)
{
	if (!g_pGameRules->FAllowFlashlight())
	{
		return;
	}

	if ((pev->weapons & (1 << WEAPON_SUIT)))
	{
		EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, SOUND_FLASHLIGHT_ON, 1.0, ATTN_NORM, 0, PITCH_NORM);
		SetBits(pev->effects, EF_BRIGHTLIGHT);
		MESSAGE_BEGIN(MSG_ONE, gmsgFlashlight, NULL, pev);
			WRITE_BYTE(1);
			WRITE_BYTE(m_iFlashBattery);
		MESSAGE_END();

		// Send Nightvision On message.
		MESSAGE_BEGIN(MSG_ONE, gmsgNightvision, NULL, pev);
			WRITE_BYTE(1);
		MESSAGE_END();

		m_flFlashLightTime = FLASH_DRAIN_TIME + gpGlobals->time;

	}
}


void CGearboxPlayer::FlashlightTurnOff(void)
{
	EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, SOUND_FLASHLIGHT_OFF, 1.0, ATTN_NORM, 0, PITCH_NORM);
	ClearBits(pev->effects, EF_BRIGHTLIGHT);
	MESSAGE_BEGIN(MSG_ONE, gmsgFlashlight, NULL, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(m_iFlashBattery);
	MESSAGE_END();

	// Send Nightvision Off message.
	MESSAGE_BEGIN(MSG_ONE, gmsgNightvision, NULL, pev);
		WRITE_BYTE(0);
	MESSAGE_END();

	m_flFlashLightTime = FLASH_CHARGE_TIME + gpGlobals->time;

}

void CGearboxPlayer::Spawn(void)
{
	CBasePlayer::Spawn();

	m_fInXen	= FALSE;
	m_fIsFrozen = FALSE;
}