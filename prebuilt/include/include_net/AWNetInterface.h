#ifndef _AW_NET_INTERFACE_H_
#define _AW_NET_INTERFACE_H_

typedef enum 
{
	AW_IOTYPE_USER_IPCAM_START 					    = 0x01FF,
	AW_IOTYPE_USER_IPCAM_STOP	 					= 0x02FF,
	AW_IOTYPE_USER_IPCAM_AUDIOSTART 				= 0x0300,
	AW_IOTYPE_USER_IPCAM_AUDIOSTOP 				    = 0x0301,

	AW_IOTYPE_USER_IPCAM_SPEAKERSTART 				= 0x0350,
	AW_IOTYPE_USER_IPCAM_SPEAKERSTOP 				= 0x0351,

	AW_IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ			= 0x0320,
	AW_IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP		    = 0x0321,
	AW_IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ			= 0x0322,
	AW_IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP		    = 0x0323,

	AW_IOTYPE_USER_IPCAM_SETMOTIONDETECT_REQ		= 0x0324,
	AW_IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP		= 0x0325,
	AW_IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ		= 0x0326,
	AW_IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP		= 0x0327,
	
	AW_IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ		= 0x0328,	// Get Support Stream
	AW_IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP		= 0x0329,	

	AW_IOTYPE_USER_IPCAM_DEVINFO_REQ				= 0x0330,
	AW_IOTYPE_USER_IPCAM_DEVINFO_RESP				= 0x0331,

	AW_IOTYPE_USER_IPCAM_SETPASSWORD_REQ			= 0x0332,
	AW_IOTYPE_USER_IPCAM_SETPASSWORD_RESP			= 0x0333,

	AW_IOTYPE_USER_IPCAM_LISTWIFIAP_REQ			    = 0x0340,
	AW_IOTYPE_USER_IPCAM_LISTWIFIAP_RESP			= 0x0341,
	AW_IOTYPE_USER_IPCAM_SETWIFI_REQ				= 0x0342,
	AW_IOTYPE_USER_IPCAM_SETWIFI_RESP				= 0x0343,
	AW_IOTYPE_USER_IPCAM_GETWIFI_REQ				= 0x0344,
	AW_IOTYPE_USER_IPCAM_GETWIFI_RESP				= 0x0345,
	AW_IOTYPE_USER_IPCAM_SETWIFI_REQ_2				= 0x0346,
	AW_IOTYPE_USER_IPCAM_GETWIFI_RESP_2			    = 0x0347,

	AW_IOTYPE_USER_IPCAM_SETRECORD_REQ				= 0x0310,
	AW_IOTYPE_USER_IPCAM_SETRECORD_RESP			    = 0x0311,
	AW_IOTYPE_USER_IPCAM_GETRECORD_REQ				= 0x0312,
	AW_IOTYPE_USER_IPCAM_GETRECORD_RESP			    = 0x0313,

	AW_IOTYPE_USER_IPCAM_SETRCD_DURATION_REQ		= 0x0314,
	AW_IOTYPE_USER_IPCAM_SETRCD_DURATION_RESP  	    = 0x0315,
	AW_IOTYPE_USER_IPCAM_GETRCD_DURATION_REQ		= 0x0316,
	AW_IOTYPE_USER_IPCAM_GETRCD_DURATION_RESP  	    = 0x0317,

	AW_IOTYPE_USER_IPCAM_LISTEVENT_REQ				= 0x0318,
	AW_IOTYPE_USER_IPCAM_LISTEVENT_RESP			    = 0x0319,
	
	AW_IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL 		= 0x031A,
	AW_IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP 	= 0x031B,
	
	AW_IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ		= 0x032A,
	AW_IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP	    = 0x032B,

	AW_IOTYPE_USER_IPCAM_GET_EVENTCONFIG_REQ		= 0x0400,	// Get Event Config Msg Request
	AW_IOTYPE_USER_IPCAM_GET_EVENTCONFIG_RESP		= 0x0401,	// Get Event Config Msg Response
	AW_IOTYPE_USER_IPCAM_SET_EVENTCONFIG_REQ		= 0x0402,	// Set Event Config Msg req
	AW_IOTYPE_USER_IPCAM_SET_EVENTCONFIG_RESP		= 0x0403,	// Set Event Config Msg resp

	AW_IOTYPE_USER_IPCAM_SET_ENVIRONMENT_REQ		= 0x0360,
	AW_IOTYPE_USER_IPCAM_SET_ENVIRONMENT_RESP		= 0x0361,
	AW_IOTYPE_USER_IPCAM_GET_ENVIRONMENT_REQ		= 0x0362,
	AW_IOTYPE_USER_IPCAM_GET_ENVIRONMENT_RESP		= 0x0363,
	
	AW_IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ			= 0x0370,	// Set Video Flip Mode
	AW_IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP		    = 0x0371,
	AW_IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ			= 0x0372,	// Get Video Flip Mode
	AW_IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP		    = 0x0373,
	
	AW_IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ		= 0x0380,	// Format external storage
	AW_IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_RESP		= 0x0381,	
	
	AW_IOTYPE_USER_IPCAM_PTZ_COMMAND				= 0x1001,	// P2P PTZ Command Msg

	AW_IOTYPE_USER_IPCAM_EVENT_REPORT				= 0x1FFF,	// Device Event Report Msg
	AW_IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME		= 0x1002,	// Send from client, used to talk to device that
															// client had received the first I frame
	AW_IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ			= 0x0390,
	AW_IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP			= 0x0391,
	AW_IOTYPE_USER_IPCAM_CURRENT_FLOWINFO			= 0x0392,
	
	AW_IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ           = 0x3A0,
	AW_IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP          = 0x3A1,
	AW_IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ           = 0x3B0,
	AW_IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP          = 0x3B1, 
	
    // dropbox support
    AW_IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_REQ       = 0x500,
    AW_IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_RESP      = 0x501,
    AW_IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_REQ       = 0x502,
    AW_IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_RESP      = 0x503,

	AW_IOTYPE_USER_IPCAM_START_ENCODER              =0x2001,
	AW_IOTYPE_USER_IPCAM_STOP_ENCODER               =0x2002,
	AW_IOTYPE_USER_IPCAM_RECORD_PLAY_END            =0x2003,
	AW_IOTYPE_USER_IPCAM_OFF_LINE          		    =0x2004,
	AW_IOTYPE_USER_IPCAM_ON_LINE				    =0x2005,

// file trans

	AW_IOTYPE_USER_IPCAM_FILE_TRANS_START           =0x2008,
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_START_RESP      =0x2009,
	
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_STOP            =0x2010,
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_END             =0x2011,

//end file trans

//Board testing 
    AW_IOTYPE_USER_IPCAM_START_TEST_MIC_REQ         =0x3003,
    AW_IOTYPE_USER_IPCAM_START_TEST_MIC_RESP        =0x3004,
    
    AW_IOTYPE_USER_IPCAM_STOP_TEST_MIC_REQ          =0x3005,
    AW_IOTYPE_USER_IPCAM_STOP_TEST_MIC_RESP         =0x3006,

    AW_IOTYPE_USER_IPCAM_TEST_SCAN_WIFI_REQ         =0x3007,
    AW_IOTYPE_USER_IPCAM_TEST_SCAN_WIFI_RESP        =0x3008,
    
    AW_IOTYPE_USER_IPCAM_START_TEST_SOUNDER_REQ     =0x3009,
    AW_IOTYPE_USER_IPCAM_START_TEST_SOUNDER_RESP    =0x3010,
    
    AW_IOTYPE_USER_IPCAM_STOP_TEST_SOUNDER_REQ      =0x3011, 
    AW_IOTYPE_USER_IPCAM_STOP_TEST_SOUNDER_RESP     =0x3012, 

    
    AW_IOTYPE_USER_IPCAM_SET_UUID_REQ               =0x3013,
    AW_IOTYPE_USER_IPCAM_SET_UUID_RESP              =0x3014,

    
    AW_IOTYPE_USER_IPCAM_SET_MAC_REQ                =0x3015,
    AW_IOTYPE_USER_IPCAM_SET_MAC_RESP               =0x3016,

    AW_IOTYPE_USER_IPCAM_START_MOTOR_ROLL_REQ       =0x3017,
    AW_IOTYPE_USER_IPCAM_START_MOTOR_ROLL_RESP      =0x3018,
    
    AW_IOTYPE_USER_IPCAM_STOP_MOTOR_ROLL_REQ        =0x3019,
    AW_IOTYPE_USER_IPCAM_STOP_MOTOR_ROLL_RESP       =0x3020,
//end Borad testing

//for tencent
    AW_IOTYPE_USER_IPCAM_RESART_GOP                 =0x4006,
    AW_IOTYPE_USER_IPCAM_GET_BITRATE_REQ			=0x4007,
    AW_IOTYPE_USER_IPCAM_GET_BITRATE_RESP 			=0x4008,
	AW_IOTYPE_USER_IPCAM_SET_BITRATE_REQ  			=0x4009,
    AW_IOTYPE_USER_IPCAM_SET_BITRATE_RESP           =0x400A,
    
    AW_IOTYPE_USER_IPCAM_GET_VIDEOSIZE_REQ          =0x400B,
    AW_IOTYPE_USER_IPCAM_GET_VIDEOSIZE_RESP 		=0x400C,
	AW_IOTYPE_USER_IPCAM_SET_VIDEOSIZE_REQ  		=0x400D,
    AW_IOTYPE_USER_IPCAM_SET_VIDEOSIZE_RESP         =0x400E,

    AW_IOTYPE_USER_IPCAM_GET_FRAMERATE_REQ 		    =0x400F,
    AW_IOTYPE_USER_IPCAM_GET_FRAMERATE_RESP 		=0x4010,
	AW_IOTYPE_USER_IPCAM_SET_FRAMERATE_REQ  		=0x4011,
    AW_IOTYPE_USER_IPCAM_SET_FRAMERATE_RESP         =0x4012,

	AW_IOTYPE_USER_IPCAM_GET_MEDIALIST_REQ			=0x4020,
	AW_IOTYPE_USER_IPCAM_GET_MEDIALIST_RESP			=0x4021,
	AW_IOTYPE_USER_IPCAM_PLAY_MEDIA_REQ			    =0x4022,
	AW_IOTYPE_USER_IPCAM_PLAY_MEDIA_RESP			=0x4023,
	AW_IOTYPE_USER_IPCAM_MEDIA_COMPLETE_RESP		=0x4024,
	AW_IOTYPE_USER_IPCAM_PAUSE_MEDIA_REQ			=0x4025,
	AW_IOTYPE_USER_IPCAM_PAUSE_MEDIA_RESP			=0x4026,
	AW_IOTYPE_USER_IPCAM_MOTION_ALARM				=0x4027,
	AW_IOTYPE_USER_IPCAM_MOTION_ALARM_RESP			=0x4028,
	AW_IOTYPE_USER_IPCAM_SET_RESET_RESP 			=0x4028,
//end tencent	
    AW_IOTYPE_USER_CMD_MAX
}ENUM_AW_AW_AVIOCTRL_MSGTYPE;

/*
AW_IOTYPE_USER_IPCAM_START_TEST_MIC_RESP      =0x3004,
AW_IOTYPE_USER_IPCAM_STOP_TEST_MIC_RESP       =0x3006,

//AWSMsg_AVIOCTRLTestComonResp result : 0 wifi is ok,-2  wifi had problem
AW_IOTYPE_USER_IPCAM_TEST_SCAN_WIFI_RESP      =0x3008,

AW_IOTYPE_USER_IPCAM_START_TEST_SOUNDER_RESP  =0x3010,
AW_IOTYPE_USER_IPCAM_STOP_TEST_SOUNDER_RESP   =0x3012, 
AW_IOTYPE_USER_IPCAM_SET_UUID_RESP            =0x3014,
AW_IOTYPE_USER_IPCAM_SET_MAC_RESP             =0x3016,
AW_IOTYPE_USER_IPCAM_START_MOTOR_ROLL_RESP    =0x3018,
AW_IOTYPE_USER_IPCAM_STOP_MOTOR_ROLL_RESP     =0x3020,

** @struct AWSMsg_AVIOCTRLTestComonResp
*/
typedef struct
{
    int result; //0: call funtion success; -1: fail to call funtion
    unsigned char reserved[4];
}AWSMsg_AVIOCTRLTestComonResp;


/////////////////////////////////////////////////////////////////////////////////
/////////////////// Type ENUM Define ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	AW_AVIOCTRL_OK					= 0x00,
	AW_AVIOCTRL_ERR				= -0x01,
	AW_AVIOCTRL_ERR_PASSWORD		= AW_AVIOCTRL_ERR - 0x01,
	AW_AVIOCTRL_ERR_STREAMCTRL		= AW_AVIOCTRL_ERR - 0x02,
	AW_AVIOCTRL_ERR_MONTIONDETECT	= AW_AVIOCTRL_ERR - 0x03,
	AW_AVIOCTRL_ERR_DEVICEINFO		= AW_AVIOCTRL_ERR - 0x04,
	AW_AVIOCTRL_ERR_LOGIN			= AW_AVIOCTRL_ERR - 5,
	AW_AVIOCTRL_ERR_LISTWIFIAP		= AW_AVIOCTRL_ERR - 6,
	AW_AVIOCTRL_ERR_SETWIFI		= AW_AVIOCTRL_ERR - 7,
	AW_AVIOCTRL_ERR_GETWIFI		= AW_AVIOCTRL_ERR - 8,
	AW_AVIOCTRL_ERR_SETRECORD		= AW_AVIOCTRL_ERR - 9,
	AW_AVIOCTRL_ERR_SETRCDDURA		= AW_AVIOCTRL_ERR - 10,
	AW_AVIOCTRL_ERR_LISTEVENT		= AW_AVIOCTRL_ERR - 11,
	AW_AVIOCTRL_ERR_PLAYBACK		= AW_AVIOCTRL_ERR - 12,

	AW_AVIOCTRL_ERR_INVALIDCHANNEL	= AW_AVIOCTRL_ERR - 0x20,

	AW_AV_ER_EXCEED_MAX_ALARM       = -20005,
	AW_AV_ER_EXCEED_MAX_SIZE        = -20006,
}ENUM_AW_AVIOCTRL_ERROR; //APP don't use it now
 
// AW_AVIOCTRL Event Type
typedef enum 
{
	AW_AVIOCTRL_EVENT_ALL					= 0x00,	// all event type(general APP-->IPCamera)
	AW_AVIOCTRL_EVENT_MOTIONDECT			= 0x01,	// motion detect start//==s==
	AW_AVIOCTRL_EVENT_VIDEOLOST			= 0x02,	// video lost alarm
	AW_AVIOCTRL_EVENT_IOALARM				= 0x03, // io alarmin start //---s--

	AW_AVIOCTRL_EVENT_MOTIONPASS			= 0x04, // motion detect end  //==e==
	AW_AVIOCTRL_EVENT_VIDEORESUME			= 0x05,	// video resume
	AW_AVIOCTRL_EVENT_IOALARMPASS			= 0x06, // IO alarmin end   //---e--

	AW_AVIOCTRL_EVENT_EXPT_REBOOT			= 0x10, // system exception reboot
	AW_AVIOCTRL_EVENT_SDFAULT				= 0x11, // sd record exception
}ENUM_EVENTTYPE;

// AW_AVIOCTRL Record Type
typedef enum
{
	AW_AVIOTC_RECORDTYPE_OFF				= 0x00,
	AW_AVIOTC_RECORDTYPE_FULLTIME			= 0x01,
	AW_AVIOTC_RECORDTYPE_ALARM				= 0x02,
	AW_AVIOTC_RECORDTYPE_MANUAL			= 0x03,
}ENUM_AW_RECORD_TYPE;

// AW_AVIOCTRL Play Record Command
typedef enum 
{
	AW_AVIOCTRL_RECORD_PLAY_PAUSE			= 0x00,
	AW_AVIOCTRL_RECORD_PLAY_STOP			= 0x01,
	AW_AVIOCTRL_RECORD_PLAY_STEPFORWARD	= 0x02, //now, APP no use
	AW_AVIOCTRL_RECORD_PLAY_STEPBACKWARD	= 0x03, //now, APP no use
	AW_AVIOCTRL_RECORD_PLAY_FORWARD		= 0x04, //now, APP no use
	AW_AVIOCTRL_RECORD_PLAY_BACKWARD		= 0x05, //now, APP no use
	AW_AVIOCTRL_RECORD_PLAY_SEEKTIME		= 0x06, //now, APP no use
	AW_AVIOCTRL_RECORD_PLAY_END			= 0x07,
	AW_AVIOCTRL_RECORD_PLAY_START			= 0x10,
}ENUM_PLAYCONTROL;
  
// AW_AVIOCTRL PTZ Command Value
typedef enum 
{
	AW_AVIOCTRL_PTZ_STOP					= 0,
	AW_AVIOCTRL_PTZ_UP						= 1,
	AW_AVIOCTRL_PTZ_DOWN					= 2,
	AW_AVIOCTRL_PTZ_LEFT					= 3,
	AW_AVIOCTRL_PTZ_LEFT_UP				= 4,
	AW_AVIOCTRL_PTZ_LEFT_DOWN				= 5,
	AW_AVIOCTRL_PTZ_RIGHT					= 6, 
	AW_AVIOCTRL_PTZ_RIGHT_UP				= 7, 
	AW_AVIOCTRL_PTZ_RIGHT_DOWN				= 8, 
	AW_AVIOCTRL_PTZ_AUTO					= 9, 
	AW_AVIOCTRL_PTZ_SET_POINT				= 10,
	AW_AVIOCTRL_PTZ_CLEAR_POINT			= 11,
	AW_AVIOCTRL_PTZ_GOTO_POINT				= 12,

	AW_AVIOCTRL_PTZ_SET_MODE_START			= 13,
	AW_AVIOCTRL_PTZ_SET_MODE_STOP			= 14,
	AW_AVIOCTRL_PTZ_MODE_RUN				= 15,

	AW_AVIOCTRL_PTZ_MENU_OPEN				= 16, 
	AW_AVIOCTRL_PTZ_MENU_EXIT				= 17,
	AW_AVIOCTRL_PTZ_MENU_ENTER				= 18,

	AW_AVIOCTRL_PTZ_FLIP					= 19,
	AW_AVIOCTRL_PTZ_START					= 20,

	AW_AVIOCTRL_LENS_APERTURE_OPEN			= 21,
	AW_AVIOCTRL_LENS_APERTURE_CLOSE		= 22,

	AW_AVIOCTRL_LENS_ZOOM_IN				= 23, 
	AW_AVIOCTRL_LENS_ZOOM_OUT				= 24,

	AW_AVIOCTRL_LENS_FOCAL_NEAR			= 25,
	AW_AVIOCTRL_LENS_FOCAL_FAR				= 26,

	AW_AVIOCTRL_AUTO_PAN_SPEED				= 27,
	AW_AVIOCTRL_AUTO_PAN_LIMIT				= 28,
	AW_AVIOCTRL_AUTO_PAN_START				= 29,

	AW_AVIOCTRL_PATTERN_START				= 30,
	AW_AVIOCTRL_PATTERN_STOP				= 31,
	AW_AVIOCTRL_PATTERN_RUN				= 32,

	AW_AVIOCTRL_SET_AUX					= 33,
	AW_AVIOCTRL_CLEAR_AUX					= 34,
	AW_AVIOCTRL_MOTOR_RESET_POSITION		= 35,
}ENUM_PTZCMD;


/////////////////////////////////////////////////////////////////////////////
///////////////////////// Message Body Define ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*
AW_IOTYPE_USER_IPCAM_START 				= 0x01FF,
AW_IOTYPE_USER_IPCAM_STOP	 				= 0x02FF,
AW_IOTYPE_USER_IPCAM_AUDIOSTART 			= 0x0300,
AW_IOTYPE_USER_IPCAM_AUDIOSTOP 			= 0x0301,
AW_IOTYPE_USER_IPCAM_SPEAKERSTART 			= 0x0350,
AW_IOTYPE_USER_IPCAM_SPEAKERSTOP 			= 0x0351,
** @struct AWSMsg_AVIOCTRLAVStream
*/
typedef struct
{
	unsigned int channel; // Camera Index
	unsigned char reserved[4];
} AWSMsg_AVIOCTRLAVStream;

/*
AW_IOTYPE_USER_IPCAM_START_ENCODER            =0x2001,
AW_IOTYPE_USER_IPCAM_STOP_ENCODER             =0x2002,
*/
typedef struct
{
	unsigned int stream_type; // ENUM_AW_PLAY_TYPE
	unsigned char reserved[4];
} AWSMsg_AVIOCTRLStartStream;

/*
AW_IOTYPE_USER_IPCAM_SET_BITRATE
*/

typedef struct
{
	unsigned int bitrate;
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetBitrate;

/*
AW_IOTYPE_USER_IPCAM_GET_FRAMERATE_RESP
AW_IOTYPE_USER_IPCAM_SET_FRAMERATE_REQ
*/

typedef struct
{
	unsigned int frameRate;
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLFrameRate;


/*
AW_IOTYPE_USER_IPCAM_SET_VIDEOSIZE_REQ
AW_IOTYPE_USER_IPCAM_GET_VIDEOSIZE_RESP
*/

typedef struct
{
	unsigned int width;
    unsigned int height;
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLVideoSize;



/*
AW_IOTYPE_USER_IPCAM_GET_MEDIALIST_RESP
*/
typedef struct
{
	char medialist[1024];
	unsigned char reserved[4];
} AWSMsg_AVIOCTRLGetMediaListResp;


/*
AW_IOTYPE_USER_IPCAM_PLAY_MEDIA_REQ		= 0x3002,
** @struct AWSMsg_AVIOCTRLPlayMedia
*/
/* AVIOCTRL Media Type */
typedef enum
{
    AW_AVIOCTRL_MEDIA_TYPE_AMR		= 0x00,
    AW_AVIOCTRL_MEDIA_TYPE_MP3		= 0x01
}ENUM_MEDIA_TYPE;

/*
AW_IOTYPE_USER_IPCAM_PLAY_MEDIA_REQ
*/
typedef struct
{
	unsigned int mediatype; // ENUM_MEDIA_TYPE
	char filepath[128];
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLPlayMediaReq;


/*
AW_IOTYPE_USER_IPCAM_PLAY_MEDIA_RESP
*/
typedef struct
{
	int result;
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLPlayMediaResp;

/*
AW_IOTYPE_USER_IPCAM_MEDIA_COMPLETE_RESP
*/
typedef struct
{
	char filepath[128];
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLMediaCompleteResp;

/*
AW_IOTYPE_USER_IPCAM_PAUSE_MEDIA_REQ
*/
typedef struct
{
	unsigned int mediatype; // ENUM_MEDIA_TYPE
	char filepath[128];
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLPauseMediaReq;

/*
AW_IOTYPE_USER_IPCAM_PAUSE_MEDIA_RESP
*/
typedef struct
{
	int result;
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLPauseMediaResp;

/*
AW_IOTYPE_USER_IPCAM_MOTION_ALARM
*/
typedef struct {
	char file_path[128];
	char thumb_path[128];
	char title[32];
	char digest[32];
}AWSMsg_AVIOCTRLMotionAlarm;


/*
AW_IOTYPE_USER_IPCAM_WIFI_SYNC_ACK
*/
//typedef struct
//{
//	char ipstr[128];
//	unsigned port;
//	unsigned char reserved[4];
//} AWSMsg_AVIOCTRLWifiSyncAck;


/*
AW_IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ		= 0x0322,
** @struct AWSMsg_AVIOCTRLGetStreamCtrlReq
*/
typedef struct
{
	unsigned int channel;	// Camera Index
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetStreamCtrlReq;

/*
AW_IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ		= 0x0320,
AW_IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP	= 0x0323,
** @struct AWSMsg_AVIOCTRLSetStreamCtrlReq, AWSMsg_AVIOCTRLGetStreamCtrlResq
*/
/* AVIOCTRL Quality Type */
typedef enum
{
    AVIOCTRL_QUALITY_UNKNOWN        = 0x00,
    AVIOCTRL_QUALITY_MAX            = 0x01,     //640*480, 30fps, bit rate not limited
    AVIOCTRL_QUALITY_HIGH           = 0x02,     //640*480, 15fps, 512kbps
    AVIOCTRL_QUALITY_MIDDLE         = 0x03,     //320*240, 15fps, 256kbps
    AVIOCTRL_QUALITY_LOW            = 0x04,     //320*240, 10fps, 128kbps
    AVIOCTRL_QUALITY_MIN            = 0x05,     //160*120, 10fps, 64kbps
}ENUM_QUALITY_LEVEL;

typedef struct
{
	unsigned int  channel;	// Camera Index
	unsigned char quality;	//refer to ENUM_QUALITY_LEVEL
	unsigned char reserved[3];
} AWSMsg_AVIOCTRLSetStreamCtrlReq, AWSMsg_AVIOCTRLGetStreamCtrlResq;

/*
AW_IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP	= 0x0321,
** @struct AWSMsg_AVIOCTRLSetStreamCtrlResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetStreamCtrlResp;


/*
AW_IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ	= 0x0326,
** @struct AWSMsg_AVIOCTRLGetMotionDetectReq
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetMotionDetectReq;


/*
AW_IOTYPE_USER_IPCAM_SETMOTIONDETECT_REQ		= 0x0324,
AW_IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP		= 0x0327,
** @struct AWSMsg_AVIOCTRLSetMotionDetectReq, AWSMsg_AVIOCTRLGetMotionDetectResp
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned int sensitivity; 	// 0(Disabled) ~ 100(MAX):
								// index		sensitivity value
								// 0			0
								// 1			25
								// 2			50
								// 3			75
								// 4			100
}AWSMsg_AVIOCTRLSetMotionDetectReq, AWSMsg_AVIOCTRLGetMotionDetectResp;


/*
AW_IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP	= 0x0325,
** @struct AWSMsg_AVIOCTRLSetMotionDetectResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetMotionDetectResp;


/*
AW_IOTYPE_USER_IPCAM_DEVINFO_REQ			= 0x0330,
** @struct AWSMsg_AVIOCTRLDeviceInfoReq
*/
typedef struct
{
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLDeviceInfoReq;


/*
AW_IOTYPE_USER_IPCAM_DEVINFO_RESP			= 0x0331,
** @struct AWSMsg_AVIOCTRLDeviceInfo
*/
typedef struct
{
	unsigned char model[16];	// IPCam mode
	unsigned char vendor[16];	// IPCam manufacturer
	unsigned int version;		// IPCam firmware version	ex. v1.2.3.4 => 0x01020304;  v1.0.0.2 => 0x01000002
	unsigned int channel;		// Camera index
	unsigned int total;			// 0: No cards been detected or an unrecognizeable sdcard that could not be re-formatted.
								// -1: if camera detect an unrecognizable sdcard, and could be re-formatted
								// otherwise: return total space size of sdcard (MBytes)								
								
	unsigned int free;			// Free space size of sdcard (MBytes)
	unsigned char reserved[8];	// reserved
}AWSMsg_AVIOCTRLDeviceInfoResp;

/*
AW_IOTYPE_USER_IPCAM_SETPASSWORD_REQ		= 0x0332,
** @struct AWSMsg_AVIOCTRLSetPasswdReq
*/
typedef struct
{
	char oldpasswd[32];			// The old security code
	char newpasswd[32];			// The new security code
}AWSMsg_AVIOCTRLSetPasswdReq;


/*
AW_IOTYPE_USER_IPCAM_SETPASSWORD_RESP		= 0x0333,
** @struct AWSMsg_AVIOCTRLSetPasswdResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetPasswdResp;


/*
AW_IOTYPE_USER_IPCAM_LISTWIFIAP_REQ		= 0x0340,
** @struct AWSMsg_AVIOCTRLListWifiApReq
*/
typedef struct
{
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLListWifiApReq;

typedef struct
{
	char ssid[32]; 				// WiFi ssid
	char mode;	   				// refer to ENUM_AP_MODE
	char enctype;  				// refer to ENUM_AP_ENCTYPE
	char signal;   				// signal intensity 0--100%
	char status;   				// 0 : invalid ssid or disconnected
								// 1 : connected with default gateway
								// 2 : unmatched password
								// 3 : weak signal and connected
								// 4 : selected:
								//		- password matched and
								//		- disconnected or connected but not default gateway
}SWifiAp;

/*
AW_IOTYPE_USER_IPCAM_LISTWIFIAP_RESP		= 0x0341,
** @struct AWSMsg_AVIOCTRLListWifiApResp
*/
typedef struct
{
	unsigned int number; // MAX number: 1024(IOCtrl packet size) / 36(bytes) = 28
	SWifiAp stWifiAp[1];
}AWSMsg_AVIOCTRLListWifiApResp;

/*
AW_IOTYPE_USER_IPCAM_SETWIFI_REQ			= 0x0342,
** @struct AWSMsg_AVIOCTRLSetWifiReq
*/
typedef struct
{
	unsigned char ssid[32];			//WiFi ssid
	unsigned char password[32];		//if exist, WiFi password
	unsigned char mode;				//refer to ENUM_AP_MODE
	unsigned char enctype;			//refer to ENUM_AP_ENCTYPE
	unsigned char reserved[10];
}AWSMsg_AVIOCTRLSetWifiReq;

//AW_IOTYPE_USER_IPCAM_SETWIFI_REQ_2		= 0x0346,
typedef struct
{
	unsigned char ssid[32];		// WiFi ssid
	unsigned char password[64];	// if exist, WiFi password
	unsigned char mode;			// refer to ENUM_AP_MODE
	unsigned char enctype;		// refer to ENUM_AP_ENCTYPE
	unsigned char reserved[10];
}AWSMsg_AVIOCTRLSetWifiReq2;

/*
AW_IOTYPE_USER_IPCAM_SETWIFI_RESP			= 0x0343,
** @struct AWSMsg_AVIOCTRLSetWifiResp
*/
typedef struct
{
	int result; //0: wifi connected; 1: failed to connect
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetWifiResp;

/*
AW_IOTYPE_USER_IPCAM_GETWIFI_REQ			= 0x0344,
** @struct AWSMsg_AVIOCTRLGetWifiReq
*/
typedef struct
{
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetWifiReq;

/*
AW_IOTYPE_USER_IPCAM_GETWIFI_RESP			= 0x0345,
** @struct AWSMsg_AVIOCTRLGetWifiResp //if no wifi connected, members of AWSMsg_AVIOCTRLGetWifiResp are all 0
*/
typedef enum
{
    AVIOTC_WIFIAPMODE_NULL      = 0x00,
    AVIOTC_WIFIAPMODE_MANAGED   = 0x01,
    AVIOTC_WIFIAPMODE_ADHOC = 0x02,
}ENUM_AP_MODE;
typedef enum
{
    AVIOTC_WIFIAPENC_INVALID    = 0x00,
    AVIOTC_WIFIAPENC_NONE       = 0x01,
    AVIOTC_WIFIAPENC_WEP        = 0x02, //WEP, for no password
    AVIOTC_WIFIAPENC_WPA_TKIP   = 0x03,
    AVIOTC_WIFIAPENC_WPA_AES    = 0x04,
    AVIOTC_WIFIAPENC_WPA2_TKIP  = 0x05,
    AVIOTC_WIFIAPENC_WPA2_AES   = 0x06,
    AVIOTC_WIFIAPENC_WPA_PSK_TKIP   = 0x07,
    AVIOTC_WIFIAPENC_WPA_PSK_AES    = 0x08,
    AVIOTC_WIFIAPENC_WPA2_PSK_TKIP  = 0x09,
    AVIOTC_WIFIAPENC_WPA2_PSK_AES   = 0x0A,
}ENUM_AP_ENCTYPE;

typedef struct
{
	unsigned char ssid[32];		// WiFi ssid
	unsigned char password[32]; // WiFi password if not empty
	unsigned char mode;			// refer to ENUM_AP_MODE
	unsigned char enctype;		// refer to ENUM_AP_ENCTYPE
	unsigned char signal;		// signal intensity 0--100%
	unsigned char status;		// refer to "status" of SWifiAp
}AWSMsg_AVIOCTRLGetWifiResp;

typedef struct
{
	int result;	// 0: success; -1: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLCommResp;

//AW_IOTYPE_USER_IPCAM_GET_BITRATE_RESP 
typedef struct
{
	unsigned int bitrate;	// 0: success; -1: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetBitrate;




//changed: WI-FI Password 32bit Change to 64bit 
//AW_IOTYPE_USER_IPCAM_GETWIFI_RESP_2    = 0x0347,
typedef struct
{
 unsigned char ssid[32];	 // WiFi ssid
 unsigned char password[64]; // WiFi password if not empty
 unsigned char mode;	// refer to ENUM_AP_MODE
 unsigned char enctype; // refer to ENUM_AP_ENCTYPE
 unsigned char signal;  // signal intensity 0--100%
 unsigned char status;  // refer to "status" of SWifiAp
}AWSMsg_AVIOCTRLGetWifiResp2;

/*
AW_IOTYPE_USER_IPCAM_GETRECORD_REQ			= 0x0312,
** @struct AWSMsg_AVIOCTRLGetRecordReq
*/
typedef struct
{
	unsigned int channel; // Camera Index
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetRecordReq;

/*
AW_IOTYPE_USER_IPCAM_SETRECORD_REQ			= 0x0310,
AW_IOTYPE_USER_IPCAM_GETRECORD_RESP		= 0x0313,
** @struct AWSMsg_AVIOCTRLSetRecordReq, AWSMsg_AVIOCTRLGetRecordResq
*/
typedef struct
{
	unsigned int channel;		// Camera Index
	unsigned int recordType;	// Refer to ENUM_RECORD_TYPE
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetRecordReq, AWSMsg_AVIOCTRLGetRecordResp;

/*
AW_IOTYPE_USER_IPCAM_SETRECORD_RESP		= 0x0311,
** @struct AWSMsg_AVIOCTRLSetRecordResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetRecordResp;


/*
AW_IOTYPE_USER_IPCAM_GETRCD_DURATION_REQ	= 0x0316,
** @struct AWSMsg_AVIOCTRLGetRcdDurationReq
*/
typedef struct
{
	unsigned int channel; // Camera Index
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetRcdDurationReq;

/*
AW_IOTYPE_USER_IPCAM_SETRCD_DURATION_REQ	= 0x0314,
AW_IOTYPE_USER_IPCAM_GETRCD_DURATION_RESP  = 0x0317,
** @struct AWSMsg_AVIOCTRLSetRcdDurationReq, AWSMsg_AVIOCTRLGetRcdDurationResp
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned int presecond; 	// pre-recording (sec)
	unsigned int durasecond;	// recording (sec)
}AWSMsg_AVIOCTRLSetRcdDurationReq, AWSMsg_AVIOCTRLGetRcdDurationResp;


/*
AW_IOTYPE_USER_IPCAM_SETRCD_DURATION_RESP  = 0x0315,
** @struct AWSMsg_AVIOCTRLSetRcdDurationResp
*/
typedef struct
{
	int result;	// 0: success; otherwise: failed.
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLSetRcdDurationResp;


typedef struct
{
	unsigned short year;	// The number of year.
	unsigned char month;	// The number of months since January, in the range 1 to 12.
	unsigned char day;		// The day of the month, in the range 1 to 31.
	unsigned char wday;		// The number of days since Sunday, in the range 0 to 6. (Sunday = 0, Monday = 1, ...)
	unsigned char hour;     // The number of hours past midnight, in the range 0 to 23.
	unsigned char minute;   // The number of minutes after the hour, in the range 0 to 59.
	unsigned char second;   // The number of seconds after the minute, in the range 0 to 59.
}STimeDay;

/*
AW_IOTYPE_USER_IPCAM_LISTEVENT_REQ			= 0x0318,
** @struct AWSMsg_AVIOCTRLListEventReq
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	STimeDay stStartTime; 		// Search event from ...
	STimeDay stEndTime;	  		// ... to (search event)
	unsigned char event;  		// event type, refer to ENUM_EVENTTYPE
	unsigned char status; 		// 0x00: Recording file exists, Event unreaded
								// 0x01: Recording file exists, Event readed
								// 0x02: No Recording file in the event
	unsigned char reserved[2];
}AWSMsg_AVIOCTRLListEventReq;


typedef struct
{
	STimeDay stTime;
	unsigned char event;
	unsigned char status;	// 0x00: Recording file exists, Event unreaded
							// 0x01: Recording file exists, Event readed
							// 0x02: No Recording file in the event
	unsigned char reserved[2];
}SAvEvent;
	
/*
AW_IOTYPE_USER_IPCAM_LISTEVENT_RESP		= 0x0319,
** @struct AWSMsg_AVIOCTRLListEventResp
*/
typedef struct
{
	unsigned int  channel;		// Camera Index
	unsigned int  total;		// Total event amount in this search session
	unsigned char index;		// package index, 0,1,2...; 
								// because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
	unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
	unsigned char count;		// how much events in this package
	unsigned char reserved[1];
	SAvEvent stEvent[1];		// The first memory address of the events in this package
}AWSMsg_AVIOCTRLListEventResp;

	
/*
AW_IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL 	= 0x031A,
** @struct AWSMsg_AVIOCTRLPlayRecord
*/
typedef struct
{
	unsigned int channel;	// Camera Index
	unsigned int command;	// play record command. refer to ENUM_PLAYCONTROL
	unsigned int Param;		// command param, that the user defined
	STimeDay stTimeDay;		// Event time from ListEvent
	unsigned char reserved[4];
} AWSMsg_AVIOCTRLPlayRecord;

/*
AW_IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP 	= 0x031B,
** @struct AWSMsg_AVIOCTRLPlayRecordResp
*/
typedef struct
{
	unsigned int command;	// Play record command. refer to ENUM_PLAYCONTROL
	int result; 	// Depends on command
							// when is AW_AVIOCTRL_RECORD_PLAY_START:
							//	result>=0   real channel no used by device for playback
							//	result <0	error
							//			-1	playback error
							//			-2	exceed max allow client amount
	unsigned char reserved[4];
} AWSMsg_AVIOCTRLPlayRecordResp; // only for play record start command


/*
AW_IOTYPE_USER_IPCAM_PTZ_COMMAND	= 0x1001,	// P2P Ptz Command Msg 
** @struct AWSMsg_AVIOCTRLPtzCmd
*/
typedef struct
{
	unsigned char control;	// PTZ control command, refer to ENUM_PTZCMD
	unsigned char speed;	// PTZ control speed
	unsigned char point;	// no use in APP so far. preset position, for RS485 PT
	unsigned char limit;	// no use in APP so far. 
	unsigned char aux;		// no use in APP so far. auxiliary switch, for RS485 PT
	unsigned char channel;	// camera index
	unsigned char reserve[2];
} AWSMsg_AVIOCTRLPtzCmd;

/*
AW_IOTYPE_USER_IPCAM_EVENT_REPORT	= 0x1FFF,	// Device Event Report Msg 
*/
/** @struct AWSMsg_AVIOCTRLEvent
 */
 //IOTYPE_USER_IPCAM_EVENT_REPORT (0x1FFF)
//IPCamera to App
typedef struct
{
	STimeDay stTime;
	unsigned long time; 	// UTC Time
	unsigned int  channel; 	// Camera Index
	unsigned int  event; 	// Event Type
	unsigned char reserved[4];
} AWSMsg_AVIOCTRLEvent;

/*
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_START         =0x2008,
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_START_RESP    =0x2009,
	
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_STOP          =0x2010,
	AW_IOTYPE_USER_IPCAM_FILE_TRANS_END           =0x2011,
*/
typedef struct
{
	unsigned char name[128];
	unsigned char path[128];
	unsigned int  fileLenth; 	
	unsigned int  filetype;
	unsigned char md5[32];
	unsigned char reserved[32];
} AWSMsg_AVIOCTRLFille;

#define HANDCHECK_VALUE 0x1234ABCD
typedef struct
{
	unsigned int handCheck;
	unsigned int pktNo;
	unsigned int lenth;
}AWFileInfo;
#if 0

/* 	AW_IOTYPE_USER_IPCAM_GET_EVENTCONFIG_REQ	= 0x0400,	// Get Event Config Msg Request 
 */
/** @struct AWSMsg_AVIOCTRLGetEventConfig
 */
typedef struct
{
	unsigned int	channel; 		  //Camera Index
	unsigned char   externIoOutIndex; //extern out index: bit0->io0 bit1->io1 ... bit7->io7;=1: get this io value or not get
    unsigned char   externIoInIndex;  //extern in index: bit0->io0 bit1->io1 ... bit7->io7; =1: get this io value or not get
	char reserved[2];
} AWSMsg_AVIOCTRLGetEventConfig;
 
/*
	AW_IOTYPE_USER_IPCAM_GET_EVENTCONFIG_RESP	= 0x0401,	// Get Event Config Msg Response 
	AW_IOTYPE_USER_IPCAM_SET_EVENTCONFIG_REQ	= 0x0402,	// Set Event Config Msg req 
*/
/* @struct AWSMsg_AVIOCTRLSetEventConfig
 * @struct AWSMsg_AVIOCTRLGetEventCfgResp
 */
typedef struct
{
	unsigned int    channel;        // Camera Index
	unsigned char   mail;           // enable send email
	unsigned char   ftp;            // enable ftp upload photo
	unsigned char   externIoOutStatus;   // enable extern io output //bit0->io0 bit1->io1 ... bit7->io7; 1:on; 0:off
	unsigned char   p2pPushMsg;			 // enable p2p push msg
	unsigned char   externIoInStatus;    // enable extern io input  //bit0->io0 bit1->io1 ... bit7->io7; 1:on; 0:off
	char            reserved[3];
}AWSMsg_AVIOCTRLSetEventConfig, AWSMsg_AVIOCTRLGetEventCfgResp;

/*
	AW_IOTYPE_USER_IPCAM_SET_EVENTCONFIG_RESP	= 0x0403,	// Set Event Config Msg resp 
*/
/** @struct AWSMsg_AVIOCTRLSetEventCfgResp
 */
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned int result;	// 0: success; otherwise: failed.
}AWSMsg_AVIOCTRLSetEventCfgResp;

#endif


/*
AW_IOTYPE_USER_IPCAM_SET_ENVIRONMENT_REQ		= 0x0360,
** @struct AWSMsg_AVIOCTRLSetEnvironmentReq
*/
/*
AW_IOTYPE_USER_IPCAM_GET_ENVIRONMENT_RESP		= 0x0363,
** @struct AWSMsg_AVIOCTRLGetEnvironmentResp
*/

typedef enum
{
	AVIOCTRL_ENVIRONMENT_INDOOR_50HZ = 0x00,
	AVIOCTRL_ENVIRONMENT_INDOOR_60HZ  = 0x01,
	AVIOCTRL_ENVIRONMENT_OUTDOOR      = 0x02,
	AVIOCTRL_ENVIRONMENT_NIGHT    = 0x03,
}ENUM_ENVIRONMENT_MODE;

typedef struct
{
	unsigned int channel;		// Camera Index
	unsigned char mode;			// refer to ENUM_ENVIRONMENT_MODE
	unsigned char reserved[3];
}AWSMsg_AVIOCTRLSetEnvironmentReq, AWSMsg_AVIOCTRLGetEnvironmentResp;


/*
AW_IOTYPE_USER_IPCAM_SET_ENVIRONMENT_RESP		= 0x0361,
** @struct AWSMsg_AVIOCTRLSetEnvironmentResp
*/
typedef struct
{
	unsigned int channel; 		// Camera Index
	unsigned char result;		// 0: success; otherwise: failed.
	unsigned char reserved[3];
}AWSMsg_AVIOCTRLSetEnvironmentResp;


/*
AW_IOTYPE_USER_IPCAM_GET_ENVIRONMENT_REQ		= 0x0362,
** @struct AWSMsg_AVIOCTRLGetEnvironmentReq
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetEnvironmentReq;


typedef enum
{
    AVIOCTRL_VIDEOMODE_NORMAL           = 0x00,
    AVIOCTRL_VIDEOMODE_FLIP             = 0x01, // vertical flip
    AVIOCTRL_VIDEOMODE_MIRROR           = 0x02, // horizontal flip
    AVIOCTRL_VIDEOMODE_FLIP_MIRROR      = 0x03, // vertical & horizontal flip
}ENUM_VIDEO_MODE;

/*
AW_IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ			= 0x0370,
** @struct AWSMsg_AVIOCTRLSetVideoModeReq
*/
/*
AW_IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP 	= 0x0373,
** @struct AWSMsg_AVIOCTRLGetVideoModeResp
*/
typedef struct
{
	unsigned int channel;	// Camera Index
	unsigned char mode;		// refer to ENUM_VIDEO_MODE
	unsigned char reserved[3];
}AWSMsg_AVIOCTRLSetVideoModeReq, AWSMsg_AVIOCTRLGetVideoModeResp;


/*
AW_IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP		= 0x0371,
** @struct AWSMsg_AVIOCTRLSetVideoModeResp
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char result;	// 0: success; otherwise: failed.
	unsigned char reserved[3];
}AWSMsg_AVIOCTRLSetVideoModeResp;


/*
AW_IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ			= 0x0372,
** @struct AWSMsg_AVIOCTRLGetVideoModeReq
*/
typedef struct
{
	unsigned int channel; 	// Camera Index
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetVideoModeReq;


/*
/AW_IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ			= 0x0380,
** @struct AWSMsg_AVIOCTRLFormatExtStorageReq
*/
typedef struct
{
	unsigned int storage; 	// Storage index (ex. sdcard slot = 0, internal flash = 1, ...)
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLFormatExtStorageReq;


/*
AW_IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ		= 0x0381,
** @struct AWSMsg_AVIOCTRLFormatExtStorageResp
*/
typedef struct
{
	unsigned int  storage; 	// Storage index
	unsigned char result;	// 0: success;
							// -1: format command is not supported.
							// otherwise: failed.
	unsigned char reserved[3];
}AWSMsg_AVIOCTRLFormatExtStorageResp;


typedef struct
{
	unsigned short index;		// the stream index of camera
	unsigned short channel;		// the channel index used in AVAPIs, that is ChID in avServStart2(...,ChID)
	char reserved[4];
}SStreamDef;


/*	AW_IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ			= 0x0328,
 */
typedef struct
{
	unsigned char reserved[4];
}AWSMsg_AVIOCTRLGetSupportStreamReq;


/*	AW_IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP			= 0x0329,
 */
typedef struct
{
	unsigned int number; 		// the quanity of supported audio&video stream or video stream
	SStreamDef streams[1];
}AWSMsg_AVIOCTRLGetSupportStreamResp;


/* AW_IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ			= 0x032A, //used to speak. but once camera is connected by App, send this at once.
 */
typedef struct
{
	unsigned int channel;		// camera index
	char reserved[4];
}AWSMsg_AVIOCTRLGetAudioOutFormatReq;

/* AW_IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP			= 0x032B,
 */
typedef struct
{
	unsigned int channel;		// camera index
	int format;					// refer to ENUM_CODECID in AVFRAMEINFO.h
	char reserved[4];
}AWSMsg_AVIOCTRLGetAudioOutFormatResp;

/* AW_IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME			= 0x1002,
 */
typedef struct
{
	unsigned int channel;		// camera index
	char reserved[4];
}AWSMsg_AVIOCTRLReceiveFirstIFrame;

/* AW_IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ              = 0x390
 */
typedef struct
{
	unsigned int channel;			// camera index
	unsigned int collect_interval;	// seconds of interval to collect flow information
									// send 0 indicates stop collecting.
}AWSMsg_AVIOCTRLGetFlowInfoReq;

/* AW_IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP            = 0x391
 */
typedef struct
{
	unsigned int channel;			// camera index
	unsigned int collect_interval;	// seconds of interval client will collect flow information
}AWSMsg_AVIOCTRLGetFlowInfoResp;

/* AW_IOTYPE_USER_IPCAM_CURRENT_FLOWINFO              = 0x392
 */
typedef struct
{
	unsigned int channel;						// camera index
	unsigned int total_frame_count;				// Total frame count in the specified interval
	unsigned int lost_incomplete_frame_count;	// Total lost and incomplete frame count in the specified interval
	unsigned int total_expected_frame_size;		// Total expected frame size from avRecvFrameData2()
	unsigned int total_actual_frame_size;		// Total actual frame size from avRecvFrameData2()
	unsigned int timestamp_ms;					// Timestamp in millisecond of this report.
	char reserved[8];
}AWSMsg_AVIOCTRLCurrentFlowInfo;

/* AW_IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ               = 0x3A0
 * AW_IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP              = 0x3A1
 * AW_IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ               = 0x3B0
 * AW_IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP              = 0x3B1
 */
typedef struct
{
	int cbSize;							// the following package size in bytes, should be sizeof(AWSMsg_AVIOCTRLTimeZone)
	int nIsSupportTimeZone;
	int nGMTDiff;						// the difference between GMT in hours
	char szTimeZoneString[256];			// the timezone description string in multi-bytes char format
}AWSMsg_AVIOCTRLTimeZone;

/*
// dropbox support
AW_IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_REQ      = 0x500,
AW_IOTYPE_USER_IPCAM_GET_SAVE_DROPBOX_RESP     = 0x501,
*/
typedef struct
{
    unsigned short nSupportDropbox;     // 0:no support/ 1: support dropbox
    unsigned short nLinked;             // 0:no link/ 1:linked
    char szLinkUDID[64];                // Link UDID for App
}AWSMsg_AVIOCTRLGetDropbox;


/*
 // dropbox support
 AW_IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_REQ      = 0x502,
 AW_IOTYPE_USER_IPCAM_SET_SAVE_DROPBOX_RESP     = 0x503,
 */
typedef struct
{
    unsigned short nLinked;             // 0:no link/ 1:linked
    char szLinkUDID[64];                // UDID for App
    char szAccessToken[128];             // Oauth token
    char szAccessTokenSecret[128];       // Oauth token secret
	char szAppKey[128];                  // App Key (reserved)
	char szSecret[128];                  // Secret  (reserved)
}AWSMsg_AVIOCTRLSetDropbox;

typedef struct _FRAMEINFO
{
	unsigned short codec_id;	// Media codec type defined in sys_mmdef.h,
								// MEDIA_CODEC_AUDIO_PCMLE16 for audio,
								// MEDIA_CODEC_VIDEO_H264 for video.
	unsigned char flags;		// Combined with IPC_FRAME_xxx.
	unsigned char cam_index;	// 0 - n

	unsigned char onlineNum;	// number of client connected this device
	unsigned char reserve1[3];

	unsigned int reserve2;	//
	unsigned int timestamp;	// Timestamp of the frame, in milliseconds
 
		
}FRAMEINFO_t;


typedef struct _MediaFramExt
{
    int nGopIndex;
	int nFrameIndex;
	int nTotalIndex; 
	int nAvgQP;
	int resert1;
	int resert2;
}MediaFramExt_t;

typedef enum {
	P2P   = 0x0,
	RELAY = 0x1,
	LAN   = 0x2
} ENUM_NET_MODE;

typedef struct _NetInfo
{
	unsigned char Mode; //!< 0: P2P mode, 1: Relay mode, 2: LAN mode
	char RemoteIP[17]; //!< The IP address of remote site used during this IOTC session
	unsigned short RemotePort; //!< The port number of remote site used during this IOTC session
	unsigned char NatType; //!< The remote NAT type
	unsigned char isSecure; //!< 0: The IOTC session is in non-secure mode, 1: The IOTC session is in secure mode
}NetInfo_t;


typedef enum
{
	VSTREAM_INVALID			= -1,
	VSTREAM_MAIN			= 0,
	VSTREAM_P2P				= 1,
	ASTREAM_VOICE			= 2,
	VSTREAM_PLAYBACK		= 3,
}ENUM_AW_PLAY_TYPE;

	
typedef enum 
{
	MEDIA_CODEC_UNKNOWN			= 0x00,
	MEDIA_CODEC_VIDEO_MPEG4		= 0x4C,
	MEDIA_CODEC_VIDEO_H263		= 0x4D,
	MEDIA_CODEC_VIDEO_H264		= 0x4E,
	MEDIA_CODEC_VIDEO_MJPEG		= 0x4F,
	
    MEDIA_CODEC_AUDIO_AAC       = 0x88,   // 2014-07-02 add AAC audio codec definition
    MEDIA_CODEC_AUDIO_G711U     = 0x89,   //g711 u-law
    MEDIA_CODEC_AUDIO_G711A     = 0x8A,   //g711 a-law	
    MEDIA_CODEC_AUDIO_ADPCM     = 0X8B,
	MEDIA_CODEC_AUDIO_PCM		= 0x8C,
	MEDIA_CODEC_AUDIO_SPEEX		= 0x8D,
	MEDIA_CODEC_AUDIO_MP3		= 0x8E,
    MEDIA_CODEC_AUDIO_G726      = 0x8F,

}ENUM_CODECID;

/* FRAME Flag */
typedef enum 
{
	IPC_FRAME_FLAG_PBFRAME	= 0x00,	// A/V P/B frame..
	IPC_FRAME_FLAG_IFRAME	= 0x01,	// A/V I frame.
	IPC_FRAME_FLAG_MD		= 0x02,	// For motion detection.
	IPC_FRAME_FLAG_IO		= 0x03,	// For Alarm IO detection.
}ENUM_FRAMEFLAG;

typedef enum
{
	AUDIO_SAMPLE_8K			= 0x00,
	AUDIO_SAMPLE_11K		= 0x01,
	AUDIO_SAMPLE_12K		= 0x02,
	AUDIO_SAMPLE_16K		= 0x03,
	AUDIO_SAMPLE_22K		= 0x04,
	AUDIO_SAMPLE_24K		= 0x05,
	AUDIO_SAMPLE_32K		= 0x06,
	AUDIO_SAMPLE_44K		= 0x07,
	AUDIO_SAMPLE_48K		= 0x08,
}ENUM_AUDIO_SAMPLERATE;

typedef enum
{
	AUDIO_DATABITS_8		= 0,
	AUDIO_DATABITS_16		= 1,
}ENUM_AUDIO_DATABITS;

typedef enum
{
	AUDIO_CHANNEL_MONO		= 0,
	AUDIO_CHANNEL_STERO		= 1,
}ENUM_AUDIO_CHANNEL;

#define AUDIO_BUF_SIZE	1024
#define VIDEO_BUF_SIZE	(1024 * 300)

#define NET_WORK_TYPE_DEFAULT 0
#define NET_WORK_TYPE_FACTORY 1

class AWNetNotificationHandler {
public:
		AWNetNotificationHandler() {};
		virtual ~AWNetNotificationHandler() {};
		virtual int handleNetCmd(int SID, int CommdID, char* buf) = 0;
		virtual int handleRecvFile(int SID, AWFileInfo* fileInfo, char* buf, unsigned int buferLen) = 0;
		
		virtual int handleRecvVideoData(char *abFrameData, int nFrameDataMaxSize,char *abFrameInfo, 
								int nFrameInfoMaxSize, unsigned int nFrameIdx)= 0;
		virtual int handleRecvAudioData(char *abAudioData, int nAudioDataMaxSize,char *abFrameInfo, 
								int nFrameInfoMaxSize, unsigned int nFrameIdx)= 0;

};

class AWNetInterface {
public:

//#define NET_WORK_TYPE_DEFAULT 0
//#define NET_WORK_TYPE_FACTORY 1
	static AWNetInterface * getInstance(int type = 0);
	
	virtual int init(char* uuid, char* password, int deviceType, char *ip, unsigned port) = 0;
    virtual int setDevName(const char *devname, int leng) = 0;
	virtual int deInit() = 0;
	virtual bool isInit() = 0;
	virtual int awSendVideoData(ENUM_AW_PLAY_TYPE playType, const char *cabFrameData, int nFrameDataSize,
								const void *cabFrameInfo, int nFrameInfoSize, void* revert) = 0;
															
	virtual int awSendAudioData(const char *cabAudioData, int nAudioDataSize,
								const void *cabFrameInfo, int nFrameInfoSize, void* revert) = 0;
	
	virtual int awSendIOCtrl(int SID, unsigned int nIOCtrlType, const char *cabIOCtrlData, int nIOCtrlDataSize) = 0;
	
 	virtual void setPassword(char* password) = 0;
	virtual int awGetNetInfo(int SID, NetInfo_t * pNetInfo) = 0;
	virtual void registerNotificationHandler(AWNetNotificationHandler * pAWNetNotificationHandler) = 0;
	virtual ~AWNetInterface(){};
	
};


#endif
