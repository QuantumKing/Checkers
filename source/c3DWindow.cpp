#include "c3DWindow.h"


c3DWindow::c3DWindow(int W, int H, int ScreenFlags, int ScreenBPP)
{
	w = W;
	h = H;

	SDL_Init(SDL_INIT_VIDEO);

	const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();

	desktop_w = videoInfo->current_w;
	desktop_h = videoInfo->current_h;

	flags = ScreenFlags;
	bpp = ScreenBPP;

	screen = NULL;

	resize(w,h);

	fullscreen = false;
}


c3DWindow::~c3DWindow()
{
	SDL_FreeSurface(screen);
}


int c3DWindow::width (void) const
{
	return w;
}


int c3DWindow::height (void) const
{
	return h;
}


void c3DWindow::resize (int W, int H)
{
	if(fullscreen)
		screen = SDL_SetVideoMode(W, H, bpp, flags | SDL_FULLSCREEN);
	else screen = SDL_SetVideoMode(W, H, bpp, flags);

	/* Height / width ration */
	GLfloat ratio;
 
	/* Protect against a divide by zero */
	if ( H == 0 )
		H = 1;

	ratio = ( GLfloat )W / ( GLfloat )H;

	/* Setup our viewport. */
	glViewport( 0, 0, ( GLint )W, ( GLint )H );

	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	/* Set our perspective */
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );

	/* Reset The View */
 	glLoadIdentity( );
}


void c3DWindow::toggle_fullscreen (void)
{
	if(fullscreen)
	{
		fullscreen = false;
		resize(w,h);
	}
	else
	{
		fullscreen = true;
		resize(desktop_w-1,desktop_h-1);
	}
}


