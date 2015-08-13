
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

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"player.h"
#include	"weapons.h"
#include	"gamerules.h"
#include	"skill.h"
#include	"items.h"

//---------------------------------------------------------
// Purpose:
//---------------------------------------------------------
CGearboxMultiplay::CGearboxMultiplay() : CHalfLifeMultiplay()
{

}


//=========================================================
//=========================================================
void CGearboxMultiplay::RefreshSkillData(void)
{
	// load all default values
	CHalfLifeMultiplay::RefreshSkillData();

	// override some values for multiplay.

	// Pipe wrench
	gSkillData.plrDmgPWrench = 20;

	// Knife
	gSkillData.plrDmgKnife = 10;

	// Grapple
	gSkillData.plrDmgGrapple = 25;

	// Eagle
	gSkillData.plrDmgEagle = 34;

	// Displacer player damage
	gSkillData.plrDmgDisplacer = 5;

	// Shockroach
	gSkillData.plrDmgShockroach = 10;

	// Spore
	gSkillData.plrDmgSpore = 50;

	// 762
	gSkillData.plrDmg762 = 100;

	// 556
	gSkillData.plrDmg556 = 15;





	// 762
	gSkillData.monDmg762 = 100;

	// 556
	gSkillData.monDmg556 = 15;

	// Displacer monster damage
	gSkillData.monDmgDisplacer = 250;

	// Shockroach
	gSkillData.monDmgShockroach = 15;

	// Displacer radius
	gSkillData.displacerDmgRadius = 300;


}


//=========================================================
//
// OP4 CTF Gamerules
//
//=========================================================

//---------------------------------------------------------------
// Constructor
//---------------------------------------------------------------
CCTFMultiplay::CCTFMultiplay() : CGearboxMultiplay()
{

}