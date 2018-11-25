#ifndef __ZETA_DISPLAY_INTERFACE__
#define __ZETA_DISPLAY_INTERFACE__

#include <log.h>
#include <hwdisplay.h>

typedef struct view_info ViewInfo;
struct ZETA_RECT
{
	int x;
	int y;
	int w;
	int h;
};
namespace zeta {
	class ZetaDisplay
	{
		public:
			ZetaDisplay(int disp_id, ViewInfo *sur);
			~ZetaDisplay();
			int getHandle();
			void setBottom();
			void hdmisetBottom();
			void hdmisetTop();
			void setRect(ZETA_RECT &rect);
			void open(int hlay=-1);
			void close(int hlay=-1);
			void openAdasScreen();
			void closeAdasScreen();
			void exchange(int hlay, int flag); //flag:1-otherOnTop
			void otherScreen(int screen, int hlay);
			void clean(void);
		private:
			HwDisplay *mHwDisplay;
			int       mHlay;
			bool      mLayerOpened;
	}; // class ZetaDisplay
}; // namespace zeta
#endif //__ZETA_DISPLAY_INTERFACE__
