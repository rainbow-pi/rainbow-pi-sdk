#!/bin/sh

NFSROOT=/home/dev/fs/nfs/buildroot-h5-uclibc

# rebuild opencv3 package
make O=output-h5-uclibc opencv3-rebuild

if [ $? != 0 ]; then
    echo "Building failed!"
    exit 1
fi

# copy libs
cp output-h5-uclibc/build/opencv3-3.3.0/buildroot-build/lib/* ${NFSROOT}/usr/lib
cp output-h5-uclibc/build/opencv3-3.3.0/buildroot-build/lib/python3/cv2.cpython-36m-x86_64-linux-gnu.so \
   ${NFSROOT}/usr/lib/python3.6/site-packages/

echo "Deploy to NFS done!"
exit 0
