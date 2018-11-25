/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * lcd.c
 *     lcd api, based on frame buffer api
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdint.h>
#include "lcd.h"
#include "cvtcolor.h"

static struct fb_info fbinfo;

int lcd_open(void)
{
	return fb_open(0, &fbinfo);
}

void lcd_close(void)
{
	fb_close(&fbinfo);
}

void lcd_set_pixel(int x, int y, uint32_t pixel)
{
	fb_set_pixel(&fbinfo, x, y, pixel);
}

void lcd_show_buffer(const uint8_t *buffer, size_t len)
{

}

/* show openmv RGB565 */
void lcd_show_image(image_t *image, rectangle_t *roi)
{
	int x, y;
	int sx, sy;
	int dx, dy;
	int dw, dh;
	
	rectangle_t roi_tmp;
	uint8_t     r, g, b;
	uint8_t     a;
	
	if (!roi) {
		roi = &roi_tmp;
		roi->x = 0;
		roi->y = 0;
		roi->w = image->w;
		roi->h = image->h;
	}

	dx = 0;
	dy = 0;
	dw = roi->w;
	dh = roi->h;

	sx = roi->x;
	sy = roi->y;

	for (y = 0; y < dh; y++) {
		uint8_t *s = (uint8_t *)(image->data
					   + (sy + y) * image->w * image->bpp + sx * image->bpp);
		
		uint32_t *d = (uint32_t *)(fb_bg_line_ptr(&fbinfo, dy + y) + dx * sizeof(uint32_t));

		for (x = 0; x < dw; x++) {
			if (image->bpp == 2) {
				uint16_t t = *(uint16_t *)s;
				r = ((t >> 11) & 0x1f) << 3;
				g = ((t >> 5)  & 0x3f) << 2;
				b = ((t >> 0)  & 0x1f) << 3;
				*d++ = LCD_PIXEL_RGB(r, g, b);LCD_PIXEL_RGB(r, g, b);
			} else {
				//r = g = b = *s;
				r = *(s + 2);				
				g = *(s + 1);
				b = *(s + 0);				
				*d++ = LCD_PIXEL_RGB(r, g, b);LCD_PIXEL_RGB(r, g, b);
			}
			
			s += image->bpp;
		}
	}

	fb_update(&fbinfo);
}

