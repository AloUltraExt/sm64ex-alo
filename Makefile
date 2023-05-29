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

# Makefile Refactor from Refresh 13 is somewhat adapted but
# has to be carefully to make sure sm64ex and other ports still work.
# There's also some HackerSM64 N64 specific Makefile changes.

# Manual target defines

# Build for original N64
TARGET_N64 ?= 0
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

# Compiler to use for N64 (and other targets if required)
#   gcc - uses the GNU C Compiler
#   clang - uses clang C/C++ frontend for LLVM
COMPILER_TYPE ?= gcc
$(eval $(call validate-option,COMPILER_TYPE,gcc clang))

COMPILER_OPT ?= default
$(eval $(call validate-option,COMPILER_OPT,debug default fast))

# Automatic target defines

# Build for Windows
WINDOWS_BUILD ?= 0
# Build for Android
TARGET_ANDROID ?= 0
# Makeflag to enable OSX fixes
OSX_BUILD ?= 0
# Specify the target you are building for, TARGET_BITS=0 means native
TARGET_ARCH ?= native
TARGET_BITS ?= 0

# PC Port defines
PC_PORT_DEFINES ?= 0
# PC Port defines from a ported console device
TARGET_PORT_CONSOLE ?= 0

# Various workarounds for weird and/or old toolchains
NO_BZERO_BCOPY ?= 0
NO_LDIV ?= 0
NO_PIE ?= 1

# Backend selection

# Renders: GL, GL_LEGACY, D3D11, D3D12, GX2 (forced if the target is Wii U), C3D (forced if the target is 3DS)
RENDER_API ?= GL
# Window managers: SDL1, SDL2, DXGI (forced if D3D11 or D3D12 in RENDER_API), GX2 (forced if the target is Wii U), 3DS (forced if the target is 3DS)
WINDOW_API ?= SDL2
# Audio backends: SDL1, SDL2 (forced if the target is Wii U), 3DS (forced if the target is 3DS)
AUDIO_API ?= SDL2
# Controller backends (can have multiple, space separated): SDL1, SDL2
# WII_U (forced if the target is Wii U), 3DS (forced if the target is 3DS), SWITCH (forced if the target is SWITCH)
CONTROLLER_API ?= SDL2

#==============================================================================#
# Automatic settings for target devices                                        #
#==============================================================================#

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

OLD_APKSIGNER ?= 0

# Attempt to detect termux android build
ifneq ($(shell which termux-setup-storage 2>/dev/null),)
  TARGET_ANDROID := 1
  COMPILER_TYPE := clang
  ifeq ($(shell dpkg -s apksigner | grep Version | sed "s/Version: //"),0.7-2)
    OLD_APKSIGNER := 1
  endif
endif

ifeq ($(TARGET_N64),0)
  GRUCODE := f3dex2e
  PC_PORT_DEFINES := 1
else
  GRUCODE ?= f3dzex
  NO_LDIV := 1
endif

ifeq ($(TARGET_WII_U),1)
  RENDER_API := GX2
  WINDOW_API := GX2
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

TOUCH_CONTROLS ?= 0

ifeq ($(TARGET_ANDROID),1)
  RENDER_API := GL
  WINDOW_API := SDL2
  AUDIO_API := SDL2
  CONTROLLER_API := SDL2

  TOUCH_CONTROLS := 1
endif

# Custom Defines
include defines.mk

# MXE overrides
ifeq ($(HOST_OS),Windows)
  ifeq ($(TARGET_WEB),0)
    ifeq ($(TARGET_PORT_CONSOLE),0)
      WINDOWS_BUILD := 1
    endif
  endif

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

# macOS overrides
ifeq ($(HOST_OS),Darwin)
  OSX_BUILD := 1
  # Using Homebrew?
  ifeq ($(shell which brew >/dev/null 2>&1 && echo y),y)
    OSX_GCC_VER = $(shell find `brew --prefix`/bin/gcc* | grep -oE '[[:digit:]]+' | sort -n | uniq | tail -1)
    CC := gcc-$(OSX_GCC_VER)
    CXX := g++-$(OSX_GCC_VER)
    CPP := cpp-$(OSX_GCC_VER)
    PLATFORM_CFLAGS := -I $(shell brew --prefix)/include
    PLATFORM_LDFLAGS := -L $(shell brew --prefix)/lib
  else
    # Using MacPorts?
    ifeq ($(shell test -d /opt/local/lib && echo y),y)
      OSX_GCC_VER = $(shell find /opt/local/bin/gcc* | grep -oE '[[:digit:]]+' | sort -n | uniq | tail -1)
      CC := gcc-mp-$(OSX_GCC_VER)
      CXX := g++-mp-$(OSX_GCC_VER)
      CPP := cpp-mp-$(OSX_GCC_VER)
      PLATFORM_CFLAGS := -I /opt/local/include
      PLATFORM_LDFLAGS := -L /opt/local/lib
    else
      $(error No suitable macOS toolchain found, have you installed Homebrew?)
    endif
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

# Base settings for EXTERNAL_DATA
ifeq ($(TARGET_PORT_CONSOLE),1)
  BASEDIR ?= sm64ex_res
else
  BASEDIR ?= res
endif

BASEPACK ?= base.zip


#==============================================================================#
# Main defines                                                                 #
#==============================================================================#

# VERSION - selects the version of the game to build
#   jp - builds the 1996 Japanese version
#   us - builds the 1996 North American version
#   eu - builds the 1997 PAL version
#   sh - builds the 1997 Japanese Shindou version, with rumble pak support
VERSION ?= us
$(eval $(call validate-option,VERSION,jp us eu sh))

ifeq      ($(VERSION),jp)
  VER_DEFINES   += VERSION_JP=1
else ifeq ($(VERSION),us)
  VER_DEFINES   += VERSION_US=1
else ifeq ($(VERSION),eu)
  VER_DEFINES   += VERSION_EU=1
else ifeq ($(VERSION),sh)
  VER_DEFINES   += VERSION_SH=1
endif

DEFINES += $(VER_DEFINES)

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
  GRU_DEFINES += F3D_OLD=1
else ifeq ($(GRUCODE),f3d_new) # Fast3D 2.0H
  GRU_DEFINES += F3D_NEW=1
else ifeq ($(GRUCODE),f3dex) # Fast3DEX
  GRU_DEFINES += F3DEX_GBI=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dex2) # Fast3DEX2
  GRU_DEFINES += F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),l3dex2) # Line3DEX2
  GRU_DEFINES += L3DEX2_GBI=1 L3DEX2_ALONE=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dex2pl) # Fast3DEX2_PosLight
  GRU_DEFINES += F3DEX2PL_GBI=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dzex) # Fast3DZEX (2.08J / Animal Forest - Dōbutsu no Mori)
  GRU_DEFINES += F3DZEX_GBI_2=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),super3d) # Super3D
  $(warning Super3D is experimental. Try at your own risk.)
  GRU_DEFINES += SUPER3D_GBI=1 F3D_NEW=1
else ifeq ($(GRUCODE),f3dex2e) # Fast3DEX2 Extended (PC Only)
  ifeq ($(TARGET_N64),1)
    $(error f3dex2e is only supported on PC Port)
  else
    GRU_DEFINES += F3DEX_GBI_2E=1
  endif
endif

DEFINES += $(GRU_DEFINES)

# Specify target defines
ifeq ($(TARGET_RPI),1) # Define RPi to change SDL2 title & GLES2 hints
  DEFINES += TARGET_RPI=1 USE_GLES=1
else ifeq ($(TARGET_ANDROID),1)
  DEFINES += TARGET_ANDROID=1 USE_GLES=1
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

# Libultra defines
LIBULTRA ?= L

# Libultra number revision (only used on 2.0D)
LIBULTRA_REVISION ?= 0

# LIBULTRA - sets the libultra OS version to use
$(eval $(call validate-option,LIBULTRA,D F H I K L BB))

# Libultra number revision (only used on 2.0D)
LIBULTRA_REVISION ?= 0

ULTRA_VER_D := 1
ULTRA_VER_E := 2
ULTRA_VER_F := 3
ULTRA_VER_G := 4
ULTRA_VER_H := 5
ULTRA_VER_I := 6
ULTRA_VER_J := 7
ULTRA_VER_K := 8
ULTRA_VER_L := 9

ifeq ($(LIBULTRA),BB)
  ULTRA_VER_DEF  := LIBULTRA_VERSION=$(ULTRA_VER_L) BBPLAYER LIBULTRA_STR_VER=\"L\"
else
  ULTRA_VER_DEF  := LIBULTRA_VERSION=$(ULTRA_VER_$(LIBULTRA)) LIBULTRA_REVISION=$(LIBULTRA_REVISION) LIBULTRA_STR_VER=\"$(LIBULTRA)\"
endif

DEFINES += $(ULTRA_VER_DEF)

# Important defines

# Mandatory defines to ensture correct compilation
DEFINES += NON_MATCHING=1 AVOID_UB=1

# Check for no bzero/bcopy workaround option
ifeq ($(NO_BZERO_BCOPY),1)
  DEFINES += NO_BZERO_BCOPY=1
endif

# Use internal ldiv()/lldiv()
ifeq ($(NO_LDIV),1)
  DEFINES += NO_LDIV=1
endif

ifeq ($(TARGET_N64),1)
  DEFINES += TARGET_N64=1 _FINALROM=1
endif

#==============================================================================#
# Universal Dependencies                                                       #
#==============================================================================#

PYTHON := python3
TOOLS_DIR = tools

# (This is a bit hacky, but a lot of rules implicitly depend
# on tools and assets, and we use directory globs further down
# in the makefile that we want should cover assets.)

ifeq ($(filter clean distclean print-%,$(MAKECMDGOALS)),)

  # Make sure assets exist
  NOEXTRACT ?= 0
  ifeq ($(NOEXTRACT),0)
    DUMMY != $(PYTHON) extract_assets.py $(VERSION) >&2 || echo FAIL
    ifeq ($(DUMMY),FAIL)
      $(error Failed to extract assets from US ROM)
    endif
    ifneq (,$(wildcard baserom.jp.z64))
      DUMMY != $(PYTHON) extract_assets.py jp >&2 || echo FAIL
      ifeq ($(DUMMY),FAIL)
        $(error Failed to extract assets from JP ROM)
      endif
    endif
    ifneq (,$(wildcard baserom.eu.z64))
      DUMMY != $(PYTHON) extract_assets.py eu >&2 || echo FAIL
      ifeq ($(DUMMY),FAIL)
        $(error Failed to extract assets from EU ROM)
      endif
    endif
    ifneq (,$(wildcard baserom.sh.z64))
      DUMMY != $(PYTHON) extract_assets.py sh >&2 || echo FAIL
      ifeq ($(DUMMY),FAIL)
        $(error Failed to extract assets from SH ROM)
      endif
    endif
  endif

  # Make tools if out of date
  $(info Building tools...)
ifeq ($(TARGET_PORT_CONSOLE),0)
  DUMMY != CC=$(CC) CXX=$(CXX) $(MAKE) -s -C $(TOOLS_DIR) >&2 || echo FAIL
else
  DUMMY != $(MAKE) -s -C $(TOOLS_DIR) >&2 || echo FAIL
endif
    ifeq ($(DUMMY),FAIL)
      $(error Failed to build tools)
    endif
  $(info Building game...)

endif

#==============================================================================#
# Target Executable and Sources                                                #
#==============================================================================#

# BUILD_DIR is location where all build artifacts are placed
BUILD_DIR_BASE := build
TARGET_NAME :=

ifeq ($(TARGET_N64),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)
  EXE := $(BUILD_DIR)/$(TARGET)
  ROM := $(BUILD_DIR)/$(TARGET).z64
  TARGET_NAME := Nintendo 64
else ifeq ($(TARGET_WEB),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_web
  EXE := $(BUILD_DIR)/$(TARGET).html
  TARGET_NAME := Website
else ifeq ($(TARGET_WII_U),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_wiiu
  EXE := $(BUILD_DIR)/$(TARGET).rpx
  TARGET_NAME := Nintendo Wii U
else ifeq ($(TARGET_N3DS),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_3ds
  EXE := $(BUILD_DIR)/$(TARGET).3dsx
  CIA := $(BUILD_DIR)/$(TARGET).cia
  TARGET_NAME := Nintendo 3DS
else ifeq ($(TARGET_SWITCH),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_nx
  EXE := $(BUILD_DIR)/$(TARGET).nro
  TARGET_NAME := Nintendo Switch
else ifeq ($(TARGET_ANDROID),1)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_android
  EXE := $(BUILD_DIR)/libmain.so
  APK := $(BUILD_DIR)/$(TARGET).unsigned.apk
  APK_SIGNED := $(BUILD_DIR)/$(TARGET).apk
  TARGET_NAME := Android
else ifeq ($(WINDOWS_BUILD),1) # us_win (to be renamed)
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_pc
  EXE := $(BUILD_DIR)/$(TARGET).exe
  TARGET_NAME := Windows
else # Linux/Unix builds/binary namer
  BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_pc
  ifeq ($(TARGET_RPI),1) # us_rpi (to be renamed)
    EXE := $(BUILD_DIR)/$(TARGET).arm
  else # us_unix (to be renamed)
    EXE := $(BUILD_DIR)/$(TARGET)
  endif
  TARGET_NAME := Unix-based system
endif

LD_SCRIPT := sm64.ld

ELF := $(BUILD_DIR)/$(TARGET).elf
MIO0_DIR := $(BUILD_DIR)/bin
SOUND_BIN_DIR := $(BUILD_DIR)/sound
TEXTURE_DIR := textures
ACTOR_DIR := actors
LEVEL_DIRS := $(patsubst levels/%,%,$(dir $(wildcard levels/*/header.h)))

# Directories containing source files
SRC_DIRS := src src/engine src/game src/audio src/menu src/buffers src/extras actors levels bin bin/$(VERSION) data assets sound
BOOT_DIR := src/boot
ifeq ($(TARGET_N64),1)
  SRC_DIRS += asm lib src/extras/n64
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

ifeq ($(TARGET_PORT_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    SRC_DIRS += src/pc/discord
  endif
endif

BIN_DIRS := bin bin/$(VERSION)

ifeq ($(LIBULTRA),BB)
  ULTRA_SRC_DIRS := $(shell find lib/ultra -type d)
else
  ULTRA_SRC_DIRS := $(shell find lib/ultra -type d -not -path "lib/ultra/bb/*")
endif
ULTRA_BIN_DIRS := lib/bin
LIBGCC_SRC_DIRS := lib/gcc

ifeq ($(GODDARD_MFACE),1)
  GODDARD_SRC_DIRS := src/goddard src/goddard/dynlists
endif

#==============================================================================#
# Optimization flags                                                           #
#==============================================================================#

ifeq ($(TARGET_N64),1)
  ifeq ($(COMPILER_TYPE),gcc)
    MIPSISET     := -mips3
    OPT_FLAGS    := -Ofast
  else ifeq ($(COMPILER_TYPE),clang)
    # clang doesn't support ABI 'o32' for 'mips3'
    MIPSISET     := -mips2
    OPT_FLAGS    := -Ofast
  endif
else
  ifeq ($(COMPILER_OPT),default)
    OPT_FLAGS := -O2
  else ifeq ($(COMPILER_OPT),debug)
    OPT_FLAGS := -g
  else ifeq ($(COMPILER_OPT),fast)
    OPT_FLAGS := -Ofast
  endif

  # Set BITS (32/64) to compile for
  OPT_FLAGS += $(BITS)
endif

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

# File dependencies and variables for specific files
include Makefile.split

# Source code files
LEVEL_C_FILES := $(wildcard levels/*/leveldata.c) $(wildcard levels/*/script.c) $(wildcard levels/*/geo.c)
ifeq ($(RM2C),1)
  LEVEL_C_FILES += $(wildcard levels/*/custom.leveldata.c) $(wildcard levels/*/custom.script.c) $(wildcard levels/*/custom.geo.c)
endif
C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) $(LEVEL_C_FILES)
CXX_FILES     := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
S_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
ifeq ($(TARGET_N64),1)
  C_FILES += $(foreach dir,$(BOOT_DIR),$(wildcard $(dir)/*.c))
  S_FILES += $(foreach dir,$(BOOT_DIR),$(wildcard $(dir)/*.s))

  ULTRA_C_FILES := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.c))
  ULTRA_S_FILES := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.s))
  LIBGCC_C_FILES := $(foreach dir,$(LIBGCC_SRC_DIRS),$(wildcard $(dir)/*.c))
endif
ifeq ($(GODDARD_MFACE),1)
  GODDARD_C_FILES := $(foreach dir,$(GODDARD_SRC_DIRS),$(wildcard $(dir)/*.c))
endif
ifeq ($(WINDOWS_BUILD),1)
  RC_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.rc))
endif

GENERATED_C_FILES := $(BUILD_DIR)/assets/mario_anim_data.c $(BUILD_DIR)/assets/demo_data.c

ifneq ($(TARGET_N64),1)
GENERATED_C_FILES += $(addprefix $(BUILD_DIR)/bin/,$(addsuffix _skybox.c,$(notdir $(basename $(wildcard textures/skyboxes/*.png)))))

ULTRA_C_FILES := \
  audio/bnkf.c \
  gu/lookatref.c \
  gu/mtxutil.c \
  gu/normalize.c \
  gu/ortho.c \
  gu/perspective.c \
  gu/rotate.c \
  gu/scale.c \
  gu/translate.c \
  libc/ldiv.c

ULTRA_C_FILES := $(addprefix lib/ultra/,$(ULTRA_C_FILES))

C_FILES += $(addprefix src/boot/,memory.c)
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

ifeq ($(TARGET_N64),1)
  LIBGCC_O_FILES := $(foreach file,$(LIBGCC_C_FILES),$(BUILD_DIR)/$(file:.c=.o))
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
ifeq ($(TARGET_N64),1)
  DEP_FILES += $(LIBGCC_O_FILES:.o=.d)
endif

#==============================================================================#
# Compiler Options                                                             #
#==============================================================================#

INCLUDE_DIRS := include $(BUILD_DIR) $(BUILD_DIR)/include src .
ifeq ($(TARGET_N64),1)
  INCLUDE_DIRS += include/gcc
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
  INCLUDE_DIRS += $(LIBNX)/include $(PORTLIBS)/include

  NX_APP_TITLE := Super Mario 64
  NX_APP_AUTHOR := Nintendo - Port by Vatuu, fgsfdsfgs and KiritoDev
  NX_APP_VERSION := ver_$(VERSION)
  NX_APP_ICON := $(PLATFORM_DIR)/logo.jpg
  NACP_FILE := $(BUILD_DIR)/$(PLATFORM_DIR)/sm64.nacp
endif

C_DEFINES := $(foreach d,$(DEFINES),-D$(d))
DEF_INC_CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I $(i)) $(C_DEFINES)

# Set C Preprocessor flags
ifeq ($(COMPILER_TYPE),gcc)
  CPPFLAGS := -P -Wno-trigraphs
else ifeq ($(COMPILER_TYPE),clang)
  CPPFLAGS := -E -P -x c -Wno-trigraphs
endif

CPPFLAGS += $(DEF_INC_CFLAGS) $(CUSTOM_C_DEFINES)

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
# detect prefix for MIPS toolchain
ifneq ($(call find-command,mips64-elf-ld),)
  CROSS := mips64-elf-
# else ifneq ($(call find-command,mips-n64-ld),)
#   CROSS := mips-n64-
else ifneq ($(call find-command,mips64-ld),)
  CROSS := mips64-
else ifneq ($(call find-command,mips-linux-gnu-ld),)
  CROSS := mips-linux-gnu-
else ifneq ($(call find-command,mips64-linux-gnu-ld),)
  CROSS := mips64-linux-gnu-
else ifneq ($(call find-command,mips-ld),)
  CROSS := mips-
else
  $(error Unable to detect a suitable MIPS toolchain installed)
endif

# change the compiler to gcc, to use the default, install the gcc-mips-linux-gnu package
ifeq ($(COMPILER_TYPE),gcc)
  CC      := $(CROSS)gcc
else ifeq ($(COMPILER_TYPE),clang)
  CC      := clang
endif
CPP       := cpp
# use GNU binutils for assembler, linker, archiver, and object tools
AS        := $(CROSS)as
LD        := $(CROSS)ld
AR        := $(CROSS)ar
OBJDUMP   := $(CROSS)objdump
OBJCOPY   := $(CROSS)objcopy

# Check code syntax with host compiler
CFLAGS := -G 0 -nostdinc $(MIPSISET) $(DEF_INC_CFLAGS)

ifeq ($(COMPILER_TYPE),gcc)
  CFLAGS += -mno-shared -march=vr4300 -mfix4300 -mabi=32 -mhard-float -mdivide-breaks -fno-stack-protector -fno-common -fno-zero-initialized-in-bss -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra
  CFLAGS += -Wno-missing-braces
else ifeq ($(COMPILER_TYPE),clang)
  CFLAGS += -mfpxx -target mips -mabi=32 -mhard-float -fomit-frame-pointer -fno-stack-protector -fno-common -I include -I src/ -I $(BUILD_DIR)/include -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra
  CFLAGS += -Wno-missing-braces
else
  CFLAGS += -non_shared -Wab,-r4300_mul -Xcpluscomm -Xfullwarn -signed -32
endif

ASMFLAGS = -G 0 $(DEF_INC_CFLAGS) -w -nostdinc -c -march=vr4300 -mfix4300 -mno-abicalls -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_MIPS_SZLONG=32

RSPDEFINES := $(VER_DEFINES) $(GRU_DEFINES)
RSPASMFLAGS := $(foreach d,$(RSPDEFINES),-definelabel $(subst =, ,$(d)))

OBJCOPYFLAGS := --pad-to=0x800000 --gap-fill=0xFF
SYMBOL_LINKING_FLAGS := --no-check-sections $(addprefix -R ,$(SEG_FILES))
LDFLAGS := -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(BUILD_DIR)/sm64.$(VERSION).map $(SYMBOL_LINKING_FLAGS)

CFLAGS += $(CUSTOM_C_DEFINES)

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

  SMDH_TITLE ?= Super Mario 64
  SMDH_DESCRIPTION ?= Super Mario 64 3DS Port
  SMDH_AUTHOR ?= Nintendo - port by Fnouwt (Gericom) and mkst
  SMDH_ICON := $(PLATFORM_DIR)/icon.smdh
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
  OBJCOPY := i686-w64-mingw32-objcopy
  OBJDUMP := i686-w64-mingw32-objdump
else ifeq ($(TARGET_ANDROID),1) # Termux has clang
  ifeq ($(COMPILER_TYPE),clang)
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

# for now, it's either SDL+GL, DXGI+DirectX, GX2 or C3D so choose based on WAPI
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
    BACKEND_LDFLAGS += -framework OpenGL $(shell pkg-config --libs glew)
  else
    BACKEND_LDFLAGS += -lGL
  endif
else ifeq ($(WINDOW_API),GX2)
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

ifeq ($(TARGET_WII_U),0)

ifneq ($(SDL1_USED)$(SDL2_USED),00)
  ifeq ($(TARGET_ANDROID),1)
    BACKEND_LDFLAGS += -lhidapi -lSDL2
  else ifeq ($(OSX_BUILD),1)
    # on OSX at least the homebrew version of sdl-config gives include path as `.../include/SDL2` instead of `.../include`
    OSX_PREFIX := $(shell $(SDLCONFIG) --prefix)
    BACKEND_CFLAGS += -I$(OSX_PREFIX)/include $(shell $(SDLCONFIG) --cflags)
    BACKEND_LDFLAGS += $(shell $(SDLCONFIG) --libs)
  else
    BACKEND_CFLAGS += $(shell $(SDLCONFIG) --cflags)
    ifeq ($(WINDOWS_BUILD),1)
      BACKEND_LDFLAGS += $(shell $(SDLCONFIG) --static-libs) -lsetupapi -luser32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion
    else
      BACKEND_LDFLAGS += $(shell $(SDLCONFIG) --libs)
    endif
  endif
endif

endif

ifeq ($(WINDOWS_BUILD),1)
  CFLAGS := $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -fwrapv
  ifeq ($(TARGET_BITS), 32)
    BACKEND_LDFLAGS += -ldbghelp
  endif
else ifeq ($(TARGET_WEB),1)
  CFLAGS := $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -fwrapv -s USE_SDL=2
# Linux / Other builds below
else
  CFLAGS := $(PLATFORM_CFLAGS) $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -fwrapv
endif

ifeq ($(TARGET_WII_U),1)
  CFLAGS += -ffunction-sections $(MACHDEP) -ffast-math -D__WIIU__ -D__WUT__ $(INCLUDE)
endif

ifeq ($(TARGET_N3DS),1)
  CTRULIB  :=  $(DEVKITPRO)/libctru
  LIBDIRS  := $(CTRULIB)
  export LIBPATHS  :=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)
  CFLAGS += -mtp=soft -DosGetTime=n64_osGetTime -D__3DS__ -march=armv6k -mtune=mpcore -mfloat-abi=hard -mword-relocations -fomit-frame-pointer -ffast-math $(foreach dir,$(LIBDIRS),-I$(dir)/include)

  ifeq ($(DISABLE_N3DS_AUDIO),1)
    CFLAGS += -DDISABLE_N3DS_AUDIO
  endif
  ifeq ($(DISABLE_N3DS_FRAMESKIP),1)
    CFLAGS += -DDISABLE_N3DS_FRAMESKIP
  endif
endif

ifeq ($(TARGET_SWITCH),1)
  CFLAGS := $(NXARCH) $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -fno-strict-aliasing -ftls-model=local-exec -fPIC -fwrapv -D__SWITCH__=1
endif

CFLAGS += $(CUSTOM_C_DEFINES)

# Load external textures
ifeq ($(EXTERNAL_DATA),1)
  CFLAGS += -DFS_BASEDIR="\"$(BASEDIR)\""
  # tell skyconv to write names instead of actual texture data and save the split tiles so we can use them later
  SKYTILE_DIR := $(BUILD_DIR)/textures/skybox_tiles
  SKYCONV_ARGS := --store-names --write-tiles "$(SKYTILE_DIR)"
endif

ASMFLAGS = $(DEF_INC_CFLAGS) -D_LANGUAGE_ASSEMBLY

ifeq ($(TARGET_WEB),1)
LDFLAGS := -lm -lGL -lSDL2 -no-pie -s TOTAL_MEMORY=64MB -g4 --source-map-base http://localhost:8080/ -s "EXTRA_EXPORTED_RUNTIME_METHODS=['callMain']"

else ifeq ($(TARGET_WII_U),1)
LDFLAGS := -lm -no-pie $(BACKEND_LDFLAGS) $(MACHDEP) $(RPXSPECS) $(LIBPATHS)

else ifeq ($(TARGET_N3DS),1)
LDFLAGS := $(LIBPATHS) -lcitro3d -lctru -lm -specs=3dsx.specs -g -marm -mthumb-interwork -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft # -Wl,-Map,$(notdir $*.map)

else ifeq ($(TARGET_SWITCH),1)
  LDFLAGS := -specs=$(LIBNX)/switch.specs $(NXARCH) $(BACKEND_LDFLAGS) -lstdc++ -lm

else ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -Llib -lpthread $(BACKEND_LDFLAGS) -static
  ifeq ($(CROSS),)
    LDFLAGS += -no-pie
  endif
  ifeq ($(COMPILER_OPT),debug)
    LDFLAGS += -mconsole
  endif

else ifeq ($(TARGET_RPI),1)
  LDFLAGS := -lm $(BACKEND_LDFLAGS) -no-pie

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
  LDFLAGS := -lm $(PLATFORM_LDFLAGS) $(BACKEND_LDFLAGS) -lpthread

else ifeq ($(HOST_OS),Haiku)
  LDFLAGS := $(BACKEND_LDFLAGS) -no-pie

else
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -lm $(BACKEND_LDFLAGS) -lpthread -ldl
  ifeq ($(NO_PIE), 1)
    LDFLAGS += -no-pie
  endif
  ifeq ($(DISCORDRPC),1)
    LDFLAGS += -Wl,-rpath .
  endif

endif # End of LDFLAGS

endif

#==============================================================================#
# Miscellaneous Tools                                                          #
#==============================================================================#

WINEXT :=
ifeq ($(HOST_OS),Windows)
WINEXT := .exe
endif

# Executable tools
MIO0TOOL              := $(TOOLS_DIR)/sm64tools/mio0$(WINEXT)
N64CKSUM              := $(TOOLS_DIR)/sm64tools/n64cksum$(WINEXT)
N64GRAPHICS           := $(TOOLS_DIR)/sm64tools/n64graphics$(WINEXT)
N64GRAPHICS_CI        := $(TOOLS_DIR)/sm64tools/n64graphics_ci$(WINEXT)
TEXTCONV              := $(TOOLS_DIR)/textconv$(WINEXT)
TABLEDESIGN           := $(TOOLS_DIR)/tabledesign$(WINEXT)
VADPCM_ENC            := $(TOOLS_DIR)/vadpcm_enc$(WINEXT)
EXTRACT_DATA_FOR_MIO  := $(TOOLS_DIR)/extract_data_for_mio$(WINEXT)
SKYCONV               := $(TOOLS_DIR)/skyconv$(WINEXT)
ifneq (,$(call find-command,armips))
  RSPASM = armips
else
  RSPASM := $(TOOLS_DIR)/armips$(WINEXT)
endif

# Python tools
ZEROTERM          := $(PYTHON) $(TOOLS_DIR)/zeroterm.py
GET_GODDARD_SIZE  := $(PYTHON) $(TOOLS_DIR)/getGoddardSize.py
BINPNG            := $(TOOLS_DIR)/BinPNG.py

ENDIAN_BITWIDTH   := $(BUILD_DIR)/endian-and-bitwidth

EMULATOR = mupen64plus
EMU_FLAGS =
LOADER = loader64
LOADER_FLAGS = -vwf
SHA1SUM = sha1sum
PRINT = printf

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
YELLOW  := \033[0;33m
BLINK   := \033[32;5m
endif

EXTRACT_DATA_FOR_MIO := $(OBJCOPY) -O binary --only-section=.data

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

#==============================================================================#
# Main Targets                                                                 #
#==============================================================================#

ifeq ($(TARGET_N64),1)
ALL_FILE := $(ROM)
else ifeq ($(TARGET_ANDROID),1)
ALL_FILE := $(APK_SIGNED)
else
ALL_FILE := $(EXE)
endif

all: $(ALL_FILE)
	@$(SHA1SUM) $(ALL_FILE)
	@$(PRINT) "${BLINK}Build succeeded.\n$(NO_COL)"
	@$(PRINT) "==== Build Details ====$(NO_COL)\n"
	@$(PRINT) "${GREEN}File:           $(BLUE)$(ALL_FILE)$(NO_COL)\n"
	@$(PRINT) "${GREEN}Version:        $(BLUE)$(VERSION)$(NO_COL)\n"
ifeq ($(TARGET_N64),1)
	@$(PRINT) "${GREEN}Microcode:      $(BLUE)$(GRUCODE)$(NO_COL)\n"
endif
	@$(PRINT) "${GREEN}Target:         $(BLUE)$(TARGET_NAME)$(NO_COL)\n"

ifeq ($(TARGET_ANDROID),1)
  EXE_DEPEND := $(APK_SIGNED)
else
  EXE_DEPEND := $(EXE)
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
  ifeq ($(VERSION),sh)
	@echo "$(BUILD_DIR)/sound/sequences_header sound/sequences_header" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/ctl_header sound/ctl_header" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/tbl_header sound/tbl_header" >> $(BASEPACK_LST)
  endif
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

distclean: clean
	$(PYTHON) ./extract_assets.py --clean
	$(MAKE) -C $(TOOLS_DIR) clean

test: $(ROM)
	$(EMULATOR) $(EMU_FLAGS) $<

load: $(ROM)
	$(LOADER) $(LOADER_FLAGS) $<

$(BUILD_DIR)/$(RPC_LIBS):
	@$(CP) -f $(RPC_LIBS) $(BUILD_DIR)

# Extra object file dependencies
ifeq ($(TARGET_N64),1)
  $(BUILD_DIR)/asm/boot.o: $(IPL3_RAW_FILES)
  $(BUILD_DIR)/src/boot/crash_screen.o: $(CRASH_TEXTURE_C_FILES)
  $(CRASH_TEXTURE_C_FILES): TEXTURE_ENCODING := u32

  RSP_DIR := $(BUILD_DIR)/rsp
  $(BUILD_DIR)/lib/rsp.o: $(RSP_DIR)/rspboot.bin $(RSP_DIR)/fast3d.bin $(RSP_DIR)/audio.bin
else
  $(BUILD_DIR)/src/pc/crash_screen_pc.o: $(CRASH_TEXTURE_PC_C_FILES)
endif

SOUND_FILES := $(SOUND_BIN_DIR)/sound_data.ctl $(SOUND_BIN_DIR)/sound_data.tbl $(SOUND_BIN_DIR)/sequences.bin $(SOUND_BIN_DIR)/bank_sets
SOUND_FILES_SH :=
ifeq ($(VERSION),sh)
  ifeq ($(EXTERNAL_DATA),1)
    SOUND_FILES_SH := $(SOUND_BIN_DIR)/sequences_header $(SOUND_BIN_DIR)/ctl_header $(SOUND_BIN_DIR)/tbl_header
    SOUND_FILES += $(SOUND_FILES_SH)
  else
    SOUND_FILES_SH := $(SOUND_BIN_DIR)/bank_sets.inc.c $(SOUND_BIN_DIR)/sequences_header.inc.c $(SOUND_BIN_DIR)/ctl_header.inc.c $(SOUND_BIN_DIR)/tbl_header.inc.c
    $(BUILD_DIR)/src/audio/load_sh.o: $(SOUND_FILES_SH)
  endif
endif

$(SOUND_BIN_DIR)/sound_data.o: $(SOUND_FILES)
$(BUILD_DIR)/levels/scripts.o: $(BUILD_DIR)/include/level_headers.h

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

# N64 specific optimization files
ifeq ($(TARGET_N64),1)
  $(BUILD_DIR)/actors/%.o: OPT_FLAGS := -Ofast -mlong-calls
  $(BUILD_DIR)/levels/%.o: OPT_FLAGS := -Ofast -mlong-calls
  $(BUILD_DIR)/src/audio/heap.o: OPT_FLAGS := -Os -fno-jump-tables
  $(BUILD_DIR)/src/audio/synthesis.o: OPT_FLAGS := -Os -fno-jump-tables
  $(BUILD_DIR)/lib/ultra/%.o: OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/gcc/%.o: OPT_FLAGS := -O2

  ifeq ($(COMPILER_TYPE),gcc)
    $(BUILD_DIR)/src/engine/surface_collision.o: OPT_FLAGS += --param case-values-threshold=20 --param max-completely-peeled-insns=100 --param max-unrolled-insns=100 -finline-limit=0 -fno-inline -freorder-blocks-algorithm=simple -falign-functions=32
    # Setting any sort of -finline-limit has shown to worsen performance with math_util.c,
    # lower values were the worst, the higher you go - the closer performance gets to not setting it at all
    $(BUILD_DIR)/src/engine/math_util.o: OPT_FLAGS +=-fno-unroll-loops -fno-peel-loops --param case-values-threshold=20 -falign-functions=32
    $(BUILD_DIR)/src/game/rendering_graph_node.o: OPT_FLAGS += --param case-values-threshold=20 --param max-completely-peeled-insns=100 --param max-unrolled-insns=100 -finline-limit=0 -freorder-blocks-algorithm=simple -falign-functions=32
  endif
endif

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(BOOT_DIR) $(GODDARD_SRC_DIRS) $(ULTRA_SRC_DIRS) $(ULTRA_BIN_DIRS) $(BIN_DIRS) $(TEXTURE_DIRS) $(TEXT_DIRS) $(SOUND_SAMPLE_DIRS) $(addprefix levels/,$(LEVEL_DIRS)) include) $(MIO0_DIR) $(addprefix $(MIO0_DIR)/,$(VERSION)) $(SOUND_BIN_DIR) $(SOUND_BIN_DIR)/sequences/$(VERSION)

ifeq ($(TARGET_N64),1)
  ALL_DIRS += $(RSP_DIR) $(BUILD_DIR)/$(LIBGCC_SRC_DIRS)
endif

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

ifeq ($(EXT_DEBUG_MENU),1)
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
  $(BUILD_DIR)/src/boot/ext_mem_screen.o: $(BUILD_DIR)/include/text_strings.h
endif

ifeq ($(EXT_OPTIONS_MENU),1)

  ifeq ($(BETTERCAMERA),1)
    $(BUILD_DIR)/src/extras/bettercamera.o: $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif

  ifeq ($(CHEATS_ACTIONS),1)
    $(BUILD_DIR)/src/extras/cheats.o:       $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif

  ifeq ($(EXT_DEBUG_MENU),1)
    $(BUILD_DIR)/src/extras/debug_menu.o:   $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif

  $(BUILD_DIR)/src/extras/options_menu.o:   $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
endif

ifeq ($(TARGET_PORT_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    $(BUILD_DIR)/src/pc/discord/discordrpc.o: $(BUILD_DIR)/include/text_strings.h $(LANG_O_FILES)
  endif
endif

#==============================================================================#
# Texture Generation                                                           #
#==============================================================================#
TEXTURE_ENCODING := u8

# Convert PNGs to RGBA32, RGBA16, IA16, IA8, IA4, IA1, I8, I4 binary files
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

# Color Index CI8
$(BUILD_DIR)/%.ci8.inc.c: %.ci8.png
	$(call print,Converting CI:,$<,$@)
	$(PYTHON) $(BINPNG) $< $@ 8

# Color Index CI4
$(BUILD_DIR)/%.ci4.inc.c: %.ci4.png
	$(call print,Converting CI:,$<,$@)
	$(PYTHON) $(BINPNG) $< $@ 4
endif

#==============================================================================#
# Compressed Segment Generation                                                #
#==============================================================================#

ifeq ($(TARGET_N64),1)
# Link segment file to resolve external labels
# TODO: ideally this would be `-Trodata-segment=0x07000000` but that doesn't set the address
$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o
	$(call print,Linking ELF file:,$<,$@)
	$(V)$(LD) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map -o $@ $<
# Override for leveldata.elf, which otherwise matches the above pattern.
# Has to be a static pattern rule for make-4.4 and above to trigger the second expansion.
.SECONDEXPANSION:
$(LEVEL_ELF_FILES): $(BUILD_DIR)/levels/%/leveldata.elf: $(BUILD_DIR)/levels/%/leveldata.o $(BUILD_DIR)/bin/$$(TEXTURE_BIN).elf
	$(call print,Linking level ELF file:,$<,$@)
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

#==============================================================================#
# Sound File Generation                                                        #
#==============================================================================#

$(BUILD_DIR)/%.table: %.aiff
	$(call print,Generating ADPCM table:,$<,$@)
	$(V)$(TABLEDESIGN) -s 1 $< >$@

$(BUILD_DIR)/%.aifc: $(BUILD_DIR)/%.table %.aiff
	$(call print,Encoding ADPCM:,$(word 2,$^),$@)
	$(V)$(VADPCM_ENC) -c $^ $@

# Endianness and bit width
$(ENDIAN_BITWIDTH): $(TOOLS_DIR)/determine-endian-bitwidth.c
	@$(PRINT) "$(GREEN)Generating endian-bitwidth $(NO_COL)\n"
	$(V)$(CC) -c $(CFLAGS) -o $@.dummy2 $< 2>$@.dummy1; true
	$(V)grep -o 'msgbegin --endian .* --bitwidth .* msgend' $@.dummy1 > $@.dummy2
	$(V)head -n1 <$@.dummy2 | cut -d' ' -f2-5 > $@
	$(V)$(RM) $@.dummy1
	$(V)$(RM) $@.dummy2

$(SOUND_BIN_DIR)/sound_data.ctl: sound/sound_banks/ $(SOUND_BANK_FILES) $(SOUND_SAMPLE_AIFCS) $(ENDIAN_BITWIDTH)
	@$(PRINT) "$(GREEN)Generating: $(BLUE)$@ $(NO_COL)\n"
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

#==============================================================================#
# Generated Source Code Files                                                  #
#==============================================================================#

# Convert binary file to a comma-separated list of byte values for inclusion in C code
$(BUILD_DIR)/%.inc.c: $(BUILD_DIR)/%
	$(call print,Converting to C:,$<,$@)
	$(V)hexdump -v -e '1/1 "0x%X,"' $< > $@
	$(V)echo >> $@

# Generate animation data
$(BUILD_DIR)/assets/mario_anim_data.c: $(wildcard assets/anims/*.inc.c)
	@$(PRINT) "$(GREEN)Generating animation data $(NO_COL)\n"
	$(V)$(PYTHON) tools/mario_anims_converter.py > $@

# Generate demo input data
$(BUILD_DIR)/assets/demo_data.c: assets/demo_data.json $(wildcard assets/demos/*.bin)
	@$(PRINT) "$(GREEN)Generating demo data $(NO_COL)\n"
	$(V)$(PYTHON) tools/demo_data_converter.py assets/demo_data.json $(DEF_INC_CFLAGS) > $@

# Encode in-game text strings
$(BUILD_DIR)/include/text_strings.h: include/text_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@

$(BUILD_DIR)/include/text_menu_strings.h: include/text_menu_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap_menu.txt $< $@

$(BUILD_DIR)/text/%/define_courses.inc.c: text/define_courses.inc.c text/%/courses.h
	@$(PRINT) "$(GREEN)Preprocessing: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(CPP) $(CPPFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

$(BUILD_DIR)/text/%/define_text.inc.c: text/define_text.inc.c text/%/courses.h text/%/dialogs.h
	@$(PRINT) "$(GREEN)Preprocessing: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(CPP) $(CPPFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

ifeq ($(EXT_OPTIONS_MENU),1)
$(BUILD_DIR)/include/text_options_strings.h: include/text_options_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@

ifeq ($(CHEATS_ACTIONS),1)
$(BUILD_DIR)/include/text_cheats_strings.h: include/text_cheats_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@
endif

ifeq ($(EXT_DEBUG_MENU),1)
$(BUILD_DIR)/include/text_debug_strings.h: include/text_debug_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@
endif

endif

# Level headers
$(BUILD_DIR)/include/level_headers.h: levels/level_headers.h.in
	$(call print,Preprocessing level headers:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -I . $< | sed -E 's|(.+)|#include "\1"|' > $@

#==============================================================================#
# Compilation Recipes                                                          #
#==============================================================================#

# Compile C code
$(BUILD_DIR)/%.o: %.c
	$(call print,Compiling:,$<,$@)
	$(V)$(CC) -c $(CFLAGS) -D_LANGUAGE_C=1 $(OPT_FLAGS) -MMD -MF $(BUILD_DIR)/$*.d -o $@ $<

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	$(call print,Compiling:,$<,$@)
	$(V)$(CC) -c $(CFLAGS) -D_LANGUAGE_C=1 $(OPT_FLAGS) -MMD -MF $(BUILD_DIR)/$*.d -o $@ $<

# Compile C++ code
$(BUILD_DIR)/%.o: %.cpp
	$(call print,Compiling:,$<,$@)
	$(V)$(CXX) -c $(CFLAGS) $(OPT_FLAGS) -MMD -MF $(BUILD_DIR)/$*.d -o $@ $<

# Assemble assembly code
$(BUILD_DIR)/%.o: %.s
	$(call print,Assembling:,$<,$@)
	$(V)$(CC) -c $(ASMFLAGS) -x assembler-with-cpp -MMD -MF $(BUILD_DIR)/$*.d -o $@ $<

ifeq ($(TARGET_N64),1)
# Assemble RSP assembly code
$(BUILD_DIR)/rsp/%.bin $(BUILD_DIR)/rsp/%_data.bin: rsp/%.s
	$(call print,Assembling:,$<,$@)
	$(V)$(RSPASM) -sym $@.sym $(RSPASMFLAGS) -strequ CODE_FILE $(BUILD_DIR)/rsp/$*.bin -strequ DATA_FILE $(BUILD_DIR)/rsp/$*_data.bin $<
endif

# Compile Windows icon
ifeq ($(WINDOWS_BUILD),1)
$(BUILD_DIR)/%.o: %.rc
	$(call print,Applying Windows Icon:,$<,$@)
	$(V)$(WINDRES) -o $@ -i $<
endif

#==============================================================================#
# Executable Generation                                                        #
#==============================================================================#

ifeq ($(TARGET_N64),1)

# Link libgcc
$(BUILD_DIR)/libgcc.a: $(LIBGCC_O_FILES)
	@$(PRINT) "$(GREEN)Linking libgcc:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(LIBGCC_O_FILES)

LIB_GCC_FILE := $(BUILD_DIR)/libgcc.a
LIB_GCC_FLAG := -lgcc

ifeq ($(GODDARD_MFACE),1)
  GODDARD_TXT_INC := $(BUILD_DIR)/goddard.txt
endif

# Run linker script through the C preprocessor
$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT) $(GODDARD_TXT_INC)
	$(call print,Preprocessing linker script:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

# Link libultra
$(BUILD_DIR)/libultra.a: $(ULTRA_O_FILES)
	@$(PRINT) "$(GREEN)Linking libultra: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(ULTRA_O_FILES)

ifeq ($(GODDARD_MFACE),1)
# Link libgoddard
$(BUILD_DIR)/libgoddard.a: $(GODDARD_O_FILES)
	@$(PRINT) "$(GREEN)Linking libgoddard: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(GODDARD_O_FILES)

LIB_GD_FILE := $(BUILD_DIR)/libgoddard.a
LIB_GD_FLAG := -lgoddard

# SS2: Goddard rules to get size
$(BUILD_DIR)/sm64_prelim.ld: $(LD_SCRIPT) $(O_FILES) $(MIO0_OBJ_FILES) $(SEG_FILES) $(BUILD_DIR)/libultra.a $(LIB_GD_FILE) $(LIB_GCC_FILE)
	$(call print,Preprocessing preliminary linker script:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -DPRELIMINARY=1 -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

$(BUILD_DIR)/sm64_prelim.elf: $(BUILD_DIR)/sm64_prelim.ld
	@$(PRINT) "$(GREEN)Linking Preliminary ELF file: $(BLUE)$@ $(NO_COL)\n"
    # Slightly edited version of LDFLAGS
	$(V)$(LD) -L $(BUILD_DIR) -T $< -Map $(BUILD_DIR)/sm64_prelim.map $(SYMBOL_LINKING_FLAGS) -o $@ $(O_FILES) -lultra $(LIB_GD_FLAG) $(LIB_GCC_FLAG)

$(BUILD_DIR)/goddard.txt: $(BUILD_DIR)/sm64_prelim.elf
	$(call print,Getting Goddard size...)
	$(V)$(GET_GODDARD_SIZE) $(BUILD_DIR)/sm64_prelim.map $(VERSION)

LIB_GD_PRE_ELF := $(BUILD_DIR)/sm64_prelim.elf

endif # GODDARD_MFACE

# Link SM64 ELF file
$(ELF): $(LIB_GD_PRE_ELF) $(O_FILES) $(MIO0_OBJ_FILES) $(SEG_FILES) $(BUILD_DIR)/$(LD_SCRIPT) $(BUILD_DIR)/libultra.a $(LIB_GD_FILE) $(LIB_GCC_FILE)
	@$(PRINT) "$(GREEN)Linking ELF file: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) -L $(BUILD_DIR) $(LDFLAGS) $(GODDARD_TXT_INC) -o $@ $(O_FILES) -lultra $(LIB_GD_FLAG) $(LIB_GCC_FLAG)

# Build ROM
$(ROM): $(ELF)
	$(V)$(OBJCOPY) $(OBJCOPYFLAGS) $< $(@:.z64=.bin) -O binary
	$(V)$(N64CKSUM) $(@:.z64=.bin) $@

$(BUILD_DIR)/$(TARGET).objdump: $(ELF)
	$(OBJDUMP) -D $< > $@

else ifeq ($(TARGET_WII_U),1)
$(ELF): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS)
	@$(PRINT) "$(GREEN)Linking ELF file: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)

$(EXE): $(ELF)
	$(V)cp $< $*.strip.elf
	$(V)$(STRIP) -g $*.strip.elf $(ERROR_FILTER)
	$(V)elf2rpl $*.strip.elf $@ $(ERROR_FILTER)
	$(V)rm $*.strip.elf

else ifeq ($(TARGET_N3DS),1)
# Builds the vertex shader
$(BUILD_DIR)/src/pc/gfx/shader.shbin.o : src/pc/gfx/shader.v.pica
	$(eval CURBIN := $<.shbin)
	$(call print,Compiling 3DS Shader:,$<,$@)
	$(V)$(DEVKITPRO)/tools/bin/picasso -o $(BUILD_DIR)/src/pc/gfx/shader.shbin $<
	$(V)$(DEVKITPRO)/tools/bin/bin2s $(BUILD_DIR)/src/pc/gfx/shader.shbin | $(AS) -o $@

$(ELF): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/src/pc/gfx/shader.shbin.o $(SMDH_ICON)
	@$(PRINT) "$(GREEN)Linking ELF file: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(BUILD_DIR)/src/pc/gfx/shader.shbin.o $(MINIMAP_T3X_O) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)

$(EXE): $(ELF)
	$(V)3dsxtool $< $@ --smdh=$(BUILD_DIR)/$(SMDH_ICON)

$(CIA): $(ELF)
	@echo "Generating $@, please wait..."
	$(V)makerom -f cia -o "$@" -rsf $(PLATFORM_DIR)/template.rsf -target t -elf "$<" -icon $(PLATFORM_DIR)/icon.icn -banner $(PLATFORM_DIR)/banner.bnr

%.smdh: %.png
	$(V)smdhtool --create "$(SMDH_TITLE)" "$(SMDH_DESCRIPTION)" "$(SMDH_AUTHOR)" $< $(BUILD_DIR)/$@

# Builds converted 3DS textures

# from /opt/devkitpro/devkitARM/base_tools
define bin2o
  bin2s -a 4 -H $(BUILD_DIR)/$(MINIMAP_TEXTURES)/`(echo $(<F) | tr . _)`.h $(BUILD_DIR)/$< | $(AS) -o $(BUILD_DIR)/$(MINIMAP_TEXTURES)/$(<F).o
endef

# TODO: simplify dependency chain
$(BUILD_DIR)/src/pc/gfx/gfx_citro3d.o: $(BUILD_DIR)/src/pc/gfx/gfx_3ds.o
$(BUILD_DIR)/src/pc/gfx/gfx_3ds.o: $(BUILD_DIR)/src/pc/gfx/gfx_3ds_menu.o
$(BUILD_DIR)/src/pc/gfx/gfx_3ds_menu.o: $(MINIMAP_T3X_HEADERS)

# Phase 3
%.t3x.o $(BUILD_DIR)/%_t3x.h: %.t3x
	$(call print,Assembling 3DS texture:,$<,$@)
	$(V)$(bin2o)

# Phase 2
%.t3x: %.t3s
	$(call print,Converting 3DS texture:,$<,$@)
	$(V)tex3ds -i $(BUILD_DIR)/$< -o $(BUILD_DIR)/$@

# Phase 1
%.t3s: %.png
	$(call print,Preprocessing 3DS texture header:,$<,$@)
	@printf -- "-f rgba -z auto\n../../../../../../$(<)\n" > $(BUILD_DIR)/$@

else ifeq ($(TARGET_SWITCH),1)
$(ELF): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES)
	@$(PRINT) "$(GREEN)Linking ELF file: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)

$(EXE): $(ELF)
	$(V)cp $< $*.strip.elf
	$(V)$(STRIP) -g $*.strip.elf $(ERROR_FILTER)
	$(V)nacptool --create "$(NX_APP_TITLE)" "$(NX_APP_AUTHOR)" "$(NX_APP_VERSION)" $(NACP_FILE) $(NACPFLAGS)
	$(V)elf2nro $*.strip.elf $@ --nacp=$(NACP_FILE) --icon=$(NX_APP_ICON) $(ERROR_FILTER)
	$(V)rm $*.strip.elf
else

ifeq ($(TARGET_ANDROID),1)
APK_FILES := $(shell find $(PLATFORM_DIR)/android/ -type f)

$(APK): $(EXE) $(APK_FILES)
	@$(PRINT) "$(GREEN)Packing game and libraries to an APK: $(BLUE)$@ $(NO_COL)\n"
	$(V)cp -r $(PLATFORM_DIR)/android $(BUILD_DIR)/$(PLATFORM_DIR)/ && \
	cp $(PREFIX)/lib/libc++_shared.so $(BUILD_DIR)/$(PLATFORM_DIR)/android/lib/$(ARCH_APK)/ && \
	cp $(EXE) $(BUILD_DIR)/$(PLATFORM_DIR)/android/lib/$(ARCH_APK)/ && \
	cd $(BUILD_DIR)/$(PLATFORM_DIR)/android && \
	zip -q -r ../../../../../$@ ./* && \
	cd ../../../../.. && \
	rm -rf $(BUILD_DIR)/$(PLATFORM_DIR)/android

ifeq ($(OLD_APKSIGNER),1)
$(APK_SIGNED): $(APK)
	$(call print,Signing APK:,$<,$@)
	$(V)apksigner $(BUILD_DIR)/keystore $< $@
else
$(APK_SIGNED): $(APK)
	$(call print,Signing APK:,$<,$@)
	$(V)cp $< $@
	$(V)apksigner sign --cert $(PLATFORM_DIR)/certificate.pem --key $(PLATFORM_DIR)/key.pk8 $@
endif
endif

# For the crash handler on Windows
ifeq ($(WINDOWS_BUILD),1)
all: PC_EXE_MAP
PC_EXE_MAP: $(EXE)
	$(V)objdump -t $(EXE) > $(BUILD_DIR)/sm64pc.map
endif

$(EXE): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS)
	$(V)$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
endif

# Remove built-in rules, to improve performance
MAKEFLAGS += -r

# with no prerequisites, .SECONDARY causes no intermediate target to be removed
.SECONDARY:

# Disable built-in rules
.SUFFIXES:

# Phony targets
.PHONY: all clean distclean default diff test load libultra res

# General Dependencies

-include $(DEP_FILES)

# Debug variable print target
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
