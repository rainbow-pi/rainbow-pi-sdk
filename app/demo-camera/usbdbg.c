/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * usbdbg.c
 *     send image via usb CDC gadget
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include "timeutil.h"
#include "netdbg.h"
#include "usbdbg.h"

#define DEBUG

static const char *port_name = "/dev/ttyGS0";
static int portfd = -1;
static struct termios oldtio, newtio;

int sp_blocking_write(int fd, const void *buf,
			     size_t count, unsigned int timeout_ms)
{
	int ret;
	
	int s = 0;

	int w;

//	printf("sp_blocking_write : count = %d\n", count);
	
	while (s < count) {
		w = count - s;

		if (w > 1024)
			w = 1024;

//		printf("sending ... %d\n", w);
		
		ret = write(fd, buf + s, w);
		if (ret >= 0) {
			s += ret;
		} else {
			return ret;
		}

		usleep(7000);
//		printf("### %d\n", s);
	}

	return s;
}

int sp_blocking_write1(int fd, const void *buf,
			     size_t count, unsigned int timeout_ms)
{
        size_t bytes_written = 0;
        unsigned char *ptr = (unsigned char *) buf;
        struct timeval start, delta, now, end = {0, 0};
        int started = 0;
        fd_set fds;
        int result;

        if (timeout_ms) {
                /* Get time at start of operation. */
                gettimeofday(&start, NULL);
                /* Define duration of timeout. */
                delta.tv_sec = timeout_ms / 1000;
                delta.tv_usec = (timeout_ms % 1000) * 1000;
                /* Calculate time at which we should give up. */
                timeradd(&start, &delta, &end);
        }

        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        /* Loop until we have written the requested number of bytes. */
        while (bytes_written < count) {
                /*
                 * Check timeout only if we have run select() at least once,
                 * to avoid any issues if a short timeout is reached before
                 * select() is even run.
                 */
                if (timeout_ms && started) {
                        gettimeofday(&now, NULL);
                        if (timercmp(&now, &end, >))
                                /* Timeout has expired. */
                                break;
                        timersub(&end, &now, &delta);
                }
                result = select(fd + 1, NULL, &fds, NULL, timeout_ms ? &delta : NULL);
                started = 1;
                if (result < 0) {
                        if (errno == EINTR) {
                                printf("select() call was interrupted, repeating");
                                continue;
                        } else {
                                printf("select() failed");
				return -1;
                        }
                } else if (result == 0) {
                        /* Timeout has expired. */
                        break;
                }

                /* Do write. */
                result = write(fd, ptr, count - bytes_written);
                if (result < 0) {
                        if (errno == EAGAIN)
                                /* This shouldn't happen because we did a select() first, but handle anyway. */
                                continue;
                        else {
                                /* This is an actual failure. */
                                printf("write() failed");
				return -1;
			}
                }

                bytes_written += result;
                ptr += result;
        }

        if (bytes_written < count) {
                DEBUG("Write timed out");
	}

	return bytes_written;
}

int sp_blocking_read(int fd, void *buf,
			    size_t count, unsigned int timeout_ms)
{
        size_t bytes_read = 0;
        unsigned char *ptr = (unsigned char *) buf;
        struct timeval start, delta, now, end = {0, 0};
        int started = 0;
        fd_set fds;
        int result;

        if (timeout_ms) {
                /* Get time at start of operation. */
                gettimeofday(&start, NULL);
                /* Define duration of timeout. */
                delta.tv_sec = timeout_ms / 1000;
                delta.tv_usec = (timeout_ms % 1000) * 1000;
                /* Calculate time at which we should give up. */
                timeradd(&start, &delta, &end);
        }

        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        /* Loop until we have the requested number of bytes. */
        while (bytes_read < count) {
                /*
                 * Check timeout only if we have run select() at least once,
                 * to avoid any issues if a short timeout is reached before
                 * select() is even run.
                 */
                if (timeout_ms && started) {
                        gettimeofday(&now, NULL);
                        if (timercmp(&now, &end, >))
                                /* Timeout has expired. */
                                break;
                        timersub(&end, &now, &delta);
                }
                result = select(fd + 1, &fds, NULL, NULL, timeout_ms ? &delta : NULL);
                started = 1;
                if (result < 0) {
                        if (errno == EINTR) {
                                DEBUG("select() call was interrupted, repeating");
                                continue;
                        } else {
                                printf("select() failed");
				return -1;
                        }
                } else if (result == 0) {
                        /* Timeout has expired. */
                        break;
                }

                /* Do read. */
                result = read(fd, ptr, count - bytes_read);

                if (result < 0) {
                        if (errno == EAGAIN)
                                /*
                                 * This shouldn't happen because we did a
                                 * select() first, but handle anyway.
                                 */
                                continue;
                        else {
                                /* This is an actual failure. */
                                printf("read() failed");
				return -1;
			}
                }

                bytes_read += result;
                ptr += result;
        }

        if (bytes_read < count)
                DEBUG("Read timed out\n");

        return bytes_read;
	
}

int sp_open(void)
{
	if (portfd >= 0)
		return portfd;
	
	portfd = open(port_name, O_RDWR | O_NOCTTY);
        if (portfd < 0) {
		fprintf(stderr, "open %s failed!\n", port_name);
		return -1;
	}

        tcgetattr(portfd, &oldtio);
        memset(&newtio, 0, sizeof(newtio));

        newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
        /* newtio.c_iflag = IGNPAR | ICRNL; */
	newtio.c_iflag = PARENB | ICRNL;

/*        newtio.c_oflag = 0; */
/*        newtio.c_lflag = ICANON; */

        tcflush(portfd, TCIFLUSH);
        tcsetattr(portfd, TCSANOW, &newtio);

	return portfd;
quit:
	fprintf(stdout, "app quit\n");
        tcsetattr(portfd, TCSANOW, &oldtio);
        close(portfd);
	return 0;
}

int usbdbg_connect(void)
{
	return sp_open();
}

void usbdbg_close(void)
{

}

int usbdbg_send(const uint8_t *buf, int size)
{
	int ret;

	int writen = 0;
	while (writen < size) {
		ret = write(portfd, buf + writen, size - writen);
		if (ret < 0) {
			close(portfd);
			portfd = -1;
			return -1;
		}

		writen += ret;
	}

	return size;
}

#if 0
int usbdbg_send_jpeg(const char *title, const char *jpeg_buffer, int w, int h, int size)
{
	int ret;

	packet_head_t pkt;

	pkt.w = w;
	pkt.h = h;
	pkt.len = size;

	sprintf(pkt.title, "%s", !title ? "Camera" : title);

	usleep(10000);
	
	ret = usbdbg_send((void *)&pkt, sizeof(pkt));
	if (ret < 0) {
		return -1;
	}

	usleep(10000);
	
	return usbdbg_send((void *)jpeg_buffer, size);
}
#endif

int usbdbg_send_jpeg(const char *title, const char *jpeg_buffer, int w, int h, int size)
{
	int ret;

	static uint8_t buf[2 * 1024 * 1024];
	packet_head_t *pkt = (packet_head_t *)buf;;

	pkt->w = w;
	pkt->h = h;
	pkt->len = size;

	sprintf(pkt->title, "%s", !title ? "Camera" : title);

	memcpy(buf + 32, jpeg_buffer, size);
	ret = usbdbg_send(buf, size + 32);
	return 0;
}

int usbdbg_send_image(const char *title, image_t *img, int quality)
{
	int ret = 0;
	image_t out;

	printf("usbdbg_send_image\n");
	if (img->bpp != 2) {
		return -1;
	}

	ret = imutil_jpeg_compress_rgb(img, &out, quality);
	if (ret < 0) {
		goto quit;
	}
	
	ret = usbdbg_send_jpeg(title, out.pixels, out.w, out.h, out.bpp);
	free(out.pixels);
quit:

	return ret;
}
