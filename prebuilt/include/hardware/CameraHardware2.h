
#ifndef __HAL_CAMERA_HARDWARE_H__
#define __HAL_CAMERA_HARDWARE_H__

/*
 * Contains declaration of a class CameraHardware that encapsulates functionality
 * common to all V4L2Cameras ("fake", "webcam", "video file", etc.).
 * Instances of this class (for each V4L2Camera) are created during the
 * construction of the HALCameraFactory instance.
 * This class serves as an entry point for all camera API calls that defined
 * by camera_device_ops_t API.
 */

//#include <utils/Mutex.h>

#include <videodev2.h>
#include <CameraParameters.h>
#if 0  // face
#include <FaceDetectionApi.h>
#endif

#include "V4L2CameraDevice2.h"
#include "PreviewWindow.h"
#include "CallbackNotifier.h"
#include "CCameraConfig.h"

namespace zeta {

//#define KEY_CAPTURE_SIZE_WIDTH			"capture-size-width"
//#define KEY_CAPTURE_SIZE_HEIGHT			"capture-size-height"
//#define KEY_PREVIEW_CAPTURE_SIZE_WIDTH	"preview_capture-size-width"
//#define KEY_PREVIEW_CAPTURE_SIZE_HEIGHT	"preview_capture-size-height"

//#define KEY_PICTURE_MODE				"picture-mode"
//#define PICTURE_MODE_NORMAL				"normal"
//#define VALUE_PICTURE_MODE_FAST         "fast"
//#define PICTURE_MODE_CONTINUOUS			"continuous"
//#define PICTURE_MODE_CONTINUOUS_FAST	"continuous-fast"
//#define KEY_CANCEL_CONTINUOUS_PICTURE	"cancel_continuous_picture"		// "true" for stopping

//#define KEY_IS_IMAGECAPTURE_INTENT		"is-imagecapture-intent"
/* Encapsulates functionality common to all V4L2Cameras.
 *
 * Note that HALCameraFactory instantiates object of this class just once,
 * when HALCameraFactory instance gets constructed. Connection to /
 * disconnection from the actual camera device is handled by calls to connectDevice(),
 * and closeCamera() methods of this class that are ivoked in response to
 * hw_module_methods_t::open, and camera_device::close callbacks.
 */
class CameraHardware : public camera_device {
public:
    /* Constructs CameraHardware instance.
     * Param:
     *  module - V4L2Camera HAL module descriptor.
     */
    CameraHardware(CCameraConfig* pCameraCfg);

    /* Destructs CameraHardware instance. */
    virtual ~CameraHardware();

    /****************************************************************************
     * Public API
     ***************************************************************************/

public:
    /* Initializes CameraHardware instance.
     * Return:
     *  NO_ERROR on success, or an appropriate error status on failure.
     */
    virtual status_t Initialize();

    /* Entry point for notifications that occur in camera device.
     * Param:
     *  err - CAMERA_ERROR_XXX error code.
     */
    virtual void onCameraDeviceError(int err);

    /****************************************************************************
     * Camera API implementation
     ***************************************************************************/

public:
    /* Creates connection to the V4L2Camera device.
     * This method is called in response to hw_module_methods_t::open callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t connectCamera(hw_device_t** device);

    /* Closes connection to the V4L2Camera.
     * This method is called in response to camera_device::close callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t closeCamera();

    /****************************************************************************
     * Camera API implementation.
     * These methods are called from the camera API callback routines.
     ***************************************************************************/

protected:
    /* Actual handler for camera_device_ops_t::set_preview_window callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t setPreviewWindow(struct preview_stream_ops *window);

    /* Actual handler for camera_device_ops_t::set_callbacks callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void setCallbacks(camera_notify_callback notify_cb,
                              camera_data_callback data_cb,
                              camera_data_timestamp_callback data_cb_timestamp,
                              camera_request_memory get_memory,
                              void* user);

    /* Actual handler for camera_device_ops_t::enable_msg_type callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void enableMsgType(int32_t msg_type);

    /* Actual handler for camera_device_ops_t::disable_msg_type callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void disableMsgType(int32_t msg_type);

    /* Actual handler for camera_device_ops_t::msg_type_enabled callback.
     * NOTE: When this method is called the object is locked.
     * Return:
     *  0 if message(s) is (are) disabled, != 0 if enabled.
     */
    virtual int isMsgTypeEnabled(int32_t msg_type);

    /* Actual handler for camera_device_ops_t::start_preview callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t startPreview();

    /* Actual handler for camera_device_ops_t::stop_preview callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void stopPreview();

    /* Actual handler for camera_device_ops_t::preview_enabled callback.
     * NOTE: When this method is called the object is locked.
     * Return:
     *  0 if preview is disabled, != 0 if enabled.
     */
    virtual int isPreviewEnabled();

    /* Actual handler for camera_device_ops_t::store_meta_data_in_buffers callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t storeMetaDataInBuffers(int enable);

    /* Actual handler for camera_device_ops_t::start_recording callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t startRecording();

    /* Actual handler for camera_device_ops_t::stop_recording callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void stopRecording();

    /* Actual handler for camera_device_ops_t::recording_enabled callback.
     * NOTE: When this method is called the object is locked.
     * Return:
     *  0 if recording is disabled, != 0 if enabled.
     */
    virtual int isRecordingEnabled();

    /* Actual handler for camera_device_ops_t::release_recording_frame callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void releaseRecordingFrame(const void* opaque);

    /* Actual handler for camera_device_ops_t::auto_focus callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t setAutoFocus();

    /* Actual handler for camera_device_ops_t::cancel_auto_focus callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t cancelAutoFocus();

    /* Actual handler for camera_device_ops_t::take_picture callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t takePicture();

    /* Actual handler for camera_device_ops_t::cancel_picture callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t cancelPicture();

    /* Actual handler for camera_device_ops_t::set_parameters callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t setParameters(const char* parms);

    /* Actual handler for camera_device_ops_t::get_parameters callback.
     * NOTE: When this method is called the object is locked.
     * Return:
     *  Flattened parameters string. The caller will free the buffer allocated
     *  for the string by calling camera_device_ops_t::put_parameters callback.
     */
    virtual char* getParameters();

    /* Actual handler for camera_device_ops_t::put_parameters callback.
     * Called to free the string returned from camera_device_ops_t::get_parameters
     * callback. There is nothing more to it: the name of the callback is just
     * misleading.
     * NOTE: When this method is called the object is locked.
     */
    virtual void putParameters(char* params);

    /* Actual handler for camera_device_ops_t::send_command callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t sendCommand(int32_t cmd, int32_t arg1, int32_t arg2);


	virtual status_t getV4l2QueryCtrl(struct v4l2_queryctrl *ctrl, int id);

	virtual int getInputSource(int *source);

	virtual int getTVinSystem(int *system);

    status_t setUvcGadgetMode(int value);
#ifdef ADAS_ENABLE
    status_t adasSetGsensorData(int val0, float val1, float val2);
#endif

#ifdef WATERMARK_ENABLE
    status_t setWaterMark(int enable, const char *str);
#endif

    /* Actual handler for camera_device_ops_t::release callback.
     * NOTE: When this method is called the object is locked.
     */
    virtual void releaseCamera();

    /* Actual handler for camera_device_ops_t::dump callback.
     * NOTE: When this method is called the object is locked.
     * Note that failures in this method are reported as negave EXXX statuses.
     */
    virtual status_t dumpCamera(int fd);

    /****************************************************************************
     * Preview management.
     ***************************************************************************/

protected:
public:
    /* Starts preview.
     * Note that when this method is called mPreviewWindow may be NULL,
     * indicating that framework has an intention to start displaying video
     * frames, but didn't create the preview window yet.
     * Return:
     *  NO_ERROR on success, or an appropriate error status on failure.
     */
    virtual status_t doStartPreview();

    /* Stops preview.
     * This method reverts DoStartPreview.
     * Return:
     *  NO_ERROR on success, or an appropriate error status on failure.
     */
    virtual status_t doStopPreview();

	status_t doTakePicture();
	status_t doTakePictureEnd();

    /****************************************************************************
     * Private API.
     ***************************************************************************/

protected:
    /* Cleans up camera when released. */
    virtual status_t cleanupCamera();

    /****************************************************************************
     * Camera API callbacks as defined by camera_device_ops structure.
     * See hardware/libhardware/include/hardware/camera.h for information on
     * each of these callbacks. Implemented in this class, these callbacks simply
     * dispatch the call into an instance of CameraHardware class defined by the
     * 'camera_device' parameter.
     ***************************************************************************/

private:
    static int set_preview_window(struct camera_device* dev,
                                   struct preview_stream_ops* window);

    static void set_callbacks(struct camera_device* dev,
                              camera_notify_callback notify_cb,
                              camera_data_callback data_cb,
                              camera_data_timestamp_callback data_cb_timestamp,
                              camera_request_memory get_memory,
                              void* user);

    static void enable_msg_type(struct camera_device* dev, int32_t msg_type);

    static void disable_msg_type(struct camera_device* dev, int32_t msg_type);

    static int msg_type_enabled(struct camera_device* dev, int32_t msg_type);

    static int start_preview(struct camera_device* dev);

    static void stop_preview(struct camera_device* dev);

    static int preview_enabled(struct camera_device* dev);

    static int store_meta_data_in_buffers(struct camera_device* dev, int enable);

    static int start_recording(struct camera_device* dev);

    static void stop_recording(struct camera_device* dev);

    static int recording_enabled(struct camera_device* dev);

    static void release_recording_frame(struct camera_device* dev,
                                        const void* opaque);

    static int auto_focus(struct camera_device* dev);

    static int cancel_auto_focus(struct camera_device* dev);

    static int take_picture(struct camera_device* dev);

    static int cancel_picture(struct camera_device* dev);

    static int set_parameters(struct camera_device* dev, const char* parms);

    static char* get_parameters(struct camera_device* dev);

    static void put_parameters(struct camera_device* dev, char* params);

    static int send_command(struct camera_device* dev,
                            int32_t cmd,
                            int32_t arg1,
                            int32_t arg2);

    static void release(struct camera_device* dev);

    static int dump(struct camera_device* dev, int fd);

	static int get_v4l2_query_ctrl(struct camera_device* dev,
                                 struct v4l2_queryctrl *ctrl, int id);

	static int get_input_source(struct camera_device* dev, int *source);

	static int get_tvin_system(struct camera_device* dev, int *system);

	static int set_waterMark(struct camera_device *dev, int enable, const char *str);
    static int set_uvcGadgetMode(struct camera_device *dev, int value);
    static int set_adasGsensorData(struct camera_device *dev, int val0, float val1, float val2);

    static int close(struct hw_device_t* device);

    /****************************************************************************
     * Data members
     ***************************************************************************/

protected:
    /* Locks this instance for parameters, state, etc. change. */
    Mutex                           mObjectLock;

    /* Camera parameters. */
    CameraParameters                mParameters;

    /* Preview window. */
    PreviewWindow                   mPreviewWindow;

    /* Callback notifier. */
    CallbackNotifier                mCallbackNotifier;

	V4L2CameraDevice *   			mV4L2CameraDevice;

private:
    /* Registered callbacks implementing camera API. */
    static camera_device_ops_t      mDeviceOps;

    /****************************************************************************
     * Common keys
     ***************************************************************************/

public:
    static const char FACING_KEY[];
    static const char ORIENTATION_KEY[];
    static const char RECORDING_HINT_KEY[];

     /****************************************************************************
     * Common string values
     ***************************************************************************/

    /* Possible values for FACING_KEY */
    static const char FACING_BACK[];
    static const char FACING_FRONT[];

	// -------------------------------------------------------------------------
	// extended interfaces here <***** star *****>
	// -------------------------------------------------------------------------
public:
	status_t setCameraHardwareInfo(HALCameraInfo * halInfo);
	void initDefaultParameters();

	void notifyPictureMsg(const void* frame);
	
	//void setNewCrop(Rect * rect);
	int setAutoFocusRange();
#if 0  // face
	int getCurrentFaceFrame(void * frame);
	int faceDetection(camera_frame_metadata_t *face);
#endif
    
    int parse_focus_areas(const char * str, bool is_face = false);
	bool checkFocusArea(const char * area);
	bool checkFocusMode(const char * mode);

	bool commandThread();
	bool autoFocusThread();

	//void setVideoCaptureSize(int video_w, int video_h);
	void getCurrentOriention(int * oriention);

	bool isCameraIdle();

	status_t resetCaptureSize(int width, int height);
    status_t setPreviewFrameRate(int fps);

protected:
	CCameraConfig * 				mCameraConfig;

	HALCameraInfo					mHalCameraInfo;

    Mutex                           mCameraIdleLock;
	bool							mIsCameraIdle;

	bool							mFirstSetParameters;
	//bool							mIsSupportFocus;
	//bool							mIsSupportEffect;
	//bool							mIsSupportFlash;
	//bool							mIsSupportScene;
	//bool							mIsSupportWhiteBlance;
	//bool							mIsSupportExposure;

	int								mFullSizeWidth;     //max capture size which the sensor can support. call mV4L2CameraDevice->getFullSize() to get.
	int								mFullSizeHeight;
	int								mCaptureWidth;      //truly capture size which is set to mV4L2CameraDevice(main channel). mV4L2CameraDevice->startDevice().
	int								mCaptureHeight;
	//int								mVideoCaptureWidth; //when video record, the capture size which will be set to mV4L2CameraDevice.
	//int								mVideoCaptureHeight;
	bool							mUseHwEncoder;

	//char							mCallingProcessName[128];

#if 0  // face
	FaceDetectionDev *				mFaceDetection;
#endif
	
	//Rect							mFrameRectCrop;		// current frame buffer crop for focus
	//char							mFocusAreasStr[32];
	struct v4l2_win_coordinate		mLastFocusAreas;

	typedef enum CMD_QUEUE_t{
		CMD_QUEUE_SET_COLOR_EFFECT 	= 0,
		CMD_QUEUE_SET_WHITE_BALANCE,
		CMD_QUEUE_SET_FLASH_MODE,
		CMD_QUEUE_SET_FOCUS_MODE,
		CMD_QUEUE_SET_FOCUS_AREA,
		CMD_QUEUE_SET_EXPOSURE_COMPENSATION,
		
		CMD_QUEUE_START_FACE_DETECTE,
		CMD_QUEUE_STOP_FACE_DETECTE,

		CMD_QUEUE_TAKE_PICTURE,
		CMD_QUEUE_PICTURE_MSG,
		CMD_QUEUE_STOP_CONTINUOUSSNAP,
		
		CMD_QUEUE_SET_FOCUS_STATUS,

		/* MOTION_DETECTION_ENABLE start */
		CMD_QUEUE_START_AWMD,
		CMD_QUEUE_STOP_AWMD,
		CMD_QUEUE_SET_AWMD_SENSITIVITY_LEVEL,
		/* MOTION_DETECTION_ENABLE end */

		/* for ADAS start */
		CMD_QUEUE_ADAS_START_DETECT,
		CMD_QUEUE_ADAS_STOP_DETECT,
		CMD_QUEUE_ADAS_SET_LANELINE_OFFSET_SENSITY,
		CMD_QUEUE_ADAS_SET_DISTANCE_DETECT_LEVEL,
		CMD_QUEUE_ADAS_SET_CAR_SPEED,
		CMD_QUEUE_ADAS_SET_AUDIO_VOL,
		CMD_QUEUE_ADAS_SET_MODE,
		CMD_QUEUE_ADAS_SET_TIPS_MODE,
		/* for ADAS end */

        CMD_QUEUE_SET_QRDECODE,

        CMD_QUEUE_START_RENDER,
        CMD_QUEUE_STOP_RENDER,

		CMD_QUEUE_SET_COLORFX,

		CMD_QUEUE_MAX
	}CMD_QUEUE;

	OSAL_QUEUE						mQueueCommand;
	
	typedef struct Queue_Element_t {
		CMD_QUEUE cmd;
		int data;
	}Queue_Element;

	Queue_Element					mQueueElement[CMD_QUEUE_MAX];

	class DoCommandThread : public Thread {
        CameraHardware* mCameraHardware;
		ThreadState		mThreadStatus;
    public:
        DoCommandThread(CameraHardware* hw) :
			mCameraHardware(hw),
			mThreadStatus(THREAD_STATE_NULL) {
		}
        void startThread() {
			mThreadStatus = THREAD_STATE_RUNNING;
			run("CameraCommandThread", PRIORITY_NORMAL);
        }
		void stopThread() {
			mThreadStatus = THREAD_STATE_EXIT;
        }
		ThreadState getThreadStatus() {
			return mThreadStatus;
		}
		bool isThreadStarted() {
			return (mThreadStatus == THREAD_STATE_PAUSED) || (mThreadStatus == THREAD_STATE_RUNNING);
		}
        virtual bool threadLoop() {
			return mCameraHardware->commandThread();
        }
    };
	DoCommandThread				*mCommandThread;
	
	pthread_mutex_t 				mCommandMutex;
	pthread_cond_t					mCommandCond;

	class DoAutoFocusThread : public Thread {
        CameraHardware* mCameraHardware;
		ThreadState		mThreadStatus;
    public:
        DoAutoFocusThread(CameraHardware* hw) :
			mCameraHardware(hw),
			mThreadStatus(THREAD_STATE_NULL) {
		}
        void startThread() {
			mThreadStatus = THREAD_STATE_RUNNING;
			run("CameraAutoFocusThread", PRIORITY_NORMAL);
        }
		void stopThread() {
			mThreadStatus = THREAD_STATE_EXIT;
        }
		ThreadState getThreadStatus() {
			return mThreadStatus;
		}
		bool isThreadStarted() {
			return (mThreadStatus == THREAD_STATE_PAUSED) || (mThreadStatus == THREAD_STATE_RUNNING);
		}
        virtual bool threadLoop() {
			return mCameraHardware->autoFocusThread();
        }
    };
	DoAutoFocusThread			*mAutoFocusThread;
	
	pthread_mutex_t 				mAutoFocusMutex;
	pthread_cond_t					mAutoFocusCond;
	bool							mAutoFocusThreadExit;

public:
	typedef enum FocusStatus_t {
		FOCUS_STATUS_IDLE		= 0x0,
		FOCUS_STATUS_SUCCESS	= 0x1,
		FOCUS_STATUS_FAIL		= 0x2,
		FOCUS_STATUS_DONE		= FOCUS_STATUS_SUCCESS | FOCUS_STATUS_FAIL,
		FOCUS_STATUS_BUSY		= 0x4,
	}FocusStatus;

protected:
	FocusStatus						mFocusStatus;
	bool							mIsSingleFocus;

	int								mOriention; //0, 90, 180, 270.

	int								mZoomRatio;
	//bool                            mIsImageCaptureIntent;


//aw extend.
private:
    bool checkPreviewSizeValid(Size newPreivewSize);
    bool checkVideoSizeValid(Size newVideoSize);
    bool checkPreviewFrameRateValid(int newPreviewFrameRate);
};

}; /* namespace zeta */

#endif  /* __HAL_CAMERA_HARDWARE_H__ */
