#!/bin/sh

OUTDIR=./output-rainbow-pi-baseline/

mkdir -p ${OUTDIR}

if [ ! -f ${OUTDIR}.config ]; then
    cp ${BUILDROOT_DIR}../configs/buildroot.config.qt ${OUTDIR}.config
    make O=${OUTDIR} oldconfig
fi

make O=${OUTDIR}

exit 0

