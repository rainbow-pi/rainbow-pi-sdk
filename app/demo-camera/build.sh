#!/bin/sh

source ${RAINBOWPI_SDK_DIR}env-qt
NFSROOT=/home/dev/fs/nfs/rainbow-pi/

make CROSS_COMPILE=${BR_CROSS_COMPILE} -j 6 demo-camera
