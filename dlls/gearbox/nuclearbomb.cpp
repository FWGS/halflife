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

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"
#include "player.h"
#include "skill.h"
#include "items.h"
#include "gamerules.h"

#define SF_BUTTON_DONTMOVE		1
#define SF_ROTBUTTON_NOTSOLID	1
#define	SF_BUTTON_TOGGLE		32	// button stays pushed until reactivated
#define	SF_BUTTON_SPARK_IF_OFF	64	// button sparks in OFF state
#define SF_BUTTON_TOUCH_ONLY	256	// button only fires as a result of USE key.

//=========================================================
// Nuclear bomb
//=========================================================

#define NUKE_CLASSNAME_BUTTON	"item_nuclearbomb_button"
#define NUKE_CLASSNAME_TIMER	"item_nuclearbomb_timer"

#define NUKE_MODEL_BUTTON		"models/nuke_button.mdl"
#define NUKE_MODEL_CASE			"models/nuke_case.mdl"
#define NUKE_MODEL_TIMER		"models/nuke_timer.mdl"

//----------------------------------------------
// Nuke button
//----------------------------------------------
class CNukeButton : public CBaseAnimating
{
public:
	void Spawn(void);
	void Precache(void);
};

LINK_ENTITY_TO_CLASS(item_nuclearbomb_button, CNukeButton);

void CNukeButton::Spawn(void)
{
	Precache();
	SET_MODEL(ENT(pev), "models/nuke_button.mdl");

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
}

void CNukeButton::Precache(void)
{
	PRECACHE_MODEL("models/nuke_button.mdl");
}

//----------------------------------------------
// Nuke timer
//----------------------------------------------

class CNukeTimer : public CBaseAnimating
{
public:
	void Spawn(void);
	void Precache(void);
};

LINK_ENTITY_TO_CLASS(item_nuclearbomb_timer, CNukeTimer);

void CNukeTimer::Spawn(void)
{
	Precache();
	SET_MODEL(ENT(pev), "models/nuke_timer.mdl");

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
}

void CNukeTimer::Precache(void)
{
	PRECACHE_MODEL("models/nuke_timer.mdl");
}

//----------------------------------------------
// Nuke case
//----------------------------------------------
class CNukeCase : public CBaseButton
{
public:

	virtual int		Save(CSave &save);
	virtual int		Restore(CRestore &restore);

	static	TYPEDESCRIPTION m_SaveData[];

	void KeyValue(KeyValueData *pkvd);

	void Spawn(void);
	void Precache(void);

	void EXPORT StartupThink(void);
	void EXPORT CaseThink(void);

	int m_initialstate;
	float m_flWait;

	EHANDLE m_hNukeButton;
	EHANDLE m_hNukeTimer;
};

LINK_ENTITY_TO_CLASS(item_nuclearbomb, CNukeCase);

TYPEDESCRIPTION CNukeCase::m_SaveData[] =
{
	DEFINE_FIELD(CNukeCase, m_initialstate, FIELD_INTEGER),
	DEFINE_FIELD(CNukeCase, m_flWait, FIELD_FLOAT),

	DEFINE_FIELD(CNukeCase, m_hNukeButton, FIELD_EHANDLE),
	DEFINE_FIELD(CNukeCase, m_hNukeTimer, FIELD_EHANDLE),

};

IMPLEMENT_SAVERESTORE(CNukeCase, CBaseButton);

void CNukeCase::KeyValue(KeyValueData* pkvd)
{
	if (FStrEq(pkvd->szKeyName, "initialstate"))
	{
		m_initialstate = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "wait"))
	{
		m_flWait = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

void CNukeCase::Spawn(void)
{
	//
	// Remove touch button flag, so that it will correctly set
	// the default "ButtonUse" function pointer in the 
	// CBaseButton::Spawn function.
	//
	pev->spawnflags &= ~SF_BUTTON_TOUCH_ONLY;

	//
	// Set model name right now so that it will be precached
	// from the CBaseButton::Precache and set from
	// the CBaseButton::Spawn function.
	//
	pev->model = ALLOC_STRING( NUKE_MODEL_CASE );

	// Call CBaseButton (baseclass) spawn function.
	CBaseButton::Spawn();

	pev->movetype = MOVETYPE_FLY;
	pev->solid = SOLID_BBOX;

	UTIL_SetOrigin( pev, pev->origin );
	UTIL_SetSize( pev, Vector(-16, -16, 0), Vector(16, 16, 36) );

	// Remove any speed (make the case not move at all).
	// pev->speed = 0;

	// Remove lip (distance to remain from target position).
	m_flLip = 0;

	// Change button sound.
	pev->noise = ALLOC_STRING("buttons/button4.wav");

	m_hNukeButton.Set(NULL);
	m_hNukeTimer.Set(NULL);

	SetThink(&CNukeCase::StartupThink);
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CNukeCase::Precache(void)
{
	CBaseButton::Precache();

	PRECACHE_MODEL((char*)STRING(pev->model));

	UTIL_PrecacheOther( NUKE_CLASSNAME_BUTTON );
	UTIL_PrecacheOther( NUKE_CLASSNAME_TIMER );
}


void CNukeCase::StartupThink(void)
{
	pev->nextthink = gpGlobals->time + 0.1f;

	CBaseEntity* pPart = NULL;

	pPart = CBaseEntity::Create(NUKE_CLASSNAME_BUTTON, pev->origin, pev->angles);

	if (pPart)
	{
		m_hNukeButton = pPart;
	}
	else
	{
		ALERT(at_aiconsole, "ERROR: Failed to create entity with classname %s.\n", NUKE_CLASSNAME_BUTTON);
	}

	pPart = CBaseEntity::Create(NUKE_CLASSNAME_TIMER, pev->origin, pev->angles);

	if (pPart)
	{
		m_hNukeTimer = pPart;
	}
	else
	{
		ALERT(at_aiconsole, "ERROR: Failed to create entity with classname %s.\n", NUKE_CLASSNAME_TIMER);
	}

	SetThink(&CNukeCase::CaseThink);
}

void CNukeCase::CaseThink(void)
{
	pev->nextthink = gpGlobals->time + 0.1f;
}