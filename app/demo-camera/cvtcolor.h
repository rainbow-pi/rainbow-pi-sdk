/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * cvtcolor.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __YUV2RGB_H__
#define __YUV2RGB_H__

void rgb565_to_rgb32(uint8_t *src, int srcw, int srch, uint8_t *dst, uint8_t alpha,
		     int is_openmv_rgb565);
void rgb24_to_rgb32(uint8_t *src, int srcw, int srch, uint8_t *dst, uint8_t alpha);

/* YUV420, also called I420 */
int yu12_rgb565(const unsigned char *src, unsigned char *dst, int width, int height);
int yu12_rgb24(const unsigned char *src, unsigned char *dst, int width, int height);
int yu12_bgr24(const unsigned char *src, unsigned char *dst, int width, int height);
int yu12_grey(const unsigned char *src, unsigned char *dst, int width, int height);
#define yuv420_rgb565 yu12_rgb565
#define yuv420_rgb24  yu12_rgb24
#define yuv420_bgr24  yu12_bgr24
#define yuv420_grey   yu12_grey
#define yuv420_gray   yu12_grey

/* YUV422P, also called I422 */
int yuv422p_rgb565_openmv(const unsigned char *src, unsigned char *dst, int width, int height);
int yuv422p_rgb565(const unsigned char *src, unsigned char *dst, int width, int height);
int yuv422p_rgb24(const unsigned char *src, unsigned char *dst, int width, int height);
int yuv422p_bgr24(const unsigned char *src, unsigned char *dst, int width, int height);

int yuv422p_rgb32(const unsigned char *src, unsigned char *dst, int width, int height, uint8_t alpha);
int yuv422p_bgr32(const unsigned char *src, unsigned char *dst, int width, int height, uint8_t alpha);

#define yuv422p_grey yu12_grey
#define yuv422p_gray yu12_grey

/* yuv422 packed : YUYV */
int yuv422_grayscale(unsigned char *src, unsigned char *dst, int width, int height);
int yuv422_grayscale_roi(uint8_t *src, int srcw, int srch,
			 uint8_t *dst, int roix, int roiy, int roiw, int roih);

#endif
