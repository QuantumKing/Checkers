#include "3Ddefs.h"

class c3DWindow
{

		int w;
		int h;

		SDL_Surface *screen;

		bool fullscreen;

		int desktop_w, desktop_h;

		int flags, bpp;

	public:

		c3DWindow(int W, int H, int ScreenFlags, int ScreenBPP);

		~c3DWindow();

		int width (void) const;

		int height (void) const;

		void resize (int W, int H);

		void toggle_fullscreen (void);	
};
