/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * lcd.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __LCD_H__
#define __LCD_H__

#include "fbdev.h"
#include "imutil.h"

#define LCD_PIXEL_ARGB(A,R,G,B) (((A) << 24) | ((B) << 16) | ((G) << 8) | (R))
#define LCD_PIXEL_RGB(R,G,B) (((B) << 16) | ((G) << 8) | (R) | 0xFF000000)
#define LCD_PIXEL_BGR(B,G,R) LCD_PIXEL_RGB((R),(G),(B))

int  lcd_open(void);
void lcd_close(void);

void lcd_show_image(image_t *image, rectangle_t *roi);

#endif
