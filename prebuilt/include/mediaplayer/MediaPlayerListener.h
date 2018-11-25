#ifndef __MEDIA_PLAYER_LISTENER_H__
#define __MEDIA_PLAYER_LISTENER_H__

class MediaPlayerListener{
public:
	MediaPlayerListener(){}
	virtual ~MediaPlayerListener(){}
    virtual void onPrepared() = 0;	
    virtual void onCompletion() = 0;

};
#endif