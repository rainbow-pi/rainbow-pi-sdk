#!/bin/sh

STATE_FILE=/tmp/sdcard_state
MNT_DIR=/mnt/sdcard

echo "hotplug : /dev/$MDEV remove!" > /dev/console

umount -l ${MNT_DIR}

echo "0:/dev/$MDEV" > ${STATE_FILE}

