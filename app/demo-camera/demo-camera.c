/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * demo-camera.c
 *     camera demo, to show how to use camera and lcd
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <libyuv.h>

#include "imutil.h"
#include "timeutil.h"
#include "fileutil.h"
#include "v4l2dev.h"
#include "lcd.h"
#include "cvtcolor.h"
#include "netdbg.h"
#include "usbdbg.h"

static struct option long_options[] = {
        { "device_id          ", 1, 0, 'i'},
	{ "cam_resolution     ", 1, 0, 'r'},
	{ "cam_format         ", 1, 0, 'f'},
	{ "encode             ", 1, 0, 'e'},
	{ "decode             ", 1, 0, 'd'},
	{ "snapshot_num       ", 1, 0, 's'},
	{ "lcden              ", 1, 0, 'l'},
	{ "usben              ", 1, 0, 'u'},
	{ "neten              ", 1, 0, 'n'},
	{ "serverip           ", 1, 0, 'a'},
	{ "serverport         ", 1, 0, 'p'},
	{ "help               ", 0, 0, 'h'},
};

static char short_options[] = "i:r:f:e:d:s:l:u:n:a:p:h";

static char *opt_dev_id = "0";
static char *opt_camera_resolution = "vga";
static unsigned int opt_camera_format = V4L2_PIX_FMT_NV12;
static int  opt_snapshot_num    = -1;
static int  opt_restart_counter = -1;
static int  opt_net_enabled = 0;
static int  opt_usb_enabled = 0;
static char *opt_serverip = "192.168.6.37";
static int  opt_serverport = 5000;
static int  opt_lcd_enabled = 1;
static int  opt_jpeg_quality = 75;
static char *opt_h264enc_file = NULL;
static char *opt_h264dec_file = NULL;
static int  opt_upload_div = 1;

static void usage(void)
{
        printf("\nUsage: demo-camera [options]\n");
	printf("\t-i dev_id\n"
	       "\t-r camera_resolution [vga 720p 1080p]\n"
	       "\t-s snapshot_num\n"
	       "\t-e h264_end_file_path\n"
	       "\t-d h264_dec_file_path\n"
	       "\t-n net_enabled\n"
	       "\t-l lcd_enable\n"
	       "\t-u usbacm_enable\n"
	       "\t-a serverip\n"
	       "\t-p serverport\n");
	
}

static int parse_args(int argc, const char **argv)
{
	int ret;
	while ((ret = getopt_long(argc, (char * const*)argv,
				  short_options, long_options, NULL)) != -1) {
		switch (ret) {
		case 'h':
			usage();
			return 0;
		case 'e':
			opt_h264enc_file = optarg;
			break;
		case 'i':
			opt_dev_id = optarg;
			break;
		case 's':
			opt_snapshot_num = atoi(optarg);
			break;
		case 'r':
			opt_camera_resolution = optarg;
			break;
		case 'f':
			/* todo : more v4l2 format */
			if (!strcmp(optarg, "nv12"))
				opt_camera_format = V4L2_PIX_FMT_NV12;
			else if (!strcmp(optarg, "yuyv"))
				opt_camera_format = V4L2_PIX_FMT_YUYV;
			else if (!strcmp(optarg, "rgb565"))
				opt_camera_format = V4L2_PIX_FMT_RGB565;
			else if (!strcmp(optarg, "422p"))
				opt_camera_format = V4L2_PIX_FMT_YUV422P;
			break;			
		case 'l':
			opt_lcd_enabled = atoi(optarg);
			break;
		case 'u':
			opt_usb_enabled = atoi(optarg);
			break;
		case 'n':
			opt_net_enabled = atoi(optarg);
			break;
		case 'a':
			opt_serverip = optarg;
			break;
		case 'p':
			opt_serverport = atoi(optarg);
			break;
		default:
			usage();
			return -1;
		}
	}
}

static int total_frames = 0;
static long long fps_time_mark;
static long long time_mark;

/* camera, v4l2 API */
static v4l2dev_t camera = {
	-1,
};

int main(int argc, const char **argv)
{
        int ret;
	rectangle_t roi;
	int netdbg_connected = 0;
	char title[16];
	int w, h;
	
	if (parse_args(argc, argv) < 0) {
		return -1;
	}

        if (!strcmp(opt_camera_resolution, "vga")) {
		w = 640;
		h = 480;
	} else if (!strcmp(opt_camera_resolution, "720p")) {
		w = 1280;
		h = 720;
	} else if (!strcmp(opt_camera_resolution, "1080p")) {
		w = 1920;
		h = 1080;
	} else {
		usage();
		return -1;
	}

	printf("========= Run hwtest =========\n");
	printf("LCD : %s\n", opt_lcd_enabled ? "Yes" : "No");
	printf("ACM : %s\n", opt_usb_enabled ? "Yes" : "No");
	printf("NET : %s\n", opt_net_enabled ? "Yes" : "No");
	if (opt_net_enabled) {
		printf("\tServer:%s, Port:%d\n", opt_serverip, opt_serverport);
	}

	printf("\n\n");
	
	sprintf(title, "%s", opt_dev_id);
	
	if (opt_lcd_enabled) {
		lcd_open();
	}

        v4l2_open(&camera, 0);
	v4l2_enum_fmt(&camera);
	v4l2_query_cap(&camera);
	v4l2_s_input(&camera, 0);
	v4l2_s_fmt(&camera, w, h, opt_camera_format);
	v4l2_g_fmt(&camera);
	v4l2_reqbufs(&camera, 4);
	v4l2_stream(&camera, 1);

	uint8_t *frame_ptr;
	int      frame_len;

	uint8_t  *rgb565_ptr;
	uint8_t  *argb_ptr;
	
	argb_ptr = malloc(camera.fmt.fmt.pix.width * camera.fmt.fmt.pix.height * 4);

	fps_time_mark = get_timestamp();
	
	while (1) {
		if ((opt_snapshot_num >= 0) && (--opt_snapshot_num < 0)) {
			break;
		}
		
		v4l2_read_frame(&camera, (void *)&frame_ptr, &frame_len);
		if (frame_len <= 0) {
			continue;
		}

		time_mark = get_timestamp();
		NV12ToARGB(frame_ptr, v4l2_width(&camera),
			   frame_ptr + v4l2_width(&camera) * v4l2_height(&camera),
			   v4l2_width(&camera),
			   argb_ptr,
			   v4l2_width(&camera) * 4,
			   v4l2_width(&camera), v4l2_height(&camera));
//		print_timestamp("NV12ToARGB", get_timestamp() - time_mark);
		free(frame_ptr);

		image_t img;
		img.w = v4l2_width(&camera);
		img.h = v4l2_height(&camera);
		img.bpp = 4;
		img.data = argb_ptr;			

		if (opt_lcd_enabled) {
			/* lcd 320x240 */
			roi.x = (img.w - 320) / 2;
			roi.y = (img.h - 240) / 2;
			roi.w = 320;
			roi.h = 240;
			lcd_show_image(&img, &roi);
		}
		
		image_t imgjpg = {.bpp = 0, .data = NULL};
		{
			static int udiv = 0;
			if (++udiv < opt_upload_div) {
				goto release_frame;
			}
			udiv = 0;
		}
		
		if (opt_usb_enabled || opt_net_enabled) {
			time_mark = get_timestamp();
			ret = imutil_jpeg_compress_rgb(&img, &imgjpg, opt_jpeg_quality);
			// print_timestamp("imutil_jpeg_compress_rgb", get_timestamp() - time_mark);
			if (ret < 0 || !imgjpg.bpp) {
				continue;
			}
		}
		
		if (opt_usb_enabled) {
			ret = usbdbg_connect();
			if (ret >= 0) {
				ret = usbdbg_send_jpeg(title, imgjpg.data, imgjpg.w, imgjpg.h, imgjpg.bpp);
			}
		}
		
		if (opt_net_enabled) {
			if (!netdbg_connected) {
				ret = netdbg_connect(opt_serverip, opt_serverport);
				if (ret < 0) {
					printf("netdbg_connect failed!\n");
					netdbg_connected = 0;
				} else {
					netdbg_connected = 1;
				}
			}
			
			if (netdbg_connected) {
				ret = 0;
				if (ret == 0) {
					time_mark = get_timestamp();
					ret = netdbg_send_jpeg(title, imgjpg.data, imgjpg.w, imgjpg.h, imgjpg.bpp);
//					print_timestamp("netdbg_send_jpeg", get_timestamp() - time_mark);
					if (ret < 0) {
						printf("netdbg_send_jpeg failed!\n");
						netdbg_close();
						netdbg_connected = 0;
					}
				}
			}
		}

	release_frame:
#if 0
		/* argb ptr, no free */
		if (img.data) {
			free(img.data);
			img.data = NULL;
		}
#endif				
		if (imgjpg.data) {
			free(imgjpg.data);
			imgjpg.data = NULL;
		}

		total_frames++;
#if 0
		printf("fps = %.1f\n",
		       total_frames * 1.0f / ((get_timestamp() - fps_time_mark) / 1000 / 1000));
#endif		
	}

	
	if (opt_lcd_enabled)
		lcd_close();

	netdbg_close();
	return 0;
}

