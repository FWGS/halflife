
#ifndef GEARBOX_SKILL_H
#define GEARBOX_SKILL_H

#if defined ( GEARBOX_DLL )

#include "skill.h"

struct gearboxskilldata_t : skilldata_t
{


	// Monster Health & Damage
	float otisHealth;

	// Player Weapons
	float plrDmgDisplacer;
	float plrDmgEagle;
	float plrDmgGrapple;
	float plrDmgKnife;
	float plrDmgM249;
	float plrDmgPipeWrench;
	float plrDmgSniperrifle;
	float plrDmgSporelauncher;

	// weapons shared by monsters
	float monDmg9MM;
	float monDmgMP5;
	float monDmg12MM;
	float monDmgHornet;
};

#endif // GEARBOX_DLLL

#endif // GEARBOX_SKILL_H