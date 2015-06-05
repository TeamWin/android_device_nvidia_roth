#include <stdlib.h>

// These are paths to folders in /sys which contain "uevent" file
// need to init this device.
// MultiROM needs to init framebuffer, mmc blocks, input devices,
// some ADB-related stuff and USB drives, if OTG is supported
// You can use * at the end to init this folder and all its subfolders
const char *mr_init_devices[] =
{
 "/sys/class/graphics/fb0",

 // Internal SD
 "/sys/block/mmcblk0",
 "/sys/devices/platform/sdhci-tegra.3",
 "/sys/devices/platform/sdhci-tegra.3/mmc_host/mmc0",
 "/sys/devices/platform/sdhci-tegra.3/mmc_host/mmc0/mmc0:0001",
 "/sys/devices/platform/sdhci-tegra.3/mmc_host/mmc0/mmc0:0001/block/mmcblk0*",

 // External SD
 "/sys/block/mmcblk1",
 "/sys/devices/platform/sdhci-tegra.2",
 "/sys/devices/platform/sdhci-tegra.2/mmc_host/mmc1",
 "/sys/devices/platform/sdhci-tegra.2/mmc_host/mmc1/mmc1:1234",
 "/sys/devices/platform/sdhci-tegra.2/mmc_host/mmc1/mmc1:1234/block/mmcblk1*",

 // SD block devices
 "/sys/bus/mmc",
 "/sys/bus/mmc/drivers/mmcblk",
 "/sys/bus/sdio/drivers/bcmsdh_sdmmc",
 "/sys/module/mmc_core",
 "/sys/module/mmcblk",
 "/sys/module/sdhci",

 // Support currently non-operational
 /*"/sys/devices/virtual/input*",
 "/sys/devices/virtual/misc/uinput",
 "/sys/bus/spi",
 "/sys/bus/spi/drivers/rm_ts_spidev",
 "/sys/devices/platform/tegra11-spi.0",
 "/sys/devices/platform/tegra11-spi.0*",
 "/sys/bus/platform/drivers/tegra11-spi",
 "/sys/devices/virtual/misc/raydium_ts",
 "/sys/bus/hid",
 "/sys/bus/hid/drivers/hid-multitouch",*/

 // Adb
 "/sys/class/tty/ptmx",
 "/sys/devices/virtual/misc/android_adb",
 "/sys/devices/virtual/android_usb/android0/f_adb",
 "/sys/bus/usb",

 // External harddrive
 "/sys/devices/platform/tegra-ehci.2*",

 // Android system keys
 "/sys/devices/platform/gpio-keys.0",
 "/sys/devices/platform/gpio-keys.0*",
 "/sys/bus/platform/drivers/gpio-keys",

 // Gamepad
 "/sys/devices/platform/tegra-ehci.2/usb1/1-1/1-1:1.0/input/input3",
 "/sys/devices/platform/tegra-ehci.2/usb1/1-1/1-1:1.0/input/input3*",

 NULL
};
