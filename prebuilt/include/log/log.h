#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#define _GLOG_INFO  0
#define _GLOG_WARN  1
#define _GLOG_ERROR 2
#define _GLOG_FATAL 3

// --------------------------------------------------------------------
/* color */
#define LIGHT   "1"
#define DARK    "0"

#define FG      "3"
#define BG      "4"

#define BLACK   "0"
#define RED     "1"
#define GREEN   "2"
#define YELLOW  "3"
#define BLUE    "4"
#define PURPLE  "5"
#define CYAN    "6"
#define WRITE   "7"

#define FG_COLOR(color)    FG color
#define BG_COLOR(color)    BG color

#if COLOR_LOG
#define FMT_DEFAULT                 "\033[0m"
#define FMT_COLOR_FG(light, color)  "\033[" light ";" FG_COLOR(color) "m"
#define FMT_COLOR_BG(fg, color)     "\033[" BG_COLOR(color) ";" FG_COLOR(fg) "m"
#else
#define FMT_DEFAULT
#define FMT_COLOR_FG(light, color)
#define FMT_COLOR_BG(fg, color)
#endif

/* position */
#if FORMAT_LOG
#define XPOSTO(x)   "\033[" #x "D\033[" #x "C"
#else
#define XPOSTO(x)
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define GLOG_PRINT(level, fmt, arg...) \
do { \
    syslog(LOG_USER | LOG_DEBUG, "<%s:%s:%d:%d>:" fmt "\n", __FILENAME__, __func__, __LINE__, level, ## arg); \
} while (0)

#define ZLOGE(fmt, arg...) GLOG_PRINT(_GLOG_ERROR, fmt, ##arg)
#define ZLOGD(fmt, arg...) GLOG_PRINT(_GLOG_INFO, fmt, ##arg)
#define ZLOGV(fmt, arg...) GLOG_PRINT(_GLOG_INFO, fmt, ##arg)
#define ZLOGI(fmt, arg...) GLOG_PRINT(_GLOG_INFO, fmt, ##arg)
#define ZLOGW(fmt, arg...) GLOG_PRINT(_GLOG_WARN, fmt, ##arg)

#endif
