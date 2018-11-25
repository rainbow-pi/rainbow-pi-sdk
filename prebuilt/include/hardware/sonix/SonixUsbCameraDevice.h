#ifndef SONIX_UVC_H
#define SONIX_UVC_H

//#include <linux/videodev2.h>
//#include <linux/version.h>

//#define V4L2_PIX_FMT_H264 v4l2_fourcc('H','2','6','4') /* H264 */
#define V4L2_PIX_FMT_MP2T v4l2_fourcc('M','P','2','T') /* MPEG-2 TS */

//#ifndef KERNEL_VERSION
//#define KERNEL_VERSION(a,b,c) ((a)<<16+(b)<<8+(c))
//#endif

//#if LINUX_VERSION_CODE >= KERNEL_VERSION (2,6,32)
//#define V4L_BUFFERS_DEFAULT	10//16
//#define V4L_BUFFERS_MAX		16//32
//#else
#define V4L_BUFFERS_DEFAULT	10
#define V4L_BUFFERS_MAX		10
//#endif


namespace zeta {
/* Video buffers */
typedef struct Mem_Map_t{
	void *	mem[V4L_BUFFERS_MAX]; 
	int 	length;
} Mem_Map_t;
	
class SonixUsbCameraDevice {
public:
    SonixUsbCameraDevice();
    ~SonixUsbCameraDevice();
	
	void* readOneH264Frame(v4l2_buffer *v4l2_buf);
	int releaseOneH264Frame(int index);	
	int waitH264FrameReady(void);
	int openH264CameraDevice(const char *dev_name, int width, int height);
	int closeH264CameraDevice(void);
	int isSonixUVCChip(int dev);
	int initCameraParam(int dev);
	void useH264DevRec(bool isH264);
	int startRecording();
	int stopRecording();
	bool isUseH264DevRec(void);	
	int setVideoBitRate(int32_t bitRate);
	int setVideoSize(int w, int h);
	int updateInternalTime(int dev);
	int tryH264FmtSize(int w, int h);
private:
	int video_open(const char *devname);
	void uvc_set_control(int dev, unsigned int id, int value);
	int video_set_format(int dev, unsigned int w, unsigned int h, unsigned int format);
	int video_set_framerate(int dev);
	int video_reqbufs(int dev, int nbufs);
	int video_querybuf(int dev, Mem_Map_t* mem_map, int nbufs);
	int video_unmapBuf(Mem_Map_t* mem_map, int nbufs);
	int video_enable(int dev, int enable);
	void video_query_menu(int dev, unsigned int id);
	void video_list_controls(int dev);
	void video_enum_inputs(int dev);
	int video_get_input(int dev);
	int video_dequeue_buffer(int dev, struct v4l2_buffer *buf);
	int video_requeue_buffer(int dev, int index);
	int video_set_input(int dev, unsigned int input);
	int video_try_fmt_size(int dev, int * width, int * height, unsigned int format);

private:
	Mem_Map_t	 		mH264MemMap;
	int 				mH264NumBufs;
	int 				mH264Fd;
	bool				mUseH264DevRec;
	char				mH264DevName[16];

};

};
#endif
