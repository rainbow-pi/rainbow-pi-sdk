#ifndef _WATER_MARK_INTERFACE_H
#define _WATER_MARK_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
	unsigned char *y;
	unsigned char *c;
	int posx;
	int posy;
	int width;
	int height;
	char *display;
    int main_channel;
	float scale;
} WaterMarkInData;

extern int doWaterMarkMultiple(WaterMarkInData *data, void *ctrl, const char *time_str);
extern void *initialwaterMark(int wm_height);
extern int releaseWaterMark(void *ctrl);
extern int waterMarkSetMultiple(void *ctrl, const char *waterMark);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WATER_MARK_INTERFACE_H */
