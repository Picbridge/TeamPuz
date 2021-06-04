/******************************************************************************/
/*!
file    PuzGraphics.cpp
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/09/21

This File contains all of the Functions for the Graphics Engine
*/
/******************************************************************************/
#include "PuzApp.h"

/****************************************************************************/
/*!
\brief
call this function before drawing
*/
/****************************************************************************/
void Graphics::StartDraw()
{
	//Clear screen
    SDL_RenderClear( gRenderer );
}

/****************************************************************************/
/*!
\brief
this function initializes the graphics


\return
assert if fail to call SDL init
*/
/****************************************************************************/
bool Graphics::InitGraphics()
{
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		DEBUG_ASSERT(0,"Fail to initialize SDL \n PuzGraphics.cpp::InitGraphics()");
	}
	else
	{
		//Get window surface
		gScreenSurface = SDL_GetWindowSurface(App::GetAppInstance()->sdlWndInfo.GetgWindow());
	}
	
	InitRenderer();
	return true;
}

/****************************************************************************/
/*!
\brief
this function takes a source of image and cuts it into 'aniFrame'pieces.
then it makes texture to be drawn on the screen continuously

\param clip
clips for dividing texture into pieces

\param aniFrame
number of pieces to devide

\param imgWidth
width of image

\param imgHeight
height of image
*/
/****************************************************************************/
void Graphics::Animation(PuzAnimate* clip,int aniFrame,int imgWidth, int imgHeight)
{
	//location where drawing pixel starts
	int jumpClip = 0;
	//pixel drawing with one jump
	int oneJump =  imgWidth/aniFrame;

	for(int i = 0;i<aniFrame;++i)
	{
	    clip[i].x = jumpClip;
		clip[i].y = 0;
		clip[i].w = oneJump;
		clip[i].h = imgHeight;
		jumpClip += oneJump;
	}
}
/****************************************************************************/
/*!
\brief
this function returns the renderer created at init

\return
created renderer
*/
/****************************************************************************/
SDL_Renderer* Graphics::GetgRenderer()const
{
	return gRenderer;
}
/****************************************************************************/
/*!
\brief
this function creates and initializes the renderer.

*/
/****************************************************************************/
void Graphics::InitRenderer()
{
	gRenderer = SDL_CreateRenderer(App::GetAppInstance()->sdlWndInfo.GetgWindow(),-1,
		                           SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL)
	{
		DEBUG_ASSERT(0,"Fail to creat renderer! \n PuzGraphics::Renderer()");
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer,0xE8,0xE8,0xE8,0xFF);
			//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if( !(IMG_Init(imgFlags) & imgFlags) )
		{
			DEBUG_ASSERT(0,"SDL_image could not initialize! \n PuzGraphics::InitGraphics()");
		}
	}
}

/****************************************************************************/
/*!
\brief
this function takes a source surface 
and stamps a copy of it onto the destination surface.

\param xPos
x position of viewport

\param yPos
y position of viewport

\param width
width of viewport

\param height
height of viewport

*/
/****************************************************************************/
void Graphics::PuzGraphicsSetViewport(int xPos,int yPos,int width,int height)
{
	SDL_Rect newViewport;
                newViewport.x = xPos;
                newViewport.y = yPos;
                newViewport.w = width;
                newViewport.h = height;
                SDL_RenderSetViewport( gRenderer, &newViewport );
}
/****************************************************************************/
/*!
\brief
this function is called after drawing all textures
*/
/****************************************************************************/
void Graphics::EndDraw()
{
	//Update screen
	SDL_RenderPresent(App::GetAppInstance()->GFX.GetgRenderer());
}

/****************************************************************************/
/*!
\brief
this function is called in shutdown
this function deallocates surface and quit SDL subsystems
*/
/****************************************************************************/
void Graphics::ShutdownGraphics()
{
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}