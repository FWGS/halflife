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

#ifndef GEARBOX_GAMERULES_H
#define GEARBOX_GAMERULES_H

#include "gamerules.h"

//=========================================================
// CGearboxRules - rules for the single player 
// Half-Life : Opposing Force game.
//=========================================================
class CGearboxRules : public CHalfLifeRules
{
public:
	CGearboxRules(void);

	virtual void RefreshSkillData(void);
};

//=========================================================
// CGearboxMultiplay - rules for the basic half life multiplayer
// competition
//=========================================================
class CGearboxMultiplay : public CHalfLifeMultiplay
{
public:
	CGearboxMultiplay();

	virtual void RefreshSkillData(void);
};


#endif // GEARBOX_GAMERULES_H