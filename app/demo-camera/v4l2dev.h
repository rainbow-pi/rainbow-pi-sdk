/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * v4l2dev.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __V4L2DEV_H__
#define __V4L2DEV_H__

#include <linux/videodev2.h>

struct v4l2dev_buf {
	struct v4l2_buffer v4l2buf;
	void               *start;
};

typedef struct {
	int fd;
	struct v4l2_capability     cap;
	struct v4l2_format         fmt;
	struct v4l2_requestbuffers req;

	int                        bufsnr;
	struct v4l2dev_buf          *bufs;
} v4l2dev_t;

#define v4l2_width(dev)  ((dev)->fmt.fmt.pix.width)
#define v4l2_height(dev) ((dev)->fmt.fmt.pix.height)

int v4l2_enum_fmt(v4l2dev_t *dev);
int v4l2_query_cap(v4l2dev_t *dev);
int v4l2_s_input(v4l2dev_t *dev, int index);
int v4l2_g_fmt(v4l2dev_t *dev);
int v4l2_s_fmt(v4l2dev_t *dev, int w, int h, int pixfmt);
int v4l2_reqbufs(v4l2dev_t *dev, int bufsnr);
int v4l2_stream(v4l2dev_t *dev, int on);
int v4l2_read_frame(v4l2dev_t *dev, void **data, int *dlen);
int v4l2_open(v4l2dev_t *dev, int idx);
int v4l2_close(v4l2dev_t *dev);

#endif /* __V4L2DEV_H__ */
