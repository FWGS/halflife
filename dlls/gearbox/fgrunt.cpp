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
// friendly grunt
//=========================================================
// UNDONE: Holster weapon?

#include	"extdll.h"
#include	"plane.h"
#include	"util.h"
#include	"cbase.h"
#include	"monsters.h"
#include	"talkmonster.h"
#include	"schedule.h"
#include	"animation.h"
#include	"weapons.h"
#include	"talkmonster.h"
#include	"soundent.h"
#include	"effects.h"
#include	"customentity.h"

extern int g_fGruntQuestion;		// true if an idle grunt asked a question. Cleared when someone answers.

extern DLL_GLOBAL int		g_iSkillLevel;

extern Schedule_t	slIdleStand[];

//=========================================================
// monster-specific DEFINE's
//=========================================================
#define	FGRUNT_CLIP_SIZE_MP5				36		// how many bullets in a clip? - NOTE: 3 round burst sound, so keep as 3 * x!
#define	FGRUNT_CLIP_SIZE_SAW				50		// Same as above
#define FGRUNT_VOL						0.35		// volume of grunt sounds
#define FGRUNT_ATTN						ATTN_NORM	// attenutation of grunt sentences
#define FGRUNT_LIMP_HEALTH				20
#define FGRUNT_DMG_HEADSHOT				( DMG_BULLET | DMG_CLUB )	// damage types that can kill a grunt with a single headshot.
#define FGRUNT_NUM_HEADS				8 // how many grunt heads are there? 
#define FGRUNT_MINIMUM_HEADSHOT_DAMAGE	15 // must do at least this much damage in one shot to head to score a headshot kill
#define	FGRUNT_SENTENCE_VOLUME			(float)0.35 // volume of grunt sentences

#define FGRUNT_9MMAR				( 1 << 0 )
#define FGRUNT_HANDGRENADE			( 1 << 1 )
#define FGRUNT_GRENADELAUNCHER		( 1 << 2 )
#define FGRUNT_SHOTGUN				( 1 << 3 )
#define FGRUNT_SAW					( 1 << 4 )

#define HEAD_GROUP					1
#define TORSO_GROUP					2
#define GUN_GROUP					3

#define HEAD_GASMASK				0
#define HEAD_BERET					1
#define HEAD_OPS_MASK				2
#define HEAD_BANDANA_WHITE			3
#define HEAD_BANDANA_BLACK			4
#define HEAD_MP						5
#define HEAD_MAJOR					6
#define HEAD_BERET_BLACK			7

#define TORSO_BACKPACK				0
#define TORSO_SAW					1
#define TORSO_NOBACKPACK			2
#define TORSO_SHELLS				3

#define GUN_MP5						0
#define GUN_SHOTGUN					1
#define GUN_SAW						2
#define GUN_NONE					3

//=========================================================
// Monster's Anim Events Go Here
//=========================================================
#define		FGRUNT_AE_RELOAD		( 2 )
#define		FGRUNT_AE_KICK			( 3 )
#define		FGRUNT_AE_BURST1		( 4 )
#define		FGRUNT_AE_BURST2		( 5 ) 
#define		FGRUNT_AE_BURST3		( 6 ) 
#define		FGRUNT_AE_GREN_TOSS		( 7 )
#define		FGRUNT_AE_GREN_LAUNCH	( 8 )
#define		FGRUNT_AE_GREN_DROP		( 9 )
#define		FGRUNT_AE_CAUGHT_ENEMY	( 10) // grunt established sight with an enemy (player only) that had previously eluded the squad.
#define		FGRUNT_AE_DROP_GUN		( 11) // grunt (probably dead) is dropping his mp5.

static const char* g_pszDeathSounds[] =
{
	"fgrunt/death1.wav",
	"fgrunt/death2.wav",
	"fgrunt/death3.wav",
	"fgrunt/death4.wav",
	"fgrunt/death5.wav",
	"fgrunt/death6.wav",
};

static const char* g_pszPainSounds[] =
{
	"fgrunt/pain1.wav",
	"fgrunt/pain2.wav",
	"fgrunt/pain3.wav",
	"fgrunt/pain4.wav",
	"fgrunt/pain5.wav",
	"fgrunt/pain6.wav",
};

#define FGRUNT_NUM_DEATH_SOUNDS		ARRAYSIZE( g_pszDeathSounds )
#define FGRUNT_NUM_PAIN_SOUNDS		ARRAYSIZE( g_pszPainSounds )

//=========================================================
// CFGrunt
//=========================================================
class CFGrunt : public CTalkMonster
{
public:
#if 1
	virtual void KeyValue(KeyValueData *pkvd);
#endif

	void Spawn(void);
	void Precache(void);
	void SetYawSpeed(void);
	int  ISoundMask(void);
	void AlertSound(void);
	int  Classify(void);
	void HandleAnimEvent(MonsterEvent_t *pEvent);

	void RunTask(Task_t *pTask);
	void StartTask(Task_t *pTask);
	virtual int	ObjectCaps(void) { return CTalkMonster::ObjectCaps() | FCAP_IMPULSE_USE; }
	int TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType);
	BOOL CheckRangeAttack1(float flDot, float flDist);

	void DeclineFollowing(void);

	// Override these to set behavior
	Schedule_t *GetScheduleOfType(int Type);
	Schedule_t *GetSchedule(void);
	MONSTERSTATE GetIdealState(void);

	void DeathSound(void);
	void PainSound(void);

	void TalkInit(void);

	void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType);
	void Killed(entvars_t *pevAttacker, int iGib);

#if 1

	virtual BOOL IsMedic(void) const { return false; }

	CBaseEntity* DropGun( const Vector& vecSrc, const Vector& vecAngles, char* szClassname = NULL );

	void Fire(
		const Vector& vecShootOrigin,
		const Vector& vecShoorDir,
		const Vector& vecSpread,
		int model,
		int effects = EF_MUZZLEFLASH,
		int bulletType = BULLET_MONSTER_MP5,
		int soundType = TE_BOUNCE_SHELL);

	Vector GetGunPosition(void);
	void Shoot(void);
	void Shotgun(void);
	void Saw(void);

	virtual void GibMonster(void);
	void SpeakSentence(void);
	virtual BOOL FOkToSpeak(void);
	void JustSpoke(void);

	CBaseEntity	*Kick(void);
#endif

	virtual int		Save(CSave &save);
	virtual int		Restore(CRestore &restore);
	static	TYPEDESCRIPTION m_SaveData[];

	float	m_painTime;
	float	m_checkAttackTime;
	BOOL	m_lastAttackCheck;

	// UNDONE: What is this for?  It isn't used?
	float	m_flPlayerDamage;// how much pain has the player inflicted on me?



	// checking the feasibility of a grenade toss is kind of costly, so we do it every couple of seconds,
	// not every server frame.
	float m_flNextGrenadeCheck;
	float m_flNextPainTime;
	float m_flLastEnemySightTime;

	Vector	m_vecTossVelocity;

	BOOL	m_fThrowGrenade;
	BOOL	m_fStanding;
	BOOL	m_fFirstEncounter;// only put on the handsign show in the squad's first encounter.
	int		m_cClipSize;

	int m_voicePitch;

	int		m_iBrassShell;
	int		m_iShotgunShell;
	int		m_iSawShell;

	int		m_iSentence;

	static const char *pGruntSentences[];

	CUSTOM_SCHEDULES;

	int head;
	int torso;
};



LINK_ENTITY_TO_CLASS(monster_human_grunt_ally, CFGrunt);

TYPEDESCRIPTION	CFGrunt::m_SaveData[] =
{
	DEFINE_FIELD(CFGrunt, m_painTime, FIELD_TIME),
	DEFINE_FIELD(CFGrunt, m_checkAttackTime, FIELD_TIME),
	DEFINE_FIELD(CFGrunt, m_lastAttackCheck, FIELD_BOOLEAN),
	DEFINE_FIELD(CFGrunt, m_flPlayerDamage, FIELD_FLOAT),

	DEFINE_FIELD(CFGrunt, head, FIELD_INTEGER),
	DEFINE_FIELD(CFGrunt, torso, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CFGrunt, CTalkMonster);



//=========================================================
// AI Schedules Specific to this monster
//=========================================================
Task_t	tlFgFollow[] =
{
	{ TASK_MOVE_TO_TARGET_RANGE, (float)128 },	// Move within 128 of target ent (client)
	{ TASK_SET_SCHEDULE, (float)SCHED_TARGET_FACE },
};

Schedule_t	slFgFollow[] =
{
	{
		tlFgFollow,
		ARRAYSIZE(tlFgFollow),
		bits_COND_NEW_ENEMY |
		bits_COND_LIGHT_DAMAGE |
		bits_COND_HEAVY_DAMAGE |
		bits_COND_HEAR_SOUND |
		bits_COND_PROVOKED,
		bits_SOUND_DANGER,
		"Follow"
	},
};

//=========================================================
// BarneyDraw- much better looking draw schedule for when
// barney knows who he's gonna attack.
//=========================================================
Task_t	tlFgEnemyDraw[] =
{
	{ TASK_STOP_MOVING, 0 },
	{ TASK_FACE_ENEMY, 0 },
	{ TASK_PLAY_SEQUENCE_FACE_ENEMY, (float)ACT_ARM },
};

Schedule_t slFgEnemyDraw[] =
{
	{
		tlFgEnemyDraw,
		ARRAYSIZE(tlFgEnemyDraw),
		0,
		0,
		"FGrunt Enemy Draw"
	}
};

Task_t	tlFgFaceTarget[] =
{
	{ TASK_SET_ACTIVITY, (float)ACT_IDLE },
	{ TASK_FACE_TARGET, (float)0 },
	{ TASK_SET_ACTIVITY, (float)ACT_IDLE },
	{ TASK_SET_SCHEDULE, (float)SCHED_TARGET_CHASE },
};

Schedule_t	slFgFaceTarget[] =
{
	{
		tlFgFaceTarget,
		ARRAYSIZE(tlFgFaceTarget),
		bits_COND_CLIENT_PUSH |
		bits_COND_NEW_ENEMY |
		bits_COND_LIGHT_DAMAGE |
		bits_COND_HEAVY_DAMAGE |
		bits_COND_HEAR_SOUND |
		bits_COND_PROVOKED,
		bits_SOUND_DANGER,
		"FaceTarget"
	},
};


Task_t	tlIdleFgStand[] =
{
	{ TASK_STOP_MOVING, 0 },
	{ TASK_SET_ACTIVITY, (float)ACT_IDLE },
	{ TASK_WAIT, (float)2 }, // repick IDLESTAND every two seconds.
	{ TASK_TLK_HEADRESET, (float)0 }, // reset head position
};

Schedule_t	slIdleFgStand[] =
{
	{
		tlIdleFgStand,
		ARRAYSIZE(tlIdleFgStand),
		bits_COND_NEW_ENEMY |
		bits_COND_LIGHT_DAMAGE |
		bits_COND_HEAVY_DAMAGE |
		bits_COND_HEAR_SOUND |
		bits_COND_SMELL |
		bits_COND_PROVOKED,

		bits_SOUND_COMBAT |// sound flags - change these, and you'll break the talking code.
		//bits_SOUND_PLAYER		|
		//bits_SOUND_WORLD		|

		bits_SOUND_DANGER |
		bits_SOUND_MEAT |// scents
		bits_SOUND_CARCASS |
		bits_SOUND_GARBAGE,
		"IdleStand"
	},
};

DEFINE_CUSTOM_SCHEDULES(CFGrunt)
{
	slFgFollow,
		slFgEnemyDraw,
		slFgFaceTarget,
		slIdleFgStand,
};


IMPLEMENT_CUSTOM_SCHEDULES(CFGrunt, CTalkMonster);


const char *CFGrunt::pGruntSentences[] =
{
	"HG_GREN", // grenade scared grunt
	"HG_ALERT", // sees player
	"HG_MONSTER", // sees monster
	"HG_COVER", // running to cover
	"HG_THROW", // about to throw grenade
	"HG_CHARGE",  // running out to get the enemy
	"HG_TAUNT", // say rude things
};

enum
{
	HGRUNT_SENT_NONE = -1,
	HGRUNT_SENT_GREN = 0,
	HGRUNT_SENT_ALERT,
	HGRUNT_SENT_MONSTER,
	HGRUNT_SENT_COVER,
	HGRUNT_SENT_THROW,
	HGRUNT_SENT_CHARGE,
	HGRUNT_SENT_TAUNT,
} FGRUNT_SENTENCE_TYPES;

//=========================================================
// Speak Sentence - say your cued up sentence.
//
// Some grunt sentences (take cover and charge) rely on actually
// being able to execute the intended action. It's really lame
// when a grunt says 'COVER ME' and then doesn't move. The problem
// is that the sentences were played when the decision to TRY
// to move to cover was made. Now the sentence is played after 
// we know for sure that there is a valid path. The schedule
// may still fail but in most cases, well after the grunt has 
// started moving.
//=========================================================
void CFGrunt::SpeakSentence(void)
{
	if (m_iSentence == HGRUNT_SENT_NONE)
	{
		// no sentence cued up.
		return;
	}

	if (FOkToSpeak())
	{
		SENTENCEG_PlayRndSz(ENT(pev), pGruntSentences[m_iSentence], FGRUNT_SENTENCE_VOLUME, FGRUNT_ATTN, 0, m_voicePitch);
		JustSpoke();
	}
}

//=========================================================
// GibMonster - make gun fly through the air.
//=========================================================
void CFGrunt::GibMonster(void)
{
	Vector	vecGunPos;
	Vector	vecGunAngles;

	if (GetBodygroup(2) != 2)
	{// throw a gun if the grunt has one
		GetAttachment(0, vecGunPos, vecGunAngles);

		CBaseEntity *pGun;
		if (FBitSet(pev->weapons, FGRUNT_SHOTGUN))
		{
			pGun = DropItem("weapon_shotgun", vecGunPos, vecGunAngles);
		}
		else if (FBitSet(pev->weapons, FGRUNT_SAW))
		{
			pGun = DropItem("weapon_m249", vecGunPos, vecGunAngles);
		}
		else
		{
			pGun = DropItem("weapon_9mmAR", vecGunPos, vecGunAngles);
		}
		if (pGun)
		{
			pGun->pev->velocity = Vector(RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(200, 300));
			pGun->pev->avelocity = Vector(0, RANDOM_FLOAT(200, 400), 0);
		}

		if (FBitSet(pev->weapons, FGRUNT_GRENADELAUNCHER))
		{
			pGun = DropItem("ammo_ARgrenades", vecGunPos, vecGunAngles);
			if (pGun)
			{
				pGun->pev->velocity = Vector(RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(200, 300));
				pGun->pev->avelocity = Vector(0, RANDOM_FLOAT(200, 400), 0);
			}
		}
	}

	CTalkMonster::GibMonster();
}

//=========================================================
// ISoundMask - returns a bit mask indicating which types
// of sounds this monster regards. 
//=========================================================
int CFGrunt::ISoundMask(void)
{
	return	bits_SOUND_WORLD |
		bits_SOUND_COMBAT |
		bits_SOUND_CARCASS |
		bits_SOUND_MEAT |
		bits_SOUND_GARBAGE |
		bits_SOUND_DANGER |
		bits_SOUND_PLAYER;
}


//=========================================================
// someone else is talking - don't speak
//=========================================================
BOOL CFGrunt::FOkToSpeak(void)
{
	// if someone else is talking, don't speak
	if (gpGlobals->time <= CTalkMonster::g_talkWaitTime)
		return FALSE;

	if (pev->spawnflags & SF_MONSTER_GAG)
	{
		if (m_MonsterState != MONSTERSTATE_COMBAT)
		{
			// no talking outside of combat if gagged.
			return FALSE;
		}
	}

	// if player is not in pvs, don't speak
	//	if (FNullEnt(FIND_CLIENT_IN_PVS(edict())))
	//		return FALSE;

	return TRUE;
}

//=========================================================
//=========================================================
void CFGrunt::JustSpoke(void)
{
	CTalkMonster::g_talkWaitTime = gpGlobals->time + RANDOM_FLOAT(1.5, 2.0);
	m_iSentence = HGRUNT_SENT_NONE;
}


//=========================================================
// Classify - indicates this monster's place in the 
// relationship table.
//=========================================================
int	CFGrunt::Classify(void)
{
	return	CLASS_PLAYER_ALLY;
}


//=========================================================
//=========================================================
CBaseEntity *CFGrunt::Kick(void)
{
	TraceResult tr;

	UTIL_MakeVectors(pev->angles);
	Vector vecStart = pev->origin;
	vecStart.z += pev->size.z * 0.5;
	Vector vecEnd = vecStart + (gpGlobals->v_forward * 70);

	UTIL_TraceHull(vecStart, vecEnd, dont_ignore_monsters, head_hull, ENT(pev), &tr);

	if (tr.pHit)
	{
		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
		return pEntity;
	}

	return NULL;
}

//=========================================================
// GetGunPosition	return the end of the barrel
//=========================================================

Vector CFGrunt::GetGunPosition()
{
	if (m_fStanding)
	{
		return pev->origin + Vector(0, 0, 60);
	}
	else
	{
		return pev->origin + Vector(0, 0, 48);
	}
}

//=========================================================
// ALertSound - barney says "Freeze!"
//=========================================================
void CFGrunt::AlertSound(void)
{
	if (m_hEnemy != NULL)
	{
		if (FOkToSpeak())
		{
			PlaySentence("FG_ATTACK", RANDOM_FLOAT(2.8, 3.2), VOL_NORM, ATTN_IDLE);
		}
	}

}
//=========================================================
// SetYawSpeed - allows each sequence to have a different
// turn rate associated with it.
//=========================================================
void CFGrunt::SetYawSpeed(void)
{
	int ys;

	ys = 0;

	switch (m_Activity)
	{
	case ACT_IDLE:
		ys = 70;
		break;
	case ACT_WALK:
		ys = 70;
		break;
	case ACT_RUN:
		ys = 90;
		break;
	default:
		ys = 70;
		break;
	}

	pev->yaw_speed = ys;
}


//=========================================================
// CheckRangeAttack1
//=========================================================
BOOL CFGrunt::CheckRangeAttack1(float flDot, float flDist)
{
	if (flDist <= 1024 && flDot >= 0.5)
	{
		if (gpGlobals->time > m_checkAttackTime)
		{
			TraceResult tr;

			Vector shootOrigin = pev->origin + Vector(0, 0, 55);
			CBaseEntity *pEnemy = m_hEnemy;
			Vector shootTarget = ((pEnemy->BodyTarget(shootOrigin) - pEnemy->pev->origin) + m_vecEnemyLKP);
			UTIL_TraceLine(shootOrigin, shootTarget, dont_ignore_monsters, ENT(pev), &tr);
			m_checkAttackTime = gpGlobals->time + 1;
			if (tr.flFraction == 1.0 || (tr.pHit != NULL && CBaseEntity::Instance(tr.pHit) == pEnemy))
				m_lastAttackCheck = TRUE;
			else
				m_lastAttackCheck = FALSE;
			m_checkAttackTime = gpGlobals->time + 1.5;
		}
		return m_lastAttackCheck;
	}
	return FALSE;
}

//=========================================================
// Fire
//=========================================================
void CFGrunt::Fire(const Vector& vecShootOrigin, const Vector& vecShootDir, const Vector& vecSpread, int model, int effects, int bulletType, int soundType)
{
	UTIL_MakeVectors(pev->angles);

	Vector	vecShellVelocity = gpGlobals->v_right * RANDOM_FLOAT(40, 90) + gpGlobals->v_up * RANDOM_FLOAT(75, 200) + gpGlobals->v_forward * RANDOM_FLOAT(-40, 40);
	EjectBrass(vecShootOrigin - vecShootDir * 24, vecShellVelocity, pev->angles.y, model, soundType);
	FireBullets(1, vecShootOrigin, vecShootDir, vecSpread, 2048, bulletType); // shoot +-5 degrees

	pev->effects |= effects;

	Vector angDir = UTIL_VecToAngles(vecShootDir);
	SetBlending(0, angDir.x);
}

//=========================================================
// Shoot
//=========================================================
void CFGrunt::Shoot(void)
{
	if (m_hEnemy == NULL)
	{
		return;
	}

	Fire(GetGunPosition(), ShootAtEnemy(GetGunPosition()), VECTOR_CONE_10DEGREES, m_iBrassShell, EF_MUZZLEFLASH, BULLET_MONSTER_MP5, TE_BOUNCE_SHELL);

	m_cAmmoLoaded--;// take away a bullet!
}

//=========================================================
// Shotgun
//=========================================================
void CFGrunt::Shotgun(void)
{
	if (m_hEnemy == NULL)
	{
		return;
	}

	Fire(GetGunPosition(), ShootAtEnemy(GetGunPosition()), VECTOR_CONE_15DEGREES, m_iShotgunShell, EF_MUZZLEFLASH, BULLET_PLAYER_BUCKSHOT, TE_BOUNCE_SHELL);

	m_cAmmoLoaded--;// take away a bullet!
}

//=========================================================
// Saw
//=========================================================
void CFGrunt::Saw(void)
{
	if (m_hEnemy == NULL)
	{
		return;
	}

	Fire(GetGunPosition(), ShootAtEnemy(GetGunPosition()), VECTOR_CONE_10DEGREES, m_iSawShell, EF_MUZZLEFLASH, BULLET_PLAYER_556, TE_BOUNCE_SHELL);

	m_cAmmoLoaded--;// take away a bullet!
}


//=========================================================
// HandleAnimEvent - catches the monster-specific messages
// that occur when tagged animation frames are played.
//
// Returns number of events handled, 0 if none.
//=========================================================
void CFGrunt::HandleAnimEvent(MonsterEvent_t *pEvent)
{
	Vector	vecShootDir;
	Vector	vecShootOrigin;

	switch (pEvent->event)
	{
	case FGRUNT_AE_DROP_GUN:
	{
		Vector	vecGunPos;
		Vector	vecGunAngles;

		GetAttachment(0, vecGunPos, vecGunAngles);

		// switch to body group with no gun.
		SetBodygroup(GUN_GROUP, GUN_NONE);

		// now spawn a gun.
		DropGun(vecGunPos, vecGunAngles);

		// Drop grenades if supported.
		if (FBitSet(pev->weapons, FGRUNT_GRENADELAUNCHER))
		{
			DropItem("ammo_ARgrenades", BodyTarget(pev->origin), vecGunAngles);
		}

	}
	break;

	case FGRUNT_AE_RELOAD:
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "hgrunt/gr_reload1.wav", 1, ATTN_NORM);
		m_cAmmoLoaded = m_cClipSize;
		ClearConditions(bits_COND_NO_AMMO_LOADED);
		break;

	case FGRUNT_AE_GREN_TOSS:
	{
		UTIL_MakeVectors(pev->angles);
		// CGrenade::ShootTimed( pev, pev->origin + gpGlobals->v_forward * 34 + Vector (0, 0, 32), m_vecTossVelocity, 3.5 );
		CGrenade::ShootTimed(pev, GetGunPosition(), m_vecTossVelocity, 3.5);

		m_fThrowGrenade = FALSE;
		m_flNextGrenadeCheck = gpGlobals->time + 6;// wait six seconds before even looking again to see if a grenade can be thrown.
		// !!!LATER - when in a group, only try to throw grenade if ordered.
	}
	break;

	case FGRUNT_AE_GREN_LAUNCH:
	{
		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/glauncher.wav", 0.8, ATTN_NORM);
		CGrenade::ShootContact(pev, GetGunPosition(), m_vecTossVelocity);
		m_fThrowGrenade = FALSE;
		if (g_iSkillLevel == SKILL_HARD)
			m_flNextGrenadeCheck = gpGlobals->time + RANDOM_FLOAT(2, 5);// wait a random amount of time before shooting again
		else
			m_flNextGrenadeCheck = gpGlobals->time + 6;// wait six seconds before even looking again to see if a grenade can be thrown.
	}
	break;

	case FGRUNT_AE_GREN_DROP:
	{
		UTIL_MakeVectors(pev->angles);
		CGrenade::ShootTimed(pev, pev->origin + gpGlobals->v_forward * 17 - gpGlobals->v_right * 27 + gpGlobals->v_up * 6, g_vecZero, 3);
	}
	break;

	case FGRUNT_AE_BURST1:
	{
		if (FBitSet(pev->weapons, FGRUNT_9MMAR))
		{
			Shoot();

			// the first round of the three round burst plays the sound and puts a sound in the world sound list.
			if (RANDOM_LONG(0, 1))
			{
				EMIT_SOUND(ENT(pev), CHAN_WEAPON, "hgrunt/gr_mgun1.wav", 1, ATTN_NORM);
			}
			else
			{
				EMIT_SOUND(ENT(pev), CHAN_WEAPON, "hgrunt/gr_mgun2.wav", 1, ATTN_NORM);
			}
		}
		else if (FBitSet(pev->weapons, FGRUNT_SAW))
		{
			Saw();

			switch (RANDOM_LONG(0, 2))
			{
			case 0: EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/saw_fire1.wav", 1, ATTN_NORM); break;
			case 1: EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/saw_fire2.wav", 1, ATTN_NORM); break;
			case 2: EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/saw_fire3.wav", 1, ATTN_NORM); break;
			default:
				break;
			}
		}
		else
		{
			Shotgun();

			EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/sbarrel1.wav", 1, ATTN_NORM);
		}

		CSoundEnt::InsertSound(bits_SOUND_COMBAT, pev->origin, 384, 0.3);
	}
	break;

	case FGRUNT_AE_BURST2:
	case FGRUNT_AE_BURST3:
		if (FBitSet(pev->weapons, FGRUNT_9MMAR))
		{
			Shoot();
		}
		else if(FBitSet(pev->weapons, FGRUNT_SAW))
		{
			Saw();
		}
		break;

	case FGRUNT_AE_KICK:
	{
		CBaseEntity *pHurt = Kick();

		if (pHurt)
		{
			// SOUND HERE!
			UTIL_MakeVectors(pev->angles);
			pHurt->pev->punchangle.x = 15;
			pHurt->pev->velocity = pHurt->pev->velocity + gpGlobals->v_forward * 100 + gpGlobals->v_up * 50;
			pHurt->TakeDamage(pev, pev, gSkillData.hgruntDmgKick, DMG_CLUB);
		}
	}
	break;

	case FGRUNT_AE_CAUGHT_ENEMY:
	{
		if (FOkToSpeak())
		{
			SENTENCEG_PlayRndSz(ENT(pev), "FG_ALERT", FGRUNT_SENTENCE_VOLUME, FGRUNT_ATTN, 0, m_voicePitch);
			JustSpoke();
		}

	}

	default:
		CTalkMonster::HandleAnimEvent(pEvent);
		break;
	}
}

//=========================================================
// Spawn
//=========================================================
void CFGrunt::Spawn()
{
	Precache();

	SET_MODEL(ENT(pev), "models/hgrunt_opfor.mdl");
	UTIL_SetSize(pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX);

	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_STEP;
	m_bloodColor = BLOOD_COLOR_RED;
	pev->health = gSkillData.barneyHealth;
	pev->view_ofs = Vector(0, 0, 50);// position of the eyes relative to monster's origin.
	m_flFieldOfView = VIEW_FIELD_WIDE; // NOTE: we need a wide field of view so npc will notice player and say hello
	m_MonsterState = MONSTERSTATE_NONE;

	pev->body = 0; // gun in holster

	m_afCapability = bits_CAP_HEAR | bits_CAP_TURN_HEAD | bits_CAP_DOORS_GROUP;


	// Select a random head.
	if (head == -1)
	{
		SetBodygroup(HEAD_GROUP, RANDOM_LONG(0, FGRUNT_NUM_HEADS - 1 ));
	}
	else
	{
		SetBodygroup(HEAD_GROUP, head);
	}

	if (pev->weapons == 0)
	{
		// initialize to original values
		pev->weapons = FGRUNT_9MMAR | FGRUNT_HANDGRENADE;
	}

	// Setup bodygroups.
	if (FBitSet(pev->weapons, FGRUNT_SHOTGUN))
	{
		torso = TORSO_SHELLS;

		SetBodygroup(TORSO_GROUP, torso);
		SetBodygroup(GUN_GROUP, GUN_SHOTGUN);

		m_cClipSize = 8;
	}
	else if (FBitSet(pev->weapons, FGRUNT_SAW))
	{
		torso = TORSO_SAW;

		SetBodygroup(TORSO_GROUP, torso);
		SetBodygroup(GUN_GROUP, GUN_SAW);

		m_cClipSize = FGRUNT_CLIP_SIZE_SAW;
	}
	else
	{
		torso = TORSO_BACKPACK;

		SetBodygroup(TORSO_GROUP, torso);
		SetBodygroup(GUN_GROUP, GUN_MP5);

		m_cClipSize = FGRUNT_CLIP_SIZE_MP5;
	}


	m_cAmmoLoaded = m_cClipSize;

	MonsterInit();
	SetUse(&CFGrunt::FollowerUse);
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CFGrunt::Precache()
{
	PRECACHE_MODEL("models/hgrunt_opfor.mdl");

	PRECACHE_SOUND("hgrunt/gr_mgun1.wav");
	PRECACHE_SOUND("hgrunt/gr_mgun2.wav");

	PRECACHE_SOUND("hgrunt/saw_fire1.wav");
	PRECACHE_SOUND("hgrunt/saw_fire2.wav");
	PRECACHE_SOUND("hgrunt/saw_fire3.wav");

	PRECACHE_SOUND("hgrunt/gr_reload1.wav");

	PRECACHE_SOUND("weapons/glauncher.wav");

	PRECACHE_SOUND("weapons/sbarrel1.wav");

	PRECACHE_SOUND("zombie/claw_miss2.wav");// because we use the basemonster SWIPE animation event

	PRECACHE_SOUND_ARRAY( g_pszDeathSounds );

	PRECACHE_SOUND_ARRAY( g_pszPainSounds );

	m_iBrassShell = PRECACHE_MODEL("models/shell.mdl");// brass shell
	m_iShotgunShell = PRECACHE_MODEL("models/shotgunshell.mdl");
	m_iSawShell = PRECACHE_MODEL("models/saw_shell.mdl");


	// every new barney must call this, otherwise
	// when a level is loaded, nobody will talk (time is reset to 0)
	TalkInit();
	CTalkMonster::Precache();
}

// Init talk data
void CFGrunt::TalkInit()
{

	CTalkMonster::TalkInit();

	// scientists speach group names (group names are in sentences.txt)

	m_szGrp[TLK_ANSWER] = "FG_ANSWER";
	m_szGrp[TLK_QUESTION] = "FG_QUESTION";
	m_szGrp[TLK_IDLE] = "FG_IDLE";
	m_szGrp[TLK_STARE] = "FG_STARE";
	m_szGrp[TLK_USE] = "FG_OK";
	m_szGrp[TLK_UNUSE] = "FG_WAIT";
	m_szGrp[TLK_STOP] = "FG_STOP";

	m_szGrp[TLK_NOSHOOT] = "FG_SCARED";
	m_szGrp[TLK_HELLO] = "FG_HELLO";

	m_szGrp[TLK_PLHURT1] = "!FG_CUREA";
	m_szGrp[TLK_PLHURT2] = "!FG_CUREB";
	m_szGrp[TLK_PLHURT3] = "!FG_CUREC";

	m_szGrp[TLK_PHELLO] = NULL;
	m_szGrp[TLK_PIDLE] = NULL;	
	m_szGrp[TLK_PQUESTION] = "FG_PQUEST";

	m_szGrp[TLK_SMELL] = "FG_SMELL";

	m_szGrp[TLK_WOUND] = "FG_WOUND";
	m_szGrp[TLK_MORTAL] = "FG_MORTAL";

	// get voice for head - just one barney voice for now
	m_voicePitch = 100;
}


static BOOL IsFacing(entvars_t *pevTest, const Vector &reference)
{
	Vector vecDir = (reference - pevTest->origin);
	vecDir.z = 0;
	vecDir = vecDir.Normalize();
	Vector forward, angle;
	angle = pevTest->v_angle;
	angle.x = 0;
	UTIL_MakeVectorsPrivate(angle, forward, NULL, NULL);
	// He's facing me, he meant it
	if (DotProduct(forward, vecDir) > 0.96)	// +/- 15 degrees or so
	{
		return TRUE;
	}
	return FALSE;
}


int CFGrunt::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType)
{
	// make sure friends talk about it if player hurts talkmonsters...
	int ret = CTalkMonster::TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType);
	if (!IsAlive() || pev->deadflag == DEAD_DYING)
		return ret;

	if (m_MonsterState != MONSTERSTATE_PRONE && (pevAttacker->flags & FL_CLIENT))
	{
		m_flPlayerDamage += flDamage;

		// This is a heurstic to determine if the player intended to harm me
		// If I have an enemy, we can't establish intent (may just be crossfire)
		if (m_hEnemy == NULL)
		{
			// If the player was facing directly at me, or I'm already suspicious, get mad
			if ((m_afMemory & bits_MEMORY_SUSPICIOUS) || IsFacing(pevAttacker, pev->origin))
			{
				// Alright, now I'm pissed!
				PlaySentence("FG_MAD", 4, VOL_NORM, ATTN_NORM);

				Remember(bits_MEMORY_PROVOKED);
				StopFollowing(TRUE);
			}
			else
			{
				// Hey, be careful with that
				PlaySentence("FG_SHOT", 4, VOL_NORM, ATTN_NORM);
				Remember(bits_MEMORY_SUSPICIOUS);
			}
		}
		else if (!(m_hEnemy->IsPlayer()) && pev->deadflag == DEAD_NO)
		{
			PlaySentence("FG_SHOT", 4, VOL_NORM, ATTN_NORM);
		}
	}

	return ret;
}


//=========================================================
// PainSound
//=========================================================
void CFGrunt::PainSound(void)
{
	if (gpGlobals->time < m_painTime)
		return;

	m_painTime = gpGlobals->time + RANDOM_FLOAT(0.5, 0.75);

	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, g_pszPainSounds[ RANDOM_LONG(0, FGRUNT_NUM_PAIN_SOUNDS - 1) ], 1, ATTN_NORM, 0, GetVoicePitch());
}

//=========================================================
// DeathSound 
//=========================================================
void CFGrunt::DeathSound(void)
{
	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, g_pszDeathSounds[RANDOM_LONG(0, FGRUNT_NUM_DEATH_SOUNDS - 1)], 1, ATTN_NORM, 0, GetVoicePitch());
}


//=========================================================
// TractAttack
//=========================================================
void CFGrunt::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	switch (ptr->iHitgroup)
	{
	case HITGROUP_CHEST:
	case HITGROUP_STOMACH:
		if (bitsDamageType & (DMG_BULLET | DMG_SLASH | DMG_BLAST))
		{
			flDamage = flDamage / 2;
		}
		break;
	case 10:
		if (bitsDamageType & (DMG_BULLET | DMG_SLASH | DMG_CLUB))
		{
			flDamage -= 20;
			if (flDamage <= 0)
			{
				UTIL_Ricochet(ptr->vecEndPos, 1.0);
				flDamage = 0.01;
			}
		}
		// always a head shot
		ptr->iHitgroup = HITGROUP_HEAD;
		break;
	}

	CTalkMonster::TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}


void CFGrunt::Killed(entvars_t *pevAttacker, int iGib)
{
	if (GetBodygroup(2) != 2)
	{
		Vector vecGunPos;
		Vector vecGunAngles;

		// throw a gun if the grunt has one
		GetAttachment(0, vecGunPos, vecGunAngles);

		DropGun(vecGunPos, vecGunAngles);
	}

	SetUse(NULL);
	CTalkMonster::Killed(pevAttacker, iGib);
}


//=========================================================
// DropGun
//=========================================================
CBaseEntity* CFGrunt::DropGun(const Vector& vecGunPos, const Vector& vecGunAngles, char* szClassname)
{
	CBaseEntity* pGun = NULL;

	if (szClassname && *szClassname)
	{
		pGun = DropItem(szClassname, vecGunPos, vecGunAngles);

		if (pGun)
		{
			return pGun;
		}
		else
		{
			ALERT(at_console, "ERROR: Could not find classname %s. No such class.\n", szClassname);
		}
	}

	if (FBitSet(pev->weapons, FGRUNT_SHOTGUN))
	{
		pGun = DropItem("weapon_shotgun", vecGunPos, vecGunAngles);
	}
	else if (FBitSet(pev->weapons, FGRUNT_SAW))
	{
		pGun = DropItem("weapon_m249", vecGunPos, vecGunAngles);
	}
	else
	{
		pGun = DropItem("weapon_9mmAR", vecGunPos, vecGunAngles);
	}

	return pGun;
}

//=========================================================
// AI Schedules Specific to this monster
//=========================================================

Schedule_t* CFGrunt::GetScheduleOfType(int Type)
{
	Schedule_t *psched;

	switch (Type)
	{
	case SCHED_ARM_WEAPON:
		if (m_hEnemy != NULL)
		{
			// face enemy, then draw.
			return slFgEnemyDraw;
		}
		break;

		// Hook these to make a looping schedule
	case SCHED_TARGET_FACE:
		// call base class default so that barney will talk
		// when 'used' 
		psched = CTalkMonster::GetScheduleOfType(Type);

		if (psched == slIdleStand)
			return slFgFaceTarget;	// override this for different target face behavior
		else
			return psched;

	case SCHED_TARGET_CHASE:
		return slFgFollow;

	case SCHED_IDLE_STAND:
		// call base class default so that scientist will talk
		// when standing during idle
		psched = CTalkMonster::GetScheduleOfType(Type);

		if (psched == slIdleStand)
		{
			// just look straight ahead.
			return slIdleFgStand;
		}
		else
			return psched;
	}

	return CTalkMonster::GetScheduleOfType(Type);
}

//=========================================================
// GetSchedule - Decides which type of schedule best suits
// the monster's current state and conditions. Then calls
// monster's member function to get a pointer to a schedule
// of the proper type.
//=========================================================
Schedule_t *CFGrunt::GetSchedule(void)
{
	if (HasConditions(bits_COND_HEAR_SOUND))
	{
		CSound *pSound;
		pSound = PBestSound();

		ASSERT(pSound != NULL);
		if (pSound && (pSound->m_iType & bits_SOUND_DANGER))
			return GetScheduleOfType(SCHED_TAKE_COVER_FROM_BEST_SOUND);
	}
	if (HasConditions(bits_COND_ENEMY_DEAD) && FOkToSpeak())
	{
		PlaySentence("FG_KILL", 4, VOL_NORM, ATTN_NORM);
	}

	switch (m_MonsterState)
	{
	case MONSTERSTATE_COMBAT:
	{
		// dead enemy
		if (HasConditions(bits_COND_ENEMY_DEAD))
		{
			// call base class, all code to handle dead enemies is centralized there.
			return CBaseMonster::GetSchedule();
		}

		// always act surprized with a new enemy
		if (HasConditions(bits_COND_NEW_ENEMY) && HasConditions(bits_COND_LIGHT_DAMAGE))
			return GetScheduleOfType(SCHED_SMALL_FLINCH);

#if 0
		// wait for one schedule to draw gun
		if (!m_fGunDrawn)
			return GetScheduleOfType(SCHED_ARM_WEAPON);
#endif

		if (HasConditions(bits_COND_HEAVY_DAMAGE))
			return GetScheduleOfType(SCHED_TAKE_COVER_FROM_ENEMY);
	}
	break;

	case MONSTERSTATE_ALERT:
	case MONSTERSTATE_IDLE:
		if (HasConditions(bits_COND_LIGHT_DAMAGE | bits_COND_HEAVY_DAMAGE))
		{
			// flinch if hurt
			return GetScheduleOfType(SCHED_SMALL_FLINCH);
		}

		if (m_hEnemy == NULL && IsFollowing())
		{
			if (!m_hTargetEnt->IsAlive())
			{
				// UNDONE: Comment about the recently dead player here?
				StopFollowing(FALSE);
				break;
			}
			else
			{
				if (HasConditions(bits_COND_CLIENT_PUSH))
				{
					return GetScheduleOfType(SCHED_MOVE_AWAY_FOLLOW);
				}
				return GetScheduleOfType(SCHED_TARGET_FACE);
			}
		}

		if (HasConditions(bits_COND_CLIENT_PUSH))
		{
			return GetScheduleOfType(SCHED_MOVE_AWAY);
		}

		// try to say something about smells
		TrySmellTalk();
		break;
	}

	return CTalkMonster::GetSchedule();
}

MONSTERSTATE CFGrunt::GetIdealState(void)
{
	return CTalkMonster::GetIdealState();
}

void CFGrunt::DeclineFollowing(void)
{
	PlaySentence("FG_POK", 2, VOL_NORM, ATTN_NORM);
}

void CFGrunt::StartTask(Task_t *pTask)
{
	CTalkMonster::StartTask(pTask);
}

void CFGrunt::RunTask(Task_t *pTask)
{
	switch (pTask->iTask)
	{
	case TASK_RANGE_ATTACK1:
		if (m_hEnemy != NULL && (m_hEnemy->IsPlayer()))
		{
			pev->framerate = 1.5;
		}
		CTalkMonster::RunTask(pTask);
		break;
	default:
		CTalkMonster::RunTask(pTask);
		break;
	}
}


void CFGrunt::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "head"))
	{
		head = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CTalkMonster::KeyValue(pkvd);
}







//=========================================================
// DEAD FGRUNT PROP
//=========================================================
class CDeadFGrunt : public CBaseMonster
{
public:
	void Spawn(void);
	int	Classify(void) { return	CLASS_HUMAN_MILITARY; }

	void KeyValue(KeyValueData *pkvd);

	virtual int		Save(CSave &save);
	virtual int		Restore(CRestore &restore);
	static	TYPEDESCRIPTION m_SaveData[];

	int	m_iPose;// which sequence to display	-- temporary, don't need to save
	int m_iHead;
	static char *m_szPoses[6];
};

LINK_ENTITY_TO_CLASS(monster_human_grunt_ally_dead, CDeadFGrunt);

TYPEDESCRIPTION CDeadFGrunt::m_SaveData[] =
{
	DEFINE_FIELD(CDeadFGrunt, m_iHead, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CDeadFGrunt, CBaseMonster);

char *CDeadFGrunt::m_szPoses[] = { "deadstomach", "deadside", "deadsitting", "dead_on_back", "dead_on_stomach", "dead_headcrabed" };

void CDeadFGrunt::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "pose"))
	{
		m_iPose = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "head"))
	{
		m_iHead = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseMonster::KeyValue(pkvd);
}


//=========================================================
// ********** DeadHGrunt SPAWN **********
//=========================================================
void CDeadFGrunt::Spawn(void)
{
	PRECACHE_MODEL("models/hgrunt_opfor.mdl");
	SET_MODEL(ENT(pev), "models/hgrunt_opfor.mdl");

	pev->effects = 0;
	pev->yaw_speed = 8;
	pev->sequence = 0;
	m_bloodColor = BLOOD_COLOR_RED;

	pev->sequence = LookupSequence(m_szPoses[m_iPose]);

	if (pev->sequence == -1)
	{
		ALERT(at_console, "Dead fgrunt with bad pose\n");
	}

	// Corpses have less health
	pev->health = 8;


	// Select a random head.
	if (m_iHead == -1)
	{
		SetBodygroup(HEAD_GROUP, RANDOM_LONG(0, FGRUNT_NUM_HEADS - 1));
	}

	if (pev->weapons == 0)
	{
		SetBodygroup(HEAD_GROUP, HEAD_GASMASK);
		SetBodygroup(TORSO_GROUP, TORSO_BACKPACK);
		SetBodygroup(GUN_GROUP, GUN_MP5);
	}
	else if (FBitSet(pev->weapons, FGRUNT_9MMAR))
	{
		SetBodygroup(TORSO_GROUP, TORSO_BACKPACK);
		SetBodygroup(GUN_GROUP, GUN_MP5);
	}

#if 0
	// map old bodies onto new bodies
	switch (pev->body)
	{
	case 0: // Grunt with Gun
		pev->body = 0;
		pev->skin = 0;
		SetBodygroup(HEAD_GROUP, HEAD_GRUNT);
		SetBodygroup(GUN_GROUP, GUN_MP5);
		break;
	case 1: // Commander with Gun
		pev->body = 0;
		pev->skin = 0;
		SetBodygroup(HEAD_GROUP, HEAD_COMMANDER);
		SetBodygroup(GUN_GROUP, GUN_MP5);
		break;
	case 2: // Grunt no Gun
		pev->body = 0;
		pev->skin = 0;
		SetBodygroup(HEAD_GROUP, HEAD_GRUNT);
		SetBodygroup(GUN_GROUP, GUN_NONE);
		break;
	case 3: // Commander no Gun
		pev->body = 0;
		pev->skin = 0;
		SetBodygroup(HEAD_GROUP, HEAD_COMMANDER);
		SetBodygroup(GUN_GROUP, GUN_NONE);
		break;
	}
#else
	// Until we get head support, set these to default.
	pev->body = 0;
	pev->skin = 0;
#endif

	MonsterInitDead();
}