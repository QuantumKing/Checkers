#include "c3DCheckers.h"

int main(int argc, char**argv)
{
	int sf = SDL_OPENGL | SDL_RESIZABLE;

	c3DCheckers *game = NULL;	

	game = new c3DCheckers(720,720,sf,32);

	game->Execute();

	return 0;
}
