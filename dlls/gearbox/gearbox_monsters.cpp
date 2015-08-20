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
#include "squadmonster.h"
#include "monsters.h"
#include "effects.h"
#include "customentity.h"
#include "gearbox_monsters.h"

#if 0
//=========================================================
// Purpose:
//=========================================================
void CBaseMonster::Spawn(void)
{
	m_flGlowShellDuration	= 0.0f;
	m_flGlowShellStartTime	= 0.0f;
	rendercolorprev			= pev->rendercolor;
}

//=========================================================
// Purpose:
//=========================================================
void CBaseMonster::PrescheduleThink(void)
{
	// Update glow shell.
	GlowShellUpdate();
}

//=========================================================
// Purpose:
//=========================================================
void CBaseMonster::GlowShellOn(Vector color, float flDuration)
{
	pev->effects |= EF_GLOWSHELL;

	rendercolorprev = pev->rendercolor;
	glowshellcolor = color;

	pev->renderfx = kRenderFxGlowShell;
	pev->rendercolor = glowshellcolor;
	pev->renderamt = 5;

	m_flGlowShellStartTime = gpGlobals->time;
	m_flGlowShellDuration = flDuration;
}

void CBaseMonster::GlowShellOff(void)
{
	pev->effects &= ~EF_GLOWSHELL;

	pev->renderfx = kRenderFxNone;
	pev->rendercolor = rendercolorprev;
	pev->renderamt = 255;

	m_flGlowShellStartTime = 0.0f;
	m_flGlowShellDuration = 0.0f;
}

void CBaseMonster::GlowShellUpdate(void)
{
	if (pev->effects & EF_GLOWSHELL)
	{
		if ((gpGlobals->time - m_flGlowShellStartTime) > m_flGlowShellDuration)
		{
			GlowShellOff();
		}
		else
		{
			pev->renderfx = kRenderFxGlowShell;
			pev->rendercolor = glowshellcolor;
			pev->renderamt = 5;
		}
	}
}
#endif