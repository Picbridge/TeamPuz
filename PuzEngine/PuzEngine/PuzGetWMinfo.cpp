/******************************************************************************/
/*!
file    PuzGetWMinfo.cpp
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/09/21

   the class in this file gets hwnd and changes it into sdl windows.
*/
/******************************************************************************/
#include "PuzApp.h"

void WMinfo::GetSystemData()
{
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_Window* sdlWnd = SDL_CreateWindowFrom(App::GetWindow());

	SDL_Surface* s = SDL_GetWindowSurface(sdlWnd);
	SDL_FillRect(s, &s->clip_rect, 0xffffffff);
	SDL_UpdateWindowSurface(sdlWnd);

	windowWidth = App::GetWidth();
	windowHeight = App::GetHeight();
	gWindow = sdlWnd;
	if(gWindow == NULL)
	{
		DEBUG_ASSERT(0,"Window cannot be created! \n PuzGetWMinfo::GetSystemData");
	}
}

int WMinfo::GetwindowWidth()const
{
	return windowWidth;
}

int  WMinfo::GetwindowHeight()const
{
	return windowHeight;
}

SDL_Window*  WMinfo::GetgWindow()const
{
	return gWindow;
}

void WMinfo::SetgWindow(SDL_Window* sdlWnd)
{
	gWindow = sdlWnd;
}