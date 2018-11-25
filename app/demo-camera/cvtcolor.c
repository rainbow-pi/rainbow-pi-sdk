/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * color format convert
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cvtcolor.h"

#define USE_FIXED_POINT 1

#define LCD_PIXEL_ARGB(A,R,G,B) (((A) << 24) | ((B) << 16) | ((G) << 8) | (R))
#define LCD_PIXEL_RGB(R,G,B) (((B) << 16) | ((G) << 8) | (R) | 0xFF000000)
#define LCD_PIXEL_BGR(B,G,R) LCD_PIXEL_RGB((R),(G),(B))

void rgb565_to_rgb32(uint8_t *src, int srcw, int srch, uint8_t *dst, uint8_t alpha,
		     int is_openmv_rgb565)
{
	int size = srcw * srch;
	uint32_t *d = (uint32_t *)dst;
	uint8_t r, g, b;
	uint16_t *s = (uint16_t *)src;
	while (size--) {
		uint16_t t;
		
                if (!is_openmv_rgb565) {
			/* normal RGB565 */
			t = *s;
		} else {
			/* openmv RGB565 */
			/* swap bytes */
			t = ((*s >> 8) & 0xff) | ((*s & 0xff) << 8);
		}

		r = ((t >> 11) & 0x1f) << 3;
		g = ((t >> 5)  & 0x3f) << 2;
		b = ((t >> 0)  & 0x1f) << 3;

		*d++ = LCD_PIXEL_RGB(r, g, b);
		s++;
	}
}

void rgb24_to_rgb32(uint8_t *src, int srcw, int srch, uint8_t *dst, uint8_t alpha)
{
	int size = srcw * srch;
	uint32_t *d = (uint32_t *)dst;

	while (size--) {
		*d++ = LCD_PIXEL_RGB(*(src + 0), *(src + 1), *(src + 2));
		src += 3;
	}
}

static int nv16_rgb_internal(const unsigned char *src, unsigned char *dst,
			     int width, int height, int rgb)
{
	int x, y;	
	int y_ratio = 1;
	const unsigned char *yp, *up, *vp;
#if USE_FIXED_POINT
        uint8_t Y, U, V;
	int c, d, e;
#else
	int Y, U, V;
#endif
	int r, g, b;
	
	yp = src;
	up = src + width * height;
	vp = up + 1;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
//			Y = *(yp + y * width + x);
//			U = *(up + ((y/y_ratio) *(width/2)) + x/2);
//			V = *(vp + ((y/y_ratio) *(width/2)) + x/2);
			Y = *yp;
			U = *up;
			V = *vp;

			yp++;
			
			if (x && (x % 2 == 0)) {
				up += 2;
				vp = up + 1;
			}
#if USE_FIXED_POINT
			c = Y - 16;
			d = U - 128;
			e = V - 128;

                        r = (298 * c           + 409 * e + 128) >> 8;
			g = (298 * c - 100 * d - 208 * e + 128) >> 8;
			b = (298 * c + 516 * d           + 128) >> 8;
#else			
			r = Y + 1.402 * (V - 128);
			g = Y - 0.34414 * (U - 128) - 0.71414 * (V - 128);
			b = Y + 1.772 * (U - 128);
#endif			

			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			if (r < 0)   r = 0;
			if (g < 0)   g = 0;
			if (b < 0)   b = 0;

			if (rgb) {
				/* RGB 24 */
				*(dst + (y * width + x) * 3 + 0) = r;
				*(dst + (y * width + x) * 3 + 1) = g;
				*(dst + (y * width + x) * 3 + 2) = b;
			} else {
				/* BGR 24 */
				*(dst + (y * width + x) * 3 + 0) = b;
				*(dst + (y * width + x) * 3 + 1) = g;
				*(dst + (y * width + x) * 3 + 2) = r;
			}
		}
	}

	return 0;
}

/* YUV420, I420, YU12 */
int nv16_rgb24(const unsigned char *src, unsigned char *dst, int width, int height)
{
	return nv16_rgb_internal(src, dst, width, height, 1);
}

/* YUV422P, I422 */
/*
 * int rgb : 1 for RGB24, 0 for BGR24
 */
static int yuv422p_rgb_internal(const unsigned char *src, unsigned char *dst,
				int width, int height, int rgb, int bpp, uint8_t alpha)
{
	int x, y;	
	int y_ratio = 1;
	const unsigned char *yp, *up, *vp;
#if USE_FIXED_POINT
        uint8_t Y, U, V;
	int c, d, e;
#else
	int Y, U, V;
#endif
	int r, g, b;
	
	yp = src;
	up = src + width * height;
	vp = up + (width * height) / 2;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			Y = *(yp + y * width + x);
			U = *(up + ((y/y_ratio) *(width/2)) + x/2);
			V = *(vp + ((y/y_ratio) *(width/2)) + x/2);

#if USE_FIXED_POINT
			c = Y - 16;
			d = U - 128;
			e = V - 128;

                        r = (298 * c           + 409 * e + 128) >> 8;
			g = (298 * c - 100 * d - 208 * e + 128) >> 8;
			b = (298 * c + 516 * d           + 128) >> 8;
#else			
			r = Y + 1.402 * (V - 128);
			g = Y - 0.34414 * (U - 128) - 0.71414 * (V - 128);
			b = Y + 1.772 * (U - 128);
#endif			

			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			if (r < 0)   r = 0;
			if (g < 0)   g = 0;
			if (b < 0)   b = 0;

			if (bpp == 24) {
				if (rgb) {
					/* RGB 24 */
					*(dst + (y * width + x) * 3 + 0) = r;
					*(dst + (y * width + x) * 3 + 1) = g;
					*(dst + (y * width + x) * 3 + 2) = b;
				} else {
					/* BGR 24 */
					*(dst + (y * width + x) * 3 + 0) = b;
					*(dst + (y * width + x) * 3 + 1) = g;
					*(dst + (y * width + x) * 3 + 2) = r;
				}
			} else if (bpp == 32) {
                                if (rgb) {
					/* RGB 32 */
					*(dst + (y * width + x) * 4 + 0) = r;
					*(dst + (y * width + x) * 4 + 1) = g;
					*(dst + (y * width + x) * 4 + 2) = b;
					*(dst + (y * width + x) * 4 + 3) = alpha;
				} else {
					/* BGR 32 */
					*(dst + (y * width + x) * 4 + 0) = b;
					*(dst + (y * width + x) * 4 + 1) = g;
					*(dst + (y * width + x) * 4 + 2) = r;
					*(dst + (y * width + x) * 4 + 3) = alpha;
				}
			} else if (bpp == 16 || bpp == 17) {
				uint16_t tmp;
				tmp = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
				if (bpp == 16) {
					/* normal RGB565 */
					*(dst + (y * width + x) * 2 + 0) = tmp & 0xff;
					*(dst + (y * width + x) * 2 + 1) = tmp >> 8;
				} else {
					/* openmv RGB565 */
					*(dst + (y * width + x) * 2 + 1) = tmp & 0xff;
					*(dst + (y * width + x) * 2 + 0) = tmp >> 8;
				}
			}
		}
	}

	return 0;
}	

/* YUV420, I420, YU12 */
int yuv422p_rgb24(const unsigned char *src, unsigned char *dst, int width, int height)
{
	return yuv422p_rgb_internal(src, dst, width, height, 1, 24, 0);
}

/* YUV420, I420, YU12 */
int yuv422p_bgr24(const unsigned char *src, unsigned char *dst, int width, int height)
{
	return yuv422p_rgb_internal(src, dst, width, height, 0, 24, 0);
}

/* YUV420, I420, YU12 */
int yuv422p_rgb32(const unsigned char *src, unsigned char *dst, int width, int height, uint8_t alpha)
{
	return yuv422p_rgb_internal(src, dst, width, height, 1, 32, alpha);
}

/* YUV420, I420, YU12 */
int yuv422p_bgr32(const unsigned char *src, unsigned char *dst, int width, int height, uint8_t alpha)
{
	return yuv422p_rgb_internal(src, dst, width, height, 0, 32, alpha);
}

int yuv422p_rgb565(const unsigned char *src, unsigned char *dst, int width, int height)
{
	return yuv422p_rgb_internal(src, dst, width, height, 0, 16, 0);
}

int yuv422p_rgb565_openmv(const unsigned char *src, unsigned char *dst, int width, int height)
{
	/* inverse byte order */
	return yuv422p_rgb_internal(src, dst, width, height, 0, 16 + 1, 0);
}


/* YUV420, I420, YU12 */
/*
 * int rgb : 1 for RGB24, 0 for BGR24
 */
static int yu12_rgb_internal(const unsigned char *src, unsigned char *dst, int width, int height, int rgb)
{
	int x, y;	
	
	const unsigned char *yp, *up, *vp;
#if USE_FIXED_POINT
        uint8_t Y, U, V;
	int c, d, e;
#else
	int Y, U, V;
#endif
	int r, g, b;
	
	yp = src;
	vp = src + width * height;
	up = vp + (width * height) / 4;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			Y = *(yp + y * width + x);
			U = *(up + ((y/2) *(width/2)) + x/2);
			V = *(vp + ((y/2) *(width/2)) + x/2);

#if USE_FIXED_POINT
			c = Y - 16;
			d = U - 128;
			e = V - 128;

                        r = (298 * c           + 409 * e + 128) >> 8;
			g = (298 * c - 100 * d - 208 * e + 128) >> 8;
			b = (298 * c + 516 * d           + 128) >> 8;
#else			
			r = Y + 1.402 * (V - 128);
			g = Y - 0.34414 * (U - 128) - 0.71414 * (V - 128);
			b = Y + 1.772 * (U - 128);
#endif			

			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			if (r < 0)   r = 0;
			if (g < 0)   g = 0;
			if (b < 0)   b = 0;

			if (rgb) {
				/* RGB 24 */
				*(dst + (y * width + x) * 3 + 0) = b;
				*(dst + (y * width + x) * 3 + 1) = g;
				*(dst + (y * width + x) * 3 + 2) = r;
			} else {
				/* BGR 24 */
				*(dst + (y * width + x) * 3 + 0) = r;
				*(dst + (y * width + x) * 3 + 1) = g;
				*(dst + (y * width + x) * 3 + 2) = b;
			}
		}
	}

	return 0;
}

/* YUV420, I420, YU12 */
int yu12_rgb24(const unsigned char *src, unsigned char *dst, int width, int height)
{
	return yu12_rgb_internal(src, dst, width, height, 1);
}

/* YUV420, I420, YU12 */
int yu12_bgr24(const unsigned char *src, unsigned char *dst, int width, int height)
{
	return yu12_rgb_internal(src, dst, width, height, 0);
}

int yu12_rgb565(const unsigned char *src, unsigned char *dst, int width, int height)
{
	int x, y;	
	
	const unsigned char *yp, *up, *vp;
#if USE_FIXED_POINT
        uint8_t Y, U, V;
	int c, d, e;
#else
	int Y, U, V;
#endif
	int r, g, b;

	uint16_t pixel;
	uint16_t *ptr = (uint16_t *)dst;
	
	yp = src;
	vp = src + width * height;
	up = vp + (width * height) / 4;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			Y = *(yp + y * width + x);
			U = *(up + ((y/2) *(width/2)) + x/2);
			V = *(vp + ((y/2) *(width/2)) + x/2);

#if USE_FIXED_POINT
			c = Y - 16;
			d = U - 128;
			e = V - 128;

                        r = (298 * c           + 409 * e + 128) >> 8;
			g = (298 * c - 100 * d - 208 * e + 128) >> 8;
			b = (298 * c + 516 * d           + 128) >> 8;
#else			
			r = Y + 1.402 * (V - 128);
			g = Y - 0.34414 * (U - 128) - 0.71414 * (V - 128);
			b = Y + 1.772 * (U - 128);
#endif			

			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			if (r < 0)   r = 0;
			if (g < 0)   g = 0;
			if (b < 0)   b = 0;

			pixel = ((b >> 3) << 11) | ((g >> 2) << 5) | (r >> 3);
//			pixel = ((r&0x1f) << 11) | ((g&0x3f) << 5) | ((b&0x1f) << 0);
			*ptr = pixel;
			ptr++;
		}
	}

	return 0;
}

int yu12_grayscale(const unsigned char *src, unsigned char *dst, int width, int height)
{
	memcpy(dst, src, width * height);
	return 0;
}

/* yuv422 packed : YUYV */
int yuv422_grayscale(unsigned char *src, unsigned char *dst, int width, int height)
{
        int i;
	int size = width * height;
	uint8_t *s = src;
	uint8_t *d = dst;

	for (i = 0; i < size; i++) {
		*d = *s;
		d++;
		s+=2;
	}

	return 0;
}

int yuv422_grayscale_roi(uint8_t *src, int srcw, int srch,
			 uint8_t *dst, int roix, int roiy, int roiw, int roih)
{
	uint8_t *s = src;
	uint8_t *d = dst;

	int x, y;

	for (y = roiy; y < roiy + roih; y++) {
		s = src + srcw * y * 2 + roix * 2;
		for (x = roix; x < roix + roiw; x++) {
			*d = *s;
			d++;
			s += 2;
		}
	}

	return 0;
}
