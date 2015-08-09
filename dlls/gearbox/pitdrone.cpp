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
// pitdrone
//=========================================================

#include	"extdll.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"schedule.h"
#include	"nodes.h"
#include	"effects.h"
#include	"decals.h"
#include	"soundent.h"
#include	"game.h"
#include	"bullsquid.h"

extern int iSquidSpitSprite;

#define		PITDRONE_SPRINT_DIST				256 // how close the squid has to get before starting to sprint and refusing to swerve

#define		PITDRONE_TOLERANCE_MELEE1_RANGE		85
#define		PITDRONE_TOLERANCE_MELEE2_RANGE		85

#define		PITDRONE_TOLERANCE_MELEE1_DOT		0.7
#define		PITDRONE_TOLERANCE_MELEE2_DOT		0.7

#define		PITDRONE_MELEE_ATTACK_RADIUS		70

//=========================================================
// Monster's Anim Events Go Here
//=========================================================

#define PITDRONE_AE_THROW			( 1 )
#define PITDRONE_AE_SLASH_BOTH		( 2 )
#define PITDRONE_AE_SLASH_SINGLE	( 4 )

//=========================================================
// CPitdrone
//=========================================================
class CPitdrone : public CBullsquid
{
public:

	void Spawn(void);
	void Precache(void);

	void KeyValue(KeyValueData *pkvd);

	int  Classify(void);
	void HandleAnimEvent(MonsterEvent_t *pEvent);
	void IdleSound(void);
	void PainSound(void);
	void DeathSound(void);
	void AlertSound(void);
	void AttackSound(void);
	void StartTask(Task_t *pTask);

	BOOL CheckMeleeAttack1(float flDot, float flDist);
	BOOL CheckMeleeAttack2(float flDot, float flDist);
	BOOL CheckRangeAttack1(float flDot, float flDist);
	void RunAI(void);

	int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	int IRelationship(CBaseEntity *pTarget);
	int IgnoreConditions(void);

	int	Save(CSave &save);
	int Restore(CRestore &restore);
	static TYPEDESCRIPTION m_SaveData[];

protected:

	int m_nAmmoCount;
	int m_fRightSlash;
};

LINK_ENTITY_TO_CLASS(monster_pitdrone, CPitdrone);

TYPEDESCRIPTION	CPitdrone::m_SaveData[] =
{
	DEFINE_FIELD(CPitdrone, m_nAmmoCount, FIELD_INTEGER),
	DEFINE_FIELD(CPitdrone, m_fRightSlash, FIELD_BOOLEAN),
};

IMPLEMENT_SAVERESTORE(CPitdrone, CBullsquid);

void CPitdrone::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "initammo"))
	{
		m_nAmmoCount = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBullsquid::KeyValue(pkvd);
}


//=========================================================
// Classify - indicates this monster's place in the 
// relationship table.
//=========================================================
int	CPitdrone::Classify(void)
{
	return	CLASS_ALIEN_MONSTER;
}

//=========================================================
// IgnoreConditions 
//=========================================================
int CPitdrone::IgnoreConditions(void)
{
	return CBaseMonster::IgnoreConditions();
}

//=========================================================
// IRelationship - overridden for gonome
//=========================================================
int CPitdrone::IRelationship(CBaseEntity *pTarget)
{
	return CBaseMonster::IRelationship(pTarget);
}

//=========================================================
// TakeDamage - overridden for gonome so we can keep track
// of how much time has passed since it was last injured
//=========================================================
int CPitdrone::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	float flDist;
	Vector vecApex;

	// if the squid is running, has an enemy, was hurt by the enemy, hasn't been hurt in the last 3 seconds, and isn't too close to the enemy,
	// it will swerve. (whew).
	if (m_hEnemy != NULL && IsMoving() && pevAttacker == m_hEnemy->pev && gpGlobals->time - m_flLastHurtTime > 3)
	{
		flDist = (pev->origin - m_hEnemy->pev->origin).Length2D();

		if (flDist > PITDRONE_SPRINT_DIST)
		{
			flDist = (pev->origin - m_Route[m_iRouteIndex].vecLocation).Length2D();// reusing flDist. 

			if (FTriangulate(pev->origin, m_Route[m_iRouteIndex].vecLocation, flDist * 0.5, m_hEnemy, &vecApex))
			{
				InsertWaypoint(vecApex, bits_MF_TO_DETOUR | bits_MF_DONT_SIMPLIFY);
			}
		}
	}

	return CBaseMonster::TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}


//=========================================================
// CheckRangeAttack1
//=========================================================
BOOL CPitdrone::CheckRangeAttack1(float flDot, float flDist)
{
	if (IsMoving() && flDist >= 512)
	{
		// squid will far too far behind if he stops running to spit at this distance from the enemy.
		return FALSE;
	}

	if (flDist > 64 && flDist <= 784 && flDot >= 0.5 && gpGlobals->time >= m_flNextSpitTime)
	{
		if (m_hEnemy != NULL)
		{
			if (fabs(pev->origin.z - m_hEnemy->pev->origin.z) > 256)
			{
				// don't try to spit at someone up really high or down really low.
				return FALSE;
			}
		}

		if (IsMoving())
		{
			// don't spit again for a long time, resume chasing enemy.
			m_flNextSpitTime = gpGlobals->time + 5;
		}
		else
		{
			// not moving, so spit again pretty soon.
			m_flNextSpitTime = gpGlobals->time + 0.5;
		}

		return TRUE;
	}

	return FALSE;
}

//=========================================================
// CheckMeleeAttack1 - pitdrone is a big guy, so has a longer
// melee range than most monsters. This is the tailwhip attack
//=========================================================
BOOL CPitdrone::CheckMeleeAttack1(float flDot, float flDist)
{

	if (m_hEnemy->pev->health <= gSkillData.pitdroneDmgWhip && 
		flDist <= PITDRONE_TOLERANCE_MELEE1_RANGE &&
		flDot >= PITDRONE_TOLERANCE_MELEE1_DOT)
	{
		return TRUE;
	}

	return FALSE;
}

//=========================================================
// CheckMeleeAttack2 - pitdrone is a big guy, so has a longer
// melee range than most monsters. This is the bite attack.
// this attack will not be performed if the tailwhip attack
// is valid.
//=========================================================
BOOL CPitdrone::CheckMeleeAttack2(float flDot, float flDist)
{
	if (flDist <= PITDRONE_TOLERANCE_MELEE2_RANGE &&
		flDot >= PITDRONE_TOLERANCE_MELEE2_DOT &&
		!HasConditions(bits_COND_CAN_MELEE_ATTACK1))
	{
		return TRUE;
	}

	return FALSE;
}


//=========================================================
// IdleSound 
//=========================================================
#define PITDRONE_ATTN_IDLE	(float)1.5
void CPitdrone::IdleSound(void)
{
	switch (RANDOM_LONG(0, 2))
	{
	case 0:
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_idle1.wav", 1, PITDRONE_ATTN_IDLE);
		break;
	case 1:
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_idle2.wav", 1, PITDRONE_ATTN_IDLE);
		break;
	case 2:
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_idle3.wav", 1, PITDRONE_ATTN_IDLE);
		break;
	}
}

//=========================================================
// PainSound 
//=========================================================
void CPitdrone::PainSound(void)
{
	int iPitch = RANDOM_LONG(85, 120);

	switch (RANDOM_LONG(0, 3))
	{
	case 0:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_pain1.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	case 1:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_pain2.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	case 2:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_pain3.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	case 3:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_pain4.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	}
}

//=========================================================
// AlertSound
//=========================================================
void CPitdrone::AlertSound(void)
{
	int iPitch = RANDOM_LONG(140, 160);

	switch (RANDOM_LONG(0, 2))
	{
	case 0:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_alert1.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	case 1:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_alert2.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	case 2:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "pitdrone/pitdrone_alert3.wav", 1, ATTN_NORM, 0, iPitch);
		break;
	}
}



//=========================================================
// HandleAnimEvent - catches the monster-specific messages
// that occur when tagged animation frames are played.
//=========================================================
void CPitdrone::HandleAnimEvent(MonsterEvent_t *pEvent)
{
	switch (pEvent->event)
	{

	case PITDRONE_AE_THROW:
	{
		Vector	vecSpitOffset;
		Vector	vecSpitDir;

		UTIL_MakeVectors(pev->angles);

		// !!!HACKHACK - the spot at which the spit originates (in front of the mouth) was measured in 3ds and hardcoded here.
		// we should be able to read the position of bones at runtime for this info.


		Vector vecArmPos, vecArmAng;
		GetAttachment(0, vecArmPos, vecArmAng);

		//vecSpitOffset = (gpGlobals->v_right * 8 + gpGlobals->v_forward * 37 + gpGlobals->v_up * 23);
		//vecSpitOffset = (pev->origin + vecSpitOffset);
		vecSpitOffset = vecArmPos;
		vecSpitDir = ((m_hEnemy->pev->origin + m_hEnemy->pev->view_ofs) - vecSpitOffset).Normalize();

		vecSpitDir.x += RANDOM_FLOAT(-0.05, 0.05);
		vecSpitDir.y += RANDOM_FLOAT(-0.05, 0.05);
		vecSpitDir.z += RANDOM_FLOAT(-0.05, 0);

		// do stuff for this event.
		AttackSound();

		// spew the spittle temporary ents.
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecSpitOffset);
		WRITE_BYTE(TE_SPRITE_SPRAY);
		WRITE_COORD(vecSpitOffset.x);	// pos
		WRITE_COORD(vecSpitOffset.y);
		WRITE_COORD(vecSpitOffset.z);
		WRITE_COORD(vecSpitDir.x);	// dir
		WRITE_COORD(vecSpitDir.y);
		WRITE_COORD(vecSpitDir.z);
		WRITE_SHORT(iSquidSpitSprite);	// model
		WRITE_BYTE(15);			// count
		WRITE_BYTE(210);			// speed
		WRITE_BYTE(25);			// noise ( client will divide by 100 )
		MESSAGE_END();

		CSquidSpit::Shoot(pev, vecSpitOffset, vecSpitDir * 1200); // Default: 900
	}
	break;

	case PITDRONE_AE_SLASH_SINGLE:
	{
		CBaseEntity *pHurt = CheckTraceHullAttack(PITDRONE_MELEE_ATTACK_RADIUS, gSkillData.gonomeDmgOneSlash, DMG_CLUB);
		if (pHurt)
		{
			// Left slash
			if (!m_fRightSlash)
			{
				pHurt->pev->punchangle.z = -20;
				pHurt->pev->punchangle.x = 20;
				pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_right * -100;
				pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_up * 20;
			}
			else // Right slash
			{
				pHurt->pev->punchangle.z = 20;
				pHurt->pev->punchangle.x = 20;
				pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_right * 100;
				pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_up * 20;
			}
		}

		m_fRightSlash = !m_fRightSlash;
	}
	break;

	case PITDRONE_AE_SLASH_BOTH:
	{
		CBaseEntity *pHurt = CheckTraceHullAttack(PITDRONE_MELEE_ATTACK_RADIUS, gSkillData.gonomeDmgOneSlash, DMG_CLUB);
		if (pHurt)
		{
			pHurt->pev->punchangle.x = 20;
			pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_forward * -150;
			pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_up * 20;
		}
	}
	break;

	default:
		CBaseMonster::HandleAnimEvent(pEvent);
	}
}

//=========================================================
// Spawn
//=========================================================
void CPitdrone::Spawn()
{
	Precache();

	SET_MODEL(ENT(pev), "models/pit_drone.mdl");
	UTIL_SetSize(pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX);

	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_STEP;
	m_bloodColor = BLOOD_COLOR_GREEN;
	pev->effects = 0;
	pev->health = gSkillData.pitdroneHealth;
	m_flFieldOfView = 0.2;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState = MONSTERSTATE_NONE;

	m_fCanThreatDisplay = TRUE;
	m_flNextSpitTime = gpGlobals->time;

	m_fRightSlash = FALSE;

	MonsterInit();
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CPitdrone::Precache()
{
	PRECACHE_MODEL("models/pit_drone.mdl");

	PRECACHE_MODEL("sprites/bigspit.spr");// spit projectile.

	iSquidSpitSprite = PRECACHE_MODEL("sprites/tinyspit.spr");// client side spittle.

	PRECACHE_SOUND("zombie/claw_miss2.wav");// because we use the basemonster SWIPE animation event

	PRECACHE_SOUND("pitdrone/pit_drone_attack_spike1.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_attack_spike2.wav");

	PRECACHE_SOUND("pitdrone/pit_drone_communicate1.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_communicate2.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_communicate3.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_communicate4.wav");

	PRECACHE_SOUND("pitdrone/pit_drone_die1.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_die2.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_die3.wav");

	PRECACHE_SOUND("pitdrone/pit_drone_eat.wav");

	PRECACHE_SOUND("pitdrone/pit_drone_hunt1.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_hunt2.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_hunt3.wav");

	PRECACHE_SOUND("pitdrone/pit_drone_idle1.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_idle2.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_idle3.wav");

	PRECACHE_SOUND("bullchicken/pit_drone_melee_attack1.wav");
	PRECACHE_SOUND("bullchicken/pit_drone_melee_attack2.wav");

	PRECACHE_SOUND("pitdrone/pit_drone_pain1.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_pain2.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_pain3.wav");
	PRECACHE_SOUND("pitdrone/pit_drone_pain4.wav");

	PRECACHE_SOUND("bullchicken/bc_acid1.wav");

	PRECACHE_SOUND("bullchicken/bc_bite2.wav");
	PRECACHE_SOUND("bullchicken/bc_bite3.wav");

	PRECACHE_SOUND("bullchicken/bc_spithit1.wav");
	PRECACHE_SOUND("bullchicken/bc_spithit2.wav");
}

//=========================================================
// DeathSound
//=========================================================
void CPitdrone::DeathSound(void)
{
	switch (RANDOM_LONG(0, 2))
	{
	case 0:
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "pitdrone/pit_drone_die1.wav", 1, ATTN_NORM);
		break;
	case 1:
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "pitdrone/pit_drone_die2.wav", 1, ATTN_NORM);
		break;
	case 2:
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "pitdrone/pit_drone_die3.wav", 1, ATTN_NORM);
		break;
	}
}

//=========================================================
// AttackSound
//=========================================================
void CPitdrone::AttackSound(void)
{
	switch (RANDOM_LONG(0, 1))
	{
	case 0:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "pitdrone/pit_drone_attack_spike1.wav", 1, ATTN_NORM);
		break;
	case 1:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "pitdrone/pit_drone_attack_spike2.wav", 1, ATTN_NORM);
		break;
	}
}

//========================================================
// RunAI - overridden for pitdrone because there are things
// that need to be checked every think.
//========================================================
void CPitdrone::RunAI(void)
{
	// first, do base class stuff
	CBaseMonster::RunAI();

	if (m_hEnemy != NULL && m_Activity == ACT_RUN)
	{
		// chasing enemy. Sprint for last bit
		if ((pev->origin - m_hEnemy->pev->origin).Length2D() < PITDRONE_SPRINT_DIST)
		{
			pev->framerate = 1.25;
		}
	}

}


//=========================================================
// Start task - selects the correct activity and performs
// any necessary calculations to start the next task on the
// schedule.  OVERRIDDEN for pitdrone because it needs to
// know explicitly when the last attempt to chase the enemy
// failed, since that impacts its attack choices.
//=========================================================
void CPitdrone::StartTask(Task_t *pTask)
{
	m_iTaskStatus = TASKSTATUS_RUNNING;

	switch (pTask->iTask)
	{
	case TASK_MELEE_ATTACK2:
		CBaseMonster::StartTask(pTask);
		break;

	default:
		CBullsquid::StartTask(pTask);
		break;

	}
}