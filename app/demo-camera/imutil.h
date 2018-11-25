/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * imutil.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __IMUTIL_H__
#define __IMUTIL_H__

typedef struct image {
	int w;
	int h;
	int bpp;
	union {
		uint8_t *pixels;
		uint8_t *data;
	};
} image_t;

typedef struct rectangle {
	int x;
	int y;
	int w;
	int h;
} rectangle_t;

int _imutil_libjpeg_compress_rgb(int bpp, unsigned char **dest_image, int *image_size,
				 unsigned char *input_image, int width, int height, int quality);
int imutil_jpeg_compress_rgb(image_t *img, image_t *out, int quality);
void imutil_crop(int bpp, uint8_t *src, int srcw, int srch, int srcx, int srcy,
		 uint8_t *dst, int dstw, int dsth);
void imutil_clone_roi(image_t *src, image_t *dst, rectangle_t *roi);
#endif

