#!/bin/sh

STATE_FILE=/tmp/udisk_state
MNT_DIR=/mnt/udisk

echo "hotplug : /dev/$MDEV remove!" > /dev/console

umount -l ${MNT_DIR}

echo "0:/dev/$MDEV" > ${STATE_FILE}

