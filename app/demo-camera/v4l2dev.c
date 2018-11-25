/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * v4l2dev.c
 *     video for linux 2 api wrapper
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <pthread.h>

#include <sys/mman.h>
#include <linux/fb.h>

#include "v4l2dev.h"

#include "timeutil.h"
static long long tick;

// #define dbg_info printf
#define dbg_info
#define CLEAR(x) memset (&(x), 0, sizeof (x))

#define CAM_BUF_PTR(cam, i) (dev->bufs[i].start)
#define CAM_BUF_LEN(cam, i) (dev->bufs[i].v4l2buf.length)

int v4l2_enum_fmt(v4l2dev_t *dev)
{
	int ret;
	struct v4l2_fmtdesc fmtd;
	memset(&fmtd, 0, sizeof(fmtd));
	fmtd.index = 0;
	fmtd.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	while ((ret = ioctl(dev->fd, VIDIOC_ENUM_FMT, &fmtd)) == 0) {
		fmtd.index++;
		dbg_info("\nPIXFMT = '%c%c%c%c', '%s' \n",
		       (fmtd.pixelformat)       & 0xFF,
		       (fmtd.pixelformat >> 8)  & 0xFF,
		       (fmtd.pixelformat >> 16) & 0xFF,
		       (fmtd.pixelformat >> 24) & 0xFF,
		       fmtd.description);
	}

	return 0;
}

int v4l2_query_cap(v4l2dev_t *dev)
{
	int ret;
	
	if (ioctl(dev->fd, VIDIOC_QUERYCAP, &dev->cap) < 0) {
		return -1;
	}

	dbg_info("\ncapabilities= 0x%08x\n",dev->cap.capabilities);
	return 0;
}

int v4l2_s_input(v4l2dev_t *dev, int index)
{
	int ret;

	if (ioctl(dev->fd, VIDIOC_S_INPUT, &index) < 0) {
		return -1;
	}

	return 0;
}

int v4l2_g_fmt(v4l2dev_t *dev)
{
	dev->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	if (ioctl(dev->fd, VIDIOC_G_FMT, &dev->fmt) < 0) {
		dbg_info("\tFailed!\n");
		return -1;
	}
	dbg_info("\nPIXFMT = '%c%c%c%c'\n",
	       (dev->fmt.fmt.pix.pixelformat)       & 0xFF,
	       (dev->fmt.fmt.pix.pixelformat >> 8)  & 0xFF,
	       (dev->fmt.fmt.pix.pixelformat >> 16) & 0xFF,
	       (dev->fmt.fmt.pix.pixelformat >> 24) & 0xFF);
	return 0;
}

int v4l2_s_fmt(v4l2dev_t *dev, int w, int h, int pixfmt)
{
	int ret;

	dbg_info("v4l2_s_fmt : \n");	
	dev->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dev->fmt.fmt.pix.width  = w;
	dev->fmt.fmt.pix.height = h;
	dev->fmt.fmt.pix.pixelformat = pixfmt;		
	
	if (ioctl(dev->fd, VIDIOC_S_FMT, &dev->fmt) < 0) {
		dbg_info("\tFailed!\n");
		return -1;
	}

	dbg_info("\tOK!\n");
	dbg_info("\nS_FMT : PIXFMT = '%c%c%c%c'\n",
	       (dev->fmt.fmt.pix.pixelformat)       & 0xFF,
	       (dev->fmt.fmt.pix.pixelformat >> 8)  & 0xFF,
	       (dev->fmt.fmt.pix.pixelformat >> 16) & 0xFF,
	       (dev->fmt.fmt.pix.pixelformat >> 24) & 0xFF);
	dbg_info("S_FMT : %d x %d\n", dev->fmt.fmt.pix.width, dev->fmt.fmt.pix.height);
	
	return 0;
}

int v4l2_reqbufs(v4l2dev_t *dev, int bufsnr)
{
	dbg_info("%s\n", __FUNCTION__);

	dev->req.count  = bufsnr;
	dev->req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dev->req.memory = V4L2_MEMORY_MMAP;

	if(ioctl(dev->fd, VIDIOC_REQBUFS, &dev->req) < 0) {
		return -1;
	}

	dev->bufsnr = dev->req.count;
	dbg_info("req.count = %d\n", dev->bufsnr);
	dbg_info("\tOK!\n");

	dev->bufs = calloc(dev->bufsnr, sizeof(struct v4l2dev_buf));
	if (!dev->bufs) {
		dbg_info("Out of memory!\n");
		return -1;
	}

	int i;

	for (i = 0; i < dev->bufsnr; i++) {
		dev->bufs[i].v4l2buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		dev->bufs[i].v4l2buf.memory = V4L2_MEMORY_MMAP;
		dev->bufs[i].v4l2buf.index  = i;

		if (ioctl(dev->fd, VIDIOC_QUERYBUF, &dev->bufs[i].v4l2buf) < 0) {
			dbg_info("Error:VIDIOC_QUERYBUF\n");
			return -1;
		}

		dev->bufs[i].start = mmap(NULL, /* start anywhere */
					  dev->bufs[i].v4l2buf.length,
					  PROT_READ | PROT_WRITE, /* required */
					  MAP_SHARED, /* recommended */
					  dev->fd,
					  dev->bufs[i].v4l2buf.m.offset);

		dbg_info("Buf[%d] S:%08x, L:%d, O:%08x\n",
		       i,
		       (int)dev->bufs[i].start,
		       dev->bufs[i].v4l2buf.length,
		       dev->bufs[i].v4l2buf.m.offset);

		/* clear buffers in the driver */		
		dev->bufs[i].v4l2buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		dev->bufs[i].v4l2buf.memory = V4L2_MEMORY_MMAP;
		dev->bufs[i].v4l2buf.index  = i;
		ioctl(dev->fd, VIDIOC_QBUF, &dev->bufs[i].v4l2buf);
	}

	return 0;
}

int v4l2_stream(v4l2dev_t *dev, int on)
{
	enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	return ioctl(dev->fd, on ? VIDIOC_STREAMON : VIDIOC_STREAMOFF, &type);
}

int v4l2_read_frame(v4l2dev_t *dev, void **data, int *dlen)
{
	int ret;
	fd_set fds;
	struct timeval tv;
	struct v4l2_buffer v4l2buf;

	*data = NULL;
	*dlen = 0;
	
	v4l2buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4l2buf.memory = V4L2_MEMORY_MMAP;
	v4l2buf.index  = 0;

	FD_ZERO(&fds);
	FD_SET(dev->fd, &fds);
	memset(&tv, 0, sizeof(tv));
	tv.tv_sec = 2;
	tv.tv_usec = 0;

	ret = select(dev->fd + 1, &fds, NULL, NULL, &tv);
	if (ret < 0) {
		dbg_info("ERR: select\n");
		return ret;
	}
	
	ret = ioctl(dev->fd, VIDIOC_DQBUF, &v4l2buf);
	if (ret < 0) {
		dbg_info("ERR: VIDIOC_DQBUF\n");		
		return ret;
	}

//	dbg_info("A frame here, start : %08x\n", dev->bufs[v4l2buf.index].start);
	if (dev->bufs[v4l2buf.index].v4l2buf.length > 0) {
		tick = get_timestamp();
		
		*data = malloc(dev->bufs[v4l2buf.index].v4l2buf.length);
		if (*data) {
			*dlen = dev->bufs[v4l2buf.index].v4l2buf.length;
			memcpy(*data, (void *)(dev->bufs[v4l2buf.index].start), *dlen);
		}

//		print_timestamp("frame_copy", get_timestamp() - tick);
	}

	/* put the buf back */
        v4l2buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4l2buf.memory = V4L2_MEMORY_MMAP;
	ret = ioctl(dev->fd, VIDIOC_QBUF, &v4l2buf);
//	dbg_info("VIDIOC_QBUF: %d\n", ret);
	
	return ret;
}

int v4l2_open(v4l2dev_t *dev, int idx)
{
	char buf[64];
	memset(dev, 0, sizeof(v4l2dev_t));
	dev->fd = -1;

	sprintf(buf, "/dev/video%d", idx);

	int cnt = 0;
	while (cnt--) {
		dev->fd = open(buf, O_RDWR | O_NONBLOCK, 0);		
		if (dev->fd < 0) {
			sleep(1);
			continue;
		}

		sleep(1);
		close(dev->fd);
		dev->fd = -1;
		sleep(1);		
	}
	
	dev->fd = open(buf, O_RDWR | O_NONBLOCK, 0);
	return dev->fd;
}

int v4l2_close(v4l2dev_t *dev)
{
	int i;
	int ret;
	if (dev->fd < 0)
		return 0;

	for (i = 0; i < dev->bufsnr; i++) {
		munmap(CAM_BUF_PTR(cam, i), CAM_BUF_LEN(cam, i));
	}

	free(dev->bufs);
	dev->bufs = NULL;
	close(dev->fd);
	dev->fd = -1;
	return ret;
}

