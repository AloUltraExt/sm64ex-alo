# sm64ex_alo
Fork of [sm64pc/sm64ex](https://github.com/sm64pc/sm64ex/tree/nightly) with additional features. 

## Changes
 * N64 Building - Support for it was removed in sm64ex
 * Based of the latest refresh (since sm64ex is stuck on 12)
 * Puppycam 2 (sm64ex still has Puppycam 1)
 * Quality of life fixes and features (QOL_FIXES=1 and QOL_FEATURES=1 respectively)
 * Mouse support for desktop targets (MOUSE_ACTIONS=1) (SDL1/SDL2 only, DirectX Mouse not implemented yet)
 * Simple debug options menu (EXT_DEBUG_MENU=1)
 * Kaze's more objects patch (PORT_MOP_OBJS=1)
 
## Backends included
 * Same ones as in [sm64ex](https://github.com/sm64pc/sm64ex/tree/nightly) (macOS - Raspberry Pi Series - Windows - Linux), etc.
 * [Nintendo 64](https://github.com/n64decomp/sm64) along with some [HackerSM64](https://github.com/Reonu/HackerSM64) Makefile changes
 * [Nintendo Wii U](https://github.com/aboood40091/sm64ex/tree/nightly) (by AboodXD)
 * [Nintendo 3DS](https://github.com/mkst/sm64-port) (by Fnouwt, mkst)
 * [Nintendo Switch](https://github.com/fgsfdsfgs/sm64ex/tree/switch) (by Vatuu, fgsfdsfgs, KiritoDev)
 * [Android](https://github.com/VDavid003/sm64-port-android/tree/ex/nightly) (by VDavid003)

## Patches
 * Some misc patches for this repo are available [here](https://github.com/AloXado320/sm64ex-alo-patches) (more incoming)

## Building
 **Clone the repository:**

 ```sh
 git clone https://github.com/AloXado320/sm64ex-alo
 cd sm64ex-alo
 ```
 
 **Copy baserom(s) for asset extraction:**
 
 For each version (jp/us/eu/sh) for which you want to build an executable, put an existing ROM at `./baserom.<VERSION>.z64` for asset extraction.
 
 By default it builds the US version.
 
<details>
  <summary>To build for N64, click here</summary>
 
  NOTE: Only tested in WSL, works on (Debian / Ubuntu) as well, other distros untested.

  **Install build dependencies:**
  ```sh
  sudo apt install -y binutils-mips-linux-gnu build-essential git libcapstone-dev pkgconf python3 gcc-mips-linux-gnu
  ```

  **Build:**
  ```sh
  # if you have more cores available, you can increase the -j parameter
  make -j4 TARGET_N64=1 
  ```
 
  **Enjoy your rom:**
  ```sh
  build/us/sm64.us.f3dzex.z64
  ```

</details>

<details>
  <summary>To build for Android, click here</summary>
 
  NOTE: Only Termux build is supported.
 
  **Install Termux**
 
  Install the app from F-Droid [here](https://f-droid.org/en/packages/com.termux/)
 
  Make sure you use this version, as the Google Play version is outdated.

  **Install build dependencies**
  ```sh
  pkg install git wget make python getconf zip apksigner clang
  ```

  **Copy in your baserom:**

  Do this using your default file manager (on AOSP, you can slide on the left and there will be a "Termux" option there), or using Termux.
  ```sh
  termux-setup-storage
  cp /sdcard/path/to/your/baserom.z64 ./baserom.us.z64
  ```
 
  **Get SDL includes:**
  ```sh
  cd platform/android/ && ./getSDL.sh && cd ../..
  ```
 
  **Build**
  ```sh
  # if you have more cores available, you can increase the -j parameter
  # On Termux, TARGET_ANDROID=1 is defined automatically in Makefile
  make -j4
  ```

  **Enjoy your apk:**
  ```sh
  ls -al build/us_android/sm64.us.f3dex2e.apk
  ```
 
</details>

 * To build for sm64ex platforms, [click here](https://github.com/sm64pc/sm64ex/blob/nightly/README.md).
 * To build for Wii U, [click here](https://github.com/aboood40091/sm64-port/blob/master/README.md). (TARGET_WII_U=1)
 * To build for 3DS, [click here](https://github.com/sm64-port/sm64_3ds/blob/master/README.md). (TARGET_N3DS=1)
 * To build for Switch, [click here](https://github.com/fgsfdsfgs/sm64ex/blob/switch/README.md). (TARGET_SWITCH=1)
