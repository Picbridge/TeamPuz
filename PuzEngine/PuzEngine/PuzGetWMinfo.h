/******************************************************************************/
/*!
file    PuzGetWMinfo.h
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/09/21

   the class in this header file gets hwnd and changes it into sdl windows.
*/
/******************************************************************************/
#ifndef PUZ_GETWMINFO_H
#define PUZ_GETWMINFO_H

#include "SDL_syswm.h"

class WMinfo
{
public:
	void GetSystemData();
	int GetwindowWidth()const;
	int GetwindowHeight()const;
	SDL_Window* GetgWindow()const;

	void SetgWindow(SDL_Window* sdlWnd);

private:
	int windowWidth;
	int windowHeight;
	SDL_Window *gWindow;

};

#endif /* PUZ_GETWMINFO_H */
