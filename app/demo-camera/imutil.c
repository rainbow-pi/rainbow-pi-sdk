/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * imutil.c
 *     image utilities
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#if 1
#include <turbojpeg.h>
#include <jpeglib.h>
#else
#include <cdjpeg.h>
#endif
#include "imutil.h"

int _imutil_libjpeg_compress_rgb(int bpp, unsigned char **dest_image, int *image_size,
		 unsigned char *input_image, int width, int height, int quality)
{
	int y;
	int line_len;

	unsigned long outsize = 0;

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_ptr[1];

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	jpeg_mem_dest(&cinfo, dest_image, (unsigned long *)image_size);

	cinfo.image_width = width;
	cinfo.image_height = height;
	if (bpp == 2 || bpp == 3 || bpp == 4) {
		/* RGB565, RGB24, RGB32 */
		cinfo.input_components = 3;
		cinfo.in_color_space = JCS_RGB;
	} else {
		/* Grayscale */
		cinfo.input_components = 1;
		cinfo.in_color_space = JCS_GRAYSCALE;
	}
	
        jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

	jpeg_start_compress(&cinfo, TRUE);

	if (bpp == 1)
		line_len = width;
	else
		line_len = width * 3;
	
	/* RGB565 -> RGB24 */
	if (bpp == 1 || bpp == 3) {
		row_ptr[0] = input_image;
	} else if (bpp == 2) {
		int i;
		uint8_t *d = (uint8_t *)input_image;
		uint32_t *s = (uint32_t *)input_image;
			
		for (i = 0; i < width * height; i++) {
			*(d++) = *s >> 16 & 0xff;
			*(d++) = *s >> 8 & 0xff;
			*(d++) = *s >> 0 & 0xff;			
			s++;
		}
		
		row_ptr[0] = input_image;
	} else if (bpp == 4) {
                int i;
		uint8_t *d = (uint8_t *)input_image;
		uint32_t *s = (uint32_t *)input_image;

		for (i = 0; i < width * height; i++) {
			*(d++) = *s >> 16 & 0xff;
			*(d++) = *s >> 8 & 0xff;
			*(d++) = *s >> 0 & 0xff;
			s++;
		}
		
		row_ptr[0] = input_image;
	}

	for (y = 0; y < height; y++) {
		jpeg_write_scanlines(&cinfo, row_ptr, 1);
		row_ptr[0] += line_len;
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
}

/* libjpeg */
int imutil_jpeg_compress_rgb(image_t *img, image_t *out, int quality)
{
	_imutil_libjpeg_compress_rgb(img->bpp, &out->data, &out->bpp,
			  img->data, img->w, img->h, quality);

	out->w = img->w;
	out->h = img->h;
}

#if 0
/* openmv jpeg */
int imutil_jpeg_compress(image_t *img, image_t *out, int quality)
{
	int size = 1024 * 1024;

	if (img->bpp != 2) {
		return -1;
	}
	
	out->w = img->w;
	out->h = img->h;
	out->bpp = size;
	out->pixels = malloc(size);
	if (!out->pixels) {
		return -1;
	}

	bool overflow = jpeg_compress(img, out, quality, false);
	if (overflow) {
		malloc(out->pixels);
		return -1;
	}

	return 0;
}
#endif

void imutil_crop(int bpp, uint8_t *src, int srcw, int srch, int srcx, int srcy,
	  uint8_t *dst, int dstw, int dsth)
{
	uint8_t *linesrc, *linedst;
	int srcline = srcw * bpp;
	int dstline = dstw * bpp;
	int x, y;
	for (y = 0; y < dsth; y++) {
		linesrc = src + srcline * (srcy + y) + srcx * bpp;
		linedst = dst + dstline * y;
		memcpy(linedst, linesrc, dstline);
	}
}

void imutil_clone_roi(image_t *src, image_t *dst, rectangle_t *roi)
{
	dst->w = roi->w;
	dst->h = roi->h;
	dst->bpp = src->bpp;
	dst->data = malloc(dst->w * dst->h * dst->bpp);
	
	imutil_crop(src->bpp, src->data, src->w, src->h,
		    roi->x, roi->y, dst->data, roi->w, roi->h);
}

void imutil_rgb565_to_rgb32(image_t *src, image_t *dst)
{

}

