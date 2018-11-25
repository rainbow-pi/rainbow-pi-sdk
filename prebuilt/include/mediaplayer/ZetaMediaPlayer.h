#ifndef __ZETA_MEDIA_PLAYER__
#define __ZETA_MEDIA_PLAYER__

#include "MediaPlayerListener.h"
namespace zeta {
	class ZetaMediaPlayer
	{
		public:
			ZetaMediaPlayer();
			~ZetaMediaPlayer();
			int setDataSource(const char* path);
			int setDisplay(int hlay);
			int start();
			int stop();
			int pause();
			int play();
			int prepare();

			void setMediaPlayerListener(MediaPlayerListener *pListener);	
		private:
			void *mContext;	
	}; // class ZetaZetaMediaPlayer
}; // namespace zeta
#endif //__ZETA_MEDIA_PLAY_INTERFACE__
