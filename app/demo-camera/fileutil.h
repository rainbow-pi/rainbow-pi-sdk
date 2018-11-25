/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * fileutil.h
 *     file operation utilities
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __FILEUTIL_H__
#define __FILEUTIL_H__

int file_write(const char *fn, void *buf, size_t len);
int file_append(const char *fn, void *buf, size_t len);

#endif
