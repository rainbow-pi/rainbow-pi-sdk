
#ifndef __LIB__CAMERA__TYPE__H__
#define __LIB__CAMERA__TYPE__H__

typedef struct PREVIEWINFO_t
{
	int left;
	int top;
	int width;			// preview width
	int height;			// preview height
}PREVIEWINFO_t, RECT_t;

/* support 4 ROI region */
typedef struct Venc_ROI_Config
{
	int                     bEnable;
	int                		index; /* (0~3) */
	int                     nQPoffset;
	RECT_t                  sRect;
}Venc_ROI_Config;

typedef struct V4L2BUF_t
{
	char*	addrPhyY;		// physical Y address of this frame
	char*	addrVirY;		// virtual Y address of this frame
	char*    addrPhyC;
	char*    addrVirC;
	unsigned int	width;
	unsigned int	height;
	int 			index;			// DQUE id number
	long long		timeStamp;		// time stamp of this frame, unit:us
	RECT_t			crop_rect;
	int				format; //V4L2_PIX_FMT_NV12
	int				mColorSpace;	//enum v4l2_colorspace, V4L2_COLORSPACE_JPEG
	void*           overlay_info;
	
	// thumb 
	unsigned char	isThumbAvailable;
	unsigned char	thumbUsedForPreview;
	unsigned char	thumbUsedForPhoto;
	unsigned char	thumbUsedForVideo;
	char*	thumbAddrPhyY;		// physical Y address of thumb buffer
	char*	thumbAddrVirY;		// virtual Y address of thumb buffer
	char*	thumbAddrPhyC;		// physical C address of thumb buffer
	char*	thumbAddrVirC;		// virtual C address of thumb buffer
	unsigned int	thumbWidth;
	unsigned int	thumbHeight;
	RECT_t			thumb_crop_rect;
	int 			thumbFormat;
	
	int 			refCnt; 		// used for releasing this frame

	unsigned int	bytesused;      // used by compressed source
	unsigned int    isDecodeSrc;

	int				ispPicVar;		// used for encoder 3D filter

    int             frameNum;
    int             frameOffset;
    int             fps;

	Venc_ROI_Config	roi_area[4];
}V4L2BUF_t;

typedef enum MEDIA_SRC_MODE
{
	MEDIA_SRC_PUSH_MODE,
	MEDIA_SRC_PULL_MODE
}MEDIA_SRC_MODE;

//typedef struct VIDEOINFO_t
//{
//	int video_source;   //CDX_VIDEO_SOURCE_CAMERA
//	int src_height;     // source video frame size.
//	int src_width;
//	int height;			// camcorder video frame height
//	int width;			// camcorder video frame width
//	int frameRate;		// camcorder video frame rate, *1000
//	int bitRate;		// camcorder video bitrate
//	short profileIdc;   //VENC_H264ProfileMain
//	short levelIdc;     //VENC_H264Level31
//
//	int geo_available;
//	int latitudex10000;
//	int longitudex10000;
//
	// rotate
//	int rotate_degree;		// only support 0, 90, 180 and 270
//	int MaxKeyFrameInterval;
//
//	int is_compress_source; // 0 for common source 1: for mjpeg source 2: for h264 source
//	int mPixelFormat;   //V4L2_PIX_FMT_NV12, V4L2_PIX_FMT_MJPEG
//}VIDEOINFO_t;
//
//typedef enum AUDIO_ENCODER_TYPE
//{
//	AUDIO_ENCODER_AAC_TYPE,
//	AUDIO_ENCODER_LPCM_TYPE,    //only used by mpeg2ts
//	AUDIO_ENCODER_PCM_TYPE,
//	AUDIO_ENCODER_MP3_TYPE,
//}AUDIO_ENCODER_TYPE;
//typedef struct AUDIOINFO_t
//{
//	int sampleRate;
//	int channels;
//	int bitRate;
//	int bitsPerSample;
//	int audioEncType;  // AUDIO_ENCODER_AAC_TYPE,
//}AUDIOINFO_t;

//typedef struct ENCEXTRADATAINFO_t //don't touch it, because it also defined in type.h
//{
//	char *data;
//	int length;
//}ENCEXTRADATAINFO_t;

//typedef struct ENC_BUFFER_t
//{
//    int addrY;
//	int addrCb;
//	int addrCr;
//	int width;
//	int height;
//	RECT_t crop_rect;
//	int force_keyframe;
//	void*  overlay_info;
//	int format; //V4L2_PIX_FMT_NV12
//
//	int	ispPicVar;		// used for encoder 3D filter
//
//	Venc_ROI_Config	roi_area[4];
//}ENC_BUFFER_t;
/*
typedef enum JPEG_COLOR_FORMAT
{
    JPEG_COLOR_YUV444,
    JPEG_COLOR_YUV422,
    JPEG_COLOR_YUV420,
    JPEG_COLOR_YUV411,
    JPEG_COLOR_YUV420_NV12,
    JPEG_COLOR_YUV420_NV21,
    JPEG_COLOR_TILE_32X32,
    JPEG_COLOR_CSIARGB,
    JPEG_COLOR_CSIRGBA,
    JPEG_COLOR_CSIABGR,
    JPEG_COLOR_CSIBGRA
}JPEG_COLOR_FORMAT;

typedef struct JPEG_ENC_t
{
	int				src_w;
	int				src_h;
	int				pic_w;
	int				pic_h;
	int				addrY;
	int				addrC;
	int				colorFormat;
	int				quality;
	int				rotate;

	int				scale_factor;
	double			focal_length;
	
	int				thumbWidth;
	int				thumbHeight;

	unsigned char	enable_crop;
	int				crop_x;	
	int				crop_y;
	int				crop_w;
	int				crop_h;

	// gps exif
	unsigned char	enable_gps;
	double      	gps_latitude;
	double			gps_longitude;
	long        	gps_altitude;  
	long        	gps_timestamp;
	char			gps_processing_method[100];
	int 			whitebalance;
	char  			CameraMake[64];//for the cameraMake name
	char  			CameraModel[64];//for the cameraMode
	char  			DateTime[21];//for the data and time
	void*           pover_overlay;
}JPEG_ENC_t;
*/
#endif // __LIB__CAMERA__TYPE__H__

