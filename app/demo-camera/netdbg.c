/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * netdbg.c
 *     send image to Rainbow Pi debugger running on PC
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "netdbg.h"
#include "imutil.h"

static int sock = -1;

int netdbg_connect(const char *serverip, uint16_t port)
{
	int ret;
	struct sockaddr_in serv_addr;

	if (sock < 0) {
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock < 0)
			return -1;

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(serverip);
		serv_addr.sin_port = htons(port);
		ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		if (ret < 0) {
			close(sock);
			sock = -1;
			return -1;
		}
	}

	return 0;
}

void netdbg_close(void)
{
	if (sock >= 0) {
		close(sock);
		sock = -1;
	}
}
	       
int netdbg_send(const uint8_t *buf, int size)
{
	int ret;

	int writen = 0;
	while (writen < size) {
		ret = write(sock, buf + writen, size - writen);
		if (ret < 0) {
			close(sock);
			sock = -1;
			return -1;
		}

		writen += ret;
	}

	return size;
}

int netdbg_send_jpeg(const char *title, const char *jpeg_buffer, int w, int h, int size)
{
	int ret;

	packet_head_t pkt;

	pkt.w = w;
	pkt.h = h;
	pkt.len = size;

	sprintf(pkt.title, "%s", !title ? "Camera" : title);

	ret = netdbg_send((void *)&pkt, sizeof(pkt));	
	if (ret < 0) {
		return -1;
	}

	return netdbg_send((void *)jpeg_buffer, size);
}

int netdbg_send_image(const char *title, image_t *img, int quality)
{
	int ret = 0;
	image_t out;
	
	if (img->bpp != 2) {
		return -1;
	}

	ret = imutil_jpeg_compress_rgb(img, &out, quality);
	if (ret < 0) {
		goto quit;
	}
	
	ret = netdbg_send_jpeg(title, out.pixels, out.w, out.h, out.bpp);
	free(out.pixels);
quit:

	return ret;
}

#if 0
void compress_and_save(image_t *img)
{
	static int idx = 0;
	char path[64];
        uint32_t size = 1024 * 1024;
	uint8_t *buffer = malloc(size);
	image_t out = { .w=img->w, .h=img->h, .bpp=size, .pixels=buffer };
	FIL fp;
	int quality = 50;
	
	sprintf(path, "/root/cam%d.jpg", idx++);
//	file_write_open(&fp, path);	
	// When jpeg_compress needs more memory than in currently allocated it
	// will try to realloc. MP will detect that the pointer is outside of
	// the heap and return NULL which will cause an out of memory error.
	bool overflow = jpeg_compress(img, &out, quality, false);
	if (!overflow) {
//		write_data(&fp, out.pixels, out.bpp);
		printf("%d,%d,%d\n", out.w, out.h, out.bpp);
		send_to_ide(out.pixels, out.w, out.h, out.bpp);
	}
	
//	file_close(&fp);
	free(buffer);
//	sleep(1);
	printf("%s\n", path);
}
#endif
