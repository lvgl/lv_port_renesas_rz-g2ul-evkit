# LVGL ported to Renesas RZ/G2UL-EVKIT

## Overview

The Renesas RZ/G2UL is a general-purpose MPU with a Cortex-A55 (1.0 GHz).
This evaluation kit consists of
both a SoM (System on Module) which carries the RZ/G2UL MPU, as well as a carrier board
which carries the SoM. The SoM complies with the SMARC v2.1 stardard. The carrier board
features IO useful for MPU applications such as a display interface (Parallel-IF)
and included parallel-to-Micro-HDMI bridge, 2 ethernet ports,
headphone and microphone jacks, USB serial terminal, USB host, camera input,
an additional Micro SD card slot, and exposed GPIO headers.

## Buy

You can purchase the RZ/G2UL-EVKIT from several sources. The RZ/G2UL is also sold as
SoM-only if you are using a different carrier board or already have one.

- [Renesas's website](https://www.renesas.com/en/products/microcontrollers-microprocessors/rz-mpus/rzg2ul-evkit-evaluation-board-kit-rzg2ul-mpu)
- [Mouser](https://www.mouser.com/ProductDetail/Renesas-Electronics/RTK9743U11S01000BE?qs=vvQtp7zwQdM9TF1mvTYlYA%3D%3D)
- [DigiKey](https://www.digikey.com/en/products/detail/renesas-electronics-corporation/RTK9743U11S01000BE/18099644)

## Benchmark

The benchmark was run with the v8.3 fbdev driver.

<a href="https://www.youtube.com/watch?v=VnynDLR36Xc">
    <img src="https://github.com/user-attachments/assets/c898dd69-1c3f-4937-88be-503933181776" width="75%">
</a>

| Name                      | Avg. CPU | Avg. FPS | Avg. time | render time | flush time |
| :------------------------ | -------: | -------: | --------: | ----------: | ---------: |
| Empty screen              | 19%      | 33       | 5         | 2           | 3          |
| Moving wallpaper          | 31%      | 33       | 9         | 6           | 3          |
| Single rectangle          | 4%       | 33       | 0         | 0           | 0          |
| Multiple rectangles       | 8%       | 33       | 1         | 1           | 0          |
| Multiple RGB images       | 29%      | 33       | 8         | 5           | 3          |
| Multiple ARGB images      | 60%      | 33       | 18        | 15          | 3          |
| Rotated ARGB images       | 98%      | 16       | 69        | 66          | 3          |
| Multiple labels           | 55%      | 33       | 13        | 10          | 3          |
| Screen sized text         | 3%       | 33       | 0         | 0           | 0          |
| Multiple arcs             | 43%      | 33       | 12        | 9           | 3          |
| Containers                | 34%      | 34       | 7         | 7           | 0          |
| Containers with overlay   | 90%      | 33       | 30        | 27          | 3          |
| Containers with opa       | 50%      | 33       | 11        | 11          | 0          |
| Containers with opa_layer | 63%      | 34       | 19        | 19          | 0          |
| Containers with scrolling | 83%      | 33       | 24        | 21          | 3          |
| Widgets demo              | 42%      | 33       | 12        | 11          | 1          |
| All scenes avg.           | 44%      | 32       | 14        | 13          | 1          |

## Specification

### CPU and Memory
- **MCU:** Arm Cortex-A55 (1.0 GHz)
- **RAM:** 1GB DDR4 SDRAM
- **Flash:** Micro SD card, 64GB eMMC, 16MB QSPI flash
- **GPU:** None

### Display and Touch
- **Resolution:** Tested on 1920x1080 (1280x800 virtual resolution)
- **Interface:** Micro-HDMI via the included parallel interface bridge
- **Color Depth:** 32-bit
- **Touch Pad:** USB touch input supported

### Connectivity
- 2 ethernet ports
- headphone and microphone jacks
- USB port
- camera input
- additional Micro SD card slot
- GPIO headers
- USB serial terminal

## Getting started

### Hardware setup
- Insert a prepared Micro SD card in the slot on the SoM (not the slot on the carrier board).
  See the next section for details about obtaining an OS image for the Micro SD card.
- Connect an HDMI display with a Micro-HDMI cable via the parallel-to-Micro-HDMI bridge
  which connects to the ribbon cable connector on the SoM. Do not try to use the Micro-HDMI
  port on the carrier board marked "CN13". If you use an HDMI-powered display, ensure
  the board's power adapter provides enough power for both the board and the display.
- Connect a USB mouse to interract with LVGL UIs. Optionally use a USB hub to connect
  a keyboard too. There is no desktop so there is no default purpose for a keyborad.
- Optionally connect an ethernet cable to either of the two ethernet ports.
- Optionally connect the micro USB port marked "SER 3 UART"/"CN14" to your computer.
- Connect a power adapter to the USB-C port. It was tested with a 5V-3A power supply and
  also with a PC USB-C port. See the next section about turning the board on and off.

### Software setup

These steps are based on the [Renesas RZ/G HMI SDK Getting Started guide](https://renesas-rz.github.io/rzg_hmi_sdk/latest/getting_started/).

1. Download [RZ/G HMI SDK Version 2.3.0.0](https://www.renesas.com/en/document/sws/rzg-hmi-software-development-kit-version-2300)
2. Extract the zip file.
3. Navigate into the extracted directory and extract the nested zip file called `image-file_rzg2ul_hmi-sdk_v2.3.0.0.zip`
   which contains `core-image-bsp-smarc-rzg2ul.wic.bmap` and `core-image-bsp-smarc-rzg2ul.wic.gz`.
4. Insert a Micro SD card into your PC and flash the image to it.
   - On a Linux PC, first ensure all partitions on the card are unmounted.
     See [the officical guide](https://renesas-rz.github.io/rzg_hmi_sdk/latest/getting_started/) for more details about that.
     Use `bmaptool` (`sudo apt install bmap-tools`) to flash the SD card with the command
     ```shell
     sudo bmaptool copy core-image-bsp-smarc-rzg2ul.wic.gz <path to block device>
     ```
     Where `<path to block device>` is the Micro SD card block device. It may be `/dev/mmcblk0`. Take care to ensure
     you do not accidentally overwrite a system drive.
   - On a Windows PC, use Win32 Disk Imager or balenaEtcher (you can also use this on a Linux PC, but `bmaptool` may be faster)
     to flash the file called `core-image-bsp-smarc-rzg2ul.wic.gz`.
5. Set the DIP switches as in [the officical guide](https://renesas-rz.github.io/rzg_hmi_sdk/latest/getting_started/).
   SW1 is `111` and SW11 is `1101`
6. Set up the board as in the "Hardware setup" section. Press the red power button (SW9) for 1 second.

### Run the project

1. Prepare a Linux development environment on a Linux PC or in a Docker container, WSL, or similar. Ensure the packages
   `python3`, `xz`, `file`, and `make` are installed. I.e.
   ```shell
   sudo apt update
   sudo apt install python3 xz-utils file make
   ```
2. In the extracted SDK zip from the previous section, extract the nested zip file called
   `toolchain-installer_rzg2ul_hmi-sdk_v2.3.0.0.zip`.
3. Run the below command and follow the prompts to install the cross-compiler.
   ```shell
   sudo sh poky-glibc-x86_64-core-image-bsp-aarch64-smarc-rzg2ul-toolchain-3.1.31.sh
   ```
4. From now on, every time you open a new terminal, you will need to run the following command to configure your shell's
   environment variables for building applications for RZ/G2UL.
   ```shell
   source /opt/poky/3.1.31/environment-setup-aarch64-poky-linux
   ```
5. Build the application.
   ```shell
   make -j$(nproc)
   ```
6. Now you can transfer the binary application `lvgl_demo_benchmark` to the board. You can do it any of the following ways.
   - If connected to ethernet you can transfer the file over LAN.
     ```shell
     scp lvgl_demo_benchmark root@<ip-address>:/home/root/
     ```
     where `<ip-address>` is replaced by the local IP address of the board. You can find it with
     ```shell
     ip a
     ```
     and inspect the `eth0`/`eth1`->`inet` field.
     The file will be sent to `/home/root/`.
   - You can mount the SD card on your PC and put the file into the image's filesystem anywhere you like.
     There are two partitions on the SD card. Go to the partition called `root`. A good place to put the application is
     `/home/root/`. You may need need root privileges on your PC to access this directory. Make sure you unmount
     the SD card before removing to ensure the changes are synced fully.
   - Use a USB drive to transfer the file.
7. Run the application from the serial terminal. First, you should stop the demo launcher if it's running.
   ```shell
   systemctl stop demo-launcher
   ```
   Then, run the application.
   ```shell
   ./lvgl_demo_benchmark
   ```

To delete all the build outputs, run
```shell
make clean
```
or
```shell
git clean -Xf .
```

### Debugging

Unfortunately `gdb` and `gdbserver` are not installed in the image. "`printf`" debugging will have to suffice.

## Notes

See these official Renesas resources.

- [Renesas RZ/G HMI SDK Getting Started guide](https://renesas-rz.github.io/rzg_hmi_sdk/latest/getting_started/)
- [`rzg_hmi_sdk` GitHub repo](https://github.com/renesas-rz/rzg_hmi_sdk)

Continue reading for advanced extra info.

The `rzg_hmi_sdk` repo builds apps by _dynamically_ linking to the `lvgl` and `lv_drivers` system libraries which are resident
in the G2UL's image at `/usr/lib/`. Dynamic linking reduces the size of the executable since the executable
does not actually contain LVGL's internal functions. There are other benefits but it's out of the scope of this README.
In contrast, this `lv_port_renesas_rz-g2ul-evkit` repo _statically_ links `lvgl` because the version
of `lvgl` here is different than the one installed in the G2UL image.
The `lvgl` here ports the v9 benchmark to v8.3. 

The `lv_conf.h` is similar to the one in
`/opt/poky/3.1.31/sysroots/aarch64-poky-linux/usr/include/lvgl/`.
The `rzg_hmi_sdk` repo uses those headers when compiling.

## Contribution and Support

If you find any issues with the development board feel free to open an Issue in this repository. For LVGL related issues (features, bugs, etc) please use the main [lvgl repository](https://github.com/lvgl/lvgl).

If you found a bug and found a solution too please send a Pull request. If you are new to Pull requests refer to [Our Guide](https://docs.lvgl.io/master/CONTRIBUTING.html#pull-request) to learn the basics.

