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
#include	"gearbox_gamerules.h"
#include	"skill.h"
#include	"items.h"
#include	"teamplay_gamerules.h"

#if defined ( GEARBOX_DLL )

extern int		g_teamplay;

extern cvar_t	teamplay;

//---------------------------------------------------------
// Purpose:
//---------------------------------------------------------
CGearboxRules::CGearboxRules(void)
{
	RefreshSkillData();
}

//=========================================================
// load the SkillData struct with the proper values based on the skill level.
//=========================================================
void CGearboxRules::RefreshSkillData(void)
{
	// Otis
	gSkillData.otisHealth = GetSkillCvar("sk_otis_health");

	// Pitdrone
	gSkillData.pitdroneHealth = GetSkillCvar("sk_pitdrone_health");
	gSkillData.pitdroneDmgBite = GetSkillCvar("sk_pitdrone_dmg_bite");
	gSkillData.pitdroneDmgWhip = GetSkillCvar("sk_pitdrone_dmg_whip");
	gSkillData.pitdroneDmgSpit = GetSkillCvar("sk_pitdrone_dmg_spit");

	// Hgrunt Ally
	gSkillData.hgruntAllyHealth = GetSkillCvar("sk_hgrunt_ally_health");
	gSkillData.hgruntAllyDmgKick = GetSkillCvar("sk_hgrunt_ally_kick");
	gSkillData.hgruntAllyShotgunPellets = GetSkillCvar("sk_hgrunt_ally_pellets");
	gSkillData.hgruntAllyGrenadeSpeed = GetSkillCvar("sk_hgrunt_ally_gspeed");

	// Medic Ally 
	gSkillData.medicAllyHealth = GetSkillCvar("sk_medic_ally_health");
	gSkillData.medicAllyDmgKick = GetSkillCvar("sk_medic_ally_kick");
	gSkillData.medicAllyGrenadeSpeed = GetSkillCvar("sk_medic_ally_gspeed");
	gSkillData.medicAllyHeal = GetSkillCvar("sk_medic_ally_heal");

	// Torch Ally 
	gSkillData.torchAllyHealth = GetSkillCvar("sk_torch_ally_health");
	gSkillData.torchAllyDmgKick = GetSkillCvar("sk_torch_ally_kick");
	gSkillData.torchAllyGrenadeSpeed = GetSkillCvar("sk_torch_ally_gspeed");

	// Male Assassin
	gSkillData.massnHealth = GetSkillCvar("sk_massassin_health");
	gSkillData.massnDmgKick = GetSkillCvar("sk_massassin_kick");
	gSkillData.massnGrenadeSpeed = GetSkillCvar("sk_massassin_gspeed");


	// ShockTrooper 
	gSkillData.strooperHealth = GetSkillCvar("sk_shocktrooper_health");
	gSkillData.strooperDmgKick = GetSkillCvar("sk_shocktrooper_kick");
	gSkillData.strooperGrenadeSpeed = GetSkillCvar("sk_shocktrooper_gspeed");
	gSkillData.strooperMaxCharge = GetSkillCvar("sk_shocktrooper_maxcharge");
	gSkillData.strooperRchgSpeed = GetSkillCvar("sk_shocktrooper_rchgspeed");

	// Scientist
	gSkillData.cleansuitScientistHealth = GetSkillCvar("sk_cleansuit_scientist_health");
	gSkillData.cleansuitScientistHeal = GetSkillCvar("sk_cleansuit_scientist_heal");


	// Voltigore
	gSkillData.voltigoreHealth = GetSkillCvar("sk_voltigore_health");
	gSkillData.voltigoreDmgPunch = GetSkillCvar("sk_voltigore_dmg_punch");
	gSkillData.voltigoreDmgBeam = GetSkillCvar("sk_voltigore_dmg_beam");

	// Baby Voltigore
	gSkillData.babyVoltigoreHealth = GetSkillCvar("sk_babyvoltigore_health");
	gSkillData.babyVoltigoreDmgPunch = GetSkillCvar("sk_babyvoltigore_dmg_punch");


	// Pitworm
	gSkillData.pwormHealth = GetSkillCvar("sk_pitworm_health");
	gSkillData.pwormDmgSwipe = GetSkillCvar("sk_pitworm_dmg_swipe");
	gSkillData.pwormDmgBeam = GetSkillCvar("sk_pitworm_dmg_beam");

	// Geneworm
	gSkillData.gwormHealth = GetSkillCvar("sk_geneworm_health");
	gSkillData.gwormDmgSpit = GetSkillCvar("sk_geneworm_dmg_spit");
	gSkillData.gwormDmgHit = GetSkillCvar("sk_geneworm_dmg_hit");

	// Zombie Barney
	gSkillData.zbarneyHealth = GetSkillCvar("sk_zombie_barney_health");
	gSkillData.zbarneyDmgOneSlash = GetSkillCvar("sk_zombie_barney_dmg_one_slash");
	gSkillData.zbarneyDmgBothSlash = GetSkillCvar("sk_zombie_barney_dmg_both_slash");

	// Zombie Soldier
	gSkillData.zgruntHealth = GetSkillCvar("sk_zombie_soldier_health");
	gSkillData.zgruntDmgOneSlash = GetSkillCvar("sk_zombie_soldier_dmg_one_slash");
	gSkillData.zgruntDmgBothSlash = GetSkillCvar("sk_zombie_soldier_dmg_both_slash");

	// Gonome
	gSkillData.gonomeHealth = GetSkillCvar("sk_gonome_health");
	gSkillData.gonomeDmgOneSlash = GetSkillCvar("sk_gonome_dmg_one_slash");
	gSkillData.gonomeDmgGuts = GetSkillCvar("sk_gonome_dmg_guts");
	gSkillData.gonomeDmgOneBite = GetSkillCvar("sk_gonome_dmg_one_bite");

	// Shock Roach
	gSkillData.sroachHealth = GetSkillCvar("sk_shockroach_health");
	gSkillData.sroachDmgBite = GetSkillCvar("sk_shockroach_dmg_bite");
	gSkillData.sroachLifespan = GetSkillCvar("sk_shockroach_lifespan");

	// Weapons
	gSkillData.plrDmgPWrench = GetSkillCvar("sk_plr_pipewrench");
	gSkillData.plrDmgKnife = GetSkillCvar("sk_plr_knife1");
	gSkillData.plrDmgGrapple = GetSkillCvar("sk_plr_grapple1");
	gSkillData.plrDmgEagle = GetSkillCvar("sk_plr_eagle1");
	gSkillData.plrDmgDisplacer = GetSkillCvar("sk_plr_displacer_self");
	gSkillData.plrDmgShockroach = GetSkillCvar("sk_plr_shockroachs");
	gSkillData.plrDmgSpore = GetSkillCvar("sk_plr_spore");

	gSkillData.monDmg762 = GetSkillCvar("sk_plr_762_bullet");
	gSkillData.monDmg556 = GetSkillCvar("sk_plr_556_bullet");
	gSkillData.monDmgDisplacer = GetSkillCvar("sk_plr_displacer_other");
	gSkillData.monDmgShockroach = GetSkillCvar("sk_plr_shockroachm");

	gSkillData.displacerDmgRadius = GetSkillCvar("sk_plr_displacer_radius");
}


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
	gSkillData.plrDmgPWrench		= 20;

	// Knife
	gSkillData.plrDmgKnife			= 10;

	// Grapple
	gSkillData.plrDmgGrapple		= 25;

	// Eagle
	gSkillData.plrDmgEagle			= 34;

	// Displacer player damage
	gSkillData.plrDmgDisplacer		= 5;

	// Shockroach
	gSkillData.plrDmgShockroach		= 10;

	// Spore
	gSkillData.plrDmgSpore			= 50;

	// 762
	gSkillData.monDmg762			= 100;

	// 556
	gSkillData.monDmg556			= 15;

	// Displacer monster damage
	gSkillData.monDmgDisplacer		= 250;

	// Shockroach
	gSkillData.monDmgShockroach		= 15;

	// Displacer radius
	gSkillData.displacerDmgRadius	= 300;


}

//=========================================================
// instantiate the proper game rules object
//=========================================================

#if defined ( GEARBOX_DLL )

CGameRules *InstallGameRules(void)
{
	SERVER_COMMAND("exec game.cfg\n");
	SERVER_EXECUTE();

	if (!gpGlobals->deathmatch)
	{
		// generic Op4
		g_teamplay = 0;
		return new CGearboxRules;
	}
	else
	{
		if (teamplay.value > 0)
		{
			// teamplay

			g_teamplay = 1;
			return new CHalfLifeTeamplay;
		}
		if ((int)gpGlobals->deathmatch == 1)
		{
			// vanilla Op4 deathmatch
			g_teamplay = 0;
			return new CGearboxMultiplay;
		}
		else
		{
			// vanilla Op4 deathmatch??
			g_teamplay = 0;
			return new CGearboxMultiplay;
		}
	}
}

#endif // !defined ( GEARBOX_DLL )

#endif // GEARBOX_DLL