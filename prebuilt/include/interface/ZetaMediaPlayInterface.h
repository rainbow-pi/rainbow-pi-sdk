#ifndef __ZETA_MEDIA_PLAY_INTERFACE__
#define __ZETA_MEDIA_PLAY_INTERFACE__

#include <ZetaMediaPlayer.h>
#include <log.h>
namespace zeta {
	class iZetaMediaPlayer
	{
		public:
			iZetaMediaPlayer();
			~iZetaMediaPlayer();
			int setDataSource(const char* path);
			int setDisplay(int hlay);
			int start();
			int stop();
			int pause();
			int play();
			int prepare();
			class iOnPreparedListener{
			public:
				iOnPreparedListener(){}
				virtual ~iOnPreparedListener(){}
			    virtual void onPrepared(iZetaMediaPlayer *PiZetaMediaPlayer) = 0;
			};			
			void setOnPreparedListener(iOnPreparedListener *pListener);	
			class iOnCompletionListener{
			public:
				iOnCompletionListener(){}
				virtual ~iOnCompletionListener(){}
			    virtual void onCompletion(iZetaMediaPlayer *PiZetaMediaPlayer) = 0;
			};			
			void setOnCompletionListener(iOnCompletionListener *pListener);	

			class iMediaPlayerListener : public MediaPlayerListener{
				public:
					iMediaPlayerListener(iZetaMediaPlayer *piZetaMediaPlayer){miZetaMediaPlayer = piZetaMediaPlayer;}
					void onPrepared(){
						ZLOGD("iMediaPlayerOnPreparedListener::onPrepared:-------------\n");
						if(miZetaMediaPlayer->mOnPreparedListener != NULL){
							miZetaMediaPlayer->mOnPreparedListener->onPrepared(miZetaMediaPlayer);
						}
					}
					void onCompletion(){
						ZLOGD("iMediaPlayerOnPreparedListener::onCompletion:-------------\n");
						if(miZetaMediaPlayer->mOnPreparedListener != NULL){
							miZetaMediaPlayer->mOnCompletionListener->onCompletion(miZetaMediaPlayer);
						}
					}	
				private:
					iZetaMediaPlayer *miZetaMediaPlayer;
			};
		private:	
			ZetaMediaPlayer *pZetaMediaPlayer;
			iOnPreparedListener *mOnPreparedListener;
			iOnCompletionListener *mOnCompletionListener;
			iMediaPlayerListener *miMediaPlayerListener;
	}; // class iZetaMediaPlayer
}; // namespace zeta
#endif //__ZETA_MEDIA_PLAY_INTERFACE__
