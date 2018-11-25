#!/bin/sh

wpa_supplicant -D wext -iwlan0 -c/etc/wpa_supplicant.conf &
udhcpc -iwlan0 &

