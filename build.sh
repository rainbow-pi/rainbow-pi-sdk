#!/bin/bash

#
# This file is part of the Rainbow Pi project.
# Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
# This work is licensed under the MIT license, see the file LICENSE for details.
#

#
# https://mvdevice.taobao.com   is our E-Shop
#

USERNAME=`echo $USER`
GROUPNAME=`id -gn ${USERNAME}`

mkdir -p output/
mkdir -p output/image/
mkdir -p output/rootfs/

if [ "x${RAINBOWPI_SDK_DIR}" = "x" ]; then
    echo "# "
    echo "# You should set RAINBOWPI_SDK_DIR environment variable correctly!"
    echo "# "
    echo "# See : https://github.com/rainbow-pi/rainbow-pi-sdk for details!"
    echo "# "    
    exit 1
fi

if [ ! -d ${RAINBOWPI_SDK_DIR}/buildroot -o ! -d ${RAINBOWPI_SDK_DIR}/tools/pack ]; then
    echo "# "
    echo "# You should set RAINBOWPI_SDK_DIR environment variable correctly!"
    echo "# "
    echo "# See : https://github.com/rainbow-pi/rainbow-pi-sdk for details!"
    echo "# "
    exit 1
fi

export BOARD=tiger-spinand-standard

# buildroot
export BUILDROOT_DIR=${RAINBOWPI_SDK_DIR}/buildroot/
# export BUILDROOT_OUTPUT_DIR=${BUILDROOT_DIR}output-rainbow-pi-baseline/
export BUILDROOT_OUTPUT_DIR=${BUILDROOT_DIR}output-rainbow-pi-qt/
export BUILDROOT_ROOTFS_FILE=${BUILDROOT_OUTPUT_DIR}images/rootfs.tar.bz2

export APP_COMPILER_DIR=${BUILDROOT_OUTPUT_DIR}host/bin/

# config file
export SDK_CONFIG_DIR=${RAINBOWPI_SDK_DIR}/configs/

# application
export APP_DIR=${RAINBOWPI_SDK_DIR}/app/

# u-boot
export UBOOT_DIR=${RAINBOWPI_SDK_DIR}/u-boot-2011.09/

# linux
export KERNEL_DIR=${RAINBOWPI_SDK_DIR}/linux-3.4/
export KERNEL_TOOLCHAINS_DIR=${RAINBOWPI_SDK_DIR}/tools/external-toolchain/bin/
export KERNEL_CROSS_COMPILE=${KERNEL_TOOLCHAINS_DIR}arm-linux-gnueabi-
export UBOOT_CROSS_COMPILE=${KERNEL_CROSS_COMPILE}

export PREBUILT_DIR=${RAINBOWPI_SDK_DIR}/prebuilt/
export OUTPUT_DIR=${RAINBOWPI_SDK_DIR}/output/

export HOSTTOOLS_DIR=${RAINBOWPI_SDK_DIR}/tools/bin/
export PACKTOOLS_DIR=${RAINBOWPI_SDK_DIR}/tools/pack/

export ROOTFS_DIR=${OUTPUT_DIR}rootfs/
export ROOTFS_OVERRIDE_DIR=${PREBUILT_DIR}rootfs-override/

copy_file_list=(
    ${ROOTFS_OVERRIDE_DIR}etc/wpa_supplicant.conf:${ROOTFS_DIR}etc/wpa_supplicant.conf
    ${ROOTFS_OVERRIDE_DIR}etc/hostapd.conf:${ROOTFS_DIR}etc/hostapd.conf
    ${ROOTFS_OVERRIDE_DIR}etc/udhcpd.conf:${ROOTFS_DIR}etc/udhcpd.conf
    ${ROOTFS_OVERRIDE_DIR}etc/mdev.conf:${ROOTFS_DIR}etc/mdev.conf
    ${ROOTFS_OVERRIDE_DIR}etc/init.d/S50sshd:${ROOTFS_DIR}etc/init.d/
    ${ROOTFS_OVERRIDE_DIR}etc/init.d/S90camera:${ROOTFS_DIR}etc/init.d/
    ${ROOTFS_OVERRIDE_DIR}etc/init.d/S90wifiap:${ROOTFS_DIR}etc/init.d/_S90wifiap
    ${ROOTFS_OVERRIDE_DIR}etc/init.d/S90wifista:${ROOTFS_DIR}etc/init.d/_S90wifista
    ${ROOTFS_OVERRIDE_DIR}etc/init.d/S99appstart:${ROOTFS_DIR}etc/init.d/
    ${ROOTFS_OVERRIDE_DIR}etc/ssh/sshd_config:${ROOTFS_DIR}etc/ssh/
    ${ROOTFS_OVERRIDE_DIR}root/*.sh:${ROOTFS_DIR}root/
    ${ROOTFS_OVERRIDE_DIR}root/demo-h264enc:${ROOTFS_DIR}usr/bin/
    ${APP_DIR}demo-camera/demo-camera:${ROOTFS_DIR}usr/bin/
    ${APP_DIR}demo-qt/digitalclock:${ROOTFS_DIR}root/
    ${PREBUILT_DIR}libs/*:${ROOTFS_DIR}lib/
)

function copy_file_to_rootfs()
{
    for line in ${copy_file_list[@]} ; do
	srcfile=`echo $line | awk -F: '{print $1}'`
	dstfile=`echo $line | awk -F: '{print $2}'`
	cp -drf $srcfile $dstfile 2>/dev/null
    done
}

function build_buildroot()
{
    (cd ${BUILDROOT_DIR} && ./build-qt.sh)
    [ $? -ne 0 ] && echo "build buildroot Failed" && return 1
    cd ${RAINBOWPI_SDK_DIR}
    return 0
}

function build_uboot_spinandflash_or_emmc()
{
    if [ ! -d ${UBOOT_DIR} ]; then
	git clone https://github.com/rainbow-pi/u-boot-2011.09.git
	[ $? -ne 0 ] && echo "download u-boot failed" && return 1
    fi
    (cd ${UBOOT_DIR} && ./build.sh -p sun8iw8p1_spinand_emmc)
    [ $? -ne 0 ] && echo "build u-boot Failed" && return 1
    return 0
}

function build_uboot_norflash()
{
    if [ ! -d ${UBOOT_DIR} ]; then
	git clone https://github.com/rainbow-pi/u-boot-2011.09.git
	[ $? -ne 0 ] && echo "download u-boot failed" && return 1
    fi
    (cd ${UBOOT_DIR} && ./build.sh -p sun8iw8p1_nor)
    [ $? -ne 0 ] && echo "build u-boot Failed" && return 1
    (cd ${UBOOT_DIR} && ./build.sh -p sun8iw8p1)
    [ $? -ne 0 ] && echo "build u-boot Failed" && return 1    
    return 0
}

function build_uboot()
{
    #    build_uboot_norflash
    echo "build_uboot ..."
    if [ ! -f ${OUTPUT_DIR}.stamp_uboot_built ]; then
	build_uboot_spinandflash_or_emmc
	[ $? -ne 0 ] && return 1
	touch ${OUTPUT_DIR}.stamp_uboot_built
    fi

    echo "build_uboot done!"
    return 0
}

function build_kernel()
{
    echo "build_kernel ..."

    if [ ! -d ${KERNEL_DIR} ]; then
	git clone https://github.com/rainbow-pi/linux-3.4.git
	[ $? -ne 0 ] && echo "download kernel failed" && return 1
    fi
    
    (cd ${KERNEL_DIR}; ./build.sh kernel)
    [ $? -ne 0 ] && echo "build kernel failed" && return 1
	
    (cd ${KERNEL_DIR}; ./build.sh modules)
    [ $? -ne 0 ] && echo "build kernel modules failed" && return 1

    echo "build_kernel done!"
    return 0
}

function build_kernel_modules()
{
    (cd ${KERNEL_DIR}; ./build.sh modules)
    [ $? -ne 0 ] && echo "build kernel modules failed" && return 1

    return 0
}

function deploy_nfs()
{
    # NFS for debug
    export NFS_DIR=/home/dev/fs/nfs/rainbow-pi/

    # copy
    sudo rm -fr ${NFS_DIR}*

    mkdir -p ${NFS_DIR} && \
	sudo cp -dr ${ROOTFS_DIR}* ${NFS_DIR} && \
	sudo chown -R ${USERNAME}:${GROUPNAME} ${NFS_DIR} &&
	return 0

    return 1	
}

function print_error()
{
    echo
    echo -e "\033[47;31mERROR: $*\033[0m"
    echo
}

function deploy_rootfs()
{
    if [ ! -f ${BUILDROOT_ROOTFS_FILE} ]; then
	print_error "*** ${BUILDROOT_ROOTFS_FILE} missing!"
	print_error "You should build buildroot first."
	print_error "run ./build.sh buildroot"
	
	return 1
    fi

    sudo rm -fr ${ROOTFS_DIR} && \
	mkdir ${ROOTFS_DIR} && \
	sudo tar xjvf ${BUILDROOT_ROOTFS_FILE} -C ${ROOTFS_DIR} && \
	sudo chown -R ${USERNAME}:${GROUPNAME} ${ROOTFS_DIR} && \
	copy_file_to_rootfs && \
	return 0

    return 1
}

function build_rootfs_image()
{
    echo "build_rootfs_image (ext4 image)..."

    ${HOSTTOOLS_DIR}make_ext4fs -s \
		    -l 90M \
		    ${OUTPUT_DIR}image/rootfs-ext4.img \
		    ${ROOTFS_DIR}
    [ $? -ne 0 ] && echo "build rootfs image (ext4 image) failed" && return 1
    
    echo "build_rootfs_image (ext4 image)... done!"
    return 0
}

function pack()
{
    echo "pack ..."
    cd ${PACKTOOLS_DIR} &&  ./pack -c sun8iw8p1 -p camdroid -b ${BOARD} -e spinand
    [ $? -ne 0 ] && echo "build rootfs image (ext4 image) failed" && return 1
    echo "pack ... done!"
    return 0
}

function clean()
{
    echo
    echo "Clean ......"
    echo
    
#   rm -f ${PACKTOOLS_DIR}chips/sun8iw8p1/bin/*
    rm -f ${OUTPUT_DIR}image/*.img
    rm -fr ${OUTPUT_DIR}rootfs/*
    rm -f ${PACKTOOLS_DIR}rainbow-pi.img
    rm -fr ${PACKTOOLS_DIR}out/*
    
    # force rebuild uboot
    rm -f ${OUTPUT_DIR}.stamp_*
    # force rebuild kernel
    make -C ${KERNEL_DIR} distclean

    return 0
}

if [ $# == 0 ]; then
    echo "Usage : ./build.sh all"
    exit 0
elif [ $# -gt 0 ]; then
    if [ $1 == 'buildroot' ]; then
	build_buildroot
    fi
    
    if [ $1 == 'uboot' ]; then
	build_uboot
    fi

    if [ $1 == 'uboot-rebuild' ]; then
	rm -f ${OUTPUT_DIR}.stamp_uboot_built
	build_uboot
    fi
    
    if [ $1 == 'kernel' ]; then
	build_kernel
    fi

    if [ $1 == 'kernel-config' ]; then
	if [ ! -f ${KERNEL_DIR}.config ]; then
	    echo "Copy linux config file."
	    cp ${KERNEL_DIR}arch/arm/configs/rainbowpi_defconfig
	fi
	
	(cd ${KERNEL_DIR} && make ARCH=arm menuconfig)
	[ $? -ne 0 ] && echo "kernel menuconfig Failed" && cd ${RAINBOWPI_SDK_DIR}
	cd ${RAINBOWPI_SDK_DIR}
    fi    
	
    if [ $1 == 'rootfs' ]; then
	deploy_rootfs && build_kernel
    fi

    if [ $1 == 'nfs' ]; then
	deploy_nfs
    fi
    
    if [ $1 == 'image' ]; then
	build_rootfs_image
    fi
    
    if [ $1 == 'pack' ]; then
	pack
    fi

    if [ $1 == 'clean' ]; then
	clean
    fi
    
    if [ $1 == 'all' ]; then
	deploy_rootfs && build_uboot &&	build_kernel && build_rootfs_image && pack
    fi

    if [ $1 == 'rebuildall' ]; then
	clean && deploy_rootfs && build_uboot && build_kernel && build_rootfs_image && pack
    fi
fi    
