#hlsdk-2.3 client port for android
#Copyright (c) mittorn

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := server
#ifeq ($(XASH_SDL),1)
#APP_PLATFORM := android-12
#LOCAL_SHARED_LIBRARIES += SDL2 
#LOCAL_CFLAGS += -DXASH_SDL
#else
APP_PLATFORM := android-8
#endif
LOCAL_CONLYFLAGS += -std=c99

include $(XASH3D_CONFIG)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a-hard)
LOCAL_MODULE_FILENAME = libserver_hardfp
endif

LOCAL_CFLAGS += -fsigned-char
SRCS :=
SRCS_C :=
TOPDIR := .
SRCS += $(TOPDIR)/../dlls/aflock.cpp
SRCS += $(TOPDIR)/../dlls/agrunt.cpp
SRCS += $(TOPDIR)/../dlls/airtank.cpp
SRCS += $(TOPDIR)/../dlls/animating.cpp
SRCS += $(TOPDIR)/../dlls/animation.cpp
SRCS += $(TOPDIR)/../dlls/apache.cpp
SRCS += $(TOPDIR)/../dlls/barnacle.cpp
SRCS += $(TOPDIR)/../dlls/barney.cpp
SRCS += $(TOPDIR)/../dlls/bigmomma.cpp
SRCS += $(TOPDIR)/../dlls/bloater.cpp
SRCS += $(TOPDIR)/../dlls/bmodels.cpp
SRCS += $(TOPDIR)/../dlls/bullsquid.cpp
SRCS += $(TOPDIR)/../dlls/buttons.cpp
SRCS += $(TOPDIR)/../dlls/cbase.cpp
SRCS += $(TOPDIR)/../dlls/client.cpp
SRCS += $(TOPDIR)/../dlls/combat.cpp
SRCS += $(TOPDIR)/../dlls/controller.cpp
SRCS += $(TOPDIR)/../dlls/crossbow.cpp
SRCS += $(TOPDIR)/../dlls/crowbar.cpp
SRCS += $(TOPDIR)/../dlls/defaultai.cpp
SRCS += $(TOPDIR)/../dlls/doors.cpp
SRCS += $(TOPDIR)/../dlls/effects.cpp
SRCS += $(TOPDIR)/../dlls/egon.cpp
SRCS += $(TOPDIR)/../dlls/explode.cpp
SRCS += $(TOPDIR)/../dlls/flyingmonster.cpp
SRCS += $(TOPDIR)/../dlls/func_break.cpp
SRCS += $(TOPDIR)/../dlls/func_tank.cpp
SRCS += $(TOPDIR)/../dlls/game.cpp
SRCS += $(TOPDIR)/../dlls/gamerules.cpp
SRCS += $(TOPDIR)/../dlls/gargantua.cpp
SRCS += $(TOPDIR)/../dlls/gauss.cpp
SRCS += $(TOPDIR)/../dlls/genericmonster.cpp
SRCS += $(TOPDIR)/../dlls/ggrenade.cpp
SRCS += $(TOPDIR)/../dlls/globals.cpp
SRCS += $(TOPDIR)/../dlls/gman.cpp
SRCS += $(TOPDIR)/../dlls/handgrenade.cpp
SRCS += $(TOPDIR)/../dlls/hassassin.cpp
SRCS += $(TOPDIR)/../dlls/headcrab.cpp
SRCS += $(TOPDIR)/../dlls/healthkit.cpp
SRCS += $(TOPDIR)/../dlls/hgrunt.cpp
SRCS += $(TOPDIR)/../dlls/hornet.cpp
SRCS += $(TOPDIR)/../dlls/hornetgun.cpp
SRCS += $(TOPDIR)/../dlls/houndeye.cpp
SRCS += $(TOPDIR)/../dlls/h_ai.cpp
SRCS += $(TOPDIR)/../dlls/h_battery.cpp
SRCS += $(TOPDIR)/../dlls/h_cine.cpp
SRCS += $(TOPDIR)/../dlls/h_cycler.cpp
SRCS += $(TOPDIR)/../dlls/h_export.cpp
SRCS += $(TOPDIR)/../dlls/ichthyosaur.cpp
SRCS += $(TOPDIR)/../dlls/islave.cpp
SRCS += $(TOPDIR)/../dlls/items.cpp
SRCS += $(TOPDIR)/../dlls/leech.cpp
SRCS += $(TOPDIR)/../dlls/lights.cpp
SRCS += $(TOPDIR)/../dlls/maprules.cpp
SRCS += $(TOPDIR)/../dlls/monstermaker.cpp
SRCS += $(TOPDIR)/../dlls/monsters.cpp
SRCS += $(TOPDIR)/../dlls/monsterstate.cpp
SRCS += $(TOPDIR)/../dlls/mortar.cpp
SRCS += $(TOPDIR)/../dlls/mp5.cpp
SRCS += $(TOPDIR)/../dlls/multiplay_gamerules.cpp
SRCS += $(TOPDIR)/../dlls/nihilanth.cpp
SRCS += $(TOPDIR)/../dlls/nodes.cpp
SRCS += $(TOPDIR)/../dlls/observer.cpp
SRCS += $(TOPDIR)/../dlls/osprey.cpp
SRCS += $(TOPDIR)/../dlls/pathcorner.cpp
SRCS += $(TOPDIR)/../dlls/plane.cpp
SRCS += $(TOPDIR)/../dlls/plats.cpp
SRCS += $(TOPDIR)/../dlls/player.cpp
SRCS += $(TOPDIR)/../dlls/python.cpp
SRCS += $(TOPDIR)/../dlls/rat.cpp
SRCS += $(TOPDIR)/../dlls/roach.cpp
SRCS += $(TOPDIR)/../dlls/rpg.cpp
SRCS += $(TOPDIR)/../dlls/satchel.cpp
SRCS += $(TOPDIR)/../dlls/schedule.cpp
SRCS += $(TOPDIR)/../dlls/scientist.cpp
SRCS += $(TOPDIR)/../dlls/scripted.cpp
SRCS += $(TOPDIR)/../dlls/shotgun.cpp
SRCS += $(TOPDIR)/../dlls/singleplay_gamerules.cpp
SRCS += $(TOPDIR)/../dlls/skill.cpp
SRCS += $(TOPDIR)/../dlls/sound.cpp
SRCS += $(TOPDIR)/../dlls/soundent.cpp
SRCS += $(TOPDIR)/../dlls/spectator.cpp
SRCS += $(TOPDIR)/../dlls/squadmonster.cpp
SRCS += $(TOPDIR)/../dlls/squeakgrenade.cpp
SRCS += $(TOPDIR)/../dlls/subs.cpp
SRCS += $(TOPDIR)/../dlls/talkmonster.cpp
SRCS += $(TOPDIR)/../dlls/teamplay_gamerules.cpp
SRCS += $(TOPDIR)/../dlls/tempmonster.cpp
SRCS += $(TOPDIR)/../dlls/tentacle.cpp
SRCS += $(TOPDIR)/../dlls/triggers.cpp
SRCS += $(TOPDIR)/../dlls/tripmine.cpp
SRCS += $(TOPDIR)/../dlls/turret.cpp
SRCS += $(TOPDIR)/../dlls/util.cpp
SRCS += $(TOPDIR)/../dlls/weapons.cpp
SRCS += $(TOPDIR)/../dlls/world.cpp
SRCS += $(TOPDIR)/../dlls/wpn_shared/hl_wpn_glock.cpp
SRCS += $(TOPDIR)/../dlls/xen.cpp
SRCS += $(TOPDIR)/../dlls/zombie.cpp
SRCS += $(TOPDIR)/../../game_shared/voice_gamemgr.cpp
SRCS += gearbox/fgrunt_medic.cpp
SRCS += gearbox/fgrunt_torch.cpp
SRCS += gearbox/eagle.cpp
SRCS += gearbox/grapple_tonguetip.cpp
SRCS += gearbox/sporelauncher.cpp
SRCS += gearbox/sniperrifle.cpp
SRCS += gearbox/blkop_osprey.cpp
SRCS += gearbox/ropes.cpp
SRCS += gearbox/zombie_soldier.cpp
SRCS += gearbox/grapple.cpp
#SRCS += gearbox/gearbox_client.cpp
SRCS += gearbox/skeleton.cpp
SRCS += gearbox/cleansuit_scientist.cpp
SRCS += gearbox/ctf_items.cpp
SRCS += gearbox/voltigore.cpp
SRCS += gearbox/drillsergeant.cpp
SRCS += gearbox/otis.cpp
SRCS += gearbox/shock.cpp
SRCS += gearbox/sporegrenade.cpp
SRCS += gearbox/fgrunt.cpp
SRCS += gearbox/pitworm.cpp
SRCS += gearbox/geneworm.cpp
SRCS += gearbox/knife.cpp
SRCS += gearbox/spore_ammo.cpp
SRCS += gearbox/massn.cpp
SRCS += gearbox/gearbox_triggers.cpp
SRCS += gearbox/displacer.cpp
SRCS += gearbox/houndeye_dead.cpp
SRCS += gearbox/loader.cpp
SRCS += gearbox/gearbox_subs.cpp
SRCS += gearbox/shockroach.cpp
SRCS += gearbox/pipewrench.cpp
SRCS += gearbox/islave_dead.cpp
SRCS += gearbox/blkop_apache.cpp
SRCS += gearbox/m249.cpp
SRCS += gearbox/zombie_barney.cpp
SRCS += gearbox/pitdrone.cpp
SRCS += gearbox/gonome.cpp
SRCS += gearbox/ctf_powerups.cpp
SRCS += gearbox/func_tank_of.cpp
SRCS += gearbox/shockrifle.cpp
SRCS += gearbox/gearbox_utils.cpp
SRCS += gearbox/generic_items.cpp
SRCS += gearbox/gearbox_effects.cpp
SRCS += gearbox/recruit.cpp
SRCS += gearbox/ctf_gamerules.cpp
SRCS += gearbox/penguin.cpp
SRCS += gearbox/nuclearbomb.cpp
SRCS += gearbox/strooper.cpp
SRCS_C += ../../pm_shared/pm_shared.c
SRCS_C += ../../pm_shared/pm_math.c
SRCS_C += ../../pm_shared/pm_debug.c

#INCLUDES =  -I../common -I. -I../game_shared -I../pm_shared -I../engine -I../dlls
INCLUDES =  -I$(TOPDIR)/../../common -I. -I$(TOPDIR)/../../game_shared -I$(TOPDIR)/../pm_shared -I$(TOPDIR)/../../engine -I$(TOPDIR)/../dlls -I$(TOPDIR)/../dlls/hl -I$(TOPDIR)/../../public -Igearbox

#DEFINES = -Wno-write-strings -DLINUX -D_LINUX -D_vsnprintf=vsnprintf -Dstricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp -DCLIENT_WEAPONS -DCLIENT_DLL -fpermissive -w -DHL_DLL -DGEARBOX_CLIENT_DLL -DGEARBOX_DLL -D_alloca=alloca -D_snprintf=snprintf -DDISABLE_VEC_ORIGIN -DDISABLE_JUMP_ORIGIN
DEFINES = -Wno-write-strings -DLINUX -D_LINUX -D_vsnprintf=vsnprintf -Dstricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp -DCLIENT_WEAPONS -fpermissive -w -DHL_DLL -DGEARBOX_DLL -D_alloca=alloca -D_snprintf=snprintf

LOCAL_C_INCLUDES := \
		 $(LOCAL_PATH)/../../common \
		 $(LOCAL_PATH)/../../engine \
		 $(LOCAL_PATH)/../../game_shared \
		 $(LOCAL_PATH)/../dlls \
		 $(LOCAL_PATH)/../dlls/hl \
		 $(LOCAL_PATH)/../pm_shared \
		 $(LOCAL_PATH)/../../public \
		 $(LOCAL_PATH)/gearbox $(LOCAL_PATH)/
LOCAL_CFLAGS += $(DEFINES) $(INCLUDES)

LOCAL_SRC_FILES := $(SRCS) $(SRCS_C)

include $(BUILD_SHARED_LIBRARY)
