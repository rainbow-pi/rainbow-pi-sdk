#ifndef __HAL_V4L2_CAMERA_DEVICE_H__
#define __HAL_V4L2_CAMERA_DEVICE_H__
#include <thread>
#include "CameraDebug.h"
/*
 * Contains declaration of a class V4L2CameraDevice.
 */

//#include <ui/Rect.h>
#include <fcntl.h> 
#include <utils/Thread.h>
#include <utils/Mutex.h>
#include <utils/Condition.h>
#include <hardware/camera.h>
#include <videodev2.h>

#include <type_camera.h>

#include "OSAL_Queue.h"

#include <ThreadDefs.h>

#include <utils/Mutex.h>

#ifdef WATERMARK_ENABLE
#include <include_watermark/water_mark_interface.h>
#endif
#ifdef MOTION_DETECTION_ENABLE
#include "motionDetect/MotionDetect.h"
#endif
#include "LibveDecoder.h"
#include "sonix/SonixUsbCameraDevice.h"

#ifdef CONFIG_SUPPORT_TVIN_DEVICE
#include "tvin/TVDecoder.h"
#endif

#ifdef ADAS_ENABLE
#include "adas/CameraAdas.h"
#endif

#ifdef QRDECODE_ENABLE
#include "qrdecode/CameraQrDecode.h"
#endif


#define DEBUG_V4L2_CAMERA_USED_BUFFER_CNT       (0)
#define DEBUG_RELEASE_FRAME_TIME                (0)
#define DEBUG_GET_FRAME_INTERVAL                (0)

#define DEFAULT_BUFFER_NUM                      5
#define DEFAULT_FRAME_NUM_IN_BUFFER             1
#define DEFAULT_CONTINUOUS_PICTURE_NUMBER       20
#define DEFAULT_CONTINUOUS_PICTURE_INTERVAL     200

#define PREVIEW_FRAME_RATE                      30

#define MAX_PICTURE_SIZE (2592*1936*3>>1)

#define ROI_AREA_NUM    4

namespace zeta {

class CameraHardware;
class CallbackNotifier;
class PreviewWindow;

/*
 * 
 */
typedef struct HALCameraInfo{
    char    device_name[16];        // device node name, such as "/dev/video0"
    int     device_id;              // device id for camera share with the same CSI
    int     facing;                 // facing front or back
    int     orientation;            // 
    bool    fast_picture_mode;      // main_channel and sub_channel all output, so don't need reset parameter to sensor when preview mode turn to take picture mode/record mode.
    bool    is_uvc;                 // usb camera
}HALCameraInfo;

enum TAKE_PICTURE_STATE {
    TAKE_PICTURE_NULL,          // do not take picture
    TAKE_PICTURE_NORMAL,        // stream off -> stream on -> take picture -> stream off -> stream on
    TAKE_PICTURE_FAST,          // normal mode but do not need to stream off/on
    TAKE_PICTURE_RECORD,        // take picture in recording
    TAKE_PICTURE_CONTINUOUS,
    TAKE_PICTURE_CONTINUOUS_FAST
};

enum CAMERA_DEV {
    CAMERA_CSI = 0x00,
    CAMERA_USB = 0x01,
    CAMERA_TVD = 0x02,
    CAMERA_UNKNOWN = 0xFFFF,
};

typedef struct VideoPictureBuffer {
    VideoPicture    *picture[2];
    int             isUse;
} VideoPictureBuffer;

typedef struct V4l2PreviewBuffer_tag {
	char *addrPhyY; // physical Y address of this frame
	char *addrVirY; // virtual Y address of this frame
	char *addrPhyC;
	char *addrVirC;
	unsigned int	width;
	unsigned int	height;
	RECT_t			crop_rect;
	int				format; //V4L2_PIX_FMT_NV12
	int				mColorSpace;	//enum v4l2_colorspace, V4L2_COLORSPACE_JPEG
} V4l2PreviewBuffer_tag;

/* 
 * V4L2CameraDevice
 */
class V4L2CameraDevice {
public:
    /* Constructs V4L2CameraDevice instance. */
    V4L2CameraDevice(CameraHardware* camera_hal, PreviewWindow * preview_window, CallbackNotifier * cb);
    /* Destructs V4L2CameraDevice instance. */
    ~V4L2CameraDevice();

    /***************************************************************************
     * V4L2Camera device abstract interface implementation.
     * See declarations of these methods in V4L2Camera class for
     * information on each of these methods.
     **************************************************************************/

public:
    static void saveDataInFile(const char *filename, void *buffer, int bufsize);
    static void calculateCrop(RECT_t * rect, int new_zoom, int max_zoom, int width, int height);
    static void showformat(int format, const char *str);
    static void YUYVToNV12(const void* yuyv, void *nv12, int width, int height);
    static void YUYVToNV21(const void* yuyv, void *nv21, int width, int height);
    static void NV21Rotate90Degree(unsigned char* dst_addr, unsigned char* src_addr, unsigned int width, unsigned int height);
    static void NV21Rotate270Degree(unsigned char* dst_addr, unsigned char* src_addr, unsigned int width, unsigned int height);
    static bool isNeedSendFrame(int64_t &wantedPts, int64_t pts);

    /* Connects to the camera device.
     * Since there is no real device to connect to, this method does nothing,
     * but changes the state.
     */
    status_t connectDevice(HALCameraInfo * halInfo);

    /* Disconnects from the camera device.
     * Since there is no real device to disconnect from, this method does
     * nothing, but changes the state.
     */
    status_t disconnectDevice();

    /* Starts the camera device. */
    status_t startDevice(int width, int height, int sub_w, int sub_h, uint32_t pix_fmt, int framerate, bool normalPic);

    /* Stops the camera device. */
    status_t stopDevice();

    status_t cameraDrawBlack(void);

    /* Gets current preview fame into provided buffer. */
    status_t getPreviewFrame(void* buffer);

    /* Starts delivering frames captured from the camera device.
     * This method will start the worker thread that would be pulling frames from
     * the camera device, and will deliver the pulled frames back to the emulated
     * camera via onNextFrameAvailable callback. This method must be called on a
     * connected instance of this class with a started camera device. If it is
     * called on a disconnected instance, or camera device has not been started,
     * this method must return a failure.
     * Param:
     *  one_burst - Controls how many frames should be delivered. If this
     *      parameter is 'true', only one captured frame will be delivered to the
     *      V4L2Camera. If this parameter is 'false', frames will keep
     *      coming until stopDeliveringFrames method is called. Typically, this
     *      parameter is set to 'true' only in order to obtain a single frame
     *      that will be used as a "picture" in takePicture method of the
     *      V4L2Camera.
     * Return:
     *  NO_ERROR on success, or an appropriate error status.
     */
    status_t startDeliveringFrames();
    
    /* Stops delivering frames captured from the camera device.
     * This method will stop the worker thread started by startDeliveringFrames.
     * Return:
     *  NO_ERROR on success, or an appropriate error status.
     */
    status_t stopDeliveringFrames();


    bool captureThread();
    bool previewThread();
    bool pictureThread();
    bool continuousPictureThread();
    int getHorVisualAngle();
    int getVerVisualAngle();

    //for get pic var to encoder
    int getPicVar();

    int tryFmt(int format);                         // check if driver support this format
    int tryFmtSize(int * width, int * height);      // check if driver support this size
    int setFrameRate(int rate);                     // set frame rate from camera.cfg
    int getFrameRate(int *fps);                     // get v4l2 device current frame rate
    int setPreviewFlip(int previewFlip);
    int setPreviewRotation(int rotation);

    int enumSize(char * pSize, int len);
    int enumSizeAndFrame(char *pSize, int len);
    int getFullSize(int * full_w, int * full_h);
    int getSuitableThumbScale(int full_w, int full_h);

    int setImageEffect(int effect);
    int setWhiteBalance(int wb);
    
    int setContrastValue(int value);
    int setBrightnessValue(int value);
    int setSaturationValue(int value);
    int setHueValue(int value);
    int setSharpnessValue(int value);
    int setHflip(int value);
    int setVflip(int value);
    int setPowerLineFrequencyValue(int value);  //value = V4L2_CID_POWER_LINE_FREQUENCY_50HZ

    status_t getContrastCtrl(struct v4l2_queryctrl *ctrl);
    status_t getBrightnessCtrl(struct v4l2_queryctrl *ctrl);
    status_t getSaturationCtrl(struct v4l2_queryctrl *ctrl);
    status_t getHueCtrl(struct v4l2_queryctrl *ctrl);
    status_t getSharpnessCtrl(struct v4l2_queryctrl *ctrl);

    int setTakePictureCtrl();

    // exposure
    int setExposureMode(int mode);
    int setExposureCompensation(int val);
    int setExposureWind(int num, void *areas);
    
    int setFlashMode(int mode);
    
    // af
    int setAutoFocusInit();
    int setAutoFocusRelease();
    int setAutoFocusRange(int range);
    int setAutoFocusWind(int num, void *areas);
    int setAutoFocusStart();
    int setAutoFocusStop();
    int getAutoFocusStatus();
    
    int set3ALock(int lock);
    
    void releasePreviewFrame(int index);            // Q buffer for encoder

    int getCurrentFaceFrame(void * frame);

    void setThumbUsedForVideo(bool isThumbUsedForVideo)
    {
        mIsThumbUsedForVideo = isThumbUsedForVideo;
    }

    inline void setCrop(int new_zoom, int max_zoom)
    {
        mNewZoom = new_zoom;
        mMaxZoom = max_zoom;
    }

    inline void setHwEncoder(bool hw)
    {
        mUseHwEncoder = hw;
    }

    inline void setTakePictureState(TAKE_PICTURE_STATE state)
    {
        pthread_mutex_lock(&mCaptureMutex);
        ZLOGV("setTakePictureState %d", state);
        mTakePictureState = state;
        pthread_mutex_unlock(&mCaptureMutex);
    }
    
    void startContinuousPicture();
    void stopContinuousPicture();
    void setContinuousPictureNumber(int cnt);
    void setContinuousPictureInterval(int timeMs);
    
    /*
     * State checkers.
     */
    inline bool isConnected() const
    {
        /* Instance is connected when its status is either"connected", or
         * "started". */
        return mCameraDeviceState == STATE_CONNECTED || mCameraDeviceState == STATE_STARTED;
    }
    inline bool isStarted() const
    {
        return mCameraDeviceState == STATE_STARTED;
    }

    void setVideoBufferFrameNum(int value);
    void setVideoCaptureBufferNum(int value);

#ifdef USE_MP_CONVERT
    // use for YUYV to YUV420C
    void YUYVToYUV420C(const void* yuyv, void *yuv420, int width, int height);
    void NV21ToYV12(const void* nv21, void *yv12, int width, int height);
#endif

    status_t startRecording();
    status_t stopRecording();
    status_t initSonixUsbCameraDevice(char *dev_name);
    status_t deinitSonixUsbCameraDevice();
    void setVideoBitRate(int32_t bitRate);
    bool isDualStreamDevice();
    int setVideoSize(int w, int h);
    int getCaptureFormat();
    int getVideoFormat();
    int getColorSpace();

    static void getTimeString(char *str, int len);
    int getInputSource();
    int getTVinSystem();

    status_t getUnusedPicBuffer(int *index);
    status_t getDecodeFrame(int index);
    status_t releaseDecodeFrame(int index);
    status_t releasePreviewFrameDirectly(int index);

    int setColorFx(int value);

    status_t setUvcGadgetMode(int value);

    status_t getExifInfo(struct isp_exif_attribute *exif_attri);
    status_t getLightValue(int *lightvalue);
    int getSnrValue();


    /***************************************************************************
     * Worker thread management overrides.
     * See declarations of these methods in V4L2Camera class for
     * information on each of these methods.
     **************************************************************************/
protected:

    // -------------------------------------------------------------------------
    // extended interfaces here <***** star *****>
    // -------------------------------------------------------------------------

    class DoCaptureThread : public Thread {
        V4L2CameraDevice*   mV4l2CameraDevice;
        bool                mRequestExit;
    public:
        DoCaptureThread(V4L2CameraDevice* dev):
            mV4l2CameraDevice(dev),
            mRequestExit(false) {
        }
        void startThread() {
            run("CameraCaptureThread", PRIORITY_URGENT_DISPLAY);
        }
        void stopThread() {
            mRequestExit = true;
        }
        virtual bool threadLoop() {
            if (mRequestExit) {
                return false;
            }
            return mV4l2CameraDevice->captureThread();
        }
    };
    
    class DoPreviewThread : public Thread {
        V4L2CameraDevice*   mV4l2CameraDevice;
        bool                mRequestExit;
    public:
        DoPreviewThread(V4L2CameraDevice* dev):
            mV4l2CameraDevice(dev),
            mRequestExit(false) {
        }
        void startThread() {
            run("CameraPreviewThread", PRIORITY_URGENT_DISPLAY);
        }
        void stopThread() {
            mRequestExit = true;
        }
        virtual bool threadLoop() {
            if (mRequestExit) {
                return false;
            }
            return mV4l2CameraDevice->previewThread();
        }
    };

    class DoPictureThread : public Thread {
        V4L2CameraDevice*   mV4l2CameraDevice;
        bool                mRequestExit;
    public:
        DoPictureThread(V4L2CameraDevice* dev):
            mV4l2CameraDevice(dev),
            mRequestExit(false) {
        }
        void startThread() {
            run("CameraPictrueThread", PRIORITY_AUDIO);
        }
        void stopThread() {
            mRequestExit = true;
        }
        virtual bool threadLoop() {
            if (mRequestExit) {
                return false;
            }
            return mV4l2CameraDevice->pictureThread();
        }
    };

    class DoContinuousPictureThread : public Thread {
        V4L2CameraDevice*   mV4l2CameraDevice;
        bool                mRequestExit;
    public:
        DoContinuousPictureThread(V4L2CameraDevice* dev):
            mV4l2CameraDevice(dev),
            mRequestExit(false) {
        }
        void startThread() {
            run("CameraContinuousPictrueThread", PRIORITY_AUDIO);
        }
        void stopThread() {
            mRequestExit = true;
        }
        virtual bool threadLoop() {
            if (mRequestExit) {
                return false;
            }
            return mV4l2CameraDevice->continuousPictureThread();
        }
    };


private:
    status_t openCameraDev(HALCameraInfo * halInfo);
    void closeCameraDev();
    status_t v4l2SetVideoParams(int width, int height, int sub_w, int sub_h, uint32_t pix_fmt);
    int v4l2setCaptureParams(int framerate);
    int v4l2ReqBufs(int * buf_cnt);
    int v4l2QueryBuf();
    int v4l2StartStreaming(); 
    int v4l2StopStreaming(); 
    int v4l2UnmapBuf();

    int v4l2WaitCameraReady();
    int getPreviewFrame(v4l2_buffer *buf);
    
    void dealWithVideoFrameSW(V4L2BUF_t * pBuf);
    void dealWithVideoFrameHW(V4L2BUF_t * pBuf);
    void dealWithVideoFrameTest(V4L2BUF_t * pBuf);
    
    /* Checks if it's the time to push new frame to continuous picture.
     * Note that this method must be called while object is locked. */
    bool isContinuousPictureTime();

#if 0  // face
    void waitFaceDectectTime();
#endif

    void singalDisconnect();

    status_t initV4l2Buffer();
    status_t destroyV4l2Buffer();
    status_t initVideoPictureBuffer();
    status_t destroyVideoPictureBuffer();
    status_t setFramesInV4L2BufNum();
    status_t rotationPreviewFrame(V4l2PreviewBuffer_tag *prev, int degree);

    // -------------------------------------------------------------------------
    // private data
    // -------------------------------------------------------------------------

    /* Locks this instance for parameters, state, etc. change. */
    Mutex                           mObjectLock;
    Mutex                           mReleaseBufferLock; //lock V4L2BUF_t mV4l2buf[NB_BUFFER].refCnt;

    // instance of CameraHardware
    CameraHardware                  *mCameraHardware;

    // instance of PreviewWindow
    PreviewWindow                   *mPreviewWindow;

    // instance of CallbackNotifier
    CallbackNotifier                *mCallbackNotifier;

    HALCameraInfo                   mHalCameraInfo;
    
    /* Defines possible states of the V4L2Camera device object.
     */
    enum CameraDeviceState {
        /* Object has been constructed. */
        STATE_CONSTRUCTED,
        /* Object has been connected to the physical device. */
        STATE_CONNECTED,
        /* Camera device has been started. */
        STATE_STARTED,
    };

    /* Object state. */
    CameraDeviceState               mCameraDeviceState;

    /* Defines possible states of the V4L2CameraDevice capture thread.
     */
    enum CaptureThreadState {
        /* Do not capture frame. */
        CAPTURE_STATE_NULL,
        /* Do not capture frame. */
        CAPTURE_STATE_PAUSED,
        /* Start capture frame. */
        CAPTURE_STATE_STARTED,
        /* exit thread*/
        CAPTURE_STATE_EXIT,
    };

    /* capture thread state. */
    CaptureThreadState              mCaptureThreadState;
    
    // v4l2 device handle
    int                             mCameraFd; 

    // be usb camera or not
    CAMERA_DEV                      mCameraDev;

    int                             mFrameRate;

    volatile int                    mPreviewFlip;   //value ref to CameraParameters::AWEXTEND_PREVIEW_FLIP

    int                             mPreviewRotation;

    TAKE_PICTURE_STATE              mTakePictureState;
    V4L2BUF_t                       mPicBuffer;
    bool                            mIsPicCopy;

    /* Frame width */
    int                             mFrameWidth;    //the capture width which is set to cameraDriver. setting value, vfe driver may be extend for 16 align to widht && height.

    /* Frame height */
    int                             mFrameHeight;

    /* thumb Frame width */
    int                             mThumbWidth;    //the sub capture width which is set to cameraDriver. setting value, vfe driver may be extend for 16 align to widht && height.

    /* thumb Frame height */
    int                             mThumbHeight;

    // actually buffer counts
    int                             mRealBufferNum;
    int                             mReqBufferNum;

    bool                            mUseHwEncoder;
    
    RECT_t                            mRectCrop;
    RECT_t                            mThumbRectCrop;
    int                             mNewZoom;
    int                             mLastZoom;
    int                             mMaxZoom;

    int                             mCaptureFormat;     // the driver capture format
    int                             mVideoFormat;       // V4L2_PIX_FMT_NV21. the user request format, it should convert video buffer format 
                                                        // if mVideoFormat is different from mCaptureFormat. 
	int	mColorSpace;	//enum v4l2_colorspace, V4L2_COLORSPACE_JPEG
	
	struct ScMemOpsS *mScMemOpsS; //  ion handle, add by King
#if 0
    typedef struct bufferManagerQ_t
    {
        int         buf_vir_addr[NB_BUFFER];
        int         buf_phy_addr[NB_BUFFER];
        int         write_id;
        int         read_id;
        int         buf_unused;
    }bufferManagerQ_t;
    bufferManagerQ_t                mVideoBuffer;       // for usb camera
#endif

#ifdef USE_MP_CONVERT
    int                             mG2DHandle;
#endif

    OSAL_QUEUE                      mQueueBufferPreview;
    OSAL_QUEUE                      mQueueBufferPicture;

    DoCaptureThread             *mCaptureThread;
    pthread_mutex_t                 mCaptureMutex;
    pthread_cond_t                  mCaptureCond;

    DoPreviewThread             *mPreviewThread;
    pthread_mutex_t                 mPreviewMutex;
    pthread_cond_t                  mPreviewCond;
    
    DoPictureThread             *mPictureThread;
    pthread_mutex_t                 mPictureMutex;
    pthread_cond_t                  mPictureCond;

    pthread_mutex_t                 mConnectMutex;
    pthread_cond_t                  mConnectCond;
    bool                            mCanBeDisconnected;

    DoContinuousPictureThread   *mContinuousPictureThread;
    pthread_mutex_t                 mContinuousPictureMutex;
    pthread_cond_t                  mContinuousPictureCond;
    bool                            mContinuousPictureStarted;
    int                             mContinuousPictureCnt;
    int                             mContinuousPictureMax;
    int64_t                         mContinuousPictureStartTime;

    /* Timestamp (abs. microseconds) when last frame has been pushed to the
     * preview window. */
    uint64_t                        mContinuousPictureLast;

    /* Preview frequency in microseconds. */
    uint32_t                        mContinuousPictureAfter;

#if 0  // face
    uint64_t                        mFaceDectectLast;
    uint32_t                        mFaceDectectAfter;
    V4L2BUF_t *                     mCurrentV4l2buf;

    bool                            mVideoHint;
#endif
    bool                            mIsThumbUsedForVideo;   //directly indicate encoder use thumbPicture to encode. In common, cameraDevice should not set it true.
    int                             mVideoWidth;            // for cts, same to cameraParamter->videoSize.
    int                             mVideoHeight;

    SonixUsbCameraDevice            *mSonixUsbCameraDevice;

    /* support of libve */
    DecodeHandle                    *mDecHandle;

    Mutex   mVideoPicBufLock;   //lock VideoPictureBuffer mVideoPicBuf[NB_BUFFER].isUse
    volatile int    mReleasePicBufIdx;

    void *mUvcDev;

    typedef struct V4l2Buffer_tag {
        void *memory;
        V4L2BUF_t v4l2buf;
        V4l2PreviewBuffer_tag prevbuf;
    }V4l2Buffer_tag;
    V4l2Buffer_tag *mpV4l2Buf;
    uint32_t  mMemMapLen;
    VideoPictureBuffer *mpVideoPicBuf;

#ifdef FACE_DETECTION
    void *mFD;
#endif

#if DEBUG_V4L2_CAMERA_USED_BUFFER_CNT
    int mUsedBufCnt;
#endif
#if DEBUG_RELEASE_FRAME_TIME
    int64_t mDebugTime[40];
#endif
#if DEBUG_GET_FRAME_INTERVAL
    int64_t mDebugGetFrameInterval;
#endif

    int64_t mPreviewWantedPts;

    bool mSubChannelEnable;

    uint32_t mFramesInV4l2buf;
    int mFrameOffset;

	char *mpRotPrevBuf;
	int mPrevBufIdx;


#ifdef CONFIG_SUPPORT_TVIN_DEVICE
private
    status_t TVinresetDevice();
    status_t TVinStartDevice();
    status_t TVinStopDevice();

    TVDecoder                       *mTVDecoder;
#endif

#ifdef MOTION_DETECTION_ENABLE
public:
    status_t AWMDInitialize();
    status_t AWMDDestroy();
    status_t AWMDEnable(bool enable);
    status_t AWMDSetSensitivityLevel(int level);
private:
    MotionDetect                    *mMotionDetect;
#endif


#ifdef WATERMARK_ENABLE
public:
    status_t setWaterMark(int enable, const char *str);

private:
    volatile bool                   mWaterMarkEnable;
    WaterMarkInData                 mWaterMarkIndata;
    void                            *mWaterMarkCtrlRec;
    void                            *mWaterMarkCtrlPrev;
    pthread_mutex_t                 mWaterMarkLock;
#endif


#ifdef ADAS_ENABLE
public:
    status_t adasInitialize();
    status_t adasDestroy();
    status_t adasSetLaneLineOffsetSensity(int level);
    status_t adasSetDistanceDetectLevel(int level);
	status_t adasSetMode(int mode);
	status_t adasSetTipsMode(int mode);
    status_t adasSetCarSpeed(int speed);
    status_t adasSetRoiArea(void *adas);
    status_t adasSetAudioVol(int val);
	status_t adasSetGsensorData(int val0, float val1, float val2);
private:
    CameraAdas                      *mAdas;
    int                             mAdasLaneLineOffsetSensity;
    int                             mAdasDistanceDetectLevel;
    float                           mAdasCarSpeed;
    Mutex                           mRoiLock;
    Venc_ROI_Config                 mRoiArea[ROI_AREA_NUM];
    Mutex                           mAlgorithmLock;
#endif

#ifdef QRDECODE_ENABLE
public:
    status_t setQrDecode(bool enable);
private:
    CameraQrDecode                  *mpQrDecode;
#endif
};

}; /* namespace zeta */

#endif  /* __HAL_V4L2_CAMERA_DEVICE_H__ */

