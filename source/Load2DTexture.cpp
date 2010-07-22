#include "3Ddefs.h"

Texture Load2DTexture(const char* filename)
{
	SDL_Surface *surface;
	GLenum texture_format;
	GLint  nOfColors;

	Texture texture;

	surface = SDL_LoadBMP(filename);

	if( !surface ) 
	{
		printf("SDL could not load %s: %s\n", filename, SDL_GetError());		
		throw FailedSurface();
	}
		
	// Check that the image's width is a power of 2
	if( (surface->w & (surface->w - 1)) != 0 ) 
	{
		printf("warning: %s width is not a power of 2\n",filename);
	}
			
	// Also check if the height is a power of 2
	if ( (surface->h & (surface->h - 1)) != 0 ) 
	{
		printf("warning: %s height is not a power of 2\n",filename);
	}
 		
      	// get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;

        if (nOfColors == 4)     // contains an alpha channel
        {
        	if (surface->format->Rmask == 0x000000ff)
        		texture_format = GL_RGBA;
        	else
        		texture_format = GL_BGRA;
	} 
	else if (nOfColors == 3)     // no alpha channel
	{
        	if (surface->format->Rmask == 0x000000ff)
        		texture_format = GL_RGB;
        	else
        		texture_format = GL_BGR;
	} 
	else 
	{
		printf("warning: %s is not truecolor..  this will probably break\n",filename);
	}
        		
	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture.t );
 		
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture.t );
 	
	texture.w = surface->w;
	texture.h = surface->h;
	
	// Set the texture's stretching properties
        //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	//gluBuild2DMipmaps(GL_TEXTURE_2D, nOfColors, surface->w, surface->h, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	// Edit the texture object's image data using the information SDL_Surface gives us

	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
	texture_format, GL_UNSIGNED_BYTE, surface->pixels );

	SDL_FreeSurface( surface );

	return texture;
};
