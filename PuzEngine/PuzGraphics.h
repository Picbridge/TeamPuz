/******************************************************************************/
/*!
file    PuzGraphics.h
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/09/21

   Graphics Functions
*/
/******************************************************************************/
#ifndef PUZ_GRAPHICS_H
#define PUZ_GRAPHICS_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"
#include <string>//read in string

typedef SDL_Rect PuzAnimate;
typedef SDL_Rect* clip;

class Graphics
{
public:
	//PuzGraphics.cpp
	void StartDraw();
	bool InitGraphics();
	void Animation(PuzAnimate* clip,int aniFrame,int imgWidth, int imgHeight);
	SDL_Renderer* GetgRenderer()const;
	void InitRenderer();
	void PuzGraphicsSetViewport(int xPos,int yPos,int width,int height);
	void EndDraw();
	void ShutdownGraphics();

private:
	SDL_Surface *gScreenSurface;
	SDL_Renderer *gRenderer;
};

#endif /* PUZ_GRAPHICS_H */