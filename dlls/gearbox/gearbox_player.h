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
#ifndef GEARBOX_PLAYER_H
#define GEARBOX_PLAYER_H

class CGearboxPlayer : public CBasePlayer
{
public:
	virtual int		Save(CSave &save);
	virtual int		Restore(CRestore &restore);

	BOOL	FlashlightIsOn(void);
	void	FlashlightTurnOn(void);
	void	FlashlightTurnOff(void);

	static	TYPEDESCRIPTION m_playerSaveData[];

private:
	BOOL	m_fInXen;

	friend class CDisplacer;
};

#endif // GEARBOX_PLAYER_H