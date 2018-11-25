/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * netdbg.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __NETDBG_H__
#define __NETDBG_H__

#include "imutil.h"

typedef struct packet_head {
	int w;
	int h;
	int len;
	char title[20];
} packet_head_t;

int netdbg_connect(const char *serverip, uint16_t port);
void netdbg_close(void);
int netdbg_send_jpeg(const char *title, const char *jpeg_buffer, int w, int h, int size);
int netdbg_send_image(const char *title, image_t *img, int quality);
int image_jpeg_compress(image_t *img, image_t *out, int quality);

#endif
