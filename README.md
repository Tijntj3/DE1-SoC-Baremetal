# DE1-SoC-Baremetal

This github page was set up to provide an embedded coding environment with the Terasic DE1-SoC board as the target platform.
FPGA peripherals are connected up so everything can be accessed through this embedded environment.

## Licenses

As baremetal debugging on a Intel FPGA+HPS chip can only be done through its SoC EDS Suite, an active license of the ARM Development Studio is required. However a 30-day evaluation license can be acquired once per ARM account. The embedded command shell/HWlibs that come with the suite, and are also required for the demo, do not need an active license.

## Demo application summary

The Hex_disco project provided with this guide aims to be a demonstration of controlling FPGA-side peripherals through a C application running on the HPS. The demo shows a simple animation on the HEX displays and LEDs. The animation has different modes which can be set using the switches:
| Mode | Switch value (Hex) | Description |
| ------ | ------ | ------ |
| Default | 0x0 | The default animation will play. |
| Manual | 0x1 | The animation pauzes and each frame is manually controlled by using the buttons. Button 3 will return 1 frame and button 2 will advance 1 frame. |
| Fast | 0x2 | The default animation will play, but 10 times faster. |
| Slow | 0x4 | The default animation will play, but 10 times slower. |
| Reverse | 0x7 | The default animation will play, but it is reversed. |

The simplified steps needed to be taken in order to run this demo are:

1. Configure the HPS and setup the AXI bridge between the HPS and FPGA by means of a FPGA program
2. Setup a U-boot preloader on the HPS that initializes RAM and loads/runs the C application from it

The more detailed instructions of how to run this demo are shown in the next chapter.

## Installation

It is strongly recommended to use Linux. If any changes want to be made to the hardware configuration, a new version of U-Boot will have to be generated, which can only be done on Linux.
For this project a Windwos hosted VM of Ubuntu 18.04 LTS was used.

### Set-up the DE1-SoC board

For this project, the FPGA portion will either be programmed by the EEPROM on the board, or over the USB-Blaster II interface.
To enable this, set the MSEL pins on the back of the board as following:

| Board Reference | Signal Name | Description | Value |
| ------ | ------ | ------ | ------ |
| SW10.1 | MSEL0 | Use these pins to set the FPGA Configuration scheme | ON ("0") |
| SW10.2 | MSEL1 | Use these pins to set the FPGA Configuration scheme | OFF ("1") |
| SW10.3 | MSEL2 | Use these pins to set the FPGA Configuration scheme | ON ("0") |
| SW10.4 | MSEL3 | Use these pins to set the FPGA Configuration scheme | ON ("0") |
| SW10.5 | MSEL4 | Use these pins to set the FPGA Configuration scheme | OFF ("1") |
| SW10.6 | N/A | N/A | N/A |

The USB-Blaster II interface is the only connection to the board that is needed.

### Install Ubuntu dependencies

As it is not well documented which dependencies are needed for Quartus / SoC EDS on Ubuntu, install the following tools and libraries

```sh
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install -y gcc make perl git flex bison
```

Check whether your system architecture is ```i1386```, if not, change the following command accordingly

```sh
dpkg --print-foreign-architectures
sudo apt-get install -y libc6:i386 libstdc++6:i386 libfontconfig1:i386 libfreetype6:i386 libice6:i386 lib32ncurses5 zlib1g:i386 libusb-0.1-4:i386
```

### Install SoC EDS and ARM Development Studio

The installation instructions to install SoC EDS and ARM Development Studio can be found on this [Rocketboards.org](https://rocketboards.org/foswiki/Documentation/SoCEDS) guide.

### Copy git contents

```sh
git pull https://github.com/Tijntj3/DE1-SoC-Baremetal
```

### Program FPGA

As mentioned at the beginning of this guide, the FGPA can both be programmed in a volatile way and non-volatile way.
To program the FPGA on a non-volatile way, you will need to convert the .SOF file found in ```Hex_disco/hw/quartus/output_files/Baremetal_Setup.sof``` to a .JIC file. This can be done in Quartus with the "Convert programming file" option.

To program the FPGA using the .SOF file, open the existing Quartus project and open the programmer (Tools > Programmer)
You can then select the FPGA as target with the ```Hex_disco/hw/quartus/output_files/Baremetal_Setup.sof``` file as input file.

### Toolchains

For this project, the Linaro 7.5.0 arm-eabi toolchain is recommended ([Download](https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-eabi/gcc-linaro-7.5.0-2019.12-x86_64_arm-eabi.tar.xz))

Export this to your preferred location and import this toolchain into the ARM Development Studio

### Setup the demo software project

After copying these git contents, the project can be imported in ARM DS when selecting ```Hex_disco/sw/hps/application``` as the application directory
Make sure the newly imported Linaro toolchain is configured for this project.

Check if all project properties are setup properly:
Under "C/C++ Build > Settings > GCC C Compiler 7.5.0 [arm-eabi] > Symbols" :
Make sure ```soc_cv_av``` is under "Defined Symbols"
Under "C/C++ Build > Settings > GCC C Compiler 7.5.0 [arm-eabi] > Includes" :
Make sure the following folders are present:

```
"${workspace_loc:/${ProjName}/inc}"
~/intelFPGA/20.1/embedded/ip/altera/hps/altera_hps/hwlib/include
~/intelFPGA/20.1/embedded/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av
```

Next step is to setup the debug configuration. Create one with the following parameters:

- Target: "Intel SoC FPGA > Cyclone V SoC (Dual Core) > Bare Metal Debug > Debug Cortex-A9_0"
- Target Connection: "USB-Blaster" (Your board should be discoverable if connected and powered up)
- Debugger: Select "Connect only" at "Run control"
- Debugger: Tick the box "Run debug initialization debugger script (.ds / .py)"
- Debugger: Enter: ```${workspace_loc:/Baremetal_Hex_Disco/ds_script/debug_setup.ds}``` below the "Run debug initialization debugger script (.ds / .py)" box

After these steps, one should be able to build and debug the demo project above

## AXI bridge

The AXI bridge used for this demo is configured through Quartus Prime's Platfrom designer (QSYS for older versions) using the ```Aria V/Cyclone V Hard Processor System``` and ```PIO``` IPs. Were one to make their own HPS application using this demo as a reference, these are the addresses at which the peripherals are located:

| Peripherals | Start address | End address |
| ------ | ------ | ------ |
| HEX_5 | 0x00 | 0x0F |
| HEX_4 | 0x10 | 0x1F |
| HEX_3 | 0x20 | 0x2F |
| HEX_2 | 0x30 | 0x3F |
| HEX_1 | 0x40 | 0x4F |
| HEX_0 | 0x50 | 0x5F |
| BUTTONS | 0x60 | 0x6F |
| LEDS | 0x70 | 0x7F |
| SWITCHES | 0x80 | 0x8F |
*Note that these addresses are on top of the base AXI address of 0xC0000000*

These addresses can also be found in the ```Hex_disco/sw/hps/application/inc/hps_soc_system.h``` header file.
