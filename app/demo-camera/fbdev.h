/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * fbdev.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __FBDEV_H__
#define __FBDEV_H__

#include <stdio.h>
#include <stdint.h>
#include <linux/fb.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define ASSERT(x) if (!(x)) \
	{ perror("assert(" __FILE__ ":" TOSTRING(__LINE__) "): "); exit(1); }
#define FBCTL0(ctl) if (ioctl(fd, ctl))\
	{ perror("fbctl0(" __FILE__ ":" TOSTRING(__LINE__) "): "); exit(1); }
#define FBCTL1(ctl, arg1) if (ioctl(fd, ctl, arg1))\
	{ perror("fbctl1(" __FILE__ ":" TOSTRING(__LINE__) "): "); exit(1); }

#define IOCTL0(fd, ctl) if (ioctl(fd, ctl))\
	{ perror("ioctl0(" __FILE__ ":" TOSTRING(__LINE__) "): "); exit(1); }
#define IOCTL1(fd, ctl, arg1) if (ioctl(fd, ctl, arg1))\
	{ perror("ioctl1(" __FILE__ ":" TOSTRING(__LINE__) "): "); exit(1); }

struct fb_info
{
	int fd;

	void *ptr;
	void *bgptr;
	
	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;
	unsigned bytespp;
};

#define fb_xres(fb) ((fb)->var.xres)
#define fb_yres(fb) ((fb)->var.yres)
#define fb_bpp(fb)  ((fb)->var.bits_per_pixel)
#define fb_line_length(fb) ((fb)->fix.line_length)

#define fb_line_ptr(fb, line) ((fb)->ptr + fb_line_length(fb) * (line))
#define fb_bg_line_ptr(fb, line) ((fb)->bgptr + fb_line_length(fb) * (line))

extern char fontdata_8x8[];

int fb_open(int fb_num, struct fb_info *fb_info);
void fb_close(struct fb_info *fb_info);
void fb_set_pixel(struct fb_info *fb_info, int x, int y, uint32_t pixel);
void fb_update(struct fb_info *fb_info);

void fb_update_window(int fd, short x, short y, short w, short h);
void fb_sync_gfx(int fd);
int fb_put_string(struct fb_info *fb_info, int x, int y, char *s, int maxlen,
		int color, int clear, int clearlen);

#define FB_PIXEL_ARGB(A,R,G,B) (((A) << 24) | ((B) << 16) | ((G) << 8) | (R))
#define FB_PIXEL_RGB(R,G,B)    (((B) << 16) | ((G) << 8) | (R) | 0xFF000000)
#define FB_PIXEL_BGR(B,G,R)    FB_PIXEL_RGB((R),(G),(B))

#endif
