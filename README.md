# sm64ex_alo
Fork of [sm64pc/sm64ex](https://github.com/sm64pc/sm64ex/tree/nightly) with additional features. 

## Changes
 * N64 Building - Support for it was removed in sm64ex
 * Based of the latest refresh (14, since sm64ex is stuck on 12)
 * Quality of Life Fixes and Features (QOL_FIXES=1 and QOL_FEATURES=1 respectively)
 * Mouse Support for Desktop targets (SDL1/SDL2 only, DirectX Mouse not implemented yet)
 * Simple Debug Options Menu (DEBUG=1)
 
## Backends included
 * Same ones as in [sm64ex](https://github.com/sm64pc/sm64ex/tree/nightly) (macOS - Raspberry Pi Series - Windows - Linux) etc.
 * [Nintendo 64](https://github.com/n64decomp/sm64) along with some [HackerSM64](https://github.com/Reonu/HackerSM64) Makefile changes
 * [Nintendo Wii U](https://github.com/aboood40091/sm64ex/tree/nightly)(by AboodXD)
 * [Nintendo 3DS](https://github.com/mkst/sm64-port) (by Fnouwt, mkst)
 * [Nintendo Switch] (by Vatuu, fgsfdsfgs, KiritoDev)
 
## Patches
 * Some misc patches for this repo are available [here](https://github.com/AloXado320/sm64ex-alo-patches) (more incoming)

## Building
 * To build for N64, you need GCC mips, to install it, run `sudo apt install gcc-mips-linux-gnu`. (TARGET_N64=1)
 * To build for sm64ex platforms, [click here](https://github.com/sm64pc/sm64ex/blob/nightly/README.md).
 * To build for Wii U, [click here](https://github.com/aboood40091/sm64-port/blob/master/README.md). (TARGET_WII_U=1)
 * To build for 3DS, [click here](https://github.com/sm64-port/sm64_3ds/blob/master/README.md). (TARGET_N3DS=1)
 * To build for Switch, [click here](https://github.com/fgsfdsfgs/sm64ex/blob/switch/README.md). (TARGET_SWITCH=1)
