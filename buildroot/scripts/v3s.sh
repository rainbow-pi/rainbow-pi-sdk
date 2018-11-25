#!/bin/sh

if [ $# != 2 ]; then
    echo Usage: $0 "[opencv] [clean|build|config|nfs|build-opencv3]"
    exit 0
fi

OUTPUT=outputs/v3s/$1/

if [ ! -d ${OUTPUT} ]; then
    echo ${OUTPUT} "doesn't exist!!!"
    exit 1
fi

# NFSROOT=/home/dev/sunxi/fs/nfs/buildroot-v3s-$1
COMMON=/home/dev/sunxi/fs/nfs/buildroot-v3s-common/
NFSROOT=/home/dev/sunxi/fs/nfs/buildroot-v3s-uclibc/
PACKROOT=/home/dev/v3smv/spinand/camdroid/out/target/product/tiger-spinand-standard/system/

DATE=`date +%Y%m%d%H%M%S`

if [ $# != 2 ]; then
    echo $0: usage: $0 $1 "[clean|build|config|nfs]"
    exit 1
fi

if [ $2 == "clean" ]; then
    echo "Clean ..."
#    if [ -f ${OUTPUT}.config ]; then
#	cp ${OUTPUT}.config cfgs/${OUTPUT}-config-${DATE}
#    fi
    rm -fr ${OUTPUT}*
    rm -f ${OUTPUT}.br-external.mk
    rm -f ${OUTPUT}.config.old
    rm -f ${OUTPUT}..config.tmp
#    if [ -f cfgs/${OUTPUT}-config-${DATE} ]; then
#	cp cfgs/${OUTPUT}-config-${DATE} ${OUTPUT}.config
#    fi
    echo "Done!"
    exit 0
elif [ $2 == "build" ]; then
    echo "Building ... "
    make O=${OUTPUT}
elif [ $2 == "config" ]; then
    echo "Config ... "
    make O=${OUTPUT} menuconfig
elif [ $2 == "build-opencv3" ]; then
    echo "Building opencv3"
    make O=${OUTPUT} opencv3-rebuild &&
	cp ${OUTPUT}build/opencv3-3.3.0/buildroot-build/lib/* ${NFSROOT}usr/lib
elif [ $2 == "nfs" ]; then
    echo "NFS ... "
    sudo rm -fr ${NFSROOT} && \
	mkdir ${NFSROOT} && \
	sudo tar xjvf ${OUTPUT}images/rootfs.tar.bz2 -C ${NFSROOT} && \
	sudo chown -R dev:dev ${NFSROOT} && \
	cp ${COMMON}etc/wpa_supplicant.conf ${NFSROOT}etc/wpa_supplicant.conf && \
	cp ${COMMON}etc/hostapd.conf ${NFSROOT}etc/hostapd.conf && \
	cp ${COMMON}etc/init.d/S99camera ${NFSROOT}etc/init.d/S99camera && \
	cp ${COMMON}root/v3s-*.sh ${NFSROOT}root/ && \
	ln -s cv2.cpython-36m-arm-linux-gnueabihf.so ${NFSROOT}usr/lib/python3.6/site-packages/cv2.so

    sudo rm -fr ${PACKROOT} && \
	mkdir ${PACKROOT} && \
	sudo tar xjvf ${OUTPUT}images/rootfs.tar.bz2 -C ${PACKROOT} && \
	sudo chown -R dev:dev ${PACKROOT} && \
	cp ${COMMON}etc/wpa_supplicant.conf ${PACKROOT}etc/wpa_supplicant.conf && \
	cp ${COMMON}etc/hostapd.conf ${PACKROOT}etc/hostapd.conf && \
	cp ${COMMON}etc/init.d/S99camera ${NFSROOT}etc/init.d/S99camera && \
	cp ${COMMON}root/v3s-*.sh ${PACKROOT}root/ && \
	ln -s cv2.cpython-36m-arm-linux-gnueabihf.so ${PACKROOT}usr/lib/python3.6/site-packages/cv2.so	
    
    exit 0
    
#    sudo rm -fr ${NFSROOT} && \
#    mkdir ${NFSROOT} && \
#    sudo tar xjvf ${OUTPUT}images/rootfs.tar.bz2 -C ${NFSROOT} && \
#    sudo chown -R dev:dev ${NFSROOT}root && \
#    sudo chown -R dev:dev ${NFSROOT}usr && \
    #    sudo chown -R dev:dev ${NFSROOT}etc &&
    
#    sudo ln -s /usr/lib/python3.6/site-packages/cv2.cpython-36m-x86_64-linux-gnu.so ${NFSROOT}usr/lib/python3.6/site-packages/cv2.so &&
#    cp -dr /home/dev/fs/nfs/buildroot-base/root/* ${NFSROOT}root/
    exit 0
else
    echo $0: usage: $0 "[build|config|nfs]"
fi

# make O=output-mvd3-minimal busybox-menuconfig
