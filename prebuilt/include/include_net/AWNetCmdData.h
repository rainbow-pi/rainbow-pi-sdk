#ifndef __AW_NET_CMD_DATA_H__
#define __AW_NET_CMD_DATA_H__

enum CmdType {
	NAT_CMD_SET_RECORDER_QUALITY   =   0xA001,
	NAT_CMD_SET_RECORDER_QUALITY_RESP, // 
		
	NAT_CMD_SET_RECORDER_DURATION, // 
	NAT_CMD_SET_RECORDER_DURATION_RESP, //
	
	NAT_CMD_SET_PHOTO_QUALITY, //  
	NAT_CMD_SET_PHOTO_QUALITY_RESP, //  
	
	NAT_CMD_SET_WHITE_BALANCE,//  
	NAT_CMD_SET_WHITE_BALANCE_RESP, //  
	
	NAT_CMD_SET_EXPOSURE, // 
	NAT_CMD_SET_EXPOSURE_RESP,//  0xA00A,
	
	NAT_CMD_SET_BOOT_RECORDER,//  
	NAT_CMD_SET_BOOT_RECORDER_RESP,// 
	
	NAT_CMD_SET_MUTE,//  
	NAT_CMD_SET_MUTE_RESP,// 
	
	NAT_CMD_SET_REAR_VIEW_MIRROR,// 
	NAT_CMD_SET_REAR_VIEW_MIRROR_RESP,//    0xA010,
	
	NAT_CMD_SET_TIME, //  
	NAT_CMD_SET_TIME_RESP, //   
	
	NAT_CMD_SET_LANGUAGE,//    
	NAT_CMD_SET_LANGUAGE_RESP,//  
	
	NAT_CMD_SET_SMART_DETECT , //   
	NAT_CMD_SET_SMART_DETECT_RESP , //   
	
	NAT_CMD_SET_LANE_LINE_CALIBRATION , //    
	NAT_CMD_SET_LANE_LINE_CALIBRATION_RESP , // 
	
	NAT_CMD_SET_IMPACT_SENSITIVITY , //   
	NAT_CMD_SET_IMPACT_SENSITIVITY_RESP , //  0xA01A
	
	NAT_CMD_SET_MOTION_DETECT, //    
	NAT_CMD_SET_MOTION_DETECT_RESP,//   
	
	NAT_CMD_SET_WATERMARK  , //    
	NAT_CMD_SET_WATERMARK_RESP , //    
	
	NAT_CMD_FORMAT_TF_CARD , //   
	NAT_CMD_FORMAT_TF_CARD_RESP , //   0xA020
	
	NAT_CMD_SCREEN_SLEEP  , //   
	NAT_CMD_SCREEN_SLEEP_RESP , //   
	
	NAT_CMD_PLAY_RECORDER  , //  
	NAT_CMD_PLAY_RECORDER_RESP , // 
	
	NAT_CMD_GET_FILE_LIST , //   
	NAT_CMD_GET_FILE_LIST_RESP , // 
	
	NAT_CMD_REQUEST_FILE   , // 
	NAT_CMD_REQUEST_FILE_RESP , //   
	
	NAT_CMD_REQUEST_FILE_FINISH ,
	
	NAT_CMD_CHECK_TF_CARD        , // 0xA02A
	NAT_CMD_CHECK_TF_CARD_RESP	 , //
	
	NAT_CMD_DELETE_FILE          ,
	NAT_CMD_DELETE_FILE_RESP 	,
	
	NAT_CMD_RECORD_CTL           ,
	NAT_CMD_RECORD_CTL_RESP		,
	
	NAT_CMD_TURN_OFF_WIFI        ,//0xA030
	
	NAT_CMD_SET_WIFI_PWD        , 
	
	NAT_CMD_SET_SYNC_FILE       , 
	NAT_CMD_SET_SYNC_FILE_RESP	,
	
	NAT_CMD_GET_CONFIG          , //0xA034
	NAT_CMD_GET_CONFIG_RESP		,
	
	NAT_CMD_CHANGE_CAM          , 
	NAT_CMD_CHANGE_CAM_RESP     , 
	
	NAT_CMD_TAKE_PHOTO          , 
	NAT_CMD_TAKE_PHOTO_RESP		,
	
	NAT_CMD_RECORD_ON_OFF       , //0xA03A
	NAT_CMD_RECORD_ON_OFF_RESP	, 
	
	NAT_CMD_SET_VIDEO_SIZE       ,
	NAT_CMD_SET_VIDEO_SIZE_ACK   ,

	NAT_CMD_NET_CONNECT_STATE     ,
	NAT_CMD_NET_CONNECT_STATE_RESP, // 0xA03F

	NAT_CMD_EVENT_SOS_FILE, // 0xA040
	NAT_CMD_UVC_DISCONNECT, // 0xA041

	NAT_CMD_SET_RECORDER_BITRATE ,//
	NAT_CMD_SET_RECORDER_BITRATE_RESP,

	NAT_CMD_SET_RECORDER_DELAY_TIME,//0xA044
	NAT_CMD_SET_RECORDER_DELAY_TIME_RESP,//0xA045

	NAT_CMD_SLOW_RECORD_ON_OFF       , //0xA046
	NAT_CMD_SLOW_RECORD_ON_OFF_RESP	, //0XA047

	NAT_CMD_GET_THUMBNAIL,   // 0xA048
	NAT_CMD_GET_THUMBNAIL_RESP,   // 0xA049

	NAT_CMD_SLOW_RECORD_VEDIO_SIZE, //0XA04a
	NAT_CMD_SLOW_RECORD_VEDIO_SIZE_RESP,//0XA0ab

	NAT_CMD_TIME_TAKE_PHOTO, //0XA04C
	NAT_CMD_TIME_TAKE_PHOTO_RESP,//0XA04D

	NAT_CMD_AUTO_TIME_TAKE_PHOTO, //0XA04E
	NAT_CMD_AUTO_TIME_TAKE_PHOTO_RESP,//0XA04F

	NAT_CMD_LED_FREQ, //0XA050
	NAT_CMD_LED_FREQ_RESP,//0XA051

	NAT_CMD_LED_ON_OFF, //0XA052
	NAT_CMD_LED_ON_OFF_RESP,//0XA053

	NAT_CMD_FACTORY_RESET, //0XA054
	NAT_CMD_FACTORY_RESET_RESP,//0XA055

	NAT_CMD_LIST_IMAGE_ROTATION, // 0XA056
	NAT_CMD_LIST_IMAGE_ROTATION_RESP, //0XA057

	
	NAT_CMD_MOTION_TAKE_PHOTO, // 0XA058
	NAT_CMD_MOTION_TAKE_PHOTO_RESP, //0XA059

	NAT_CMD_INSERT_TF_CARD,
	NAT_CMD_REMOVE_TF_CARD,

	NAT_CMD_STOP_NET_RECORD_PREVIEW, //0XA05C
	NAT_CMD_STOP_NET_RECORD_PREVIEW_RESP,//0XA05D

	NAT_CMD_START_NET_RECORD_PREVIEW,//0XA05E
	NAT_CMD_START_NET_RECORD_PREVIEW_RESP,//0XA05F

	NAT_CMD_MOTION_TAKE_PHOTO_FINISH,//0XA060

	NAT_CMD_RECORD_TO_FULL_DISK,//0xa061

};

#define NAT_CMD_FILE_TRANS_CMD_APK_TO_CDR                1
#define NAT_CMD_FILE_TRANS_CMD_CDR_TO_APK                0




#define NAT_BROADCAST_SID                 0

#pragma pack(1)
typedef struct __aw_cdr_net_config {
	int record_quality;
	int record_duration;
	int record_delayp;
	int record_slowp;
	int record_Sound;
	int photo_quality;
	int photo_timetakephotos;
	int photo_automatictakephotos;
	int photo_motiontakephotos;
	int exposure;
	int white_balance;
	int image_rotation;
	int led_freq;
	int led_on_off;
	int screen_sleep;
	int record_switch;
	int slow_record_switch;
	int language;
	int watermark;
	int dev_type;
	char firmware_version[32];
	
} aw_cdr_net_config;

typedef struct __aw_cdr_tf_capacity {
	unsigned long long remain;
	unsigned long long total;
} aw_cdr_tf_capacity;

typedef struct __aw_cdr_file_trans {
	int from_to;
	char filename[256];
	int local_port;
	char local_ip[20];
	int remote_port;
	char remote_ip[20];
	char url[512];
} aw_cdr_file_trans;

typedef struct __aw_cdr_handle_file {
	char filename[256];
} aw_cdr_handle_file;


typedef struct __aw_cdr_set_time {
	int tm_sec; 		/* seconds */
	int tm_min; 		/* minutes */
	int tm_hour;		/* hours */
	int tm_mday;		/* day of the month */
	int tm_mon; 		/* month */
	int tm_year;		/* year */
	int tm_wday;		/* day of the week */
	int tm_yday;		/* day in the year */
	int tm_isdst;		/* daylight saving time */
}aw_cdr_set_time;

//typedef struct __aw_cdr_net_string {
//	int max_len;
//	char* string;
//} aw_cdr_net_string, aw_cdr_file_list, aw_cdr_rtsp_url;

typedef struct __aw_cdr_play_record_ctl {
	int ctl_name; // seek = 0;
	int time;     // unit second
} aw_cdr_play_record_ctl;

typedef struct __aw_cdr_wifi_setting {
	char ssid[64];
	char old_pwd[64];
	char new_pwd[64];
} aw_cdr_wifi_setting;

typedef struct __aw_cdr_set_video_size {
	int resolution_index;
} aw_cdr_set_video_size;

typedef struct __aw_cdr_wifi_state {
	int state;
} aw_cdr_wifi_state;

typedef struct __aw_cdr_set_video_quality_index {
	int video_quality_index;
}aw_cdr_set_video_quality_index;

typedef struct __aw_cdr_index {
	int index;
}aw_cdr_set_recorder_quality, aw_cdr_set_recorder_duration,
 aw_cdr_set_photo_quality, aw_cdr_set_white_balance,
 aw_cdr_set_exposure, aw_cdr_set_boot_recorder,
 aw_cdr_set_mute, aw_cdr_set_language, aw_cdr_set_motion_detect,
 aw_cdr_set_watermark, aw_cdr_change_cam, aw_cdr_recorder_onoff,
 aw_cdr_net_state;

typedef struct __aw_cdr_sos_filename {
	char filename[256];
}aw_cdr_sos_filename;

typedef struct __aw_cdr_reply_simple_result {
	int result;
}aw_cdr_set_recorder_quality_resp, aw_cdr_set_recorder_duration_resp,
 aw_cdr_set_photo_quality_resp, aw_cdr_set_white_balance_resp,
 aw_cdr_set_exposure_resp, aw_cdr_set_boot_recorder_resp,
 aw_cdr_set_mute_resp, aw_cdr_set_language_resp, 
 aw_cdr_set_motion_detect_resp, aw_cdr_set_watermark_resp, 
 aw_cdr_change_cam_resp, aw_cdr_recorder_onoff_resp, 
 aw_cdr_set_video_quality_index_resp, aw_cdr_set_video_quality_index_resp,
 aw_cdr_set_time_resp, aw_cdr_format_tf_card_resp,
 aw_cdr_take_photo_resp, aw_cdr_delete_file_resp,aw_sdv_tf_insert_remove_resp,aw_cdr_stop_net_record_resp,
 aw_cdr_start_net_record_resp,aw_cdr_motion_take_photo_finsh_resp,aw_cdr_record_to_full_disk_resp;
#define MAX_PACKET_FILE_LIST_LEN 992
typedef struct __aw_cdr_get_file_list {
	int totalCnt;
	int currentIndex;
	char filelist[MAX_PACKET_FILE_LIST_LEN];
}aw_cdr_get_file_list_resp;

typedef struct __aw_cdr_get_thumbnail {
	char path[256];
	int result;
}aw_cdr_get_thumbnail, aw_cdr_get_thumbnail_resp;

#pragma pack()

#endif
