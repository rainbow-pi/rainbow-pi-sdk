#ifndef __LIBVE_DECORDER_H__
#define __LIBVE_DECORDER_H__
//#include <libcedarv.h>
//#include <libve_typedef.h>
#include <vdecoder.h>
//#include "cedarx_hardware.h"

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <pthread.h>
//#include "CDX_Resource_Manager.h"

#include <type_camera.h>

//#define VE_MUTEX_ENABLE 1
//
//#if  VE_MUTEX_ENABLE
//#define decorder_mutex_lock(x)		ve_mutex_lock(x)
//#define decorder_mutex_unlock(x) 	ve_mutex_unlock(x)
//#define decorder_mutex_init(x,y) 	ve_mutex_init(x,y)
//#define decorder_mutex_destroy(x) 	ve_mutex_destroy(x)
//
//#else
//#define decorder_mutex_lock(x)
//#define decorder_mutex_unlock(x)
//#define decorder_mutex_init(x,y)
//#define decorder_mutex_destroy(x)
//
//#endif
 
#ifdef __cplusplus
extern "C" {
#endif

int CameraHal_LRFlipFrame(int nFormat, int nWidth, int nHeight, char* pAddrY, char* pAddrC);

typedef struct DecodeHandle{
	//ve_mutex_t	mDecoderMutex ;	
	VideoDecoder* mDecoder; //cedarv_decoder_t
	VideoStreamInfo mStream_info;  //cedarv_stream_info_t
	VConfig mDecoderConfig;
	VideoStreamDataInfo mData_info; //cedarv_stream_data_info_t
}DecodeHandle;

DecodeHandle* libveInit(int capfmt, int outfmt, int w, int h, int *subw, int *subh, int fps, int *scl);
int	libveExit(DecodeHandle *handle);
int libveDecode(DecodeHandle *handle, const void *data_in, int data_size, int64_t pts);
VideoPicture* libveGetFrame(DecodeHandle *handle, int streamIdx);
int libveReleaseFrame(DecodeHandle *handle, VideoPicture *picture);

#ifdef __cplusplus
}
#endif

#endif  /* __LIBVE_DECORDER_H__ */

