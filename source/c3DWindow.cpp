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

	fullscreen = false;

	resize(w,h);

#ifdef __linux__
	init_gl();
#endif

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


void c3DWindow::init_gl (void)
{
	glLists::BuildLists();

	/* Sets up OpenGL double buffering */
 	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background black */
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 1.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);											// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Type Of Blending To Use
	glEnable(GL_TEXTURE_2D);

	LightAmbient[0] = 0.5f;	LightAmbient[1] = 0.5f;	LightAmbient[2] = 0.5f;	LightAmbient[3] = 1.0f;
	LightDiffuse[0] = 1.0f;	LightDiffuse[1] = 1.0f;	LightDiffuse[2] = 1.0f;	LightDiffuse[3] = 1.0f;
	LightPosition[0] = 0.0f; LightPosition[1] = 0.0f; LightPosition[2] = 2.0f; LightPosition[3] = 1.0f;

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);			// Position The Light
	glEnable(GL_LIGHT1);										// Enable Light One
	glEnable(GL_LIGHTING);										// Enable Lighting
}

void c3DWindow::resize (int W, int H)
{
	if(fullscreen)
	{
		screen = SDL_SetVideoMode(W, H, bpp, flags | SDL_FULLSCREEN);
	}
	else
	{
		screen = SDL_SetVideoMode(W, H, bpp, flags);
	}

#ifndef __linux__
	init_gl();
#endif

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


