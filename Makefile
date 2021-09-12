# Makefile to rebuild SM64 split image

include util.mk

# Default target
default: all

# Preprocessor definitions
DEFINES :=

#==============================================================================#
# Build Options                                                                #
#==============================================================================#

# These options can either be set by building with 'make SETTING=value'.
# 'make clean' may be required first.

# Makefile Refactor from Refresh 13 is half included but not fully 
# due to changes that are in this Makefile edited in sm64ex.
# However, the build clean output is there in it's own way.

# Compiler to use for N64 (ido or gcc)
# IDO will get dropped soon
#   ido - uses the SGI IRIS Development Option compiler, which is used to build
#         an original matching N64 ROM
#   gcc - uses the GNU C Compiler
COMPILER_N64 ?= gcc
$(eval $(call validate-option,COMPILER_N64,ido gcc))

# Build debug version
DEBUG ?= 0
# Build for original N64 (no pc code)
TARGET_N64 = 0
# Build and optimize for Raspberry Pi(s)
TARGET_RPI ?= 0
# Build for Emscripten/WebGL
TARGET_WEB ?= 0
# Build for the Wii U
TARGET_WII_U ?= 0
# Build for the 3DS
TARGET_N3DS ?= 0
# Build for Nintendo Switch
TARGET_SWITCH ?= 0
# Makeflag to enable OSX fixes
OSX_BUILD ?= 0
# Specify the target you are building for, TARGET_BITS=0 means native
TARGET_ARCH ?= native
TARGET_BITS ?= 0

# Enable extended options menu by default
EXT_OPTIONS_MENU ?= 1
# Enable better camera (Puppycam)
BETTERCAMERA ?= 1
# Enable cheats
CHEATS_ACTIONS ?= 1
# Disable no drawing distance by default
NODRAWINGDISTANCE ?= 0
# Disable text-based save-files by default
TEXTSAVES ?= 0
# Load resources from external files
EXTERNAL_DATA ?= 0
# Enable Discord Rich Presence
DISCORDRPC ?= 0
# Enable rumble functions (Originally in Shindou)
RUMBLE_FEEDBACK ?= 0
# Enable Goddard (Mario Face)
GODDARD_MFACE ?= 1
# Enable Command Line Options
COMMAND_LINE_OPTIONS ?= 1
# Kaze MOP Objects Port, disabled by default
PORT_MOP_OBJS ?= 0
# Enable 60 fps interpolation (PC Port only)
HIGH_FPS_PC ?= 0
# Enable PC Port defines
PC_PORT_DEFINES ?= 0

# Quality of life features
QOL_FEATURES ?= 1
# Quality of life fixes
QOL_FIXES ?= 1

# Various workarounds for weird toolchains
NO_BZERO_BCOPY ?= 0
NO_LDIV ?= 0

# Enable -no-pie linker option (PC Only)
# Doesn't apply to TARGET_PORT_CONSOLE because we assume
# it doesn't use an old version to compile
NO_PIE ?= 1

# Check if is compiling on a console (N64 doesn't count)
TARGET_PORT_CONSOLE ?= 0

# Backend selection

# Renderers: GL, GL_LEGACY, D3D11, D3D12, WHB (forced if the target is Wii U), C3D (forced if the target is 3DS)
RENDER_API ?= GL
# Window managers: SDL1, SDL2, DXGI (forced if D3D11 or D3D12 in RENDER_API), WHB (forced if the target is Wii U), 3DS (forced if the target is 3DS)
WINDOW_API ?= SDL2
# Audio backends: SDL1, SDL2 (forced if the target is Wii U), 3DS (forced if the target is 3DS)
AUDIO_API ?= SDL2
# Controller backends (can have multiple, space separated): SDL1, SDL2
# WII_U (forced if the target is Wii U), 3DS (forced if the target is 3DS), SWITCH (forced if the target is SWITCH)
CONTROLLER_API ?= SDL2

ifeq ($(TARGET_WII_U),1)
  RENDER_API := WHB
  WINDOW_API := WHB
  AUDIO_API := SDL2
  CONTROLLER_API := WII_U
  
  TARGET_PORT_CONSOLE := 1
endif

ifeq ($(TARGET_N3DS),1)
  RENDER_API := C3D
  WINDOW_API := 3DS
  AUDIO_API := 3DS
  CONTROLLER_API := 3DS
  
  TARGET_PORT_CONSOLE := 1
endif

ifeq ($(TARGET_SWITCH),1)
  RENDER_API := GL
  WINDOW_API := SDL2
  AUDIO_API := SDL2
  CONTROLLER_API := SWITCH
  
  TARGET_PORT_CONSOLE := 1
endif

# Misc settings for EXTERNAL_DATA

ifeq ($(TARGET_PORT_CONSOLE),1)
  BASEDIR ?= sm64ex_res
else
  BASEDIR ?= res
endif

BASEPACK ?= base.zip

# Automatic settings for PC port(s)

WINDOWS_BUILD ?= 0
TARGET_ANDROID ?= 0

ifeq ($(TARGET_N64),0)
  GRUCODE := f3dex2e
  PC_PORT_DEFINES := 1
else
  GRUCODE := f3dzex
  NO_LDIV := 1
endif

# Attempt to detect OS

ifeq ($(OS),Windows_NT)
  HOST_OS ?= Windows
else
  HOST_OS ?= $(shell uname -s 2>/dev/null || echo Unknown)
  # some weird MINGW/Cygwin env that doesn't define $OS
  ifneq (,$(findstring MINGW,HOST_OS))
    HOST_OS := Windows
  endif
endif

ifeq ($(TARGET_WEB),0)
  ifeq ($(TARGET_PORT_CONSOLE),0)
    ifeq ($(HOST_OS),Windows)
      WINDOWS_BUILD := 1
    else
      ifneq ($(shell which termux-setup-storage),)
        TARGET_ANDROID := 1
        ifeq ($(shell dpkg -s apksigner | grep Version | sed "s/Version: //"),0.7-2)
          OLD_APKSIGNER := 1
        endif
      endif
    endif
  endif
endif

# MXE overrides

ifeq ($(TARGET_ANDROID),1)
  RENDER_API := GL
  WINDOW_API := SDL2
  AUDIO_API := SDL2
  CONTROLLER_API := SDL2
  
  TOUCH_CONTROLS := 1
endif

ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(CROSS),i686-w64-mingw32.static-)
    TARGET_ARCH = i386pe
    TARGET_BITS = 32
    NO_BZERO_BCOPY := 1
  else ifeq ($(CROSS),x86_64-w64-mingw32.static-)
    TARGET_ARCH = i386pep
    TARGET_BITS = 64
    NO_BZERO_BCOPY := 1
  endif
endif

ifneq ($(TARGET_BITS),0)
  BITS := -m$(TARGET_BITS)
endif

# Set up WUT for Wii U

ifeq ($(TARGET_WII_U),1)
  ifeq ($(strip $(DEVKITPRO)),)
  $(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
  endif

  ifeq ($(strip $(DEVKITPPC)),)
  $(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>/devkitPro/devkitPPC")
  endif

  include $(DEVKITPPC)/base_tools

  PORTLIBS	:=	$(PORTLIBS_PATH)/wiiu $(PORTLIBS_PATH)/ppc

  export PATH := $(PORTLIBS_PATH)/wiiu/bin:$(PORTLIBS_PATH)/ppc/bin:$(PATH)

  WUT_ROOT	?=	$(DEVKITPRO)/wut

  RPXSPECS	:=	-specs=$(WUT_ROOT)/share/wut.specs

  MACHDEP	= -DESPRESSO -mcpu=750 -meabi -mhard-float

  LIBDIRS	    := $(PORTLIBS) $(WUT_ROOT)
  INCLUDE	    := $(foreach dir,$(LIBDIRS),-I$(dir)/include)
  LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)
endif

# VERSION - selects the version of the game to build
#   jp - builds the 1996 Japanese version
#   us - builds the 1996 North American version
#   eu - builds the 1997 PAL version
#   sh - builds the 1997 Japanese Shindou version, with rumble pak support
VERSION ?= us
$(eval $(call validate-option,VERSION,jp us eu sh))

ifeq      ($(VERSION),jp)
  DEFINES   += VERSION_JP=1
  VERSION_JP_US  ?= true
else ifeq ($(VERSION),us)
  DEFINES   += VERSION_US=1
  VERSION_JP_US  ?= true
else ifeq ($(VERSION),eu)
  DEFINES   += VERSION_EU=1
  VERSION_JP_US  ?= false
else ifeq ($(VERSION),sh)
  DEFINES   += VERSION_SH=1
  VERSION_JP_US  ?= false
endif

TARGET := sm64.$(VERSION).$(GRUCODE)

# GRUCODE - selects which RSP microcode to use.
#   f3d_old - First version the Fast3D (Originally in JP - US)
#   f3d_new - Second version the Fast3D (Originally in EU - SH)
#   f3dex   - First version of Fast3D Extended
#   f3dex2  - Second (rewritten) version of Fast3D Extended
#   l3dex2  - F3DEX2 version that only renders in wireframe
#   f3dex2e - Exclusive PC Version of the F3DEX2 microcode
#   f3dzex  - newer, experimental microcode used in Animal Crossing
#   super3d - extremely experimental version of Fast3D lacking many features for speed
$(eval $(call validate-option,GRUCODE,f3d_old f3dex f3dex2 f3dex2e f3dex2pl f3d_new f3dzex super3d l3dex2))

ifeq      ($(GRUCODE),f3d_old)
  DEFINES += F3D_OLD=1
else ifeq ($(GRUCODE),f3d_new) # Fast3D 2.0H
  DEFINES += F3D_NEW=1
else ifeq ($(GRUCODE),f3dex) # Fast3DEX
  DEFINES += F3DEX_GBI=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dex2) # Fast3DEX2
  DEFINES += F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),l3dex2) # Line3DEX2
  DEFINES += L3DEX2_GBI=1 L3DEX2_ALONE=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dex2pl) # Fast3DEX2_PosLight
  DEFINES += F3DEX2PL_GBI=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dzex) # Fast3DZEX (2.08J / Animal Forest - Dōbutsu no Mori)
  DEFINES += F3DZEX_GBI_2=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),super3d) # Super3D
  $(warning Super3D is experimental. Try at your own risk.)
  DEFINES += SUPER3D_GBI=1 F3D_NEW=1
else ifeq ($(GRUCODE),f3dex2e) # Fast3DEX2 Extended (PC Only)
  ifeq ($(TARGET_N64),1)
    $(error f3dex2e is only supported on PC Port)
  else
    DEFINES += F3DEX_GBI_2E=1
  endif
endif

# Specify target defines
ifeq ($(TARGET_RPI),1) # Define RPi to change SDL2 title & GLES2 hints
  DEFINES += TARGET_RPI=1 USE_GLES=1
else ifeq ($(TARGET_ANDROID),1) # Android has broken V-Sync (causes black screen) so disable it
  DEFINES += TARGET_ANDROID=1 USE_GLES=1 DISABLE_VSYNC=1
else ifeq ($(OSX_BUILD),1) # Modify GFX & SDL2 for OSX GL
  DEFINES += OSX_BUILD=1
else ifeq ($(TARGET_WEB),1)
  DEFINES += TARGET_WEB=1 USE_GLES=1
else ifeq ($(TARGET_WII_U),1)
  DEFINES += TARGET_WII_U=1
else ifeq ($(TARGET_N3DS),1)
  DEFINES += TARGET_N3DS=1
else ifeq ($(TARGET_SWITCH),1)
  DEFINES += TARGET_SWITCH=1 USE_GLES=1
endif

# IMPORTANT DEFINES TO ENSURE CORRECT FILE COMPILING
# AND AVOIDS UNDEFINED BEHAVIOR (PC Port and N64)
DEFINES += NON_MATCHING=1 AVOID_UB=1 _LANGUAGE_C=1

# Check backends

ifneq (,$(filter $(RENDER_API),D3D11 D3D12))
  ifneq ($(WINDOWS_BUILD),1)
    $(error DirectX is only supported on Windows)
  endif
  ifneq ($(WINDOW_API),DXGI)
    $(warning DirectX renderers require DXGI, forcing WINDOW_API value)
    WINDOW_API := DXGI
  endif
else
  ifeq ($(WINDOW_API),DXGI)
    $(error DXGI can only be used with DirectX renderers)
  endif
endif

################### Universal Dependencies ###################

# (This is a bit hacky, but a lot of rules implicitly depend
# on tools and assets, and we use directory globs further down
# in the makefile that we want should cover assets.)

PYTHON := python3

ifeq (,$(findstring clean,$(MAKECMDGOALS)))

# Make sure assets exist
NOEXTRACT ?= 0
ifeq ($(NOEXTRACT),0)
 DUMMY != $(PYTHON) extract_assets.py $(VERSION) >&2 || echo FAIL
ifeq ($(DUMMY),FAIL)
  $(error Failed to extract assets)
endif
endif

# Make tools if out of date
DUMMY != make -C tools >&2 || echo FAIL
ifeq ($(DUMMY),FAIL)
  $(error Failed to build tools)
endif

endif

################ Target Executable and Sources ###############

# BUILD_DIR is location where all build artifacts are placed
BUILD_DIR_BASE := build

ifeq ($(TARGET_WEB),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_web
else ifeq ($(TARGET_N64),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)
else ifeq ($(TARGET_WII_U),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_wiiu
else ifeq ($(TARGET_N3DS),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_3ds
else ifeq ($(TARGET_SWITCH),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_nx
else ifeq ($(TARGET_ANDROID),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_android
else
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_pc
endif

LIBULTRA := $(BUILD_DIR)/libultra.a

ifeq ($(TARGET_N64),0)

ifeq ($(TARGET_WEB),1)
  EXE := $(BUILD_DIR)/$(TARGET).html
else ifeq ($(TARGET_WII_U),1)
  EXE := $(BUILD_DIR)/$(TARGET).rpx
else ifeq ($(TARGET_N3DS),1)
 EXE := $(BUILD_DIR)/$(TARGET).3dsx
 ELF := $(BUILD_DIR)/$(TARGET).elf
 CIA := $(BUILD_DIR)/$(TARGET).cia
else ifeq ($(WINDOWS_BUILD),1)
  EXE := $(BUILD_DIR)/$(TARGET).exe
else ifeq ($(TARGET_ANDROID),1)
  EXE := $(BUILD_DIR)/libmain.so
  APK := $(BUILD_DIR)/$(TARGET).unsigned.apk
  APK_SIGNED := $(BUILD_DIR)/$(TARGET).apk
else # Linux builds/binary namer
  ifeq ($(TARGET_RPI),1)
    EXE := $(BUILD_DIR)/$(TARGET).arm
  else
    EXE := $(BUILD_DIR)/$(TARGET)
  endif
endif

endif

ifeq ($(TARGET_N64),1)
  EXE := $(BUILD_DIR)/$(TARGET)
endif

ROM := $(BUILD_DIR)/$(TARGET).z64
ELF := $(BUILD_DIR)/$(TARGET).elf
LD_SCRIPT := sm64.ld
MIO0_DIR := $(BUILD_DIR)/bin
SOUND_BIN_DIR := $(BUILD_DIR)/sound
TEXTURE_DIR := textures
ACTOR_DIR := actors
LEVEL_DIRS := $(patsubst levels/%,%,$(dir $(wildcard levels/*/header.h)))

# Directories containing source files
SRC_DIRS := src src/engine src/game src/audio src/menu src/buffers src/extras actors levels bin bin/$(VERSION) data assets sound
ifeq ($(TARGET_N64),1)
  SRC_DIRS += asm lib
else
# Specify target folders
  PLATFORM_DIR := platform

  SRC_DIRS += src/pc src/pc/gfx src/pc/audio src/pc/controller src/pc/fs src/pc/fs/packtypes
  ifeq ($(WINDOWS_BUILD),1)
    PLATFORM_DIR := $(PLATFORM_DIR)/win
  else ifeq ($(TARGET_N3DS),1)
    PLATFORM_DIR := $(PLATFORM_DIR)/3ds
  else ifeq ($(TARGET_SWITCH),1)
    PLATFORM_DIR := $(PLATFORM_DIR)/switch
  else ifeq ($(TARGET_ANDROID),1)
    PLATFORM_DIR := $(PLATFORM_DIR)/android
  endif
  SRC_DIRS += $(PLATFORM_DIR)
endif

ifeq ($(TARGET_WII_U),1)
  SRC_DIRS += src/pc/gfx/shaders_wiiu
endif

ifeq ($(TARGET_PORT_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    SRC_DIRS += src/pc/discord
  endif
endif

BIN_DIRS := bin bin/$(VERSION)

ULTRA_SRC_DIRS := lib/src lib/src/math lib/asm lib/data
ULTRA_BIN_DIRS := lib/bin

ifeq ($(GODDARD_MFACE),1)
  GODDARD_SRC_DIRS := src/goddard src/goddard/dynlists
endif

MIPSISET := -mips2
MIPSBIT := -32

ifeq ($(TARGET_N64),1)
  ifeq ($(COMPILER_N64),gcc)
    MIPSISET := -mips3
    ifeq ($(DEBUG),1)
      OPT_FLAGS := -O2 -g3
    else
      OPT_FLAGS := -O2
    endif
  endif

else

  ifeq ($(DEBUG),1)
    OPT_FLAGS := -g
  else
    OPT_FLAGS := -O2
  endif

endif

# Set BITS (32/64) to compile for
OPT_FLAGS += $(BITS)

ifeq ($(TARGET_WEB),1)
  OPT_FLAGS := -O2 -g4 --source-map-base http://localhost:8080/
endif

ifeq ($(TARGET_RPI),1)
  machine = $(shell sh -c 'uname -m 2>/dev/null || echo unknown')
# Raspberry Pi B+, Zero, etc
  ifneq (,$(findstring armv6l,$(machine)))
   OPT_FLAGS := -march=armv6zk+fp -mfpu=vfp -Ofast
  endif

# Raspberry Pi 2 and 3 in ARM 32bit mode
  ifneq (,$(findstring armv7l,$(machine)))
    model = $(shell sh -c 'cat /sys/firmware/devicetree/base/model 2>/dev/null || echo unknown')
    ifneq (,$(findstring 3,$(model)))
      OPT_FLAGS := -march=armv8-a+crc -mtune=cortex-a53 -mfpu=neon-fp-armv8 -O3
    else
      OPT_FLAGS := -march=armv7-a -mtune=cortex-a7 -mfpu=neon-vfpv4 -O3
    endif
  endif

# RPi3 or RPi4, in ARM64 (aarch64) mode. NEEDS TESTING 32BIT.
# DO NOT pass -mfpu stuff here, thats for 32bit ARM only and will fail for 64bit ARM.
  ifneq (,$(findstring aarch64,$(machine)))
    model = $(shell sh -c 'cat /sys/firmware/devicetree/base/model 2>/dev/null || echo unknown')
    ifneq (,$(findstring 3,$(model)))
      OPT_FLAGS := -march=armv8-a+crc -mtune=cortex-a53 -O3
    else ifneq (,$(findstring 4,$(model)))
      OPT_FLAGS := -march=armv8-a+crc+simd -mtune=cortex-a72 -O3
    endif
  endif
endif

# Whether to hide commands or not
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
  V := @
endif

# Whether to colorize build messages
COLOR ?= 1

# display selected options unless 'make clean' or 'make distclean' is run
# TODO: Add Info for other targets
ifeq ($(filter clean distclean,$(MAKECMDGOALS)),)
  $(info ==== Build Options ====)
  $(info Version:        $(VERSION))
  $(info Microcode:      $(GRUCODE))
  $(info Target:         $(TARGET))
  $(info =======================)
endif

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
YELLOW  := \033[0;33m
BLINK   := \033[33;5m
endif

# File dependencies and variables for specific files
include Makefile.split

# Source code files
LEVEL_C_FILES := $(wildcard levels/*/leveldata.c) $(wildcard levels/*/script.c) $(wildcard levels/*/geo.c)
C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) $(LEVEL_C_FILES)
CXX_FILES     := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
S_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
ifeq ($(TARGET_N64),1)
  ULTRA_C_FILES := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.c))
  ULTRA_S_FILES := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.s))
endif
ifeq ($(GODDARD_MFACE),1)
  GODDARD_C_FILES := $(foreach dir,$(GODDARD_SRC_DIRS),$(wildcard $(dir)/*.c))
endif
ifeq ($(WINDOWS_BUILD),1)
  RC_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.rc))
endif

GENERATED_C_FILES := $(BUILD_DIR)/assets/mario_anim_data.c $(BUILD_DIR)/assets/demo_data.c \
  $(addprefix $(BUILD_DIR)/bin/,$(addsuffix _skybox.c,$(notdir $(basename $(wildcard textures/skyboxes/*.png)))))

ifneq ($(TARGET_N64),1)
ULTRA_C_FILES := \
  alBnkfNew.c \
  guLookAtRef.c \
  guMtxF2L.c \
  guNormalize.c \
  guOrthoF.c \
  guPerspectiveF.c \
  guRotateF.c \
  guScaleF.c \
  guTranslateF.c \
  ldiv.c

C_FILES := $(filter-out src/game/main.c,$(C_FILES))

ULTRA_C_FILES := $(addprefix lib/src/,$(ULTRA_C_FILES))
endif

# "If we're not N64, use the above"

SOUND_BANK_FILES := $(wildcard sound/sound_banks/*.json)
SOUND_SEQUENCE_DIRS := sound/sequences sound/sequences/$(VERSION)
# all .m64 files in SOUND_SEQUENCE_DIRS, plus all .m64 files that are generated from .s files in SOUND_SEQUENCE_DIRS
SOUND_SEQUENCE_FILES := \
  $(foreach dir,$(SOUND_SEQUENCE_DIRS),\
    $(wildcard $(dir)/*.m64) \
    $(foreach file,$(wildcard $(dir)/*.s),$(BUILD_DIR)/$(file:.s=.m64)) \
  )

SOUND_SAMPLE_DIRS := $(wildcard sound/samples/*)
SOUND_SAMPLE_AIFFS := $(foreach dir,$(SOUND_SAMPLE_DIRS),$(wildcard $(dir)/*.aiff))
SOUND_SAMPLE_TABLES := $(foreach file,$(SOUND_SAMPLE_AIFFS),$(BUILD_DIR)/$(file:.aiff=.table))
SOUND_SAMPLE_AIFCS := $(foreach file,$(SOUND_SAMPLE_AIFFS),$(BUILD_DIR)/$(file:.aiff=.aifc))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(CXX_FILES),$(BUILD_DIR)/$(file:.cpp=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
           $(foreach file,$(GENERATED_C_FILES),$(file:.c=.o))

ifeq ($(WINDOWS_BUILD),1)
  O_FILES += $(foreach file,$(RC_FILES),$(BUILD_DIR)/$(file:.rc=.o))
endif

ULTRA_O_FILES := $(foreach file,$(ULTRA_S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
                 $(foreach file,$(ULTRA_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

ifeq ($(GODDARD_MFACE),1)
  GODDARD_O_FILES := $(foreach file,$(GODDARD_C_FILES),$(BUILD_DIR)/$(file:.c=.o))
endif

RPC_LIBS :=
ifeq ($(TARGET_PORT_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    ifeq ($(WINDOWS_BUILD),1)
      RPC_LIBS := lib/discord/libdiscord-rpc.dll
    else ifeq ($(OSX_BUILD),1)
      # needs testing
      RPC_LIBS := lib/discord/libdiscord-rpc.dylib
    else
      RPC_LIBS := lib/discord/libdiscord-rpc.so
    endif
  endif
endif

# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) $(ULTRA_O_FILES:.o=.d) $(GODDARD_O_FILES:.o=.d) $(BUILD_DIR)/$(LD_SCRIPT).d

# Files with GLOBAL_ASM blocks
ifeq ($(NON_MATCHING),0)
GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(wildcard src/**/*.c)
GLOBAL_ASM_O_FILES = $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file:.c=.o))
GLOBAL_ASM_DEP = $(BUILD_DIR)/src/audio/non_matching_dep
endif

###################### Custom Defines ########################
CUSTOM_C_DEFINES :=

ifeq ($(TARGET_N64),0)

# Check for PC Port Defines
ifeq ($(PC_PORT_DEFINES),1)
  CUSTOM_C_DEFINES += -DNO_SEGMENTED_MEMORY -DWIDESCREEN -DUSE_SYSTEM_MALLOC
endif

# Use Console exclusive defines
ifeq ($(TARGET_PORT_CONSOLE),1)
  CUSTOM_C_DEFINES += -DTARGET_PORT_CONSOLE
endif

ifeq ($(HIGH_FPS_PC),1)
  CUSTOM_C_DEFINES += -DHIGH_FPS_PC
endif

# Check for text save format
ifeq ($(TEXTSAVES),1)
  CUSTOM_C_DEFINES += -DTEXTSAVES
endif

# Check for external data
ifeq ($(EXTERNAL_DATA),1)
  CUSTOM_C_DEFINES += -DEXTERNAL_DATA
endif

# Use PC-only exclusive defines
ifeq ($(TARGET_PORT_CONSOLE),0)

  ifeq ($(WINDOW_API),SDL2)
    # Check for SDL2 touch controls
    ifeq ($(TOUCH_CONTROLS),1)
      CUSTOM_C_DEFINES += -DTOUCH_CONTROLS
    endif
  endif

ifeq ($(TARGET_ANDROID),0)

  # Check for Discord Rich Presence option
  ifeq ($(DISCORDRPC),1)
    CUSTOM_C_DEFINES += -DDISCORDRPC
  endif
  
  # Check for Mouse Option
  ifeq ($(EXT_OPTIONS_MENU),1)
    CUSTOM_C_DEFINES += -DMOUSE_ACTIONS
  endif

  # Check for Command Line Options
  ifeq ($(COMMAND_LINE_OPTIONS),1)
    CUSTOM_C_DEFINES += -DCOMMAND_LINE_OPTIONS
  endif

endif # !TARGET_ANDROID
endif # !TARGET_PORT_CONSOLE

endif # !TARGET_N64

# Check for Debug option
ifeq ($(DEBUG),1)
  CUSTOM_C_DEFINES += -DDEBUG
endif

# Check for Puppycam option
ifeq ($(BETTERCAMERA),1)
  CUSTOM_C_DEFINES += -DBETTERCAMERA
  EXT_OPTIONS_MENU := 1
endif

# Check for Cheats option
ifeq ($(CHEATS_ACTIONS),1)
  CUSTOM_C_DEFINES += -DCHEATS_ACTIONS
  EXT_OPTIONS_MENU := 1
endif

# Check for extended options menu option
ifeq ($(EXT_OPTIONS_MENU),1)
  CUSTOM_C_DEFINES += -DEXT_OPTIONS_MENU
endif

# Check for Rumble option
ifeq ($(TARGET_N3DS)$(TARGET_WII_U),00)
ifeq ($(RUMBLE_FEEDBACK),1)
  CUSTOM_C_DEFINES += -DRUMBLE_FEEDBACK
endif
endif

# Check for no drawing distance option
ifeq ($(NODRAWINGDISTANCE),1)
  CUSTOM_C_DEFINES += -DNODRAWINGDISTANCE
endif

# Check for Goddard option
ifeq ($(GODDARD_MFACE),1)
  CUSTOM_C_DEFINES += -DGODDARD_MFACE
endif

# Check for MOP option
ifeq ($(PORT_MOP_OBJS),1)
  CUSTOM_C_DEFINES += -DPORT_MOP_OBJS
endif

# Check for QoL fixes option
ifeq ($(QOL_FIXES),1)
  CUSTOM_C_DEFINES += -DQOL_FIXES
endif

# Check for QoL features option
ifeq ($(QOL_FEATURES),1)
  CUSTOM_C_DEFINES += -DQOL_FEATURES
endif

# Check for no bzero/bcopy workaround option
ifeq ($(NO_BZERO_BCOPY),1)
  CUSTOM_C_DEFINES += -DNO_BZERO_BCOPY
endif

# Use internal ldiv()/lldiv()
ifeq ($(NO_LDIV),1)
  CUSTOM_C_DEFINES += -DNO_LDIV
endif

##################### Compiler Options #######################
INCLUDE_DIRS := include $(BUILD_DIR) $(BUILD_DIR)/include src .
ifeq ($(TARGET_N64),1)
  INCLUDE_DIRS += include/libc
endif
ifeq ($(TARGET_ANDROID),1)
  INCLUDE_DIRS += $(PLATFORM_DIR)/SDL/include
endif

ifeq ($(TARGET_SWITCH),1)
  ifeq ($(strip $(DEVKITPRO)),)
    $(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
  endif
  export PATH := $(DEVKITPRO)/devkitA64/bin:$(PATH)
  include $(DEVKITPRO)/devkitA64/base_tools
  NXPATH := $(DEVKITPRO)/portlibs/switch/bin
  PORTLIBS ?= $(DEVKITPRO)/portlibs/switch
  LIBNX ?= $(DEVKITPRO)/libnx
  CROSS ?= aarch64-none-elf-
  SDLCROSS := $(NXPATH)/
  CC := $(CROSS)gcc
  CXX := $(CROSS)g++
  STRIP := $(CROSS)strip
  NXARCH := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE
  APP_TITLE := Super Mario 64
  APP_AUTHOR := Nintendo, n64decomp team, sm64pc team
  APP_VERSION := 1_master_$(VERSION)
  APP_ICON := $(PLATFORM_DIR)/logo.jpg
  INCLUDE_DIRS += $(LIBNX)/include $(PORTLIBS)/include
  OPT_FLAGS := -O2
endif

C_DEFINES := $(foreach d,$(DEFINES),-D$(d))
DEF_INC_CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I $(i)) $(C_DEFINES)

# Set C Preprocessor flags
CPPFLAGS := -P -Wno-trigraphs $(DEF_INC_CFLAGS) $(CUSTOM_C_DEFINES)
  
ifeq ($(TARGET_ANDROID),1)
  ifneq ($(shell which termux-setup-storage),) # Termux has clang
    CPPFLAGS := -E -P -x c -Wno-trigraphs $(DEF_INC_CFLAGS) $(CUSTOM_C_DEFINES)
  endif
endif

# 3DS Minimap flags
ifeq ($(TARGET_N3DS),1)
MINIMAP := $(PLATFORM_DIR)/minimap

MINIMAP_C := $(wildcard $(MINIMAP)/*.c)
MINIMAP_O := $(foreach file,$(MINIMAP_C),$(BUILD_DIR)/$(file:.c=.o))

MINIMAP_TEXTURES := $(MINIMAP)/textures
MINIMAP_PNG := $(wildcard $(MINIMAP_TEXTURES)/*.png)
MINIMAP_T3S := $(foreach file,$(MINIMAP_PNG),$(BUILD_DIR)/$(file:.png=.t3s))
MINIMAP_T3X := $(foreach file,$(MINIMAP_T3S),$(file:.t3s=.t3x))
MINIMAP_T3X_O := $(foreach file,$(MINIMAP_T3X),$(file:.t3x=.t3x.o))
MINIMAP_T3X_HEADERS := $(foreach file,$(MINIMAP_PNG),$(BUILD_DIR)/$(file:.png=_t3x.h))
endif

ifeq ($(TARGET_N64),1)
IRIX_ROOT := tools/ido5.3_compiler

ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips-linux-gnu-
else ifeq ($(shell type mips64-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
  CROSS := mips64-linux-gnu-
else
  CROSS := mips64-elf-
endif

# check that either QEMU_IRIX is set or qemu-irix package installed
ifeq ($(COMPILER_N64),ido)
  ifndef QEMU_IRIX
    QEMU_IRIX := $(shell which qemu-irix 2>/dev/null)
    ifeq (, $(QEMU_IRIX))
      $(error Please install qemu-irix package or set QEMU_IRIX env var to the full qemu-irix binary path)
    endif
  endif
endif

AS        := $(CROSS)as
CC        := $(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/bin/cc
CPP       := cpp
LD        := $(CROSS)ld
AR        := $(CROSS)ar
OBJDUMP   := $(CROSS)objdump
OBJCOPY   := $(CROSS)objcopy

# change the compiler to gcc, to use the default, install the gcc-mips-linux-gnu package
ifeq ($(COMPILER_N64),gcc)
  CC        := $(CROSS)gcc
endif

N64_CFLAGS := -nostdinc -DTARGET_N64
CC_CFLAGS := -fno-builtin

# Check code syntax with host compiler
CC_CHECK := gcc
CC_CHECK_CFLAGS := -fsyntax-only -fsigned-char $(CC_CFLAGS) $(N64_CFLAGS) $(DEF_INC_CFLAGS) -std=gnu90 -Wall -Wextra -Wno-format-security -Wno-main -DNON_MATCHING -DAVOID_UB

COMMON_CFLAGS = $(OPT_FLAGS) $(N64_CFLAGS) $(MIPSISET) $(DEF_INC_CFLAGS)

ASFLAGS := -march=vr4300 -mabi=32 $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(foreach d,$(DEFINES),--defsym $(d))
CFLAGS = -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -Xfullwarn -signed $(COMMON_CFLAGS) $(MIPSBIT)
RSPASMFLAGS := $(foreach d,$(DEFINES),-definelabel $(subst =, ,$(d)))

OBJCOPYFLAGS := --pad-to=0x800000 --gap-fill=0xFF
SYMBOL_LINKING_FLAGS := $(addprefix -R ,$(SEG_FILES))
LDFLAGS := -T undefined_syms.txt -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(BUILD_DIR)/sm64.$(VERSION).map --no-check-sections $(SYMBOL_LINKING_FLAGS)

# Includes extra compiler flags for workaround for n64 emus
# -mdivide-breaks:  Uses IDO compiler like behavior for dividing by zero (Old emus such as Project64 1.6)
# -fno-jump-tables: Disables jump function tables (Wii/Wii U virtual console)
ifeq ($(COMPILER_N64),gcc)
  CFLAGS := -march=vr4300 -mfix4300 -mabi=32 -mno-shared -G 0 $(COMMON_CFLAGS) -mhard-float -mdivide-breaks -fno-stack-protector -fno-common -fno-zero-initialized-in-bss -I include -I $(BUILD_DIR) -I $(BUILD_DIR)/include -I src -I . -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -fno-jump-tables -ffreestanding -fwrapv -Wall -Wextra
endif

CC_CHECK += $(CUSTOM_C_DEFINES)
CFLAGS += $(CUSTOM_C_DEFINES)

ifeq ($(shell getconf LONG_BIT), 32)
  # Work around memory allocation bug in QEMU
  export QEMU_GUEST_BASE := 1
else
  # Ensure that gcc treats the code as 32-bit
  CC_CHECK_CFLAGS += -m32
endif

# Prevent a crash with -sopt
export LANG := C

else # TARGET_N64

ifeq ($(TARGET_WII_U),1)

LD := $(CXX)
CPP := powerpc-eabi-cpp
OBJDUMP := powerpc-eabi-objdump
SDLCONFIG :=

else ifeq ($(TARGET_N3DS),1)
  CPP := $(DEVKITARM)/bin/arm-none-eabi-cpp
  OBJDUMP := $(DEVKITARM)/bin/arm-none-eabi-objdump
  OBJCOPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy
  AS := $(DEVKITARM)/bin/arm-none-eabi-as
  CC := $(DEVKITARM)/bin/arm-none-eabi-gcc
  CXX := $(DEVKITARM)/bin/arm-none-eabi-g++
  LD := $(CXX)
  SDLCONFIG :=

else

# for some reason sdl-config in dka64 is not prefixed, while pkg-config is
SDLCROSS ?= $(CROSS)

AS := $(CROSS)as

ifeq ($(OSX_BUILD),1)
AS := i686-w64-mingw32-as
endif

ifneq ($(TARGET_WEB),1) # As in, not-web PC port
  CC ?= $(CROSS)gcc
  CXX ?= $(CROSS)g++
else
  CC := emcc
  CXX := emcc
endif

LD := $(CXX)

ifeq ($(DISCORDRPC),1)
  LD := $(CXX)
else ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(CROSS),i686-w64-mingw32.static-) # fixes compilation in MXE on Linux and WSL
    LD := $(CC)
  else ifeq ($(CROSS),x86_64-w64-mingw32.static-)
    LD := $(CC)
  else
    LD := $(CXX)
  endif
endif

ifeq ($(WINDOWS_BUILD),1) # fixes compilation in MXE on Linux and WSL
  CPP := cpp
  OBJCOPY := objcopy
  OBJDUMP := $(CROSS)objdump
else ifeq ($(OSX_BUILD),1)
  CPP := cpp-9
  OBJCOPY := i686-w64-mingw32-objcopy
  OBJDUMP := i686-w64-mingw32-objdump
else ifeq ($(TARGET_ANDROID),1) # Termux has clang
  ifneq ($(shell which termux-setup-storage),)
    CPP      := clang
  else
    CPP      := cpp
  endif
  OBJCOPY := $(CROSS)objcopy
  OBJDUMP := $(CROSS)objdump
else # Linux & other builds
  CPP := $(CROSS)cpp
  OBJCOPY := $(CROSS)objcopy
  OBJDUMP := $(CROSS)objdump
endif

SDLCONFIG := $(SDLCROSS)sdl2-config

WINDRES := $(CROSS)windres

endif

# configure backend flags

BACKEND_CFLAGS := -DRAPI_$(RENDER_API)=1 -DWAPI_$(WINDOW_API)=1 -DAAPI_$(AUDIO_API)=1
# can have multiple controller APIs
BACKEND_CFLAGS += $(foreach capi,$(CONTROLLER_API),-DCAPI_$(capi)=1)
BACKEND_LDFLAGS :=

SDL1_USED := 0
SDL2_USED := 0

# for now, it's either SDL+GL, DXGI+DirectX, WHB or C3D so choose based on WAPI
ifeq ($(WINDOW_API),DXGI)
  DXBITS := `cat $(ENDIAN_BITWIDTH) | tr ' ' '\n' | tail -1`
  ifeq ($(RENDER_API),D3D12)
    BACKEND_CFLAGS += -Iinclude/dxsdk
  endif
  BACKEND_LDFLAGS += -ld3dcompiler -ldxgi -ldxguid
  BACKEND_LDFLAGS += -lsetupapi -ldinput8 -luser32 -lgdi32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion -luuid -static
else ifeq ($(findstring SDL,$(WINDOW_API)),SDL)
  ifeq ($(WINDOWS_BUILD),1)
    BACKEND_LDFLAGS += -lglew32 -lglu32 -lopengl32
  else ifeq ($(TARGET_ANDROID),1)
    BACKEND_LDFLAGS += -lGLESv2
  else ifeq ($(TARGET_RPI),1)
    BACKEND_LDFLAGS += -lGLESv2
  else ifeq ($(TARGET_SWITCH),1)
    BACKEND_LDFLAGS += -lGLESv2
  else ifeq ($(OSX_BUILD),1)
    BACKEND_LDFLAGS += -framework OpenGL `pkg-config --libs glew`
  else
    BACKEND_LDFLAGS += -lGL
  endif
else ifeq ($(WINDOW_API),WHB)
  BACKEND_LDFLAGS += -lSDL2 -lwut
else ifeq ($(WINDOW_API),C3D)
  BACKEND_LDFLAGS +=
endif

ifneq (,$(findstring SDL2,$(AUDIO_API)$(WINDOW_API)$(CONTROLLER_API)))
  SDL2_USED := 1
endif

ifneq (,$(findstring SDL1,$(AUDIO_API)$(WINDOW_API)$(CONTROLLER_API)))
  SDL1_USED := 1
endif

ifeq ($(SDL1_USED)$(SDL2_USED),11)
  $(error Cannot link both SDL1 and SDL2 at the same time)
endif

# SDL can be used by different systems, so we consolidate all of that shit into this

ifeq ($(SDL2_USED),1)
  SDLCONFIG := $(SDLCROSS)sdl2-config
  BACKEND_CFLAGS += -DHAVE_SDL2=1
else ifeq ($(SDL1_USED),1)
  SDLCONFIG := $(SDLCROSS)sdl-config
  BACKEND_CFLAGS += -DHAVE_SDL1=1
endif

ifneq ($(SDL1_USED)$(SDL2_USED),00)
  ifeq ($(TARGET_ANDROID),1)
    BACKEND_LDFLAGS += -lhidapi -lSDL2
  else
    BACKEND_CFLAGS += `$(SDLCONFIG) --cflags`
    ifeq ($(WINDOWS_BUILD),1)
      BACKEND_LDFLAGS += `$(SDLCONFIG) --static-libs` -lsetupapi -luser32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion
    else
      BACKEND_LDFLAGS += `$(SDLCONFIG) --libs`
    endif
  endif
endif

ifeq ($(WINDOWS_BUILD),1)
  CC_CHECK := $(CC) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -Wall -Wextra -Wno-format-security
  CFLAGS := $(OPT_FLAGS) $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -fwrapv

else ifeq ($(TARGET_WEB),1)
  CC_CHECK := $(CC) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -Wall -Wextra -Wno-format-security -s USE_SDL=2
  CFLAGS := $(OPT_FLAGS) $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -fwrapv -s USE_SDL=2

# Linux / Other builds below
else
  CC_CHECK := $(CC) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -Wall -Wextra -Wno-format-security
  CFLAGS := $(OPT_FLAGS) $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -fwrapv

endif

ifeq ($(TARGET_WII_U),1)
  CC_CHECK += -ffunction-sections $(MACHDEP) -ffast-math -D__WIIU__ -D__WUT__ $(INCLUDE)
  CFLAGS += -ffunction-sections $(MACHDEP) -ffast-math -D__WIIU__ -D__WUT__ $(INCLUDE)
endif

ifeq ($(TARGET_N3DS),1)
  CTRULIB  :=  $(DEVKITPRO)/libctru
  LIBDIRS  := $(CTRULIB)
  export LIBPATHS  :=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)
  CC_CHECK += -mtp=soft -DARM11 -DosGetTime=n64_osGetTime -D_3DS -march=armv6k -mtune=mpcore -mfloat-abi=hard -mword-relocations -fomit-frame-pointer -ffast-math $(foreach dir,$(LIBDIRS),-I$(dir)/include)
  CFLAGS += -mtp=soft -DARM11 -DosGetTime=n64_osGetTime -D_3DS -march=armv6k -mtune=mpcore -mfloat-abi=hard -mword-relocations -fomit-frame-pointer -ffast-math $(foreach dir,$(LIBDIRS),-I$(dir)/include)
  
  ifeq ($(DISABLE_N3DS_AUDIO),1)
    CFLAGS += -DDISABLE_N3DS_AUDIO
  endif
  ifeq ($(DISABLE_N3DS_FRAMESKIP),1)
    CFLAGS += -DDISABLE_N3DS_FRAMESKIP
  endif
endif

ifeq ($(TARGET_SWITCH),1)
  CC_CHECK := $(CC) $(NXARCH) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -Wall -Wextra -Wno-format-security -D__SWITCH__=1
  CFLAGS := $(NXARCH) $(OPT_FLAGS) $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -ftls-model=local-exec -fPIC -fwrapv -D__SWITCH__=1
endif

CC_CHECK += $(CUSTOM_C_DEFINES)
CFLAGS += $(CUSTOM_C_DEFINES)

# Load external textures
ifeq ($(EXTERNAL_DATA),1)
  CC_CHECK += -DFS_BASEDIR="\"$(BASEDIR)\""
  CFLAGS += -DFS_BASEDIR="\"$(BASEDIR)\""
  # tell skyconv to write names instead of actual texture data and save the split tiles so we can use them later
  SKYTILE_DIR := $(BUILD_DIR)/textures/skybox_tiles
  SKYCONV_ARGS := --store-names --write-tiles "$(SKYTILE_DIR)"
endif

ASFLAGS := $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(foreach d,$(DEFINES),--defsym $(d))

ifeq ($(TARGET_WEB),1)
LDFLAGS := -lm -lGL -lSDL2 -no-pie -s TOTAL_MEMORY=64MB -g4 --source-map-base http://localhost:8080/ -s "EXTRA_EXPORTED_RUNTIME_METHODS=['callMain']"

else ifeq ($(TARGET_WII_U),1)
LDFLAGS := -lm -no-pie $(BACKEND_LDFLAGS) $(MACHDEP) $(RPXSPECS) $(LIBPATHS)

else ifeq ($(TARGET_N3DS),1)
LDFLAGS := $(LIBPATHS) -lcitro3d -lctru -lm -specs=3dsx.specs -g -marm -mthumb-interwork -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft # -Wl,-Map,$(notdir $*.map)

else ifeq ($(TARGET_SWITCH),1)
  LDFLAGS := -specs=$(LIBNX)/switch.specs $(NXARCH) $(OPT_FLAGS) $(BACKEND_LDFLAGS) -lstdc++ -lm

else ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -Llib -lpthread $(BACKEND_LDFLAGS) -static
  ifeq ($(CROSS),)
    LDFLAGS += -no-pie
  endif
  ifeq ($(DEBUG),1)
    LDFLAGS += -mconsole
  endif

else ifeq ($(TARGET_RPI),1)
  LDFLAGS := $(OPT_FLAGS) -lm $(BACKEND_LDFLAGS) -no-pie

else ifeq ($(TARGET_ANDROID),1)
  ifneq ($(shell uname -m | grep "i.86"),)
    ARCH_APK := x86
  else ifeq ($(shell uname -m),x86_64)
    ARCH_APK := x86_64
  else ifeq ($(shell getconf LONG_BIT),64)
    ARCH_APK := arm64-v8a
  else
    ARCH_APK := armeabi-v7a
  endif
  CFLAGS  += -fPIC
  LDFLAGS := -L ./$(PLATFORM_DIR)/android/lib/$(ARCH_APK)/ -lm $(BACKEND_LDFLAGS) -shared

else ifeq ($(OSX_BUILD),1)
  LDFLAGS := -lm $(BACKEND_LDFLAGS) -no-pie -lpthread

else
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -lm $(BACKEND_LDFLAGS) -lpthread -ldl
  ifeq ($(NO_PIE), 1)
    LDFLAGS += -no-pie
  endif
  ifeq ($(DISCORDRPC),1)
    LDFLAGS += -Wl,-rpath .
  endif

endif # End of LDFLAGS

# Prevent a crash with -sopt
export LANG := C

endif

####################### Other Tools #########################

ifeq ($(HOST_OS),Windows)
EXT_PREFIX := .exe
else
EXT_PREFIX :=
endif

# N64 conversion tools
TOOLS_DIR = tools
MIO0TOOL = $(TOOLS_DIR)/mio0$(EXT_PREFIX)
N64CKSUM = $(TOOLS_DIR)/n64cksum$(EXT_PREFIX)
N64GRAPHICS = $(TOOLS_DIR)/n64graphics$(EXT_PREFIX)
N64GRAPHICS_CI = $(TOOLS_DIR)/n64graphics_ci$(EXT_PREFIX)
TEXTCONV = $(TOOLS_DIR)/textconv$(EXT_PREFIX)
AIFF_EXTRACT_CODEBOOK = $(TOOLS_DIR)/aiff_extract_codebook$(EXT_PREFIX)
VADPCM_ENC = $(TOOLS_DIR)/vadpcm_enc$(EXT_PREFIX)
EXTRACT_DATA_FOR_MIO = $(TOOLS_DIR)/extract_data_for_mio$(EXT_PREFIX)
SKYCONV = $(TOOLS_DIR)/skyconv$(EXT_PREFIX)
EMULATOR = mupen64plus
EMU_FLAGS = --noosd
LOADER = loader64
LOADER_FLAGS = -vwf
SHA1SUM = sha1sum
PRINT = printf
ZEROTERM = $(PYTHON) $(TOOLS_DIR)/zeroterm.py
ENDIAN_BITWIDTH := $(BUILD_DIR)/endian-and-bitwidth
GET_GODDARD_SIZE = $(PYTHON) $(TOOLS_DIR)/getGoddardSize.py

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

ifeq (, $(shell which armips 2>/dev/null))
  RSPASM := $(TOOLS_DIR)/armips$(EXT_PREFIX)
else
  RSPASM = armips
endif

###################### Dependency Check #####################

# Stubbed

######################## Targets #############################

ifeq ($(TARGET_N64),1)
all: $(ROM)
else ifeq ($(TARGET_ANDROID),1)
all: $(APK_SIGNED)
EXE_DEPEND := $(APK_SIGNED)
else
all: $(EXE)
EXE_DEPEND := $(EXE)
endif

ifeq ($(TARGET_SWITCH),1)
all: $(EXE).nro
endif

ifeq ($(TARGET_N3DS),1)
cia: $(CIA)
endif

# thank you apple very cool
ifeq ($(HOST_OS),Darwin)
  CP := gcp
else
  CP := cp
endif

ifeq ($(EXTERNAL_DATA),1)

BASEPACK_PATH := $(BUILD_DIR)/$(BASEDIR)/$(BASEPACK)
BASEPACK_LST := $(BUILD_DIR)/basepack.lst

# depend on resources as well
all: $(BASEPACK_PATH)

# phony target for building resources
res: $(BASEPACK_PATH)

# prepares the basepack.lst
$(BASEPACK_LST): $(EXE_DEPEND)
	@mkdir -p $(BUILD_DIR)/$(BASEDIR)
	@echo "$(BUILD_DIR)/sound/bank_sets sound/bank_sets" > $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sequences.bin sound/sequences.bin" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sound_data.ctl sound/sound_data.ctl" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sound_data.tbl sound/sound_data.tbl" >> $(BASEPACK_LST)
	@$(foreach f, $(wildcard $(SKYTILE_DIR)/*), echo $(f) gfx/$(f:$(BUILD_DIR)/%=%) >> $(BASEPACK_LST);)
	@find actors -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
	@find levels -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
	@find textures -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
    ifeq ($(PORT_MOP_OBJS),1)
	@find src/extras/mop/actors -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
    endif

# prepares the resource ZIP with base data
$(BASEPACK_PATH): $(BASEPACK_LST)
	@$(PYTHON) $(TOOLS_DIR)/mkzip.py $(BASEPACK_LST) $(BASEPACK_PATH)

endif

clean:
	$(RM) -r $(BUILD_DIR_BASE)

cleantools:
	$(MAKE) -C tools clean

distclean:
	$(RM) -r $(BUILD_DIR_BASE)
	./extract_assets.py --clean

test: $(ROM)
	$(EMULATOR) $(EMU_FLAGS) $<

load: $(ROM)
	$(LOADER) $(LOADER_FLAGS) $<

$(BUILD_DIR)/$(RPC_LIBS):
	@$(CP) -f $(RPC_LIBS) $(BUILD_DIR)

libultra: $(BUILD_DIR)/libultra.a

$(BUILD_DIR)/asm/boot.o: $(IPL3_RAW_FILES)
$(BUILD_DIR)/src/game/crash_screen.o: $(CRASH_TEXTURE_C_FILES)
$(CRASH_TEXTURE_C_FILES): TEXTURE_ENCODING := u32

$(BUILD_DIR)/lib/rsp.o: $(BUILD_DIR)/rsp/rspboot.bin $(BUILD_DIR)/rsp/fast3d.bin $(BUILD_DIR)/rsp/audio.bin

ifeq ($(VERSION),sh)
  $(BUILD_DIR)/src/audio/load_sh.o: $(SOUND_BIN_DIR)/bank_sets.inc.c $(SOUND_BIN_DIR)/sequences_header.inc.c $(SOUND_BIN_DIR)/ctl_header.inc.c $(SOUND_BIN_DIR)/tbl_header.inc.c
endif

$(BUILD_DIR)/include/text_strings.h: include/text_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@

$(BUILD_DIR)/include/text_menu_strings.h: include/text_menu_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap_menu.txt $< $@

ifeq ($(EXT_OPTIONS_MENU),1)
$(BUILD_DIR)/include/text_options_strings.h: include/text_options_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@

ifeq ($(CHEATS_ACTIONS),1)
$(BUILD_DIR)/include/text_cheats_strings.h: include/text_cheats_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@
endif

ifeq ($(DEBUG),1)
$(BUILD_DIR)/include/text_debug_strings.h: include/text_debug_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@
endif

endif

ifeq ($(VERSION),eu)
TEXT_DIRS := text/de text/us text/fr

# EU encoded text inserted into individual segment 0x19 files,
# and course data also duplicated in leveldata.c
$(BUILD_DIR)/bin/eu/translation_en.o: $(BUILD_DIR)/text/us/define_text.inc.c
$(BUILD_DIR)/bin/eu/translation_de.o: $(BUILD_DIR)/text/de/define_text.inc.c
$(BUILD_DIR)/bin/eu/translation_fr.o: $(BUILD_DIR)/text/fr/define_text.inc.c
$(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/us/define_courses.inc.c
$(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/de/define_courses.inc.c
$(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/fr/define_courses.inc.c

else
ifeq ($(VERSION),sh)
TEXT_DIRS := text/jp
$(BUILD_DIR)/bin/segment2.o: $(BUILD_DIR)/text/jp/define_text.inc.c

else
TEXT_DIRS := text/$(VERSION)

# non-EU encoded text inserted into segment 0x02
$(BUILD_DIR)/bin/segment2.o: $(BUILD_DIR)/text/$(VERSION)/define_text.inc.c
endif
endif

$(BUILD_DIR)/text/%/define_courses.inc.c: text/define_courses.inc.c text/%/courses.h
	@$(PRINT) "$(GREEN)Preprocessing: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(CPP) $(CPPFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

$(BUILD_DIR)/text/%/define_text.inc.c: text/define_text.inc.c text/%/courses.h text/%/dialogs.h
	@$(PRINT) "$(GREEN)Preprocessing: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(CPP) $(CPPFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

RSP_DIRS := $(BUILD_DIR)/rsp
ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(GODDARD_SRC_DIRS) $(ULTRA_SRC_DIRS) $(ULTRA_BIN_DIRS) $(BIN_DIRS) $(TEXTURE_DIRS) $(TEXT_DIRS) $(SOUND_SAMPLE_DIRS) $(addprefix levels/,$(LEVEL_DIRS)) include) $(MIO0_DIR) $(addprefix $(MIO0_DIR)/,$(VERSION)) $(SOUND_BIN_DIR) $(SOUND_BIN_DIR)/sequences/$(VERSION) $(RSP_DIRS)

ifeq ($(EXTERNAL_DATA),1)
  ALL_DIRS += $(SKYTILE_DIR)
endif

ifeq ($(TARGET_N3DS),1)
  # create build dir for .t3x etc
  ALL_DIRS += $(BUILD_DIR)/$(MINIMAP_TEXTURES) $(BUILD_DIR)/$(PLATFORM_DIR)
endif

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

$(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_menu_strings.h

ifeq ($(EXT_OPTIONS_MENU),1)
  $(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_options_strings.h
endif

ifeq ($(CHEATS_ACTIONS),1)
  $(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_cheats_strings.h
endif

ifeq ($(DEBUG),1)
  $(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_debug_strings.h
endif

ifeq ($(VERSION),eu)
  LANG_O_FILES := $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
else
  LANG_O_FILES :=
endif

$(BUILD_DIR)/src/menu/file_select.o:    $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
$(BUILD_DIR)/src/menu/star_select.o:    $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
$(BUILD_DIR)/src/game/ingame_menu.o:    $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)

ifeq ($(TARGET_N64),1)
  $(BUILD_DIR)/src/extras/n64_mem_error_screen.o: $(BUILD_DIR)/include/text_strings.h
endif

ifeq ($(EXT_OPTIONS_MENU),1)

  ifeq ($(BETTERCAMERA),1)
    $(BUILD_DIR)/src/extras/bettercamera.o: $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif

  ifeq ($(CHEATS_ACTIONS),1)
    $(BUILD_DIR)/src/extras/cheats.o:       $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif
  
  ifeq ($(DEBUG),1)
    $(BUILD_DIR)/src/extras/debug_menu.o:   $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif

  $(BUILD_DIR)/src/extras/options_menu.o:   $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
endif

ifeq ($(TARGET_PORT_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    $(BUILD_DIR)/src/pc/discord/discordrpc.o: $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif
endif

################################################################
# Texture Generation                                           #
################################################################

# Convert PNGs to RGBA32, RGBA16, IA16, IA8, IA4, IA1, I8, I4 binary files

TEXTURE_ENCODING := u8

ifeq ($(EXTERNAL_DATA),1)
$(BUILD_DIR)/%: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(ZEROTERM) "$(patsubst %.png,%,$^)" > $@
$(BUILD_DIR)/%.inc.c: $(BUILD_DIR)/% %.png
	$(call print,Converting:,$<,$@)
	$(V)hexdump -v -e '1/1 "0x%X,"' $< > $@
else
$(BUILD_DIR)/%: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS) -s raw -i $@ -g $< -f $(lastword $(subst ., ,$@))
$(BUILD_DIR)/%.inc.c: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS) -s $(TEXTURE_ENCODING) -i $@ -g $< -f $(lastword ,$(subst ., ,$(basename $<)))
endif

ifeq ($(EXTERNAL_DATA),0)

# Color Index CI8
$(BUILD_DIR)/%.ci8: %.ci8.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS_CI) -i $@ -g $< -f ci8

# Color Index CI4
$(BUILD_DIR)/%.ci4: %.ci4.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS_CI) -i $@ -g $< -f ci4

endif

################################################################

# compressed segment generation

ifeq ($(TARGET_N64),1)
# TODO: ideally this would be `-Trodata-segment=0x07000000` but that doesn't set the address
$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o
	$(call print,Linking ELF file:,$<,$@)
	$(V)$(LD) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map -o $@ $<
# Override for level.elf, which otherwise matches the above pattern
.SECONDEXPANSION:
$(BUILD_DIR)/levels/%/leveldata.elf: $(BUILD_DIR)/levels/%/leveldata.o $(BUILD_DIR)/bin/$$(TEXTURE_BIN).elf
	$(call print,Linking ELF file:,$<,$@)
	$(V)$(LD) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map --just-symbols=$(BUILD_DIR)/bin/$(TEXTURE_BIN).elf -o $@ $<

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(call print,Extracting compressible data from:,$<,$@)
	$(V)$(EXTRACT_DATA_FOR_MIO) $< $@

$(BUILD_DIR)/levels/%/leveldata.bin: $(BUILD_DIR)/levels/%/leveldata.elf
	$(call print,Extracting compressible data from:,$<,$@)
	$(V)$(EXTRACT_DATA_FOR_MIO) $< $@

# Compress binary file
$(BUILD_DIR)/%.mio0: $(BUILD_DIR)/%.bin
	$(call print,Compressing:,$<,$@)
	$(V)$(MIO0TOOL) $< $@

# convert binary mio0 to object file
$(BUILD_DIR)/%.mio0.o: $(BUILD_DIR)/%.mio0
	$(call print,Converting MIO0 to ELF:,$<,$@)
	$(V)$(LD) -r -b binary $< -o $@
endif

# PC Area
$(BUILD_DIR)/%.table: %.aiff
	$(call print,Extracting codebook:,$<,$@)
	$(V)$(AIFF_EXTRACT_CODEBOOK) $< >$@

$(BUILD_DIR)/%.aifc: $(BUILD_DIR)/%.table %.aiff
	$(call print,Encoding ADPCM:,$(word 2,$^),$@)
	$(V)$(VADPCM_ENC) -c $^ $@

# Assemble RSP assembly code
$(BUILD_DIR)/rsp/%.bin $(BUILD_DIR)/rsp/%_data.bin: rsp/%.s
	$(call print,Assembling:,$<,$@)
	$(V)$(RSPASM) -sym $@.sym $(RSPASMFLAGS) -strequ CODE_FILE $(BUILD_DIR)/rsp/$*.bin -strequ DATA_FILE $(BUILD_DIR)/rsp/$*_data.bin $<

$(ENDIAN_BITWIDTH): tools/determine-endian-bitwidth.c
	@$(PRINT) "$(GREEN)Generating endian-bitwidth $(NO_COL)\n"
	$(V)$(CC) -c $(CFLAGS) -o $@.dummy2 $< 2>$@.dummy1; true
	$(V)grep -o 'msgbegin --endian .* --bitwidth .* msgend' $@.dummy1 > $@.dummy2
	$(V)head -n1 <$@.dummy2 | cut -d' ' -f2-5 > $@
	$(V)$(RM) $@.dummy1
	$(V)$(RM) $@.dummy2

$(SOUND_BIN_DIR)/sound_data.ctl: sound/sound_banks/ $(SOUND_BANK_FILES) $(SOUND_SAMPLE_AIFCS) $(ENDIAN_BITWIDTH)
	@$(PRINT) "$(GREEN)Generating:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/assemble_sound.py $(BUILD_DIR)/sound/samples/ sound/sound_banks/ $(SOUND_BIN_DIR)/sound_data.ctl $(SOUND_BIN_DIR)/ctl_header $(SOUND_BIN_DIR)/sound_data.tbl $(SOUND_BIN_DIR)/tbl_header $(C_DEFINES) $$(cat $(ENDIAN_BITWIDTH))

$(SOUND_BIN_DIR)/sound_data.tbl: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/ctl_header: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/tbl_header: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/sequences.bin: $(SOUND_BANK_FILES) sound/sequences.json $(SOUND_SEQUENCE_DIRS) $(SOUND_SEQUENCE_FILES) $(ENDIAN_BITWIDTH)
	@$(PRINT) "$(GREEN)Generating:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/assemble_sound.py --sequences $@ $(SOUND_BIN_DIR)/sequences_header $(SOUND_BIN_DIR)/bank_sets sound/sound_banks/ sound/sequences.json $(SOUND_SEQUENCE_FILES) $(C_DEFINES) $$(cat $(ENDIAN_BITWIDTH))

$(SOUND_BIN_DIR)/bank_sets: $(SOUND_BIN_DIR)/sequences.bin
	@true

$(SOUND_BIN_DIR)/sequences_header: $(SOUND_BIN_DIR)/sequences.bin
	@true

$(SOUND_BIN_DIR)/%.m64: $(SOUND_BIN_DIR)/%.o
	$(call print,Converting to M64:,$<,$@)
	$(V)$(OBJCOPY) -j .rodata $< -O binary $@

ifeq ($(EXTERNAL_DATA),1)

$(SOUND_BIN_DIR)/%.inc.c: $(SOUND_BIN_DIR)/%
	$(ZEROTERM) "$(patsubst $(BUILD_DIR)/%,%,$^)" | hexdump -v -e '1/1 "0x%X,"' > $@

else

$(SOUND_BIN_DIR)/%.inc.c: $(SOUND_BIN_DIR)/%
	$(call print,Converting to C:,$<,$@)
	$(V)hexdump -v -e '1/1 "0x%X,"' $< > $@
	$(V)echo >> $@

endif

$(SOUND_BIN_DIR)/sound_data.o: $(SOUND_BIN_DIR)/sound_data.ctl $(SOUND_BIN_DIR)/sound_data.tbl $(SOUND_BIN_DIR)/sequences.bin $(SOUND_BIN_DIR)/bank_sets

$(BUILD_DIR)/levels/scripts.o: $(BUILD_DIR)/include/level_headers.h

$(BUILD_DIR)/include/level_headers.h: levels/level_headers.h.in
	$(call print,Preprocessing level headers:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -I . $< | sed -E 's|(.+)|#include "\1"|' > $@

$(BUILD_DIR)/assets/mario_anim_data.c: $(wildcard assets/anims/*.inc.c)
	@$(PRINT) "$(GREEN)Generating animation data $(NO_COL)\n"
	$(V)$(PYTHON) tools/mario_anims_converter.py > $@

$(BUILD_DIR)/assets/demo_data.c: assets/demo_data.json $(wildcard assets/demos/*.bin)
	@$(PRINT) "$(GREEN)Generating demo data $(NO_COL)\n"
	$(V)$(PYTHON) tools/demo_data_converter.py assets/demo_data.json $(DEF_INC_CFLAGS) > $@

# Alternate compiler flags needed for matching
ifeq ($(COMPILER),ido)
  $(BUILD_DIR)/levels/%/leveldata.o: OPT_FLAGS := -g
  $(BUILD_DIR)/actors/%.o:           OPT_FLAGS := -g
  $(BUILD_DIR)/bin/%.o:              OPT_FLAGS := -g
  $(BUILD_DIR)/src/goddard/%.o:      OPT_FLAGS := -g
  $(BUILD_DIR)/src/goddard/%.o:      MIPSISET := -mips1
  $(BUILD_DIR)/lib/src/%.o:          OPT_FLAGS :=
  $(BUILD_DIR)/lib/src/math/%.o:     OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/src/math/ll%.o:   OPT_FLAGS :=
  $(BUILD_DIR)/lib/src/math/ll%.o:   MIPSISET := -mips3 -32
  $(BUILD_DIR)/lib/src/ldiv.o:       OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/src/string.o:     OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/src/gu%.o:        OPT_FLAGS := -O3
  $(BUILD_DIR)/lib/src/al%.o:        OPT_FLAGS := -O3

  ifeq ($(VERSION),sh)
    $(BUILD_DIR)/lib/src/_Ldtob.o:   OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Litob.o:   OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Printf.o:  OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/sprintf.o:  OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/osDriveRomInit.o: OPT_FLAGS := -g
  endif
  ifeq ($(VERSION),eu)
    $(BUILD_DIR)/lib/src/_Ldtob.o:   OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Litob.o:   OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Printf.o:  OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/sprintf.o:  OPT_FLAGS := -O3

    # For all audio files other than external.c and port_eu.c, put string literals
    # in .data. (In Shindou, the port_eu.c string literals also moved to .data.)
    $(BUILD_DIR)/src/audio/%.o:        OPT_FLAGS := -O2 -use_readwrite_const
    $(BUILD_DIR)/src/audio/port_eu.o:  OPT_FLAGS := -O2
  endif
  ifeq ($(VERSION_JP_US),true)
    $(BUILD_DIR)/src/audio/%.o:        OPT_FLAGS := -O2 -Wo,-loopunroll,0
    $(BUILD_DIR)/src/audio/load.o:     OPT_FLAGS := -O2 -Wo,-loopunroll,0 -framepointer
    # The source-to-source optimizer copt is enabled for audio. This makes it use
    # acpp, which needs -Wp,-+ to handle C++-style comments.
    # All other files than external.c should really use copt, but only a few have
    # been matched so far.
    $(BUILD_DIR)/src/audio/effects.o:   OPT_FLAGS := -O2 -Wo,-loopunroll,0 -sopt,-inline=sequence_channel_process_sound,-scalaroptimize=1 -Wp,-+
    $(BUILD_DIR)/src/audio/synthesis.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0 -sopt,-scalaroptimize=1 -Wp,-+
  endif
  $(BUILD_DIR)/src/audio/external.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0

# Add a target for build/eu/src/audio/*.copt to make it easier to see debug
$(BUILD_DIR)/src/audio/%.acpp: src/audio/%.c
	$(ACPP) $(TARGET_CFLAGS) $(DEF_INC_CFLAGS) -D__sgi -+ $< > $@
$(BUILD_DIR)/src/audio/%.copt: $(BUILD_DIR)/src/audio/%.acpp
	$(COPT) -signed -I=$< -CMP=$@ -cp=i -scalaroptimize=1 $(COPTFLAGS)
$(BUILD_DIR)/src/audio/seqplayer.copt: COPTFLAGS := -inline_manual

endif

# Rebuild files with 'GLOBAL_ASM' if the NON_MATCHING flag changes.
$(GLOBAL_ASM_O_FILES): $(GLOBAL_ASM_DEP).$(NON_MATCHING)
$(GLOBAL_ASM_DEP).$(NON_MATCHING):
	@$(RM) -f $(GLOBAL_ASM_DEP).*
	$(V)touch $@

# Compile C code
$(BUILD_DIR)/%.o: %.cpp
	$(call print,Compiling:,$<,$@)
	@$(CXX) -fsyntax-only $(CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CXX) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(call print,Compiling:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) -c $(CFLAGS) -o $@ $<
    
$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	$(call print,Compiling:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) -c $(CFLAGS) -o $@ $<

# Assemble assembly code
$(BUILD_DIR)/%.o: %.s
	$(call print,Assembling:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) $< | $(AS) $(ASFLAGS) -MD $(BUILD_DIR)/$*.d -o $@

ifeq ($(WINDOWS_BUILD),1)
# Windows Icon
$(BUILD_DIR)/%.o: %.rc
	$(call print,Applying Windows Icon...)
	$(V)$(WINDRES) -o $@ -i $<
endif

ifeq ($(TARGET_N64),1)

ifeq ($(GODDARD_MFACE),1)
  GODDARD_TXT_INC := $(BUILD_DIR)/goddard.txt
endif

# Run linker script through the C preprocessor
$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT) $(GODDARD_TXT_INC)
	$(call print,Preprocessing linker script:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

# Link libultra
$(BUILD_DIR)/libultra.a: $(ULTRA_O_FILES)
	@$(PRINT) "$(GREEN)Linking libultra:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(ULTRA_O_FILES)
	$(V)$(TOOLS_DIR)/patch_elf_32bit $@

ifeq ($(GODDARD_MFACE),1)
# Link libgoddard
$(BUILD_DIR)/libgoddard.a: $(GODDARD_O_FILES)
	@$(PRINT) "$(GREEN)Linking libgoddard:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(GODDARD_O_FILES)
    
LIB_GD_FILE := $(BUILD_DIR)/libgoddard.a
LIB_GD_FLAG := -lgoddard

# SS2: Goddard rules to get size
$(BUILD_DIR)/sm64_prelim.ld: $(LD_SCRIPT) $(O_FILES) $(MIO0_OBJ_FILES) $(SEG_FILES) undefined_syms.txt $(BUILD_DIR)/libultra.a $(LIB_GD_FILE)
	$(call print,Preprocessing preliminary linker script:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -DPRELIMINARY=1 -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

$(BUILD_DIR)/sm64_prelim.elf: $(BUILD_DIR)/sm64_prelim.ld
	@$(PRINT) "$(GREEN)Linking Preliminary ELF file:  $(BLUE)$@ $(NO_COL)\n"
    # Slightly edited version of LDFLAGS
	$(V)$(LD) -L $(BUILD_DIR) -T undefined_syms.txt -T $< -Map $(BUILD_DIR)/sm64_prelim.map --no-check-sections $(SYMBOL_LINKING_FLAGS) -o $@ $(O_FILES) $(LIBS) -lultra $(LIB_GD_FLAG)

$(BUILD_DIR)/goddard.txt: $(BUILD_DIR)/sm64_prelim.elf
	$(call print,Getting Goddard size...)
	$(V)$(GET_GODDARD_SIZE) $(BUILD_DIR)/sm64_prelim.map $(VERSION)

LIB_GD_PRE_ELF := $(BUILD_DIR)/sm64_prelim.elf

endif

# Link SM64 ELF file
$(ELF): $(LIB_GD_PRE_ELF) $(O_FILES) $(MIO0_OBJ_FILES) $(SEG_FILES) $(BUILD_DIR)/$(LD_SCRIPT) undefined_syms.txt $(BUILD_DIR)/libultra.a $(LIB_GD_FILE)
	@$(PRINT) "$(GREEN)Linking ELF file:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) -L $(BUILD_DIR) $(LDFLAGS) $(GODDARD_TXT_INC) -o $@ $(O_FILES) $(LIBS) -lultra $(LIB_GD_FLAG)

# Build ROM
$(ROM): $(ELF)
	$(call print,Building ROM:,$<,$@)
	$(V)$(OBJCOPY) $(OBJCOPYFLAGS) $< $(@:.z64=.bin) -O binary
	$(V)$(N64CKSUM) $(@:.z64=.bin) $@

$(BUILD_DIR)/$(TARGET).objdump: $(ELF)
	$(OBJDUMP) -D $< > $@
else ifeq ($(TARGET_WII_U),1)
$(ELF):  $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS)
	$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
$(EXE): $(ELF)
	@cp $< $*.strip.elf
	$(SILENTCMD)$(STRIP) -g $*.strip.elf $(ERROR_FILTER)
	$(SILENTCMD)elf2rpl $*.strip.elf $@ $(ERROR_FILTER)
	@rm $*.strip.elf
	@echo built ... $(notdir $@)
else ifeq ($(TARGET_N3DS),1)
# for building the vertex shader
$(BUILD_DIR)/src/pc/gfx/shader.shbin.o : src/pc/gfx/shader.v.pica
	$(eval CURBIN := $<.shbin)
	$(DEVKITPRO)/tools/bin/picasso -o $(BUILD_DIR)/src/pc/gfx/shader.shbin $<
	$(DEVKITPRO)/tools/bin/bin2s $(BUILD_DIR)/src/pc/gfx/shader.shbin | $(AS) -o $@

SMDH_TITLE ?= Super Mario 64
SMDH_DESCRIPTION ?= Super Mario 64 3DS Port
SMDH_AUTHOR ?= mkst
SMDH_ICON := $(PLATFORM_DIR)/icon.smdh

$(ELF): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/src/pc/gfx/shader.shbin.o $(SMDH_ICON)
	$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(BUILD_DIR)/src/pc/gfx/shader.shbin.o $(MINIMAP_T3X_O) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)

$(EXE): $(ELF)
	3dsxtool $< $@ --smdh=$(BUILD_DIR)/$(SMDH_ICON)

$(CIA): $(ELF)
	@echo "Generating $@, please wait..."
	makerom -f cia -o "$@" -rsf $(PLATFORM_DIR)/template.rsf -target t -elf "$<" -icon $(PLATFORM_DIR)/icon.icn -banner $(PLATFORM_DIR)/banner.bnr

# stolen from /opt/devkitpro/devkitARM/base_tools
define bin2o
  bin2s -a 4 -H $(BUILD_DIR)/$(MINIMAP_TEXTURES)/`(echo $(<F) | tr . _)`.h $(BUILD_DIR)/$< | $(AS) -o $(BUILD_DIR)/$(MINIMAP_TEXTURES)/$(<F).o
endef

# TODO: simplify dependency chain
$(BUILD_DIR)/src/pc/gfx/gfx_citro3d.o: $(BUILD_DIR)/src/pc/gfx/gfx_3ds.o
$(BUILD_DIR)/src/pc/gfx/gfx_3ds.o: $(BUILD_DIR)/src/pc/gfx/gfx_3ds_menu.o
$(BUILD_DIR)/src/pc/gfx/gfx_3ds_menu.o: $(MINIMAP_T3X_HEADERS)

%.t3x.o $(BUILD_DIR)/%_t3x.h: %.t3x
	$(bin2o)

%.t3x: %.t3s
	tex3ds -i $(BUILD_DIR)/$< -o $(BUILD_DIR)/$@

%.t3s: %.png
	@printf -- "-f rgba -z auto\n../../../../../../$(<)\n" > $(BUILD_DIR)/$@

%.smdh: %.png
	smdhtool --create "$(SMDH_TITLE)" "$(SMDH_DESCRIPTION)" "$(SMDH_AUTHOR)" $< $(BUILD_DIR)/$@

else

ifeq ($(TARGET_ANDROID),1)
APK_FILES := $(shell find $(PLATFORM_DIR)/android/ -type f)

$(APK): $(EXE) $(APK_FILES)
	cp -r $(PLATFORM_DIR)/android $(BUILD_DIR)/$(PLATFORM_DIR)/ && \
	cp $(PREFIX)/lib/libc++_shared.so $(BUILD_DIR)/$(PLATFORM_DIR)/android/lib/$(ARCH_APK)/ && \
	cp $(EXE) $(BUILD_DIR)/$(PLATFORM_DIR)/android/lib/$(ARCH_APK)/ && \
	cd $(BUILD_DIR)/$(PLATFORM_DIR)/android && \
	zip -r ../../../../../$@ ./* && \
	cd ../../../../.. && \
	rm -rf $(BUILD_DIR)/$(PLATFORM_DIR)/android

ifeq ($(OLD_APKSIGNER),1)
$(APK_SIGNED): $(APK)
	apksigner $(BUILD_DIR)/keystore $< $@
else
$(APK_SIGNED): $(APK)
	cp $< $@
	apksigner sign --cert $(PLATFORM_DIR)/certificate.pem --key $(PLATFORM_DIR)/key.pk8 $@
endif
endif

$(EXE): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS)
	$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
endif

ifeq ($(TARGET_SWITCH), 1)

# add `--icon=$(APP_ICON)` to this when we get a suitable icon
%.nro: %.stripped %.nacp
	@elf2nro $< $@ --nacp=$*.nacp --icon=$(APP_ICON)
	@echo built ... $(notdir $@)

%.nacp:
	@nacptool --create "$(APP_TITLE)" "$(APP_AUTHOR)" "$(APP_VERSION)" $@ $(NACPFLAGS)
	@echo built ... $(notdir $@)

%.stripped: %
	@$(STRIP) -o $@ $<
	@echo stripped ... $(notdir $<)

endif

.PHONY: all clean distclean cleantools default diff test load libultra res
.PRECIOUS: $(BUILD_DIR)/bin/%.elf $(SOUND_BIN_DIR)/%.ctl $(SOUND_BIN_DIR)/%.tbl $(SOUND_SAMPLE_TABLES) $(SOUND_BIN_DIR)/%.s $(BUILD_DIR)/%
.DELETE_ON_ERROR:

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

-include $(DEP_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
