#ifndef __ZETA_CAMERA_INTERFACE__
#define __ZETA_CAMERA_INTERFACE__
#include <MemoryBase.h>
#include <ZetaDisplayInterface.h>
#include <type_camera.h>
#include <sys/mman.h>
#include <camera.h>
#include <hardware/camera.h>
//#include <HALCameraFactory.h>
#include <include_adas/Adas_interface.h>
#include "CameraHeapMemory.h"

#include <ZetaRecorder.h>

#define WTM_POSX 0
#define WTM_POSY 0
#define CAM_CNT 2
enum{
	CAM_CSI = 0,
	CAM_UVC,
	CAM_TVD
};

#define CAM_CSI_NET CAM_CNT+CAM_CSI
#define CAM_UVC_NET CAM_CNT+CAM_UVC

#define STORAGE_PATH "/mnt/extsd/"
#define VIDEO_PATH "/mnt/extsd/video/"
#define PHOTO_PATH "/mnt/extsd/photo/"
#define VIDEO_TYPE ".mp4"
#define PHOTO_TYPE ".jpg"
#define FRONT_TYPE "A"
#define REAR_TYPE "B"

enum{
    INTERFACE_VIDEO_TYPE = 0,
    INTERFACE_PHOTO_TYPE,
};

typedef enum {
	PicResolution2M = 0,
	PicResolution5M,
	PicResolution8M,
	PicResolution12M,
	ImageQuality16M,
}PicResolution_t;

typedef enum {
	VedioQuality4K15Fps = 0,	
	VedioQuality2_7K30Fps,
	VedioQuality1080P60Fps,
	VedioQuality1080P30Fps,
	VedioQuality720P120Fps,
	VedioQuality720P60Fps,
	VedioQuality720P30Fps,
	VedioQuality4K30Fps = 8,
	VedioQuality720x720_60Fps = 7, //customer demand
}VedioQuality_t;

enum {
	CRASH_WARN=0,
	LEFT_WARN,
	RIGHT_WARN,
	LEFT_CRASH_WARN,
	RIGHT_CRASH_WARN,
	NO_WARN
};

//#define CSI_1080P
#define UVC_1080P	//has no effect on recorder

#define FRONT_CAM_FRAMERATE 60
#define BACK_CAM_FRAMERATE 25

#ifdef CRANE_SDV
#define FRONT_CAM_FRAMERATE 60
#endif

#define CAM_BITRATE (5*1024*1024)
#define FRONT_CAM_BITRATE (15*1024*1024)
#define BACK_CAM_BITRATE (8*1024*1024)

#define UVC_FLIP

namespace zeta {



class ZetaCamera {
private:
	typedef void (*notify_callback)(int32_t msgType,
									int32_t ext1,
									int32_t ext2,
									void* user);

	typedef void (*data_callback)(int32_t msgType,
								  const camera_memory_t *dataPtr,
								  camera_frame_metadata_t *metadata,
								  void* user);

	typedef int32_t (*data_callback_timestamp)(int64_t timestamp,
			int32_t msgType,
			const camera_memory_t *dataPtr,
			int bufIdx,
			void *user);
	
	
	
	static void __notify_cb(int32_t msg_type, int32_t ext1, int32_t ext2, void *user)
	{
		//ZLOGD();
        ZetaCamera *__this = static_cast<ZetaCamera *>(user);

		__this->notifyCallback(msg_type, ext1, ext2, __this->mCbUser);
	}

	static void __data_cb(int32_t msg_type,
						  const camera_memory_t *data, unsigned int index,
						  camera_frame_metadata_t *metadata,
						  void *user)
	{
		//ZLOGD();
        ZetaCamera *__this = static_cast<ZetaCamera *>(user);
        CameraHeapMemory* mem(static_cast<CameraHeapMemory *>(data->handle));
        if (index >= mem->mNumBufs) {
            ZLOGE("%s: invalid buffer index %d, max allowed is %d", __FUNCTION__, index, mem->mNumBufs);
            return;
        }

		__this->dataCallback(msg_type, (camera_memory_t *)mem->mBuffers[index], metadata, __this->mCbUser);
	}

	static int __data_cb_timestamp(int64_t timestamp, int32_t msg_type,
								   const camera_memory_t *data, unsigned index,
								   int bufIdx, void *user)
	{
		//ZLOGD();
		int ret = 0;
        ZetaCamera *__this = static_cast<ZetaCamera *>(user);
        // Start refcounting the heap object from here on.  When the clients
        // drop all references, it will be destroyed (as well as the enclosed
        // MemoryHeapBase.
        CameraHeapMemory* mem(static_cast<CameraHeapMemory *>(data->handle));
        if (index >= mem->mNumBufs) {
            ZLOGE("%s: invalid buffer index %d, max allowed is %d", __FUNCTION__,
				  index, mem->mNumBufs);
            return -1;
        }

		ret = __this->dataCallbackTimestamp(timestamp, msg_type, (camera_memory_t *)mem->mBuffers[index], bufIdx, __this->mCbUser);

		
		return ret;
	}
	
	notify_callback         mNotifyCb;
	data_callback           mDataCb;
	data_callback_timestamp mDataCbTimestamp;
	void *mCbUser;
	
	//--------------- ˮӡ --------------------------
	void enableWaterMark();
	void enableLicenseWaterMark(bool IsTimeWM ,bool IsLicenseWM ,const char* licenseWM);
	void disableWaterMark();
	
	bool mWaterMarking;
	char strLWM[30];
	bool mLWM;
	bool mTWM;
	//-----------------DE 2-------------------------
	ZetaDisplay		*mZetaDisplay;
	int mHlay;
	ZETA_RECT mRect;
	//-----------------DE 2-------------------------
	
	int mPreviewFlip;
	//----------------------------------------------
	int mCameraId;
	camera_device_t *mDevice;
	
	//---------------- record ----------------
	ZetaRecorder* mRecorder;
	//----------------------------------------
	//---- preview ------
	unsigned int 	g_SrvWidth;
	unsigned int	g_SrvHeight;
	unsigned int 	g_PreviewSizeW;
	unsigned int	g_PreviewSizeH;
	int 			g_FrameRate;
	unsigned int	g_CaptureBufferCount;
	unsigned int	g_BufferFrameNum;
	int				g_Rotation;
	//---- recorder ------
	int g_RecWidth;
	int	g_RecHeight;
	int g_RecFrameRate;
	int g_RecBitRate;

	bool mPreviewing;
	bool mIsRecording;
	bool mIsP2PStreaming;
	int mDrawAlign;
    int mAdasTipsMode;
	
public:
	ZetaCamera(ZETA_RECT &rect, int camera_id);
	~ZetaCamera();

	int initCamera(unsigned int width, unsigned int height, unsigned int preview_sz_w, unsigned int preview_sz_h,
				   int framate, unsigned int captureBufferCount=10, unsigned int bufferFrameNum=1, int rotation=0);
	void startPreview(void);
	void stopPreview(void);
	void release();
	ZetaDisplay* getDisp(void);
	bool isPreviewing();
    bool isRecording();
	void takePicture(void);
	void suspend();
	void resume();
	void setLWaterMark();
	int generateFile(std::string &file, int type, int cam_id);
	int getInputSource();
	int getTVinSystem();
	int getSupportVideoFps(int width,int height);
	int getPictureSizeMode();
	
	void setPicResolution(PicResolution_t quality);
	void setPicResolution(int width,int height);
	void setPicQuality(int percent);
	void setPictureSizeMode(int mode);
	void setPictureMode();
	void setWhiteBalance(const char *mode);
	void setContrast(int mode);
	void setExposure(int mode);
	void setLightFreq(int mode);
	void setVfilp(int mode);
	void setDightZoom(int value);
	void stopMotionTakepicture(void);
	void setContinuousPicture(int mode);
	void setLWaterMark(bool IsTimeWM ,bool IsLicenseWM ,const char *licenseWM);	
	void setWaterMarkPos(int h);
	void setPreviewRotation(int drgee);
	void setBufferCnt(int cnt);
	void setCameraFlip(bool flip);
	void setUvcMode(int mode);
	void startAdas();
    void stopAdas();
    void adasSetTipsMode(int mode);
    void algorithm_car(ADASOUT_IF *mAd_if);
	int32_t sendCommand(int32_t cmd, int32_t arg1, int32_t arg2);
//	int startRecord(int cam_type);
//	int startRecord(int cam_type, CdrRecordParam_t param);
	
	
	void setCallbacks(notify_callback notify_cb,
					  data_callback data_cb,
					  data_callback_timestamp data_cb_timestamp,
					  void* user);
	void enableMsgType(int32_t msgType);
	void disableMsgType(int32_t msgType);

	void releaseRecordingFrame(void *data);

	int startP2P(int srcW, int srcH, int dstW, int dstH, int framerate, int bitrate);
	int stopP2P();
    int loopRecord(int id);
	int startRecord(int id);
	int stopRecord(int id);
	void notifyCallback(int32_t msgType, int32_t ext1, int32_t ext2, void* user);
    void dataCallback(int32_t msgType, const camera_memory_t *dataPtr, camera_frame_metadata_t *metadata, void* user);
	int dataCallbackTimestamp(int64_t timestamp, int32_t msgType, const camera_memory_t *dataPtr, int bufIdx, void *user);
	
	void setVideoRecordParam(int w, int h, int framerate, int bitrate);
	class OnAdasDataListener	
	{   
		public:		
			OnAdasDataListener()		
			{		
			}		
			virtual ~OnAdasDataListener()		
			{
			}		
			virtual void show_AdasWarn(int mode) = 0;	
	};
    
	class OnDataListener	
	{   
		public:		
			OnDataListener()		
			{		
			}		
			virtual ~OnDataListener()		
			{
			}		
			virtual void onData(H264OutputBuffer *outputBuffer) = 0;	
	};
	
	class EventHandler : public ZetaRecorder::OnHandleMessage
	{	
		public:		
			EventHandler(ZetaCamera *mCamera)
			{
				mZetaCamera = mCamera;
			}
			~EventHandler()
			{

			}
			void handleMessage(H264OutputBuffer *outputBuffer)
			{
				mZetaCamera->mOnDataListener->onData(outputBuffer);
				
				//printf("by hero onZetaH264Data size0 = %d, sizeo1 = %d, head_size = %d\n", outputBuffer->nSize0, outputBuffer->nSize1, outputBuffer->frame_info.nLength);
			}
		private:
			ZetaCamera *mZetaCamera;
	};

	void setOnAdasDataListener(OnAdasDataListener *pListener);
    void setOnDataListener(OnDataListener *pListener);
    OnAdasDataListener *mOnAdasDataListener;
	OnDataListener *mOnDataListener;
	EventHandler *mEventHandler;	
};
}; //namespace zeta
#endif // __ZETA_CAMERA_INTERFACE__
