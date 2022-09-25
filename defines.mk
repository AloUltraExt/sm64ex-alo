# --------------------------------------
# General Defines
# --------------------------------------

# Build debug version
DEBUG ?= 0
# Enable extended options menu by default
EXT_OPTIONS_MENU ?= 1
# Enable debug options menu (Enabled if DEBUG=1)
EXT_DEBUG_MENU ?= 0
# Enable better camera (Puppycam 2)
BETTERCAMERA ?= 1
# Enable cheats
CHEATS_ACTIONS ?= 1
# Enable rumble functions (Originally in Shindou)
RUMBLE_FEEDBACK ?= 1
# Disable no drawing distance by default
NODRAWINGDISTANCE ?= 0
# Enable Goddard (Mario Face)
GODDARD_MFACE ?= 1
# Kaze MOP Objects Port, disabled by default
PORT_MOP_OBJS ?= 0
# Enable level vanilla checks
VANILLA_CHECKS ?= 1
# Enable extended bounds
EXTENDED_BOUNDS ?= 0
# Accept RM2C level folder output
RM2C ?= 0

# --------------------------------------
# General QoL Defines (see include/qol_defines.h)
# --------------------------------------

# Quality of life fixes
QOL_FIXES ?= 1
# Quality of life features
QOL_FEATURES ?= 1
# Quality of life redone files
QOL_REDONE ?= 1

# --------------------------------------
# Port Only Defines
# --------------------------------------

# Enable 60 fps interpolation
HIGH_FPS_PC ?= 0
# Disable text-based save-files by default
TEXTSAVES ?= 0
# Load resources from external files
EXTERNAL_DATA ?= 0
# Enable Discord Rich Presence
DISCORDRPC ?= 0
# Enable Command Line Options
COMMAND_LINE_OPTIONS ?= 1

# --------------------------------------
# Custom Defines
# --------------------------------------

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

# Check for 60 fps interpolation
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
  ifeq ($(TARGET_N64),1)
    $(error External data is not usable on N64)
  endif
endif

# Use PC-only exclusive defines
ifeq ($(TARGET_ANDROID),1)
  # Check for touch controls
  ifeq ($(TOUCH_CONTROLS),1)
    CUSTOM_C_DEFINES += -DTOUCH_CONTROLS
  endif
endif

ifeq ($(TARGET_PORT_CONSOLE),0)

  # Check for Mouse Option (no DirectX yet)
  ifneq ($(WINDOW_API),DXGI)
    CUSTOM_C_DEFINES += -DMOUSE_ACTIONS
  endif

  # Check for Discord Rich Presence option
  ifeq ($(DISCORDRPC),1)
    CUSTOM_C_DEFINES += -DDISCORDRPC
  endif
  
  # Check for Command Line Options
  ifeq ($(COMMAND_LINE_OPTIONS),1)
    CUSTOM_C_DEFINES += -DCOMMAND_LINE_OPTIONS
  endif

endif # !TARGET_PORT_CONSOLE

endif # !TARGET_N64

# Check for Debug option
ifeq ($(DEBUG),1)
  CUSTOM_C_DEFINES += -DDEBUG
  COMPILER_OPT := debug
  EXT_DEBUG_MENU := 1
endif

# Check for Debug Menu option
ifeq ($(EXT_DEBUG_MENU),1)
  CUSTOM_C_DEFINES += -DEXT_DEBUG_MENU
  EXT_OPTIONS_MENU := 1
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

# Check for Vanilla checks
ifeq ($(VANILLA_CHECKS),1)
  CUSTOM_C_DEFINES += -DVANILLA_CHECKS
endif

# Check for Extended bounds
ifneq ($(EXTENDED_BOUNDS),0)
  CUSTOM_C_DEFINES += -DEXTENDED_BOUNDS=$(EXTENDED_BOUNDS) -DCOLLISION_FIXES
endif

# Add RM2C to flags, add var for internal name
ifeq ($(RM2C),1)
  CUSTOM_C_DEFINES += -DRM2C
endif

# Check for QoL fixes option
ifeq ($(QOL_FIXES),1)
  CUSTOM_C_DEFINES += -DQOL_FIXES
endif

# Check for QoL features option
ifeq ($(QOL_FEATURES),1)
  CUSTOM_C_DEFINES += -DQOL_FEATURES
endif

# Check for QoL features option
ifeq ($(QOL_REDONE),1)
  CUSTOM_C_DEFINES += -DQOL_REDONE
endif
