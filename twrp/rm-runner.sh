#!/sbin/busybox sh
LD_LIBRARY_PATH=/system/lib:/system/lib/hw
export TOUCH_CONF_DIR=/mnt/factory/touchscreen
export TOUCH_DATA_DIR=/data/touchscreen
/system/bin/rm-wrapper