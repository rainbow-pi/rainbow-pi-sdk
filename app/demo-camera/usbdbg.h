/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * usbdbg.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __USBDBG_H__
#define __USBDBG_H__

#include "imutil.h"

int usbdbg_connect(void);
void usbdbg_close(void);
int usbdbg_send(const uint8_t *buf, int size);
int usbdbg_send_jpeg(const char *title, const char *jpeg_buffer, int w, int h, int size);
int usbdbg_send_image(const char *title, image_t *img, int quality);

#endif
