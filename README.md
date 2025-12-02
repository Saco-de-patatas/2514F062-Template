# About

* 2514F062 / El CheapoPill template project for GNU Arm Embedded Toolchain
* This OEM chip found within extremelly cheap Bluepills and J-LinkOB is also a Megahunt variant of MH2103 with different unlock keys.
* Supported programmers: J-Link, STLink, DAPLink/PyOCD
* Supported IDE: VSCode

# AIR32F103x / MH32F103Ax / MH2103Ax Family - Mentioned for comparison, actually not the same as 2514F062.

| TYPE  | AIR32F103CBT6<br>MH32F103ACBT6<br>MH2103ACBT6 | AIR32F103CCT6<br>MH32F103ACCT6<br>MH2103ACCT6 | AIR32F103RPT6<br>MH32F103ARPT6<br>MH2103ARPT6 |
| ----- | ------------- | ------------- | ------------- |
| Flash | 128K          | 256K          | 256K          |
| RAM   | 32K           | 64K           | 96K           |
| Pack  | lqfp48        | lqfp48        | lqfp64        |

## Note

* OEM marked 2514F062 (Found in cheap J-LinkOBs from Aliexpress)/ Some marked STM32f103C8T6 chips within cheap bluepills... (the real part for these isn't known yet).
  * Very similar to the MH2103Ax (and their aliases). Some differences are present, but all the magic peripherals are there, TRNG and DACs have been tested.
  * PLL over x16 has been changed/undocumented. Still more research (or the disclosure of a private document) is needed.
  * Using PLL x16 and a 16MHz crystal in a cheap bluepill, running at 256MHz is stable (one week of continuous testing at this speed).
  * Megahunt MCUs use to run at 216MHz standard speed.
  * This variant is almost the same from the software aspect of view, minor changes have been implemented to the parent template.
  * The electrical characteristics might be different, be careful when replacing them in production, but as we currently don't know the internal code for the silicon die, this is not a big deal.
* Unlock the hidden 64K+1K RAM
  * It's very likely the gadget you bought (J-LinkOB or El CheapoPill) has 64K+1K RAM - Here is the original hack [Hedley Rainnie's blog](http://www.hrrzi.com/2022/12/the-air32f103.html), it differs from the MH32F103A hack in that the RAM area located at 0x20010000 to 0x20017FFF is turned off (either not existent or disabled).
  * This might also apply to other chips as this looks that Megahunt manufactures the silicon die and other OEM fit it within the final package.
  * The hidden RAM can be unlocked by the same special registers of the MH2103A, however the keys are different. The hack has been integrated into startup_air32f10x.s. Thanks to @deividAlfa for the original integration.
 * Other variants:
  * There is at least another 2 variants sharing the same core as the MH2103x
    * The HL2103A[C] (Plenty of documentation in english)  Visit [HLKP](https:\\www.hlkpint.com) for more information, datasheets, STM32 migration...
    * The networking SoC called W55MH32, with a great amount of documentation, an excellent SDK, and many tutorials out there in internet.

## Documents

[WIKI](https://wiki.luatos.com/chips/air32f103/index.html) | [Datasheet](https://cdn.openluat-luatcommunity.openluat.com/attachment/20220605164850945_AIR32F103%E8%8A%AF%E7%89%87%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C1.0.0.pdf) | [Migrate From STM32](https://wiki.luatos.com/chips/air32f103/switchFromSxx.html) | [Keil SDK And Demos](https://gitee.com/openLuat/luatos-soc-air32f103)

## LuatOS AIR32F103CBT6 EVB - Modified for working with this 2514F062

[EVB Schematis](https://cdn.openluat-luatcommunity.openluat.com/attachment/20220605164915340_AIR32CBT6.pdf) | [PCB](https://wiki.luatos.com/_static/bom/Air32F103.html)

# Project Structure

```
├── Build                       # Build results
├── Examples                    # Example code
│   ├── FreeRTOS                  # FreeRTOS examples
│   └── NonFreeRTOS               # Non-FreeRTOS examples
├── Libraries                   
│   ├── 2514F062Lib            # 2514F062 Peripheral library
│   │   ├── inc                 
│   │   ├── lib
│   │   └── src  
│   ├── CMSIS
│   │   ├── Core                # CMSIS Coretex M core files
│   │   └── DSP                 # CMSIS DSP library
│   ├── Debug                   # For delay and printf support
│   ├── DeviceSupport           # gcc arm startup files
│   │   └── startup
│   │       └── arm-gcc
│   ├── FreeRTOS                # FreeRTOS library
│   ├── Helix                   # Helix MP3 decoder library
│   └── LDScripts               # Link scripts
├── Makefile
├── Misc
│   └── flash.jlink             # JLink script
├── README.cn.md
├── README.md
├── rules.mk                    # Make rules
└── User                        # User application code
```

# Quick Start

## 1. Install GNU Arm Embedded Toolchain

Download toolchains from [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) and uncompress 
```bash
tar xvf gcc-arm-11.2-2022.02-x86_64-arm-none-eabi.tar.xz
cd /opt/gcc-arm/
sudo mv ~/Backup/linux/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/ .
sudo chown -R root:root gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/
```
## 2. Intall SEGGER J-Link Or ST-Flash

Download JLink from [J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink/) and install it

```bash
# installation command for .deb
sudo dpkg -i JLink_Linux_V770a_x86_64.deb
```
The default installation path is */opt/SEGGER*

## 3. Check Out This Repository

```bash
git clone https://github.com/IOsetting/hk32f030m-template.git
```

## 4. Edit Makefile

Edit Makefile, make sure ARM_TOOCHAIN and JLINKEXE point to the correct paths

```makefile
##### Project #####
# Project name
PROJECT 		?= app
# Result folder
BUILD_DIR 		= Build

##### Options #####

# Enable printf float %f support, y:yes, n:no
ENABLE_PRINTF_FLOAT	?= y
# Build with FreeRTOS, y:yes, n:no
USE_FREERTOS	?= n
# Build with CMSIS DSP functions, y:yes, n:no
USE_DSP			?= n
# Build with Helix MP3 lib, y:yes, n:no
USE_HELIX		?= n
# Programmer, jlink, stlink, cmsis-dap, pyocd
FLASH_PROGRM    ?= stlink

##### Toolchains #######

ARM_TOOCHAIN 	?= /opt/gcc-arm/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin
# path to st-flash
ST_FLASH		?= st-flash
# path to JLinkExe
JLINKEXE		?= /opt/SEGGER/JLink/JLinkExe
JLINK_DEVICE	?= STM32F103CB
# path to OpenOCD
OPENOCD			?= openocd
# path to PyOCD
PYOCD_EXE		?= pyocd
PYOCD_DEVICE	?= air32f103cb

##### Paths ############

# Link script for current chip
LDSCRIPT		= Libraries/LDScripts/2514F062cbt6.ld
```

## 5. Compile and Flash

```bash
# Clean
make clean
# Build
make
# Build verbosely
V=1 make
# Flash
make flash
```

# Try Other Examples

More examples can be found in Examples folder, copy and replace the files under User folder to try different examples.
