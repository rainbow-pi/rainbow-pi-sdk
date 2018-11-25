
#ifndef __HAL_CAMERA_FACTORY_H__
#define __HAL_CAMERA_FACTORY_H__

#include <hardware/camera.h>

#include "CCameraConfig.h"

#include "CameraHardware2.h"


namespace zeta {

#ifdef CONFIG_SUPPORT_TVIN_DEVICE
#define MAX_NUM_OF_CAMERAS	3
#else
#define MAX_NUM_OF_CAMERAS	2
#endif

/*
 * Contains declaration of a class HALCameraFactory that manages cameras
 * available. A global instance of this class is statically
 * instantiated and initialized when camera emulation HAL is loaded.
 */

class HALCameraFactory {
public:
    /* Constructs HALCameraFactory instance.
     * In this constructor the factory will create and initialize a list of
     * V4L2Cameras. All errors that occur on this constructor are reported
     * via mConstructedOK data member of this class.
     */
    HALCameraFactory();

    /* Destructs HALCameraFactory instance. */
    ~HALCameraFactory();

    /****************************************************************************
     * Camera HAL API handlers.
     ***************************************************************************/

public:
    /* Opens (connects to) a camera device.
     * This method is called in response to hw_module_methods_t::open callback.
     */
    int cameraDeviceOpen(int camera_id, hw_device_t** device);

    /* Gets V4L2Camera information.
     * This method is called in response to camera_module_t::get_camera_info callback.
     */
    int getCameraInfo(int camera_id, struct camera_info *info);

    /****************************************************************************
     * Camera HAL API callbacks.
     ***************************************************************************/

public:
    /* camera_module_t::get_number_of_cameras callback entry point. */
    static int get_number_of_cameras(void);

    /* camera_module_t::get_camera_info callback entry point. */
    static int get_camera_info(int camera_id, struct camera_info *info);

//private:
    /* hw_module_methods_t::open callback entry point. */
    static int device_open(int camera_id, hw_device_t** device);

    /****************************************************************************
     * Public API.
     ***************************************************************************/

public:

    /* Gets number of V4L2Cameras.
     */
    int getCameraHardwareNum();

    /* Checks whether or not the constructor has succeeded.
     */
    bool isConstructedOK() const {
        return mConstructedOK;
    }

    /****************************************************************************
     * Data members.
     ***************************************************************************/

private:
    /* Array of cameras available for the emulation. */
    CameraHardware      **mHardwareCameras;

    /* Number of attached Cameras, do not include usb cameras. */
    int                 mAttachedCamerasNum;

    /* Number of removable Cameras, such as usb cameras. */
    int                 mRemovableCamerasNum;

    /* Flags whether or not constructor has succeeded. */
    bool                mConstructedOK;

    // Camera Config information
    CCameraConfig       *mCameraConfig[MAX_NUM_OF_CAMERAS];

public:
    /* Contains device open entry point, as required by HAL API. */
    static struct hw_module_methods_t   mCameraModuleMethods;

public:

    HALCameraInfo       mHalCameraInfo[MAX_NUM_OF_CAMERAS];
};

}; /* namespace zeta */

/* References the global HALCameraFactory instance. */
extern zeta::HALCameraFactory   gEmulatedCameraFactory;

#endif  /* __HAL_CAMERA_FACTORY_H__ */
