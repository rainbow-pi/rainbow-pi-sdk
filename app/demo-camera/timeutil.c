/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * timeutil.c
 *     time utilities
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <sys/time.h>

/* timestamp in us */
long long get_timestamp(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);

	return (((long long) t.tv_sec) * 1000000LL) +
		((long long) t.tv_usec);
}

/* 
 * for demo how to print timestamp,
 * use %lld to print long long, otherwise you get strange result 
 */
void print_timestamp(const char *type, long long ts)
{
	printf("[%10lld] : %s\n", ts, type);
}
