/*
**
** Copyright (C) 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef _HWDEFINE_H
#define _HWDEFINE_H

struct view_info
{
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h; 
};

struct src_info
{
	unsigned int w;
	unsigned int h;
	unsigned int crop_x;
	unsigned int crop_y;
    unsigned int crop_w;
	unsigned int crop_h;
	unsigned int format;
	int color_space;	//disp_color_space
};

struct surface
{
	struct src_info src;
	struct view_info view;
};

#ifndef E_HWC_FORMAT
#define E_HWC_FORMAT
enum e_hwc_format
{
	HWC_FORMAT_MINVALUE     = 0x50,
    HWC_FORMAT_RGBA_8888    = 0x51,
    HWC_FORMAT_RGB_565      = 0x52,
    HWC_FORMAT_BGRA_8888    = 0x53,
    HWC_FORMAT_YCbYCr_422_I = 0x54,
    HWC_FORMAT_CbYCrY_422_I = 0x55,
    HWC_FORMAT_MBYUV420		= 0x56,
    HWC_FORMAT_MBYUV422		= 0x57,
    HWC_FORMAT_YUV420PLANAR	= 0x58,
    HWC_FORMAT_YUV411PLANAR 	= 0x59,
	HWC_FORMAT_YUV422PLANAR 	= 0x60,
	HWC_FORMAT_YUV444PLANAR 	= 0x61,
	HWC_FORMAT_YUV420UVC		= 0x62,
	HWC_FORMAT_YUV420VUC		= 0x63,
	HWC_FORMAT_YUV422UVC		= 0x64,
	HWC_FORMAT_YUV422VUC		= 0x65,
	HWC_FORMAT_YUV411UVC		= 0x66,
	HWC_FORMAT_YUV411VUC		= 0x67,
    HWC_FORMAT_DEFAULT      = 0x99,    // The actual color format is determined
    HWC_FORMAT_MAXVALUE     = 0x100
};
#endif

#ifndef LIBHWCLAYERPARA_T
#define LIBHWCLAYERPARA_T

typedef struct
{
	unsigned long	number;
	
	unsigned long	top_y;				// the address of frame buffer, which contains top field luminance
	unsigned long	top_c;				// the address of frame buffer, which contains top field chrominance
	unsigned long	bottom_y;			// the address of frame buffer, which contains bottom field luminance
	unsigned long	bottom_c;			// the address of frame buffer, which contains bottom field chrominance

	signed char 	bProgressiveSrc;	// Indicating the source is progressive or not
	signed char 	bTopFieldFirst; 	// VPO should check this flag when bProgressiveSrc is FALSE
	unsigned long	flag_addr;			//dit maf flag address
	unsigned long	flag_stride;		//dit maf flag line stride
	unsigned char	maf_valid;
	unsigned char	pre_frame_valid;
	unsigned int	handle;
}libhwclayerpara_t;
#endif
#endif //_HWDEFINE_
