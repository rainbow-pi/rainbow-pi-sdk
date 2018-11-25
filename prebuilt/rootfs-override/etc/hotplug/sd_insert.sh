#!/bin/sh

STATE_FILE=/tmp/sdcard_state
MNT_DIR=/mnt/sdcard

echo "hotplug : /dev/$MDEV insert!" > /dev/console

if [ -e "/dev/$MDEV" ]; then
    mkdir -p ${MNT_DIR}
    mount -rw /dev/$MDEV ${MNT_DIR}

    if [ $? != 0 ]; then
	# 1 : mount failed
	echo "1:/dev/$MDEV" > ${STATE_FILE}
	exit 0
    fi

    if [ ! -f ${MNT_DIR}/hello.txt ]; then
	# 2 : not test card
	echo "2:/dev/$MDEV" > ${STATE_FILE}
	exit 0
    fi

    echo "1234567890" > ${MNT_DIR}/test.txt
    if [ $? != 0 ]; then
	# 3 : write failed
	echo "3:/dev/$MDEV" > ${STATE_FILE}
	exit 0
    fi

    MD5=`md5sum ${MNT_DIR}/test.txt`
    echo ${MD5} > /dev/console
    
    if [ "${MD5}" != "7c12772809c1c0c3deda6103b10fdfa0  ${MNT_DIR}/test.txt" ]; then
	# 4 : writen, but checksum failed
	echo "4:/dev/$MDEV" > ${STATE_FILE}
	exit 0
    fi
    
    echo "9:/dev/$MDEV" > ${STATE_FILE}
fi
