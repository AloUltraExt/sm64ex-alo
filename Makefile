
# Makefile to rebuild SM64 split image

### Default target ###

default: all

### Build Options ###

# These options can either be changed by modifying the makefile, or
# by building with 'make SETTING=value'. 'make clean' may be required.

# Build debug version
DEBUG ?= 0
# Version of the game to build
VERSION ?= us
# Graphics microcode used
GRUCODE ?= f3dzex
# If COMPARE is 1, check the output sha1sum when building 'all'
COMPARE ?= 0
# If NON_MATCHING is 1, define the NON_MATCHING and AVOID_UB macros when building (recommended)
NON_MATCHING ?= 1
# Compiler to use in N64 (ido or gcc)
COMPILER_N64 ?= gcc

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

# Disable better camera by default
BETTERCAMERA ?= 0
# Disable no drawing distance by default
NODRAWINGDISTANCE ?= 0
# Disable QoL fixes by default (helps with them purists)
QOL_FIXES ?= 0
# Enable extended options menu by default
EXT_OPTIONS_MENU ?= 1
# Disable text-based save-files by default
TEXTSAVES ?= 0
# Load resources from external files
EXTERNAL_DATA ?= 0
# Enable Discord Rich Presence
DISCORDRPC ?= 0
# Enable rumble functions (Originally in Shindou)
RUMBLE_FEEDBACK ?= 1
# Enable PC Port defines
PC_PORT_DEFINES ?= 1

# Various workarounds for weird toolchains
NO_BZERO_BCOPY ?= 0
NO_LDIV ?= 0
# Check if is compiling on a console
TARGET_GAME_CONSOLE ?= 0

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
endif

ifeq ($(TARGET_N3DS),1)
  RENDER_API := C3D
  WINDOW_API := 3DS
  AUDIO_API := 3DS
  CONTROLLER_API := 3DS
endif

ifeq ($(TARGET_SWITCH),1)
  RENDER_API := GL
  WINDOW_API := SDL2
  AUDIO_API := SDL2
  CONTROLLER_API := SWITCH
endif

ifeq ($(TARGET_N3DS)$(TARGET_WII_U)$(TARGET_SWITCH),111)
  TARGET_GAME_CONSOLE := 1
endif

# Misc settings for EXTERNAL_DATA

ifeq ($(TARGET_GAME_CONSOLE),1)
  BASEDIR ?= sm64ex_res
else
  BASEDIR ?= res
endif

BASEPACK ?= base.zip

# Automatic settings for PC port(s)

WINDOWS_BUILD ?= 0

ifeq ($(TARGET_N64),0)
GRUCODE := f3dex2e
else
GRUCODE := $(GRUCODE)
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
  ifeq ($(TARGET_GAME_CONSOLE),0)
    ifeq ($(HOST_OS),Windows)
      WINDOWS_BUILD := 1
    endif
  endif
endif

# MXE overrides

ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(CROSS),i686-w64-mingw32.static-)
    TARGET_ARCH = i386pe
    TARGET_BITS = 32
    NO_BZERO_BCOPY := 1
  else ifeq ($(CROSS),x86_64-w64-mingw32.static-)
    TARGET_ARCH = i386pe
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

# Release (version) flag defs

ifeq ($(VERSION),jp)
  VERSION_DEF := VERSION_JP
else
ifeq ($(VERSION),us)
  VERSION_DEF := VERSION_US
else
ifeq ($(VERSION),eu)
  VERSION_DEF := VERSION_EU
else
ifeq ($(VERSION),sh)
  $(warning Building SH is experimental and is prone to breaking. Try at your own risk.)
  VERSION_DEF := VERSION_SH
# TODO: GET RID OF THIS!!! We should mandate assets for Shindou like EU but we dont have the addresses extracted yet so we'll just pretend you have everything extracted for now.
  NOEXTRACT := 1
else
  $(error unknown version "$(VERSION)")
endif
endif
endif
endif

TARGET := sm64.$(VERSION)
VERSION_CFLAGS := -D$(VERSION_DEF) -D_LANGUAGE_C
VERSION_ASFLAGS := --defsym $(VERSION_DEF)=1

# Microcode

ifeq ($(GRUCODE),f3dex) # Fast3DEX
  GRUCODE_DEF := F3DEX_GBI
  GRUCODE_ASFLAGS := --defsym F3DEX_GBI_SHARED=1
  TARGET := $(TARGET).f3dex
  COMPARE := 0
else
ifeq ($(GRUCODE),f3dex2) # Fast3DEX2
  GRUCODE_DEF := F3DEX_GBI_2
  GRUCODE_ASFLAGS := --defsym F3DEX_GBI_SHARED=1
  TARGET := $(TARGET).f3dex2
  COMPARE := 0
else
ifeq ($(GRUCODE),f3dex2e) # Fast3DEX2 Extended (PC default)
  GRUCODE_DEF := F3DEX_GBI_2E
  TARGET := $(TARGET).f3dex2e
  COMPARE := 0
else
ifeq ($(GRUCODE),f3d_new) # Fast3D 2.0H (Shindou)
  GRUCODE_DEF := F3D_NEW
  TARGET := $(TARGET).f3d_new
  COMPARE := 0
else
ifeq ($(GRUCODE),f3dzex) # Fast3DZEX (2.0J / Animal Forest - Dōbutsu no Mori)
  GRUCODE_DEF := F3DEX_GBI_2
  GRUCODE_ASFLAGS := --defsym F3DEX_GBI_SHARED=1
  TARGET := $(TARGET).f3dzex
  COMPARE := 0
endif
endif
endif
endif
endif

GRUCODE_CFLAGS := -D$(GRUCODE_DEF)
GRUCODE_ASFLAGS := $(GRUCODE_ASFLAGS) --defsym $(GRUCODE_DEF)=1

# Default build is for PC now
VERSION_CFLAGS := $(VERSION_CFLAGS) -DNON_MATCHING -DAVOID_UB

ifeq ($(TARGET_RPI),1) # Define RPi to change SDL2 title & GLES2 hints
      VERSION_CFLAGS += -DUSE_GLES
else ifeq ($(OSX_BUILD),1) # Modify GFX & SDL2 for OSX GL
     VERSION_CFLAGS += -DOSX_BUILD
else ifeq ($(TARGET_WEB),1)
  VERSION_CFLAGS := $(VERSION_CFLAGS) -DTARGET_WEB -DUSE_GLES
else ifeq ($(TARGET_WII_U),1)
  VERSION_CFLAGS := $(VERSION_CFLAGS) -DTARGET_WII_U
else ifeq ($(TARGET_N3DS),1)
  VERSION_CFLAGS := $(VERSION_CFLAGS) -DTARGET_N3DS
else ifeq ($(TARGET_SWITCH),1)
  VERSION_CFLAGS += $(VERSION_CFLAGS) -DUSE_GLES -DTARGET_SWITCH
endif

VERSION_ASFLAGS := $(VERSION_ASFLAGS) --defsym AVOID_UB=1
COMPARE := 0

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

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)

# Make sure assets exist
NOEXTRACT ?= 0
ifeq ($(NOEXTRACT),0)
DUMMY != ./extract_assets.py $(VERSION) >&2 || echo FAIL
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
else ifeq ($(WINDOWS_BUILD),1)
  EXE := $(BUILD_DIR)/$(TARGET).exe

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

# Hi, I'm a PC
SRC_DIRS := src src/engine src/game src/audio src/menu src/buffers actors levels bin bin/$(VERSION) data assets
ASM_DIRS := lib
ifeq ($(TARGET_N64),1)
  ASM_DIRS := asm $(ASM_DIRS)
else
  SRC_DIRS := $(SRC_DIRS)  src/pc src/pc/gfx src/pc/audio src/pc/controller src/pc/fs src/pc/fs/packtypes
  ASM_DIRS :=
endif

ifeq ($(TARGET_WII_U),1)
  SRC_DIRS += src/pc/gfx/shaders_wiiu
else ifeq ($(DISCORDRPC),1)
  SRC_DIRS += src/pc/discord
endif

BIN_DIRS := bin bin/$(VERSION)

ULTRA_SRC_DIRS := lib/src lib/src/math
ULTRA_ASM_DIRS := lib/asm lib/data
ULTRA_BIN_DIRS := lib/bin

GODDARD_SRC_DIRS := src/goddard src/goddard/dynlists

MIPSISET := -mips2
MIPSBIT := -32

ifeq ($(TARGET_N64),1)
ifeq ($(COMPILER_N64),gcc)
    MIPSISET := -mips3
    OPT_FLAGS := -O2
endif
endif

# to get 32 bit working, use debug
ifeq ($(DEBUG),1)
  OPT_FLAGS := -g
else
  OPT_FLAGS := -O2
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

# File dependencies and variables for specific files
include Makefile.split

# Source code files
LEVEL_C_FILES := $(wildcard levels/*/leveldata.c) $(wildcard levels/*/script.c) $(wildcard levels/*/geo.c)
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) $(LEVEL_C_FILES)

ifeq ($(TARGET_N64),1)
ULTRA_C_FILES := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.c))
endif

CXX_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
S_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
GODDARD_C_FILES := $(foreach dir,$(GODDARD_SRC_DIRS),$(wildcard $(dir)/*.c))

ifeq ($(TARGET_N64),1)
  ULTRA_S_FILES := $(foreach dir,$(ULTRA_ASM_DIRS),$(wildcard $(dir)/*.s))
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

ifeq ($(VERSION),sh)
SOUND_BANK_FILES := $(wildcard sound/sound_banks/*.json)
SOUND_SEQUENCE_FILES := $(wildcard sound/sequences/jp/*.m64) \
    $(wildcard sound/sequences/*.m64) \
    $(foreach file,$(wildcard sound/sequences/jp/*.s),$(BUILD_DIR)/$(file:.s=.m64)) \
    $(foreach file,$(wildcard sound/sequences/*.s),$(BUILD_DIR)/$(file:.s=.m64))
else
SOUND_BANK_FILES := $(wildcard sound/sound_banks/*.json)
SOUND_SEQUENCE_FILES := $(wildcard sound/sequences/$(VERSION)/*.m64) \
    $(wildcard sound/sequences/*.m64) \
    $(foreach file,$(wildcard sound/sequences/$(VERSION)/*.s),$(BUILD_DIR)/$(file:.s=.m64)) \
    $(foreach file,$(wildcard sound/sequences/*.s),$(BUILD_DIR)/$(file:.s=.m64))
endif

SOUND_SAMPLE_DIRS := $(wildcard sound/samples/*)
SOUND_SAMPLE_AIFFS := $(foreach dir,$(SOUND_SAMPLE_DIRS),$(wildcard $(dir)/*.aiff))
SOUND_SAMPLE_TABLES := $(foreach file,$(SOUND_SAMPLE_AIFFS),$(BUILD_DIR)/$(file:.aiff=.table))
SOUND_SAMPLE_AIFCS := $(foreach file,$(SOUND_SAMPLE_AIFFS),$(BUILD_DIR)/$(file:.aiff=.aifc))
SOUND_OBJ_FILES := $(SOUND_BIN_DIR)/sound_data.o

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(CXX_FILES),$(BUILD_DIR)/$(file:.cpp=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
           $(foreach file,$(GENERATED_C_FILES),$(file:.c=.o))

ULTRA_O_FILES := $(foreach file,$(ULTRA_S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
                 $(foreach file,$(ULTRA_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

GODDARD_O_FILES := $(foreach file,$(GODDARD_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

RPC_LIBS :=
ifeq ($(TARGET_WII_U),0)
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

# Segment elf files
SEG_FILES := $(SEGMENT_ELF_FILES) $(ACTOR_ELF_FILES) $(LEVEL_ELF_FILES)

##################### Compiler Options #######################
INCLUDE_CFLAGS := -I include -I $(BUILD_DIR) -I $(BUILD_DIR)/include -I src -I .
ENDIAN_BITWIDTH := $(BUILD_DIR)/endian-and-bitwidth

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
CPP       := cpp -P -Wno-trigraphs
LD        := $(CROSS)ld
AR        := $(CROSS)ar
OBJDUMP   := $(CROSS)objdump
OBJCOPY   := $(CROSS)objcopy
PYTHON    := python3

# change the compiler to gcc, to use the default, install the gcc-mips-linux-gnu package
ifeq ($(COMPILER_N64),gcc)
  CC        := $(CROSS)gcc
endif

N64_CFLAGS := -nostdinc -I include/libc -DTARGET_N64 -D_LANGUAGE_C -DNO_LDIV
CC_CFLAGS := -fno-builtin

INCLUDE_CFLAGS := -I include -I $(BUILD_DIR) -I $(BUILD_DIR)/include -I src -I .

# Check code syntax with host compiler
CC_CHECK := gcc
CC_CHECK_CFLAGS := -fsyntax-only -fsigned-char $(CC_CFLAGS) $(N64_CFLAGS) $(INCLUDE_CFLAGS) -std=gnu90 -Wall -Wextra -Wno-format-security -Wno-main -DNON_MATCHING -DAVOID_UB $(VERSION_CFLAGS) $(GRUCODE_CFLAGS)

COMMON_CFLAGS = $(OPT_FLAGS) $(N64_CFLAGS) $(INCLUDE_CFLAGS) $(VERSION_CFLAGS) $(MATCH_CFLAGS) $(MIPSISET) $(GRUCODE_CFLAGS)

ASFLAGS := -march=vr4300 -mabi=32 -I include -I $(BUILD_DIR) $(VERSION_ASFLAGS) $(MATCH_ASFLAGS) $(GRUCODE_ASFLAGS)
CFLAGS = -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -Xfullwarn -signed $(COMMON_CFLAGS) $(MIPSBIT)
OBJCOPYFLAGS := --pad-to=0x800000 --gap-fill=0xFF
SYMBOL_LINKING_FLAGS := $(addprefix -R ,$(SEG_FILES))
LDFLAGS := -T undefined_syms.txt -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(BUILD_DIR)/sm64.$(VERSION).map --no-check-sections $(SYMBOL_LINKING_FLAGS)
ENDIAN_BITWIDTH := $(BUILD_DIR)/endian-and-bitwidth

ifeq ($(COMPILER_N64),gcc)
  CFLAGS := -march=vr4300 -mfix4300 -mabi=32 -mno-shared -G 0 -mhard-float -mdivide-breaks -fno-stack-protector -fno-common -fno-zero-initialized-in-bss -I include -I src/ -I $(BUILD_DIR)/include -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra $(COMMON_CFLAGS)
endif

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
CPP := powerpc-eabi-cpp -P
OBJDUMP := powerpc-eabi-objdump
SDLCONFIG :=

else ifeq ($(TARGET_N3DS),1)
  CPP := $(DEVKITARM)/bin/arm-none-eabi-cpp -P
  OBJDUMP := $(DEVKITARM)/bin/arm-none-eabi-objdump
  OBJCOPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy
  AS := $(DEVKITARM)/bin/arm-none-eabi-as
  CC := $(DEVKITARM)/bin/arm-none-eabi-gcc
  CXX := $(DEVKITARM)/bin/arm-none-eabi-g++
  LD := $(CXX)
  SDLCONFIG :=

else

ifeq ($(TARGET_SWITCH),1)
  ifeq ($(strip $(DEVKITPRO)),)
    $(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
  endif
  export PATH := $(DEVKITPRO)/devkitA64/bin:$(PATH)
  PORTLIBS ?= $(DEVKITPRO)/portlibs/switch
  LIBNX ?= $(DEVKITPRO)/libnx
  CROSS ?= aarch64-none-elf-
  SDLCROSS :=
  CC := $(CROSS)gcc
  CXX := $(CROSS)g++
  STRIP := $(CROSS)strip
  NXARCH := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE
  APP_TITLE := Super Mario 64
  APP_AUTHOR := Nintendo, n64decomp team, sm64pc team
  APP_VERSION := 1_master_$(VERSION)
  APP_ICON := nx_icon.jpg
  INCLUDE_CFLAGS += -isystem$(LIBNX)/include -I$(PORTLIBS)/include
  OPT_FLAGS := -g -O0 -std=gnu99
endif

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

LD := $(CC)

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
  CPP := cpp -P
  OBJCOPY := objcopy
  OBJDUMP := $(CROSS)objdump
else ifeq ($(OSX_BUILD),1)
  CPP := cpp-9 -P
  OBJDUMP := i686-w64-mingw32-objdump
  OBJCOPY := i686-w64-mingw32-objcopy
else # Linux & other builds
  CPP := $(CROSS)cpp -P
  OBJCOPY := $(CROSS)objcopy
  OBJDUMP := $(CROSS)objdump
endif

SDLCONFIG := $(SDLCROSS)sdl2-config

endif

PYTHON := python3

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
 # else ifeq ($(TARGET_RPI),1)
  else ifneq ($(TARGET_RPI)$(TARGET_SWITCH),00)
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
  BACKEND_CFLAGS += `$(SDLCONFIG) --cflags`
  ifeq ($(WINDOWS_BUILD),1)
    BACKEND_LDFLAGS += `$(SDLCONFIG) --static-libs` -lsetupapi -luser32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion
  else
    BACKEND_LDFLAGS += `$(SDLCONFIG) --libs`
  endif
endif

ifeq ($(WINDOWS_BUILD),1)
  CC_CHECK := $(CC) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(INCLUDE_CFLAGS) -Wall -Wextra -Wno-format-security $(VERSION_CFLAGS) $(GRUCODE_CFLAGS)
  CFLAGS := $(OPT_FLAGS) $(INCLUDE_CFLAGS) $(BACKEND_CFLAGS) $(VERSION_CFLAGS) $(GRUCODE_CFLAGS) -fno-strict-aliasing -fwrapv

else ifeq ($(TARGET_WEB),1)
  CC_CHECK := $(CC) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(INCLUDE_CFLAGS) -Wall -Wextra -Wno-format-security $(VERSION_CFLAGS) $(GRUCODE_CFLAGS) -s USE_SDL=2
  CFLAGS := $(OPT_FLAGS) $(INCLUDE_CFLAGS) $(BACKEND_CFLAGS) $(VERSION_CFLAGS) $(GRUCODE_CFLAGS) -fno-strict-aliasing -fwrapv -s USE_SDL=2

# Linux / Other builds below
else
  CC_CHECK := $(CC) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(INCLUDE_CFLAGS) -Wall -Wextra -Wno-format-security $(VERSION_CFLAGS) $(GRUCODE_CFLAGS)
  CFLAGS := $(OPT_FLAGS) $(INCLUDE_CFLAGS) $(BACKEND_CFLAGS) $(VERSION_CFLAGS) $(GRUCODE_CFLAGS) -fno-strict-aliasing -fwrapv

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
endif

ifeq ($(TARGET_SWITCH),1)
  CC_CHECK := $(CC) $(NXARCH) -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(INCLUDE_CFLAGS) -Wall -Wextra -Wno-format-security $(VERSION_CFLAGS) $(GRUCODE_CFLAGS) -D__SWITCH__=1
  CFLAGS := $(NXARCH) $(OPT_FLAGS) $(INCLUDE_CFLAGS) $(BACKEND_CFLAGS) $(VERSION_CFLAGS) $(GRUCODE_CFLAGS) -fno-strict-aliasing -ftls-model=local-exec -fPIE -fwrapv -D__SWITCH__=1
endif

# Check for enhancement options

# Check for Puppycam option
ifeq ($(BETTERCAMERA),1)
  CC_CHECK += -DBETTERCAMERA
  CFLAGS += -DBETTERCAMERA
  EXT_OPTIONS_MENU := 1
endif

ifeq ($(TEXTSAVES),1)
  CC_CHECK += -DTEXTSAVES
  CFLAGS += -DTEXTSAVES
endif

# Check for no drawing distance option
ifeq ($(NODRAWINGDISTANCE),1)
  CC_CHECK += -DNODRAWINGDISTANCE
  CFLAGS += -DNODRAWINGDISTANCE
endif

# Check for PC Port Defines
ifeq ($(PC_PORT_DEFINES),1)
  CC_CHECK += -DNO_SEGMENTED_MEMORY -DWIDESCREEN
  CFLAGS += -DNO_SEGMENTED_MEMORY -DWIDESCREEN
endif

# Check for Discord Rich Presence option
ifeq ($(TARGET_GAME_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    CC_CHECK += -DDISCORDRPC
    CFLAGS += -DDISCORDRPC
  endif
endif

# Check for Rumble option
ifeq ($(RUMBLE_FEEDBACK),1)
  CC_CHECK += -DRUMBLE_FEEDBACK
  CFLAGS += -DRUMBLE_FEEDBACK
endif

# Check for QoL fixes option
ifeq ($(QOL_FIXES),1)
  CC_CHECK += -DQOL_FIXES
  CFLAGS += -DQOL_FIXES
endif

# Check for extended options menu option
ifeq ($(EXT_OPTIONS_MENU),1)
  CC_CHECK += -DEXT_OPTIONS_MENU -DCHEATS_ACTIONS
  CFLAGS += -DEXT_OPTIONS_MENU -DCHEATS_ACTIONS
endif

# Check for no bzero/bcopy workaround option
ifeq ($(NO_BZERO_BCOPY),1)
  CC_CHECK += -DNO_BZERO_BCOPY
  CFLAGS += -DNO_BZERO_BCOPY
endif

# Use internal ldiv()/lldiv()
ifeq ($(NO_LDIV),1)
  CC_CHECK += -DNO_LDIV
  CFLAGS += -DNO_LDIV
endif

# Use OpenGL 1.3
ifeq ($(LEGACY_GL),1)
  CC_CHECK += -DLEGACY_GL
  CFLAGS += -DLEGACY_GL
endif

# Use Console exclusive defines
ifeq ($(TARGET_GAME_CONSOLE),1)
  CC_CHECK += -DTARGET_GAME_CONSOLE
  CFLAGS += -DTARGET_GAME_CONSOLE
endif

# Load external textures
ifeq ($(EXTERNAL_DATA),1)
  CC_CHECK += -DEXTERNAL_DATA -DFS_BASEDIR="\"$(BASEDIR)\""
  CFLAGS += -DEXTERNAL_DATA -DFS_BASEDIR="\"$(BASEDIR)\""
  # tell skyconv to write names instead of actual texture data and save the split tiles so we can use them later
  SKYTILE_DIR := $(BUILD_DIR)/textures/skybox_tiles
  SKYCONV_ARGS := --store-names --write-tiles "$(SKYTILE_DIR)"
endif

ASFLAGS := -I include -I $(BUILD_DIR) $(VERSION_ASFLAGS)

ifeq ($(TARGET_WEB),1)
LDFLAGS := -lm -lGL -lSDL2 -no-pie -s TOTAL_MEMORY=20MB -g4 --source-map-base http://localhost:8080/ -s "EXTRA_EXPORTED_RUNTIME_METHODS=['callMain']"

else ifeq ($(TARGET_WII_U),1)
LDFLAGS := -lm -no-pie $(BACKEND_LDFLAGS) $(MACHDEP) $(RPXSPECS) $(LIBPATHS)

else ifeq ($(TARGET_N3DS),1)
LDFLAGS := $(LIBPATHS) -lcitro3d -lctru -lm -specs=3dsx.specs -g -marm -mthumb-interwork -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft # -Wl,-Map,$(notdir $*.map)

else ifeq ($(TARGET_SWITCH),1)
  LDFLAGS := -specs=$(LIBNX)/switch.specs $(NXARCH) $(OPT_FLAGS) -L$(LIBNX)/lib $(BACKEND_LDFLAGS) -lstdc++ -lnx -lm

else ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -Llib -lpthread $(BACKEND_LDFLAGS) -static
  ifeq ($(CROSS),)
    LDFLAGS += -no-pie
  endif
  ifeq ($(WINDOWS_CONSOLE),1)
    LDFLAGS += -mconsole
  endif

else ifeq ($(TARGET_RPI),1)
  LDFLAGS := $(OPT_FLAGS) -lm $(BACKEND_LDFLAGS) -no-pie

else ifeq ($(OSX_BUILD),1)
  LDFLAGS := -lm $(BACKEND_LDFLAGS) -no-pie -lpthread

else
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -lm $(BACKEND_LDFLAGS) -no-pie -lpthread
  ifeq ($(DISCORDRPC),1)
    LDFLAGS += -ldl -Wl,-rpath .
  endif

endif # End of LDFLAGS

# Prevent a crash with -sopt
export LANG := C

endif

####################### Other Tools #########################

# N64 conversion tools
TOOLS_DIR = tools
MIO0TOOL = $(TOOLS_DIR)/mio0
N64CKSUM = $(TOOLS_DIR)/n64cksum
N64GRAPHICS = $(TOOLS_DIR)/n64graphics
N64GRAPHICS_CI = $(TOOLS_DIR)/n64graphics_ci
TEXTCONV = $(TOOLS_DIR)/textconv
AIFF_EXTRACT_CODEBOOK = $(TOOLS_DIR)/aiff_extract_codebook
VADPCM_ENC = $(TOOLS_DIR)/vadpcm_enc
EXTRACT_DATA_FOR_MIO = $(TOOLS_DIR)/extract_data_for_mio
SKYCONV = $(TOOLS_DIR)/skyconv
EMULATOR = mupen64plus
EMU_FLAGS = --noosd
LOADER = loader64
LOADER_FLAGS = -vwf
SHA1SUM = sha1sum
ZEROTERM = $(PYTHON) $(TOOLS_DIR)/zeroterm.py

ifeq (, $(shell which armips 2>/dev/null))
  RSPASM := $(TOOLS_DIR)/armips
else
  RSPASM = armips
endif

###################### Dependency Check #####################

# Stubbed

######################## Targets #############################

ifeq ($(TARGET_N64),1)
all: $(ROM)
ifeq ($(COMPARE),1)
	@$(SHA1SUM) -c $(TARGET).sha1 || (echo 'The build succeeded, but did not match the official ROM. This is expected if you are making changes to the game.\nTo silence this message, use "make COMPARE=0"'. && false)
endif
else
all: $(EXE)
endif

ifeq ($(TARGET_SWITCH),1)
all: $(EXE).nro
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
$(BASEPACK_LST): $(EXE)
	@mkdir -p $(BUILD_DIR)/$(BASEDIR)
	@echo -n > $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/bank_sets sound/bank_sets" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sequences.bin sound/sequences.bin" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sound_data.ctl sound/sound_data.ctl" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sound_data.tbl sound/sound_data.tbl" >> $(BASEPACK_LST)
	@$(foreach f, $(wildcard $(SKYTILE_DIR)/*), echo $(f) gfx/$(f:$(BUILD_DIR)/%=%) >> $(BASEPACK_LST);)
	@find actors -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
	@find levels -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
	@find textures -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;

# prepares the resource ZIP with base data
$(BASEPACK_PATH): $(BASEPACK_LST)
	@$(PYTHON) $(TOOLS_DIR)/mkzip.py $(BASEPACK_LST) $(BASEPACK_PATH)

endif

clean:
	$(RM) -r $(BUILD_DIR_BASE)

cleantools:
	$(MAKE) -s -C tools clean

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

$(BUILD_DIR)/lib/rsp.o: $(BUILD_DIR)/rsp/rspboot.bin $(BUILD_DIR)/rsp/fast3d.bin $(BUILD_DIR)/rsp/audio.bin

#Required so the compiler doesn't complain about this not existing.
$(BUILD_DIR)/src/game/camera.o: $(BUILD_DIR)/include/text_strings.h

$(BUILD_DIR)/include/text_strings.h: include/text_strings.h.in
	$(TEXTCONV) charmap.txt $< $@

$(BUILD_DIR)/include/text_menu_strings.h: include/text_menu_strings.h.in
	$(TEXTCONV) charmap_menu.txt $< $@

$(BUILD_DIR)/include/text_options_strings.h: include/text_options_strings.h.in
	$(TEXTCONV) charmap.txt $< $@

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
	$(CPP) $(VERSION_CFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

$(BUILD_DIR)/text/%/define_text.inc.c: text/define_text.inc.c text/%/courses.h text/%/dialogs.h
	$(CPP) $(VERSION_CFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

RSP_DIRS := $(BUILD_DIR)/rsp
ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS) $(GODDARD_SRC_DIRS) $(ULTRA_SRC_DIRS) $(ULTRA_ASM_DIRS) $(ULTRA_BIN_DIRS) $(BIN_DIRS) $(TEXTURE_DIRS) $(TEXT_DIRS) $(SOUND_SAMPLE_DIRS) $(addprefix levels/,$(LEVEL_DIRS)) include) $(MIO0_DIR) $(addprefix $(MIO0_DIR)/,$(VERSION)) $(SOUND_BIN_DIR) $(SOUND_BIN_DIR)/sequences/$(VERSION) $(RSP_DIRS)

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

$(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_menu_strings.h
$(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_options_strings.h

ifeq ($(VERSION),eu)
$(BUILD_DIR)/src/menu/file_select.o: $(BUILD_DIR)/include/text_strings.h $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
$(BUILD_DIR)/src/menu/star_select.o: $(BUILD_DIR)/include/text_strings.h $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
$(BUILD_DIR)/src/game/ingame_menu.o: $(BUILD_DIR)/include/text_strings.h $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
$(BUILD_DIR)/src/game/options_menu.o: $(BUILD_DIR)/include/text_strings.h $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
# O_FILES += $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
ifeq ($(TARGET_GAME_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    $(BUILD_DIR)/src/pc/discord/discordrpc.o: $(BUILD_DIR)/include/text_strings.h $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
  endif
endif
else
$(BUILD_DIR)/src/menu/file_select.o: $(BUILD_DIR)/include/text_strings.h
$(BUILD_DIR)/src/menu/star_select.o: $(BUILD_DIR)/include/text_strings.h
$(BUILD_DIR)/src/game/ingame_menu.o: $(BUILD_DIR)/include/text_strings.h
$(BUILD_DIR)/src/game/options_menu.o: $(BUILD_DIR)/include/text_strings.h
ifeq ($(TARGET_GAME_CONSOLE),0)
  ifeq ($(DISCORDRPC),1)
    $(BUILD_DIR)/src/pc/discord/discordrpc.o: $(BUILD_DIR)/include/text_strings.h
  endif
endif
endif

################################################################
# TEXTURE GENERATION                                           #
################################################################

# RGBA32, RGBA16, IA16, IA8, IA4, IA1, I8, I4

ifeq ($(EXTERNAL_DATA),1)

$(BUILD_DIR)/%: %.png
	$(ZEROTERM) "$(patsubst %.png,%,$^)" > $@

else

$(BUILD_DIR)/%: %.png
	$(N64GRAPHICS) -i $@ -g $< -f $(lastword $(subst ., ,$@))

endif

$(BUILD_DIR)/%.inc.c: $(BUILD_DIR)/% %.png
	hexdump -v -e '1/1 "0x%X,"' $< > $@
	echo >> $@

ifeq ($(EXTERNAL_DATA),0)

# Color Index CI8
$(BUILD_DIR)/%.ci8: %.ci8.png
	$(N64GRAPHICS_CI) -i $@ -g $< -f ci8

# Color Index CI4
$(BUILD_DIR)/%.ci4: %.ci4.png
	$(N64GRAPHICS_CI) -i $@ -g $< -f ci4

endif

################################################################

# compressed segment generation

ifeq ($(TARGET_N64),1)
# TODO: ideally this would be `-Trodata-segment=0x07000000` but that doesn't set the address

$(BUILD_DIR)/bin/%.elf: $(BUILD_DIR)/bin/%.o
	$(LD) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map -o $@ $<
$(BUILD_DIR)/actors/%.elf: $(BUILD_DIR)/actors/%.o
	$(LD) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map -o $@ $<

# Override for level.elf, which otherwise matches the above pattern
.SECONDEXPANSION:
$(BUILD_DIR)/levels/%/leveldata.elf: $(BUILD_DIR)/levels/%/leveldata.o $(BUILD_DIR)/bin/$$(TEXTURE_BIN).elf
	$(LD) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map --just-symbols=$(BUILD_DIR)/bin/$(TEXTURE_BIN).elf -o $@ $<

$(BUILD_DIR)/bin/%.bin: $(BUILD_DIR)/bin/%.elf
	$(EXTRACT_DATA_FOR_MIO) $< $@

$(BUILD_DIR)/actors/%.bin: $(BUILD_DIR)/actors/%.elf
	$(EXTRACT_DATA_FOR_MIO) $< $@

$(BUILD_DIR)/levels/%/leveldata.bin: $(BUILD_DIR)/levels/%/leveldata.elf
	$(EXTRACT_DATA_FOR_MIO) $< $@

$(BUILD_DIR)/%.mio0: $(BUILD_DIR)/%.bin
	$(MIO0TOOL) $< $@

$(BUILD_DIR)/%.mio0.o: $(BUILD_DIR)/%.mio0.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.mio0.s: $(BUILD_DIR)/%.mio0
	printf ".section .data\n\n.incbin \"$<\"\n" > $@
endif

# PC Area
$(BUILD_DIR)/%.table: %.aiff
	$(AIFF_EXTRACT_CODEBOOK) $< >$@

$(BUILD_DIR)/%.aifc: $(BUILD_DIR)/%.table %.aiff
	$(VADPCM_ENC) -c $^ $@

$(BUILD_DIR)/rsp/%.bin $(BUILD_DIR)/rsp/%_data.bin: rsp/%.s
	$(RSPASM) -sym $@.sym -definelabel $(VERSION_DEF) 1 -definelabel $(GRUCODE_DEF) 1 -strequ CODE_FILE $(BUILD_DIR)/rsp/$*.bin -strequ DATA_FILE $(BUILD_DIR)/rsp/$*_data.bin $<

$(ENDIAN_BITWIDTH): tools/determine-endian-bitwidth.c
	$(CC) -c $(CFLAGS) -o $@.dummy2 $< 2>$@.dummy1; true
	grep -o 'msgbegin --endian .* --bitwidth .* msgend' $@.dummy1 > $@.dummy2
	head -n1 <$@.dummy2 | cut -d' ' -f2-5 > $@
	@rm $@.dummy1
	@rm $@.dummy2

$(SOUND_BIN_DIR)/sound_data.ctl: sound/sound_banks/ $(SOUND_BANK_FILES) $(SOUND_SAMPLE_AIFCS) $(ENDIAN_BITWIDTH)
	$(PYTHON) tools/assemble_sound.py $(BUILD_DIR)/sound/samples/ sound/sound_banks/ $(SOUND_BIN_DIR)/sound_data.ctl $(SOUND_BIN_DIR)/sound_data.tbl $(VERSION_CFLAGS) $$(cat $(ENDIAN_BITWIDTH))

$(SOUND_BIN_DIR)/sound_data.tbl: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

ifeq ($(VERSION),sh)
$(SOUND_BIN_DIR)/sequences.bin: $(SOUND_BANK_FILES) sound/sequences.json sound/sequences/ sound/sequences/jp/ $(SOUND_SEQUENCE_FILES) $(ENDIAN_BITWIDTH)
	$(PYTHON) tools/assemble_sound.py --sequences $@ $(SOUND_BIN_DIR)/bank_sets sound/sound_banks/ sound/sequences.json $(SOUND_SEQUENCE_FILES) $(VERSION_CFLAGS) $$(cat $(ENDIAN_BITWIDTH))
else
$(SOUND_BIN_DIR)/sequences.bin: $(SOUND_BANK_FILES) sound/sequences.json sound/sequences/ sound/sequences/$(VERSION)/ $(SOUND_SEQUENCE_FILES) $(ENDIAN_BITWIDTH)
	$(PYTHON) tools/assemble_sound.py --sequences $@ $(SOUND_BIN_DIR)/bank_sets sound/sound_banks/ sound/sequences.json $(SOUND_SEQUENCE_FILES) $(VERSION_CFLAGS) $$(cat $(ENDIAN_BITWIDTH))
endif

$(SOUND_BIN_DIR)/bank_sets: $(SOUND_BIN_DIR)/sequences.bin
	@true

$(SOUND_BIN_DIR)/%.m64: $(SOUND_BIN_DIR)/%.o
	$(OBJCOPY) -j .rodata $< -O binary $@

$(SOUND_BIN_DIR)/%.o: $(SOUND_BIN_DIR)/%.s
	$(AS) $(ASFLAGS) -o $@ $<

ifeq ($(EXTERNAL_DATA),1)

$(SOUND_BIN_DIR)/%.inc.c: $(SOUND_BIN_DIR)/%
	$(ZEROTERM) "$(patsubst $(BUILD_DIR)/%,%,$^)" | hexdump -v -e '1/1 "0x%X,"' > $@

else

$(SOUND_BIN_DIR)/%.inc.c: $(SOUND_BIN_DIR)/%
	hexdump -v -e '1/1 "0x%X,"' $< > $@
	echo >> $@

endif

$(SOUND_BIN_DIR)/sound_data.o: $(SOUND_BIN_DIR)/sound_data.ctl.inc.c $(SOUND_BIN_DIR)/sound_data.tbl.inc.c $(SOUND_BIN_DIR)/sequences.bin.inc.c $(SOUND_BIN_DIR)/bank_sets.inc.c

$(BUILD_DIR)/levels/scripts.o: $(BUILD_DIR)/include/level_headers.h

$(BUILD_DIR)/include/level_headers.h: levels/level_headers.h.in
	$(CPP) -I . levels/level_headers.h.in | $(PYTHON) tools/output_level_headers.py > $(BUILD_DIR)/include/level_headers.h

$(BUILD_DIR)/assets/mario_anim_data.c: $(wildcard assets/anims/*.inc.c)
	$(PYTHON) tools/mario_anims_converter.py > $@

$(BUILD_DIR)/assets/demo_data.c: assets/demo_data.json $(wildcard assets/demos/*.bin)
	$(PYTHON) tools/demo_data_converter.py assets/demo_data.json $(VERSION_CFLAGS) > $@

ifeq ($(COMPILER_N64),ido)
# Source code
$(BUILD_DIR)/levels/%/leveldata.o: OPT_FLAGS := -g
$(BUILD_DIR)/actors/%.o: OPT_FLAGS := -g
$(BUILD_DIR)/bin/%.o: OPT_FLAGS := -g
$(BUILD_DIR)/src/goddard/%.o: OPT_FLAGS := -g
$(BUILD_DIR)/src/goddard/%.o: MIPSISET := -mips1
$(BUILD_DIR)/src/audio/%.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0
$(BUILD_DIR)/src/audio/load.o: OPT_FLAGS := -O2 -framepointer -Wo,-loopunroll,0
$(BUILD_DIR)/lib/src/%.o: OPT_FLAGS :=
$(BUILD_DIR)/lib/src/math/ll%.o: MIPSISET := -mips3 -32
$(BUILD_DIR)/lib/src/math/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/lib/src/math/ll%.o: OPT_FLAGS :=
$(BUILD_DIR)/lib/src/ldiv.o: OPT_FLAGS := -O2
$(BUILD_DIR)/lib/src/string.o: OPT_FLAGS := -O2
$(BUILD_DIR)/lib/src/gu%.o: OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/al%.o: OPT_FLAGS := -O3

ifeq ($(VERSION),eu)
$(BUILD_DIR)/lib/src/_Litob.o: OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/_Ldtob.o: OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/_Printf.o: OPT_FLAGS := -O3
$(BUILD_DIR)/lib/src/sprintf.o: OPT_FLAGS := -O3

# enable loop unrolling except for external.c (external.c might also have used
# unrolling, but it makes one loop harder to match)
$(BUILD_DIR)/src/audio/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/audio/load.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/audio/external.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0
else

# The source-to-source optimizer copt is enabled for audio. This makes it use
# acpp, which needs -Wp,-+ to handle C++-style comments.
$(BUILD_DIR)/src/audio/effects.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0 -sopt,-inline=sequence_channel_process_sound,-scalaroptimize=1 -Wp,-+
$(BUILD_DIR)/src/audio/synthesis.o: OPT_FLAGS := -O2 -sopt,-scalaroptimize=1 -Wp,-+
#$(BUILD_DIR)/src/audio/seqplayer.o: OPT_FLAGS := -O2 -sopt,-inline_manual,-scalaroptimize=1 -Wp,-+ #-Wo,-v,-bb,-l,seqplayer_list.txt

# Add a target for build/eu/src/audio/*.copt to make it easier to see debug
$(BUILD_DIR)/src/audio/%.acpp: src/audio/%.c
	$(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/lib/acpp $(N64_CFLAGS) $(INCLUDE_CFLAGS) $(VERSION_CFLAGS) $(MATCH_CFLAGS) $(GRUCODE_CFLAGS) -D__sgi -+ $< > $@

$(BUILD_DIR)/src/audio/seqplayer.copt: $(BUILD_DIR)/src/audio/seqplayer.acpp
	$(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/lib/copt -signed -I=$< -CMP=$@ -cp=i -scalaroptimize=1 -inline_manual

$(BUILD_DIR)/src/audio/%.copt: $(BUILD_DIR)/src/audio/%.acpp
	$(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/lib/copt -signed -I=$< -CMP=$@ -cp=i -scalaroptimize=1

endif
endif

# Rebuild files with 'GLOBAL_ASM' if the NON_MATCHING flag changes.
$(GLOBAL_ASM_O_FILES): $(GLOBAL_ASM_DEP).$(NON_MATCHING)
$(GLOBAL_ASM_DEP).$(NON_MATCHING):
	@rm -f $(GLOBAL_ASM_DEP).*
	touch $@

$(BUILD_DIR)/%.o: %.cpp
	@$(CXX) -fsyntax-only $(CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(CXX) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@$(CC_CHECK) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(CC) -c $(CFLAGS) -o $@ $<


$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	@$(CC_CHECK) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -MD $(BUILD_DIR)/$*.d -o $@ $<


ifeq ($(TARGET_N64),1)
$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(CPP) $(VERSION_CFLAGS) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(BUILD_DIR)/libultra.a: $(ULTRA_O_FILES)
	$(AR) rcs -o $@ $(ULTRA_O_FILES)
	tools/patch_libultra_math $@

$(BUILD_DIR)/libgoddard.a: $(GODDARD_O_FILES)
	$(AR) rcs -o $@ $(GODDARD_O_FILES)

$(ELF): $(O_FILES) $(MIO0_OBJ_FILES) $(SOUND_OBJ_FILES) $(SEG_FILES) $(BUILD_DIR)/$(LD_SCRIPT) undefined_syms.txt $(BUILD_DIR)/libultra.a $(BUILD_DIR)/libgoddard.a
	$(LD) -L $(BUILD_DIR) $(LDFLAGS) -o $@ $(O_FILES) $(LIBS) -lultra -lgoddard

$(ROM): $(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $(@:.z64=.bin) -O binary
	$(N64CKSUM) $(@:.z64=.bin) $@

$(BUILD_DIR)/$(TARGET).objdump: $(ELF)
	$(OBJDUMP) -D $< > $@
else ifeq ($(TARGET_WII_U),1)
$(ELF):  $(O_FILES) $(MIO0_FILES:.mio0=.o) $(SOUND_OBJ_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS)
	$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(SOUND_OBJ_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
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

$(EXE): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(SOUND_OBJ_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/src/pc/gfx/shader.shbin.o
	$(LD) -L $(BUILD_DIR) -o $@.elf $(O_FILES) $(BUILD_DIR)/src/pc/gfx/shader.shbin.o $(SOUND_OBJ_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
	3dsxtool $@.elf $@
else
$(EXE): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(SOUND_OBJ_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS)
	$(LD) -L $(BUILD_DIR) -o $@ $(O_FILES) $(SOUND_OBJ_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
endif

ifeq ($(TARGET_SWITCH), 1)

# add `--icon=$(APP_ICON)` to this when we get a suitable icon
%.nro: %.stripped %.nacp
	@elf2nro $< $@ --nacp=$*.nacp
	@echo built ... $(notdir $@)

%.nacp:
	@nacptool --create "$(APP_TITLE)" "$(APP_AUTHOR)" "$(APP_VERSION)" $@ $(NACPFLAGS)
	@echo built ... $(notdir $@)

%.stripped: %
	@$(STRIP) -o $@ $<
	@echo stripped ... $(notdir $<)

endif

.PHONY: all clean distclean default diff test load libultra res
.PRECIOUS: $(BUILD_DIR)/bin/%.elf $(SOUND_BIN_DIR)/%.ctl $(SOUND_BIN_DIR)/%.tbl $(SOUND_SAMPLE_TABLES) $(SOUND_BIN_DIR)/%.s $(BUILD_DIR)/%
.DELETE_ON_ERROR:

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

-include $(DEP_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
