#ifndef __ZETA_RECORDER_H__
#define __ZETA_RECORDER_H__

namespace zeta
{

typedef struct H264HeaderData {
    unsigned char*  pBuffer;
    unsigned int    nLength;
}H264HeaderData;

typedef struct H264OutputBuffer {
    int               nID;
    long long         nPts;
    unsigned int   nFlag;
    unsigned int   nSize0;
    unsigned int   nSize1;
    unsigned char* pData0;
    unsigned char* pData1;

    H264HeaderData frame_info;
}H264OutputBuffer;


class ZetaRecorder
{
public:
	ZetaRecorder();
	~ZetaRecorder();	
	
	void setSourceResolution(int w, int h);
	void setTargetResolution(int w, int h);
	void seFrameRate(int rate);
	void setBitRate(int rate);
	void setRecordId(int id);
	void setFileName(const char *file_name);
	int start();
	int stop();
	int stopP2P();
	int destroy();
	int loop();
	int startP2P(int srcW, int srcH, int dstW, int dstH, int framerate, int bitrate);
	void pushVideoData(void* arg);
	
	void onZetaH264Data(H264OutputBuffer *outputBuffer);
	
	class OnHandleMessage	
	{   
		public:		
			OnHandleMessage()		
			{		
			}		
			virtual ~OnHandleMessage()		
			{
			}		
			virtual void handleMessage(H264OutputBuffer *outputBuffer) = 0;	
	};	
	void setOnRecordDataListener(OnHandleMessage *pl);
private:
	void* mContext;
	OnHandleMessage* mHandler;
};

};
#endif
