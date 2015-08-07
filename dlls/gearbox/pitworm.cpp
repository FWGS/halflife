/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   This source code contains proprietary and confidential information of
*   Valve LLC and its suppliers.  Access to this code is restricted to
*   persons who have executed a written SDK license with Valve.  Any access,
*   use or distribution of this code by or to any unlicensed person is illegal.
*
****/

//=========================================================
// Generic Monster - purely for scripted sequence work.
//=========================================================
#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"genericmonster.h"

#if defined ( GEARBOX_DLL )

//=========================================================
// Monster's Anim Events Go Here
//=========================================================

class CPitWorm : public CGenericMonster
{
public:

	void Spawn(void);
	void Precache(void);
};

LINK_ENTITY_TO_CLASS(monster_pitworm, CPitWorm);


//=========================================================
// Spawn
//=========================================================
void CPitWorm::Spawn()
{
	Precache();

	SET_MODEL(ENT(pev), "models/pit_worm_up.mdl");

	UTIL_SetSize(pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX);

	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_NONE;
	m_bloodColor = BLOOD_COLOR_YELLOW;
	pev->health = 8;
	m_flFieldOfView = 0.5;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState = MONSTERSTATE_NONE;

	MonsterInit();
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CPitWorm::Precache()
{
	PRECACHE_MODEL("models/pit_worm_up.mdl");
}

#endif // 