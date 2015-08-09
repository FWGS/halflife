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
#include "eiface.h"
#include "util.h"
#include "game.h"

// Otis
cvar_t	sk_otis_health1 = { "sk_otis_health1", "0" };
cvar_t	sk_otis_health2 = { "sk_otis_health2", "0" };
cvar_t	sk_otis_health3 = { "sk_otis_health3", "0" };

// Pitdrone
cvar_t	sk_pitdrone_health1 = { "sk_pitdrone_health1", "0" };
cvar_t	sk_pitdrone_health2 = { "sk_pitdrone_health2", "0" };
cvar_t	sk_pitdrone_health3 = { "sk_pitdrone_health3", "0" };

cvar_t	sk_pitdrone_dmg_bite1 = { "sk_pitdrone_dmg_bite1", "0" };
cvar_t	sk_pitdrone_dmg_bite2 = { "sk_pitdrone_dmg_bite2", "0" };
cvar_t	sk_pitdrone_dmg_bite3 = { "sk_pitdrone_dmg_bite3", "0" };

cvar_t	sk_pitdrone_dmg_whip1 = { "sk_pitdrone_dmg_whip1", "0" };
cvar_t	sk_pitdrone_dmg_whip2 = { "sk_pitdrone_dmg_whip2", "0" };
cvar_t	sk_pitdrone_dmg_whip3 = { "sk_pitdrone_dmg_whip3", "0" };

cvar_t	sk_pitdrone_dmg_spit1 = { "sk_pitdrone_dmg_spit1", "0" };
cvar_t	sk_pitdrone_dmg_spit2 = { "sk_pitdrone_dmg_spit2", "0" };
cvar_t	sk_pitdrone_dmg_spit3 = { "sk_pitdrone_dmg_spit3", "0" };

// Hgrunt Ally
cvar_t	sk_hgrunt_ally_health1 = { "sk_hgrunt_ally_health1", "0" };
cvar_t	sk_hgrunt_ally_health2 = { "sk_hgrunt_ally_health2", "0" };
cvar_t	sk_hgrunt_ally_health3 = { "sk_hgrunt_ally_health3", "0" };

cvar_t	sk_hgrunt_ally_kick1 = { "sk_hgrunt_ally_kick1", "0" };
cvar_t	sk_hgrunt_ally_kick2 = { "sk_hgrunt_ally_kick2", "0" };
cvar_t	sk_hgrunt_ally_kick3 = { "sk_hgrunt_ally_kick3", "0" };

cvar_t	sk_hgrunt_ally_pellets1 = { "sk_hgrunt_ally_pellets1", "0" };
cvar_t	sk_hgrunt_ally_pellets2 = { "sk_hgrunt_ally_pellets2", "0" };
cvar_t	sk_hgrunt_ally_pellets3 = { "sk_hgrunt_ally_pellets3", "0" };

cvar_t	sk_hgrunt_ally_gspeed1 = { "sk_hgrunt_ally_gspeed1", "0" };
cvar_t	sk_hgrunt_ally_gspeed2 = { "sk_hgrunt_ally_gspeed2", "0" };
cvar_t	sk_hgrunt_ally_gspeed3 = { "sk_hgrunt_ally_gspeed3", "0" };

// Medic Ally 
cvar_t	sk_medic_ally_health1 = { "sk_medic_ally_health1", "0" };
cvar_t	sk_medic_ally_health2 = { "sk_medic_ally_health2", "0" };
cvar_t	sk_medic_ally_health3 = { "sk_medic_ally_health3", "0" };

cvar_t	sk_medic_ally_kick1 = { "sk_medic_ally_kick1", "0" };
cvar_t	sk_medic_ally_kick2 = { "sk_medic_ally_kick2", "0" };
cvar_t	sk_medic_ally_kick3 = { "sk_medic_ally_kick3", "0" };

cvar_t	sk_medic_ally_gspeed1 = { "sk_medic_ally_gspeed1", "0" };
cvar_t	sk_medic_ally_gspeed2 = { "sk_medic_ally_gspeed2", "0" };
cvar_t	sk_medic_ally_gspeed3 = { "sk_medic_ally_gspeed3", "0" };

cvar_t	sk_medic_ally_heal1 = { "sk_medic_ally_heal1", "0" };
cvar_t	sk_medic_ally_heal2 = { "sk_medic_ally_heal2", "0" };
cvar_t	sk_medic_ally_heal3 = { "sk_medic_ally_heal3", "0" };

// Torch Ally 
cvar_t	sk_torch_ally_health1 = { "sk_torch_ally_health1", "0" };
cvar_t	sk_torch_ally_health2 = { "sk_torch_ally_health2", "0" };
cvar_t	sk_torch_ally_health3 = { "sk_torch_ally_health3", "0" };

cvar_t	sk_torch_ally_kick1 = { "sk_torch_ally_kick1", "0" };
cvar_t	sk_torch_ally_kick2 = { "sk_torch_ally_kick2", "0" };
cvar_t	sk_torch_ally_kick3 = { "sk_torch_ally_kick3", "0" };

cvar_t	sk_torch_ally_gspeed1 = { "sk_torch_ally_gspeed1", "0" };
cvar_t	sk_torch_ally_gspeed2 = { "sk_torch_ally_gspeed2", "0" };
cvar_t	sk_torch_ally_gspeed3 = { "sk_torch_ally_gspeed3", "0" };

// Male Assassin 
cvar_t	sk_massassin_health1 = { "sk_massassin_health1", "0" };
cvar_t	sk_massassin_health2 = { "sk_massassin_health2", "0" };
cvar_t	sk_massassin_health3 = { "sk_massassin_health3", "0" };

cvar_t	sk_massassin_kick1 = { "sk_massassin_kick1", "0" };
cvar_t	sk_massassin_kick2 = { "sk_massassin_kick2", "0" };
cvar_t	sk_massassin_kick3 = { "sk_massassin_kick3", "0" };

cvar_t	sk_massassin_gspeed1 = { "sk_massassin_gspeed1", "0" };
cvar_t	sk_massassin_gspeed2 = { "sk_massassin_gspeed2", "0" };
cvar_t	sk_massassin_gspeed3 = { "sk_massassin_gspeed3", "0" };

// ShockTrooper 
cvar_t	sk_shocktrooper_health1 = { "sk_shocktrooper_health1", "0" };
cvar_t	sk_shocktrooper_health2 = { "sk_shocktrooper_health2", "0" };
cvar_t	sk_shocktrooper_health3 = { "sk_shocktrooper_health3", "0" };

cvar_t	sk_shocktrooper_kick1 = { "sk_shocktrooper_kick1", "0" };
cvar_t	sk_shocktrooper_kick2 = { "sk_shocktrooper_kick2", "0" };
cvar_t	sk_shocktrooper_kick3 = { "sk_shocktrooper_kick3", "0" };

cvar_t	sk_shocktrooper_gspeed1 = { "sk_shocktrooper_gspeed1", "0" };
cvar_t	sk_shocktrooper_gspeed2 = { "sk_shocktrooper_gspeed2", "0" };
cvar_t	sk_shocktrooper_gspeed3 = { "sk_shocktrooper_gspeed3", "0" };

cvar_t	sk_shocktrooper_maxcharge1 = { "sk_shocktrooper_maxcharge1", "0" };
cvar_t	sk_shocktrooper_maxcharge2 = { "sk_shocktrooper_maxcharge2", "0" };
cvar_t	sk_shocktrooper_maxcharge3 = { "sk_shocktrooper_maxcharge3", "0" };

cvar_t	sk_shocktrooper_rchgspeed1 = { "sk_shocktrooper_rchgspeed1", "0" };
cvar_t	sk_shocktrooper_rchgspeed2 = { "sk_shocktrooper_rchgspeed2", "0" };
cvar_t	sk_shocktrooper_rchgspeed3 = { "sk_shocktrooper_rchgspeed3", "0" };

// Scientist
cvar_t	sk_cleansuit_scientist_health1 = { "sk_cleansuit_scientist_health1", "0" };
cvar_t	sk_cleansuit_scientist_health2 = { "sk_cleansuit_scientist_health2", "0" };
cvar_t	sk_cleansuit_scientist_health3 = { "sk_cleansuit_scientist_health3", "0" };

cvar_t	sk_cleansuit_scientist_heal1 = { "sk_cleansuit_scientist_heal1", "0" };
cvar_t	sk_cleansuit_scientist_heal2 = { "sk_cleansuit_scientist_heal2", "0" };
cvar_t	sk_cleansuit_scientist_heal3 = { "sk_cleansuit_scientist_heal3", "0" };

// Voltigore
cvar_t	sk_voltigore_health1 = { "sk_voltigore_health1", "0" };
cvar_t	sk_voltigore_health2 = { "sk_voltigore_health2", "0" };
cvar_t	sk_voltigore_health3 = { "sk_voltigore_health3", "0" };

cvar_t	sk_voltigore_dmg_punch1 = { "sk_voltigore_dmg_punch1", "0" };
cvar_t	sk_voltigore_dmg_punch2 = { "sk_voltigore_dmg_punch2", "0" };
cvar_t	sk_voltigore_dmg_punch3 = { "sk_voltigore_dmg_punch3", "0" };

cvar_t	sk_voltigore_dmg_beam1 = { "sk_voltigore_dmg_beam1", "0" };
cvar_t	sk_voltigore_dmg_beam2 = { "sk_voltigore_dmg_beam2", "0" };
cvar_t	sk_voltigore_dmg_beam3 = { "sk_voltigore_dmg_beam3", "0" };

// Baby Voltigore
cvar_t	sk_babyvoltigore_health1 = { "sk_babyvoltigore_health1", "0" };
cvar_t	sk_babyvoltigore_health2 = { "sk_babyvoltigore_health2", "0" };
cvar_t	sk_babyvoltigore_health3 = { "sk_babyvoltigore_health3", "0" };

cvar_t	sk_babyvoltigore_dmg_punch1 = { "sk_babyvoltigore_dmg_punch1", "0" };
cvar_t	sk_babyvoltigore_dmg_punch2 = { "sk_babyvoltigore_dmg_punch2", "0" };
cvar_t	sk_babyvoltigore_dmg_punch3 = { "sk_babyvoltigore_dmg_punch3", "0" };

// Pitworm
cvar_t	sk_pitworm_health1 = { "sk_pitworm_health1", "0" };
cvar_t	sk_pitworm_health2 = { "sk_pitworm_health2", "0" };
cvar_t	sk_pitworm_health3 = { "sk_pitworm_health3", "0" };

cvar_t	sk_pitworm_dmg_swipe1 = { "sk_pitworm_dmg_swipe1", "0" };
cvar_t	sk_pitworm_dmg_swipe2 = { "sk_pitworm_dmg_swipe2", "0" };
cvar_t	sk_pitworm_dmg_swipe3 = { "sk_pitworm_dmg_swipe3", "0" };

cvar_t	sk_pitworm_dmg_beam1 = { "sk_pitworm_dmg_beam1", "0" };
cvar_t	sk_pitworm_dmg_beam2 = { "sk_pitworm_dmg_beam2", "0" };
cvar_t	sk_pitworm_dmg_beam3 = { "sk_pitworm_dmg_beam3", "0" };

// Geneworm
cvar_t	sk_geneworm_health1 = { "sk_geneworm_health1", "0" };
cvar_t	sk_geneworm_health2 = { "sk_geneworm_health2", "0" };
cvar_t	sk_geneworm_health3 = { "sk_geneworm_health3", "0" };

cvar_t	sk_geneworm_dmg_spit1 = { "sk_geneworm_dmg_spit1", "0" };
cvar_t	sk_geneworm_dmg_spit2 = { "sk_geneworm_dmg_spit2", "0" };
cvar_t	sk_geneworm_dmg_spit3 = { "sk_geneworm_dmg_spit3", "0" };

cvar_t	sk_geneworm_dmg_hit1 = { "sk_geneworm_dmg_hit1", "0" };
cvar_t	sk_geneworm_dmg_hit2 = { "sk_geneworm_dmg_hit2", "0" };
cvar_t	sk_geneworm_dmg_hit3 = { "sk_geneworm_dmg_hit3", "0" };


// Zombie Barney
cvar_t	sk_zombie_barney_health1 = { "sk_zombie_barney_health1", "0" };
cvar_t	sk_zombie_barney_health2 = { "sk_zombie_barney_health2", "0" };
cvar_t	sk_zombie_barney_health3 = { "sk_zombie_barney_health3", "0" };

cvar_t	sk_zombie_barney_dmg_one_slash1 = { "sk_zombie_barney_dmg_one_slash1", "0" };
cvar_t	sk_zombie_barney_dmg_one_slash2 = { "sk_zombie_barney_dmg_one_slash2", "0" };
cvar_t	sk_zombie_barney_dmg_one_slash3 = { "sk_zombie_barney_dmg_one_slash3", "0" };

cvar_t	sk_zombie_barney_dmg_both_slash1 = { "sk_zombie_barney_dmg_both_slash1", "0" };
cvar_t	sk_zombie_barney_dmg_both_slash2 = { "sk_zombie_barney_dmg_both_slash2", "0" };
cvar_t	sk_zombie_barney_dmg_both_slash3 = { "sk_zombie_barney_dmg_both_slash3", "0" };

// Zombie Soldier
cvar_t	sk_zombie_soldier_health1 = { "sk_zombie_soldier_health1", "0" };
cvar_t	sk_zombie_soldier_health2 = { "sk_zombie_soldier_health2", "0" };
cvar_t	sk_zombie_soldier_health3 = { "sk_zombie_soldier_health3", "0" };

cvar_t	sk_zombie_soldier_dmg_one_slash1 = { "sk_zombie_soldier_dmg_one_slash1", "0" };
cvar_t	sk_zombie_soldier_dmg_one_slash2 = { "sk_zombie_soldier_dmg_one_slash2", "0" };
cvar_t	sk_zombie_soldier_dmg_one_slash3 = { "sk_zombie_soldier_dmg_one_slash3", "0" };

cvar_t	sk_zombie_soldier_dmg_both_slash1 = { "sk_zombie_soldier_dmg_both_slash1", "0" };
cvar_t	sk_zombie_soldier_dmg_both_slash2 = { "sk_zombie_soldier_dmg_both_slash2", "0" };
cvar_t	sk_zombie_soldier_dmg_both_slash3 = { "sk_zombie_soldier_dmg_both_slash3", "0" };

// Gonome
cvar_t	sk_gonome_health1 = { "sk_gonome_health1", "0" };
cvar_t	sk_gonome_health2 = { "sk_gonome_health2", "0" };
cvar_t	sk_gonome_health3 = { "sk_gonome_health3", "0" };

cvar_t	sk_gonome_dmg_one_slash1 = { "sk_gonome_dmg_one_slash1", "0" };
cvar_t	sk_gonome_dmg_one_slash2 = { "sk_gonome_dmg_one_slash2", "0" };
cvar_t	sk_gonome_dmg_one_slash3 = { "sk_gonome_dmg_one_slash3", "0" };

cvar_t	sk_gonome_dmg_guts1 = { "sk_gonome_dmg_guts1", "0" };
cvar_t	sk_gonome_dmg_guts2 = { "sk_gonome_dmg_guts2", "0" };
cvar_t	sk_gonome_dmg_guts3 = { "sk_gonome_dmg_guts3", "0" };

cvar_t	sk_gonome_dmg_one_bite1 = { "sk_gonome_dmg_one_bite1", "0" };
cvar_t	sk_gonome_dmg_one_bite2 = { "sk_gonome_dmg_one_bite2", "0" };
cvar_t	sk_gonome_dmg_one_bite3 = { "sk_gonome_dmg_one_bite3", "0" };

// Shock Roach
cvar_t	sk_shockroach_health1 = { "sk_shockroach_health1", "0" };
cvar_t	sk_shockroach_health2 = { "sk_shockroach_health2", "0" };
cvar_t	sk_shockroach_health3 = { "sk_shockroach_health3", "0" };

cvar_t	sk_shockroach_dmg_bite1 = { "sk_shockroach_dmg_bite1", "0" };
cvar_t	sk_shockroach_dmg_bite2 = { "sk_shockroach_dmg_bite2", "0" };
cvar_t	sk_shockroach_dmg_bite3 = { "sk_shockroach_dmg_bite3", "0" };

cvar_t	sk_shockroach_lifespan1 = { "sk_shockroach_lifespan1", "0" };
cvar_t	sk_shockroach_lifespan2 = { "sk_shockroach_lifespan2", "0" };
cvar_t	sk_shockroach_lifespan3 = { "sk_shockroach_lifespan3", "0" };

// Weapons
cvar_t	sk_plr_pipewrench1 = { "sk_plr_pipewrench1", "0" };
cvar_t	sk_plr_pipewrench2 = { "sk_plr_pipewrench2", "0" };
cvar_t	sk_plr_pipewrench3 = { "sk_plr_pipewrench3", "0" };

cvar_t	sk_plr_knife1 = { "sk_plr_knife1", "0" };
cvar_t	sk_plr_knife2 = { "sk_plr_knife2", "0" };
cvar_t	sk_plr_knife3 = { "sk_plr_knife3", "0" };

cvar_t	sk_plr_grapple1 = { "sk_plr_grapple1", "0" };
cvar_t	sk_plr_grapple2 = { "sk_plr_grapple2", "0" };
cvar_t	sk_plr_grapple3 = { "sk_plr_grapple3", "0" };

cvar_t	sk_plr_eagle1 = { "sk_plr_eagle1", "0" };
cvar_t	sk_plr_eagle2 = { "sk_plr_eagle2", "0" };
cvar_t	sk_plr_eagle3 = { "sk_plr_eagle3", "0" };

cvar_t	sk_plr_762_bullet1 = { "sk_plr_762_bullet1", "0" };
cvar_t	sk_plr_762_bullet2 = { "sk_plr_762_bullet2", "0" };
cvar_t	sk_plr_762_bullet3 = { "sk_plr_762_bullet3", "0" };

cvar_t	sk_plr_556_bullet1 = { "sk_plr_556_bullet1", "0" };
cvar_t	sk_plr_556_bullet2 = { "sk_plr_556_bullet2", "0" };
cvar_t	sk_plr_556_bullet3 = { "sk_plr_556_bullet3", "0" };

cvar_t	sk_plr_displacer_self1 = { "sk_plr_displacer_self1", "0" };
cvar_t	sk_plr_displacer_self2 = { "sk_plr_displacer_self2", "0" };
cvar_t	sk_plr_displacer_self3 = { "sk_plr_displacer_self3", "0" };

cvar_t	sk_plr_displacer_other1 = { "sk_plr_displacer_other1", "0" };
cvar_t	sk_plr_displacer_other2 = { "sk_plr_displacer_other2", "0" };
cvar_t	sk_plr_displacer_other3 = { "sk_plr_displacer_other3", "0" };

cvar_t	sk_plr_displacer_radius1 = { "sk_plr_displacer_radius1", "0" };
cvar_t	sk_plr_displacer_radius2 = { "sk_plr_displacer_radius2", "0" };
cvar_t	sk_plr_displacer_radius3 = { "sk_plr_displacer_radius3", "0" };

cvar_t	sk_plr_shockroachs1 = { "sk_plr_shockroachs1", "0" };
cvar_t	sk_plr_shockroachs2 = { "sk_plr_shockroachs2", "0" };
cvar_t	sk_plr_shockroachs3 = { "sk_plr_shockroachs3", "0" };

cvar_t	sk_plr_shockroachm1 = { "sk_plr_shockroachm1", "0" };
cvar_t	sk_plr_shockroachm2 = { "sk_plr_shockroachm2", "0" };
cvar_t	sk_plr_shockroachm3 = { "sk_plr_shockroachm3", "0" };

cvar_t	sk_plr_spore1 = { "sk_plr_spore1", "0" };
cvar_t	sk_plr_spore2 = { "sk_plr_spore2", "0" };
cvar_t	sk_plr_spore3 = { "sk_plr_spore3", "0" };

void CvarRegister_Op4(void)
{
// REGISTER CVARS FOR SKILL LEVEL STUFF
	// Otis
	CVAR_REGISTER(&sk_otis_health1);// {"sk_otis_health1","0"};
	CVAR_REGISTER(&sk_otis_health2);// {"sk_otis_health2","0"};
	CVAR_REGISTER(&sk_otis_health3);// {"sk_otis_health3","0"};

	// Pitdrone
	CVAR_REGISTER(&sk_pitdrone_health1);// { "sk_pitdrone_health1", "0" };
	CVAR_REGISTER(&sk_pitdrone_health2);// { "sk_pitdrone_health2", "0" };
	CVAR_REGISTER(&sk_pitdrone_health3);// { "sk_pitdrone_health3", "0" };

	CVAR_REGISTER(&sk_pitdrone_dmg_bite1);// { "sk_pitdrone_dmg_bite1", "0" };
	CVAR_REGISTER(&sk_pitdrone_dmg_bite2);// { "sk_pitdrone_dmg_bite2", "0" };
	CVAR_REGISTER(&sk_pitdrone_dmg_bite3);// { "sk_pitdrone_dmg_bite3", "0" };

	CVAR_REGISTER(&sk_pitdrone_dmg_whip1);// { "sk_pitdrone_dmg_whip1", "0" };
	CVAR_REGISTER(&sk_pitdrone_dmg_whip2);// { "sk_pitdrone_dmg_whip2", "0" };
	CVAR_REGISTER(&sk_pitdrone_dmg_whip3);// { "sk_pitdrone_dmg_whip3", "0" };

	CVAR_REGISTER(&sk_pitdrone_dmg_spit1);// { "sk_pitdrone_dmg_spit1", "0" };
	CVAR_REGISTER(&sk_pitdrone_dmg_spit2);// { "sk_pitdrone_dmg_spit2", "0" };
	CVAR_REGISTER(&sk_pitdrone_dmg_spit3);// { "sk_pitdrone_dmg_spit3", "0" };

	// Hgrunt Ally
	CVAR_REGISTER(&sk_hgrunt_ally_health1);// { "sk_hgrunt_ally_health1", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_health2);// { "sk_hgrunt_ally_health2", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_health3);// { "sk_hgrunt_ally_health3", "0" };

	CVAR_REGISTER(&sk_hgrunt_ally_kick1);// { "sk_hgrunt_ally_kick1", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_kick2);// { "sk_hgrunt_ally_kick2", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_kick3);// { "sk_hgrunt_ally_kick3", "0" };

	CVAR_REGISTER(&sk_hgrunt_ally_pellets1);// { "sk_hgrunt_ally_pellets1", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_pellets2);// { "sk_hgrunt_ally_pellets2", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_pellets3);// { "sk_hgrunt_ally_pellets3", "0" };

	CVAR_REGISTER(&sk_hgrunt_ally_gspeed1);// { "sk_hgrunt_ally_gspeed1", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_gspeed2);// { "sk_hgrunt_ally_gspeed2", "0" };
	CVAR_REGISTER(&sk_hgrunt_ally_gspeed3);// { "sk_hgrunt_ally_gspeed3", "0" };

	// Medic Ally 
	CVAR_REGISTER(&sk_medic_ally_health1);// { "sk_medic_ally_health1", "0" };
	CVAR_REGISTER(&sk_medic_ally_health2);// { "sk_medic_ally_health2", "0" };
	CVAR_REGISTER(&sk_medic_ally_health3);// { "sk_medic_ally_health3", "0" };

	CVAR_REGISTER(&sk_medic_ally_kick1);// { "sk_medic_ally_kick1", "0" };
	CVAR_REGISTER(&sk_medic_ally_kick2);// { "sk_medic_ally_kick2", "0" };
	CVAR_REGISTER(&sk_medic_ally_kick3);// { "sk_medic_ally_kick3", "0" };

	CVAR_REGISTER(&sk_medic_ally_gspeed1);// { "sk_medic_ally_gspeed1", "0" };
	CVAR_REGISTER(&sk_medic_ally_gspeed2);// { "sk_medic_ally_gspeed2", "0" };
	CVAR_REGISTER(&sk_medic_ally_gspeed3);// { "sk_medic_ally_gspeed3", "0" };

	CVAR_REGISTER(&sk_medic_ally_heal1);// { "sk_medic_ally_heal1", "0" };
	CVAR_REGISTER(&sk_medic_ally_heal2);// { "sk_medic_ally_heal2", "0" };
	CVAR_REGISTER(&sk_medic_ally_heal3);// { "sk_medic_ally_heal3", "0" };

	// Torch Ally 
	CVAR_REGISTER(&sk_torch_ally_health1);// { "sk_torch_ally_health1", "0" };
	CVAR_REGISTER(&sk_torch_ally_health2);// { "sk_torch_ally_health2", "0" };
	CVAR_REGISTER(&sk_torch_ally_health3);// { "sk_torch_ally_health3", "0" };

	CVAR_REGISTER(&sk_torch_ally_kick1);// { "sk_torch_ally_kick1", "0" };
	CVAR_REGISTER(&sk_torch_ally_kick2);// { "sk_torch_ally_kick2", "0" };
	CVAR_REGISTER(&sk_torch_ally_kick3);// { "sk_torch_ally_kick3", "0" };

	CVAR_REGISTER(&sk_torch_ally_gspeed1);// { "sk_torch_ally_gspeed1", "0" };
	CVAR_REGISTER(&sk_torch_ally_gspeed2);// { "sk_torch_ally_gspeed2", "0" };
	CVAR_REGISTER(&sk_torch_ally_gspeed3);// { "sk_torch_ally_gspeed3", "0" };

	// Male Assassin 
	CVAR_REGISTER(&sk_massassin_health1);// { "sk_massassin_health1", "0" };
	CVAR_REGISTER(&sk_massassin_health2);// { "sk_massassin_health2", "0" };
	CVAR_REGISTER(&sk_massassin_health3);// { "sk_massassin_health3", "0" };

	CVAR_REGISTER(&sk_massassin_kick1);// { "sk_massassin_kick1", "0" };
	CVAR_REGISTER(&sk_massassin_kick2);// { "sk_massassin_kick2", "0" };
	CVAR_REGISTER(&sk_massassin_kick3);// { "sk_massassin_kick3", "0" };

	CVAR_REGISTER(&sk_massassin_gspeed1);// { "sk_massassin_gspeed1", "0" };
	CVAR_REGISTER(&sk_massassin_gspeed2);// { "sk_massassin_gspeed2", "0" };
	CVAR_REGISTER(&sk_massassin_gspeed3);// { "sk_massassin_gspeed3", "0" };

	// ShockTrooper 
	CVAR_REGISTER(&sk_shocktrooper_health1);// { "sk_shocktrooper_health1", "0" };
	CVAR_REGISTER(&sk_shocktrooper_health2);// { "sk_shocktrooper_health2", "0" };
	CVAR_REGISTER(&sk_shocktrooper_health3);// { "sk_shocktrooper_health3", "0" };

	CVAR_REGISTER(&sk_shocktrooper_kick1);// { "sk_shocktrooper_kick1", "0" };
	CVAR_REGISTER(&sk_shocktrooper_kick2);// { "sk_shocktrooper_kick2", "0" };
	CVAR_REGISTER(&sk_shocktrooper_kick3);// { "sk_shocktrooper_kick3", "0" };

	CVAR_REGISTER(&sk_shocktrooper_gspeed1);// { "sk_shocktrooper_gspeed1", "0" };
	CVAR_REGISTER(&sk_shocktrooper_gspeed2);// { "sk_shocktrooper_gspeed2", "0" };
	CVAR_REGISTER(&sk_shocktrooper_gspeed3);// { "sk_shocktrooper_gspeed3", "0" };

	CVAR_REGISTER(&sk_shocktrooper_maxcharge1);// { "sk_shocktrooper_maxcharge1", "0" };
	CVAR_REGISTER(&sk_shocktrooper_maxcharge2);// { "sk_shocktrooper_maxcharge2", "0" };
	CVAR_REGISTER(&sk_shocktrooper_maxcharge3);// { "sk_shocktrooper_maxcharge3", "0" };

	CVAR_REGISTER(&sk_shocktrooper_rchgspeed1);// { "sk_shocktrooper_rchgspeed1", "0" };
	CVAR_REGISTER(&sk_shocktrooper_rchgspeed2);// { "sk_shocktrooper_rchgspeed2", "0" };
	CVAR_REGISTER(&sk_shocktrooper_rchgspeed3);// { "sk_shocktrooper_rchgspeed3", "0" };

	// Scientist
	CVAR_REGISTER(&sk_cleansuit_scientist_health1);// { "sk_cleansuit_scientist_health1", "0" };
	CVAR_REGISTER(&sk_cleansuit_scientist_health2);// { "sk_cleansuit_scientist_health2", "0" };
	CVAR_REGISTER(&sk_cleansuit_scientist_health3);// { "sk_cleansuit_scientist_health3", "0" };

	CVAR_REGISTER(&sk_cleansuit_scientist_heal1);// { "sk_cleansuit_scientist_heal1", "0" };
	CVAR_REGISTER(&sk_cleansuit_scientist_heal2);// { "sk_cleansuit_scientist_heal2", "0" };
	CVAR_REGISTER(&sk_cleansuit_scientist_heal3);// { "sk_cleansuit_scientist_heal3", "0" };

	// Voltigore
	CVAR_REGISTER(&sk_voltigore_health1);// { "sk_voltigore_health1", "0" };
	CVAR_REGISTER(&sk_voltigore_health2);// { "sk_voltigore_health2", "0" };
	CVAR_REGISTER(&sk_voltigore_health3);// { "sk_voltigore_health3", "0" };

	CVAR_REGISTER(&sk_voltigore_dmg_punch1);// { "sk_voltigore_dmg_punch1", "0" };
	CVAR_REGISTER(&sk_voltigore_dmg_punch2);// { "sk_voltigore_dmg_punch2", "0" };
	CVAR_REGISTER(&sk_voltigore_dmg_punch3);// { "sk_voltigore_dmg_punch3", "0" };

	CVAR_REGISTER(&sk_voltigore_dmg_beam1);// { "sk_voltigore_dmg_beam1", "0" };
	CVAR_REGISTER(&sk_voltigore_dmg_beam2);// { "sk_voltigore_dmg_beam2", "0" };
	CVAR_REGISTER(&sk_voltigore_dmg_beam3);// { "sk_voltigore_dmg_beam3", "0" };

	// Baby Voltigore
	CVAR_REGISTER(&sk_babyvoltigore_health1);// { "sk_babyvoltigore_health1", "0" };
	CVAR_REGISTER(&sk_babyvoltigore_health2);// { "sk_babyvoltigore_health2", "0" };
	CVAR_REGISTER(&sk_babyvoltigore_health3);// { "sk_babyvoltigore_health3", "0" };

	CVAR_REGISTER(&sk_babyvoltigore_dmg_punch1);// { "sk_babyvoltigore_dmg_punch1", "0" };
	CVAR_REGISTER(&sk_babyvoltigore_dmg_punch2);// { "sk_babyvoltigore_dmg_punch2", "0" };
	CVAR_REGISTER(&sk_babyvoltigore_dmg_punch3);// { "sk_babyvoltigore_dmg_punch3", "0" };

	// Pitworm
	CVAR_REGISTER(&sk_pitworm_health1);// { "sk_pitworm_health1", "0" };
	CVAR_REGISTER(&sk_pitworm_health2);// { "sk_pitworm_health2", "0" };
	CVAR_REGISTER(&sk_pitworm_health3);// { "sk_pitworm_health3", "0" };

	CVAR_REGISTER(&sk_pitworm_dmg_swipe1);// { "sk_pitworm_dmg_swipe1", "0" };
	CVAR_REGISTER(&sk_pitworm_dmg_swipe2);// { "sk_pitworm_dmg_swipe2", "0" };
	CVAR_REGISTER(&sk_pitworm_dmg_swipe3);// { "sk_pitworm_dmg_swipe3", "0" };

	CVAR_REGISTER(&sk_pitworm_dmg_beam1);// { "sk_pitworm_dmg_beam1", "0" };
	CVAR_REGISTER(&sk_pitworm_dmg_beam2);// { "sk_pitworm_dmg_beam2", "0" };
	CVAR_REGISTER(&sk_pitworm_dmg_beam3);// { "sk_pitworm_dmg_beam3", "0" };

	// Geneworm
	CVAR_REGISTER(&sk_geneworm_health1);// { "sk_geneworm_health1", "0" };
	CVAR_REGISTER(&sk_geneworm_health2);// { "sk_geneworm_health2", "0" };
	CVAR_REGISTER(&sk_geneworm_health3);// { "sk_geneworm_health3", "0" };

	CVAR_REGISTER(&sk_geneworm_dmg_spit1);// { "sk_geneworm_dmg_spit1", "0" };
	CVAR_REGISTER(&sk_geneworm_dmg_spit2);// { "sk_geneworm_dmg_spit2", "0" };
	CVAR_REGISTER(&sk_geneworm_dmg_spit3);// { "sk_geneworm_dmg_spit3", "0" };

	CVAR_REGISTER(&sk_geneworm_dmg_hit1);// { "sk_geneworm_dmg_hit1", "0" };
	CVAR_REGISTER(&sk_geneworm_dmg_hit2);// { "sk_geneworm_dmg_hit2", "0" };
	CVAR_REGISTER(&sk_geneworm_dmg_hit3);// { "sk_geneworm_dmg_hit3", "0" };


	// Zombie Barney
	CVAR_REGISTER(&sk_zombie_barney_health1);// { "sk_zombie_barney_health1", "0" };
	CVAR_REGISTER(&sk_zombie_barney_health2);// { "sk_zombie_barney_health2", "0" };
	CVAR_REGISTER(&sk_zombie_barney_health3);// { "sk_zombie_barney_health3", "0" };

	CVAR_REGISTER(&sk_zombie_barney_dmg_one_slash1);// { "sk_zombie_barney_dmg_one_slash1", "0" };
	CVAR_REGISTER(&sk_zombie_barney_dmg_one_slash2);// { "sk_zombie_barney_dmg_one_slash2", "0" };
	CVAR_REGISTER(&sk_zombie_barney_dmg_one_slash3);// { "sk_zombie_barney_dmg_one_slash3", "0" };

	CVAR_REGISTER(&sk_zombie_barney_dmg_both_slash1);// { "sk_zombie_barney_dmg_both_slash1", "0" };
	CVAR_REGISTER(&sk_zombie_barney_dmg_both_slash2);// { "sk_zombie_barney_dmg_both_slash2", "0" };
	CVAR_REGISTER(&sk_zombie_barney_dmg_both_slash3);// { "sk_zombie_barney_dmg_both_slash3", "0" };

	// Zombie Soldier
	CVAR_REGISTER(&sk_zombie_soldier_health1);// { "sk_zombie_soldier_health1", "0" };
	CVAR_REGISTER(&sk_zombie_soldier_health2);// { "sk_zombie_soldier_health2", "0" };
	CVAR_REGISTER(&sk_zombie_soldier_health3);// { "sk_zombie_soldier_health3", "0" };

	CVAR_REGISTER(&sk_zombie_soldier_dmg_one_slash1);// { "sk_zombie_soldier_dmg_one_slash1", "0" };
	CVAR_REGISTER(&sk_zombie_soldier_dmg_one_slash2);// { "sk_zombie_soldier_dmg_one_slash2", "0" };
	CVAR_REGISTER(&sk_zombie_soldier_dmg_one_slash3);// { "sk_zombie_soldier_dmg_one_slash3", "0" };

	CVAR_REGISTER(&sk_zombie_soldier_dmg_both_slash1);// { "sk_zombie_soldier_dmg_both_slash1", "0" };
	CVAR_REGISTER(&sk_zombie_soldier_dmg_both_slash2);// { "sk_zombie_soldier_dmg_both_slash2", "0" };
	CVAR_REGISTER(&sk_zombie_soldier_dmg_both_slash3);// { "sk_zombie_soldier_dmg_both_slash3", "0" };

	// Gonome
	CVAR_REGISTER(&sk_gonome_health1);// { "sk_gonome_health1", "0" };
	CVAR_REGISTER(&sk_gonome_health2);// { "sk_gonome_health2", "0" };
	CVAR_REGISTER(&sk_gonome_health3);// { "sk_gonome_health3", "0" };

	CVAR_REGISTER(&sk_gonome_dmg_one_slash1);// { "sk_gonome_dmg_one_slash1", "0" };
	CVAR_REGISTER(&sk_gonome_dmg_one_slash2);// { "sk_gonome_dmg_one_slash2", "0" };
	CVAR_REGISTER(&sk_gonome_dmg_one_slash3);// { "sk_gonome_dmg_one_slash3", "0" };

	CVAR_REGISTER(&sk_gonome_dmg_guts1);// { "sk_gonome_dmg_guts1", "0" };
	CVAR_REGISTER(&sk_gonome_dmg_guts2);// { "sk_gonome_dmg_guts2", "0" };
	CVAR_REGISTER(&sk_gonome_dmg_guts3);// { "sk_gonome_dmg_guts3", "0" };

	CVAR_REGISTER(&sk_gonome_dmg_one_bite1);// { "sk_gonome_dmg_one_bite1", "0" };
	CVAR_REGISTER(&sk_gonome_dmg_one_bite2);// { "sk_gonome_dmg_one_bite2", "0" };
	CVAR_REGISTER(&sk_gonome_dmg_one_bite3);// { "sk_gonome_dmg_one_bite3", "0" };

	// Shock Roach
	CVAR_REGISTER(&sk_shockroach_health1);// { "sk_shockroach_health1", "0" };
	CVAR_REGISTER(&sk_shockroach_health2);// { "sk_shockroach_health2", "0" };
	CVAR_REGISTER(&sk_shockroach_health3);// { "sk_shockroach_health3", "0" };

	CVAR_REGISTER(&sk_shockroach_dmg_bite1);// { "sk_shockroach_dmg_bite1", "0" };
	CVAR_REGISTER(&sk_shockroach_dmg_bite2);// { "sk_shockroach_dmg_bite2", "0" };
	CVAR_REGISTER(&sk_shockroach_dmg_bite3);// { "sk_shockroach_dmg_bite3", "0" };

	CVAR_REGISTER(&sk_shockroach_lifespan1);// { "sk_shockroach_lifespan1", "0" };
	CVAR_REGISTER(&sk_shockroach_lifespan2);// { "sk_shockroach_lifespan2", "0" };
	CVAR_REGISTER(&sk_shockroach_lifespan3);// { "sk_shockroach_lifespan3", "0" };

	// Weapons
	CVAR_REGISTER(&sk_plr_pipewrench1);// { "sk_plr_pipewrench1", "0" };
	CVAR_REGISTER(&sk_plr_pipewrench2);// { "sk_plr_pipewrench2", "0" };
	CVAR_REGISTER(&sk_plr_pipewrench3);// { "sk_plr_pipewrench3", "0" };

	CVAR_REGISTER(&sk_plr_knife1);// { "sk_plr_knife1", "0" };
	CVAR_REGISTER(&sk_plr_knife2);// { "sk_plr_knife2", "0" };
	CVAR_REGISTER(&sk_plr_knife3);// { "sk_plr_knife3", "0" };

	CVAR_REGISTER(&sk_plr_grapple1);// { "sk_plr_grapple1", "0" };
	CVAR_REGISTER(&sk_plr_grapple2);// { "sk_plr_grapple2", "0" };
	CVAR_REGISTER(&sk_plr_grapple3);// { "sk_plr_grapple3", "0" };

	CVAR_REGISTER(&sk_plr_eagle1);// { "sk_plr_eagle1", "0" };
	CVAR_REGISTER(&sk_plr_eagle2);// { "sk_plr_eagle2", "0" };
	CVAR_REGISTER(&sk_plr_eagle3);// { "sk_plr_eagle3", "0" };

	CVAR_REGISTER(&sk_plr_762_bullet1);// { "sk_plr_762_bullet1", "0" };
	CVAR_REGISTER(&sk_plr_762_bullet2);// { "sk_plr_762_bullet2", "0" };
	CVAR_REGISTER(&sk_plr_762_bullet3);// { "sk_plr_762_bullet3", "0" };

	CVAR_REGISTER(&sk_plr_556_bullet1);// { "sk_plr_556_bullet1", "0" };
	CVAR_REGISTER(&sk_plr_556_bullet2);// { "sk_plr_556_bullet2", "0" };
	CVAR_REGISTER(&sk_plr_556_bullet3);// { "sk_plr_556_bullet3", "0" };

	CVAR_REGISTER(&sk_plr_displacer_self1);// { "sk_plr_displacer_self1", "0" };
	CVAR_REGISTER(&sk_plr_displacer_self2);// { "sk_plr_displacer_self2", "0" };
	CVAR_REGISTER(&sk_plr_displacer_self3);// { "sk_plr_displacer_self3", "0" };

	CVAR_REGISTER(&sk_plr_displacer_other1);// { "sk_plr_displacer_other1", "0" };
	CVAR_REGISTER(&sk_plr_displacer_other2);// { "sk_plr_displacer_other2", "0" };
	CVAR_REGISTER(&sk_plr_displacer_other3);// { "sk_plr_displacer_other3", "0" };

	CVAR_REGISTER(&sk_plr_displacer_radius1);// { "sk_plr_displacer_radius1", "0" };
	CVAR_REGISTER(&sk_plr_displacer_radius2);// { "sk_plr_displacer_radius2", "0" };
	CVAR_REGISTER(&sk_plr_displacer_radius3);// { "sk_plr_displacer_radius3", "0" };

	CVAR_REGISTER(&sk_plr_shockroachs1);// { "sk_plr_shockroachs1", "0" };
	CVAR_REGISTER(&sk_plr_shockroachs2);// { "sk_plr_shockroachs2", "0" };
	CVAR_REGISTER(&sk_plr_shockroachs3);// { "sk_plr_shockroachs3", "0" };

	CVAR_REGISTER(&sk_plr_shockroachm1);// { "sk_plr_shockroachm1", "0" };
	CVAR_REGISTER(&sk_plr_shockroachm2);// { "sk_plr_shockroachm2", "0" };
	CVAR_REGISTER(&sk_plr_shockroachm3);// { "sk_plr_shockroachm3", "0" };

	CVAR_REGISTER(&sk_plr_spore1);// { "sk_plr_spore1", "0" };
	CVAR_REGISTER(&sk_plr_spore2);// { "sk_plr_spore2", "0" };
	CVAR_REGISTER(&sk_plr_spore3);// { "sk_plr_spore3", "0" };
// END REGISTER CVARS FOR SKILL LEVEL STUFF
}

void ExecSkills_Op4( void )
{
	SERVER_COMMAND("exec skillopfor.cfg\n");
}