#HLSDK server Android port
#Copyright (c) nicknekit

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := client

include $(XASH3D_CONFIG)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a-hard)
LOCAL_MODULE_FILENAME = libclient_hardfp
endif

LOCAL_CFLAGS += -w -Wno-error=format-security -DINTERNAL_VGUI_SUPPORT -DLINUX -DCLIENT_DLL -DCLIENT_WEAPONS -DHL_DLL -I/usr/include/malloc -D_snwprintf=swprintf -DDISABLE_JUMP_ORIGIN -DDISABLE_VEC_ORIGIN -fpermissive -fno-strict-aliasing -DNDEBUG -DPOSIX -D_POSIX -DLINUX -D_LINUX -DGNUC -DHL1 -Dstricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp -D_snprintf=snprintf -DQUIVER -DQUAKE2 -DVALVE_DLL -D_alloca=alloca -fno-exceptions -fexpensive-optimizations -D_vsnprintf=vsnprintf -DNO_MALLOC_OVERRIDE -Werror=return-type

LOCAL_CPPFLAGS := $(LOCAL_CFLAGS) -fno-rtti -Wno-write-strings -Wno-invalid-offsetof -std=gnu++98

LOCAL_C_INCLUDES := \
		    $(LOCAL_PATH)/. \
		    $(LOCAL_PATH)/../dlls/ \
		    $(LOCAL_PATH)/../common \
		    $(LOCAL_PATH)/../public \
		    $(LOCAL_PATH)/../pm_shared \
		    $(LOCAL_PATH)/../engine \
		    $(LOCAL_PATH)/../game_shared \
		    $(LOCAL_PATH)/../utils/vgui/include \
		    $(LOCAL_PATH)/../external \
		    $(LOCAL_PATH)/../vgui_dll/lib-src/win32 \
		    $(LOCAL_PATH)/../vgui_dll/lib-src/vgui \
		    $(LOCAL_PATH)/../xash3d/engine \
		    $(LOCAL_PATH)/../xash3d/common


HL1_DIR = .
HL1_SERVER_DIR = ../dlls
PUBLIC_DIR = ../public
COMMON_DIR = ../common
GAME_SHARED_DIR = ../game_shared
PM_SHARED_DIR = ../pm_shared
VGUI_DIR = ../vgui_dll/lib-src
VGUI_SUPPORT_DIR = ../xash3d/vgui_support/

LOCAL_SRC_FILES := \
	$(HL1_DIR)/hud_spectator.cpp \
	$(HL1_DIR)/ev_hldm.cpp \
	$(HL1_DIR)/hl/hl_baseentity.cpp \
	$(HL1_DIR)/hl/hl_events.cpp \
	$(HL1_DIR)/hl/hl_objects.cpp \
	$(HL1_DIR)/hl/hl_weapons.cpp \
	$(HL1_DIR)/hud.cpp \
	$(HL1_DIR)/input_xash3d.cpp \
	$(HL1_DIR)/ammo.cpp \
	$(HL1_DIR)/ammo_secondary.cpp \
	$(HL1_DIR)/ammohistory.cpp \
	$(HL1_DIR)/battery.cpp \
	$(HL1_DIR)/cdll_int.cpp \
	$(HL1_DIR)/com_weapons.cpp \
	$(HL1_DIR)/death.cpp \
	$(HL1_DIR)/demo.cpp \
	$(HL1_DIR)/entity.cpp \
	$(HL1_DIR)/ev_common.cpp \
	$(HL1_DIR)/events.cpp \
	$(HL1_DIR)/flashlight.cpp \
	$(HL1_DIR)/GameStudioModelRenderer.cpp \
	$(HL1_DIR)/geiger.cpp \
	$(HL1_DIR)/health.cpp \
	$(HL1_DIR)/hud_bench.cpp \
	$(HL1_DIR)/hud_benchtrace.cpp \
	$(HL1_DIR)/hud_msg.cpp \
	$(HL1_DIR)/hud_redraw.cpp \
	$(HL1_DIR)/hud_update.cpp \
	$(HL1_DIR)/in_camera.cpp \
	$(HL1_DIR)/input.cpp \
	$(HL1_DIR)/interpolation.cpp \
	$(HL1_DIR)/menu.cpp \
	$(HL1_DIR)/message.cpp \
	$(HL1_DIR)/saytext.cpp \
	$(HL1_DIR)/status_icons.cpp \
	$(HL1_DIR)/statusbar.cpp \
	$(HL1_DIR)/studio_util.cpp \
	$(HL1_DIR)/StudioModelRenderer.cpp \
	$(HL1_DIR)/text_message.cpp \
	$(HL1_DIR)/train.cpp \
	$(HL1_DIR)/tri.cpp \
	$(HL1_DIR)/util.cpp \
	$(HL1_DIR)/view.cpp \
	$(HL1_DIR)/vgui_int.cpp \
	$(HL1_DIR)/vgui_ClassMenu.cpp \
	$(HL1_DIR)/vgui_ConsolePanel.cpp \
	$(HL1_DIR)/vgui_ControlConfigPanel.cpp \
	$(HL1_DIR)/vgui_CustomObjects.cpp \
	$(HL1_DIR)/vgui_MOTDWindow.cpp \
	$(HL1_DIR)/vgui_SchemeManager.cpp \
	$(HL1_DIR)/vgui_ScorePanel.cpp \
	$(HL1_DIR)/vgui_ServerBrowser.cpp \
	$(HL1_DIR)/vgui_TeamFortressViewport.cpp \
	$(HL1_DIR)/vgui_SpectatorPanel.cpp \
	$(HL1_DIR)/vgui_teammenu.cpp \
	$(HL1_DIR)/voice_status.cpp \
	$(HL1_DIR)/hud_servers.cpp \
	$(HL1_SERVER_DIR)/crossbow.cpp \
	$(HL1_SERVER_DIR)/crowbar.cpp \
	$(HL1_SERVER_DIR)/egon.cpp \
	$(HL1_SERVER_DIR)/gauss.cpp \
	$(HL1_SERVER_DIR)/handgrenade.cpp \
	$(HL1_SERVER_DIR)/hornetgun.cpp \
	$(HL1_SERVER_DIR)/mp5.cpp \
	$(HL1_SERVER_DIR)/python.cpp \
	$(HL1_SERVER_DIR)/rpg.cpp \
	$(HL1_SERVER_DIR)/satchel.cpp \
	$(HL1_SERVER_DIR)/shotgun.cpp \
	$(HL1_SERVER_DIR)/squeakgrenade.cpp \
	$(HL1_SERVER_DIR)/tripmine.cpp \
	$(HL1_SERVER_DIR)/wpn_shared/hl_wpn_glock.cpp \
	$(PUBLIC_DIR)/interface.cpp \
	$(COMMON_DIR)/parsemsg.cpp \
	$(GAME_SHARED_DIR)/vgui_checkbutton2.cpp \
	$(GAME_SHARED_DIR)/vgui_grid.cpp \
	$(GAME_SHARED_DIR)/vgui_helpers.cpp \
	$(GAME_SHARED_DIR)/vgui_listbox.cpp \
	$(GAME_SHARED_DIR)/vgui_loadtga.cpp \
	$(GAME_SHARED_DIR)/vgui_scrollbar2.cpp \
	$(GAME_SHARED_DIR)/vgui_slider2.cpp \
	$(GAME_SHARED_DIR)/voice_banmgr.cpp \
	$(PM_SHARED_DIR)/pm_debug.c \
	$(PM_SHARED_DIR)/pm_shared.c \
	$(PM_SHARED_DIR)/pm_math.c \
../vgui_dll/lib-src/linux/App.cpp ../vgui_dll/lib-src/linux/Cursor.cpp ../vgui_dll/lib-src/linux/Font.cpp ../vgui_dll/lib-src/linux/Surface.cpp ../vgui_dll/lib-src/linux/fileimage.cpp ../vgui_dll/lib-src/linux/vfontdata.cpp ../vgui_dll/lib-src/linux/vgui.cpp ../vgui_dll/lib-src/vgui/App.cpp ../vgui_dll/lib-src/vgui/Bitmap.cpp ../vgui_dll/lib-src/vgui/BitmapTGA.cpp ../vgui_dll/lib-src/vgui/Border.cpp ../vgui_dll/lib-src/vgui/BorderLayout.cpp ../vgui_dll/lib-src/vgui/BorderPair.cpp ../vgui_dll/lib-src/vgui/BuildGroup.cpp ../vgui_dll/lib-src/vgui/Button.cpp ../vgui_dll/lib-src/vgui/ButtonGroup.cpp ../vgui_dll/lib-src/vgui/CheckButton.cpp ../vgui_dll/lib-src/vgui/Color.cpp ../vgui_dll/lib-src/vgui/ConfigWizard.cpp ../vgui_dll/lib-src/vgui/Cursor.cpp ../vgui_dll/lib-src/vgui/DataInputStream.cpp ../vgui_dll/lib-src/vgui/Desktop.cpp ../vgui_dll/lib-src/vgui/DesktopIcon.cpp ../vgui_dll/lib-src/vgui/EditPanel.cpp ../vgui_dll/lib-src/vgui/EtchedBorder.cpp ../vgui_dll/lib-src/vgui/FileInputStream.cpp ../vgui_dll/lib-src/vgui/FlowLayout.cpp ../vgui_dll/lib-src/vgui/FocusNavGroup.cpp ../vgui_dll/lib-src/vgui/Font.cpp ../vgui_dll/lib-src/vgui/Frame.cpp ../vgui_dll/lib-src/vgui/GridLayout.cpp ../vgui_dll/lib-src/vgui/HeaderPanel.cpp ../vgui_dll/lib-src/vgui/Image.cpp ../vgui_dll/lib-src/vgui/ImagePanel.cpp ../vgui_dll/lib-src/vgui/IntLabel.cpp ../vgui_dll/lib-src/vgui/Label.cpp ../vgui_dll/lib-src/vgui/Layout.cpp ../vgui_dll/lib-src/vgui/LineBorder.cpp ../vgui_dll/lib-src/vgui/ListPanel.cpp ../vgui_dll/lib-src/vgui/LoweredBorder.cpp ../vgui_dll/lib-src/vgui/Menu.cpp ../vgui_dll/lib-src/vgui/MenuItem.cpp ../vgui_dll/lib-src/vgui/MenuSeparator.cpp ../vgui_dll/lib-src/vgui/MessageBox.cpp ../vgui_dll/lib-src/vgui/MiniApp.cpp ../vgui_dll/lib-src/vgui/Panel.cpp ../vgui_dll/lib-src/vgui/PopupMenu.cpp ../vgui_dll/lib-src/vgui/ProgressBar.cpp ../vgui_dll/lib-src/vgui/RadioButton.cpp ../vgui_dll/lib-src/vgui/RaisedBorder.cpp ../vgui_dll/lib-src/vgui/Scheme.cpp ../vgui_dll/lib-src/vgui/ScrollBar.cpp ../vgui_dll/lib-src/vgui/ScrollPanel.cpp ../vgui_dll/lib-src/vgui/Slider.cpp ../vgui_dll/lib-src/vgui/StackLayout.cpp ../vgui_dll/lib-src/vgui/String.cpp ../vgui_dll/lib-src/vgui/Surface.cpp ../vgui_dll/lib-src/vgui/SurfaceBase.cpp ../vgui_dll/lib-src/vgui/TabPanel.cpp ../vgui_dll/lib-src/vgui/TablePanel.cpp ../vgui_dll/lib-src/vgui/TaskBar.cpp ../vgui_dll/lib-src/vgui/TextEntry.cpp ../vgui_dll/lib-src/vgui/TextGrid.cpp ../vgui_dll/lib-src/vgui/TextImage.cpp ../vgui_dll/lib-src/vgui/TextPanel.cpp ../vgui_dll/lib-src/vgui/ToggleButton.cpp ../vgui_dll/lib-src/vgui/TreeFolder.cpp ../vgui_dll/lib-src/vgui/WizardPanel.cpp ../vgui_dll/lib-src/vgui/vgui.cpp \
../xash3d/vgui_support/vgui_clip.cpp ../xash3d/vgui_support/vgui_font.cpp ../xash3d/vgui_support/vgui_input.cpp ../xash3d/vgui_support/vgui_int.cpp ../xash3d/vgui_support/vgui_surf.cpp

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
