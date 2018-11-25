/*
 * This file is part of the Rainbow Pi project.
 * Copyright (c) 2018 YuanJun <yuanjun2006@outlook.com>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * fileutil.c
 *     file operation utilities
 *
 */

/*
 * Please visit our E-Shop at https://mvdevice.taobao.com/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fileutil.h"

int file_write(const char *fn, void *buf, size_t len)
{
	int ret;
	
	FILE *f = fopen(fn, "w");
	if (f) {
		ret = fwrite(buf, 1, len, f);
		fflush(f);
		fclose(f);
		return ret;
	}

	printf("[%s]\n", __FUNCTION__);
	printf("\tFailed!\n");
	return -1;
}

int file_append(const char *fn, void *buf, size_t len)
{
	int ret;
	
	FILE *f = fopen(fn, "a+");
	if (f) {
		ret = fwrite(buf, 1, len, f);
		fflush(f);
		fclose(f);
		return ret;
	}

	printf("[%s]\n", __FUNCTION__);
	printf("\tFailed!\n");
	return -1;
}
