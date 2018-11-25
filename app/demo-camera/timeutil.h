/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * timeutil.h
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#ifndef __TIMEUTIL_H__
#define __TIMEUITL_H__

/* timestamp in us */
long long get_timestamp(void);
void print_timestamp(const char *type, long long ts);

#endif
