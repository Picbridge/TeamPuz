/******************************************************************************/
/*!
file    PuzLoadTexture.cpp
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/09/21

*/
/******************************************************************************/
#include "PuzApp.h"

using namespace std;

/****************************************************************************/
/*!
\brief
constructor of GraphicComponent

*/
/****************************************************************************/
GraphicComponent::GraphicComponent()
{
	camX = NULL;
	camY = NULL;
	mTexture=NULL;
	mWidth  = 0;
	mHeight = 0;
}
/****************************************************************************/
/*!
\brief
constructor of GraphicComponent

*/
/****************************************************************************/
GraphicComponent::GraphicComponent(int *passed_CamX,int *passed_CamY)
{
	camX = passed_CamX;
	camY = passed_CamY;
	mTexture=NULL;
	mWidth  = 0;
	mHeight = 0;
}
/****************************************************************************/
/*!
\brief
this function deallocates the texture

*/
/****************************************************************************/
GraphicComponent::~GraphicComponent()
{
	Free();
}

/****************************************************************************/
/*!
\brief
this function loads the texture from file

\param fileName
name of the texture file

*/
/****************************************************************************/
bool GraphicComponent::LoadFromFile(const char* fileName)
{
	//Get rid of preexisting texture
	Free();
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( fileName );
	if( loadedSurface == NULL )
	{
		DEBUG_PRINT("\n%s is unable to load", fileName);
		DEBUG_ASSERT(false,"Unable to load image \n PuzLoadTexture::loadFromFile");
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( App::GetAppInstance()->GFX.GetgRenderer(), loadedSurface );

		//Get image dimensions
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Set standard alpha blending
    SetBlendMode( SDL_BLENDMODE_BLEND );
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

/****************************************************************************/
/*!
\brief
this function destroys the used texture

*/
/****************************************************************************/
void GraphicComponent::Free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

}

/****************************************************************************/
/*!
\brief
this function is renderer 
that keeps image size and can move texture on screen
if animeClip exists, it plays animation
if rotAngle exists, it starts rotating

\param xPos
x position of screen that image will be shown

\param yPos
y position of screen that image will be shown

\param animeClip
small clip part of animation sprite 

\param xScale
scales x by its amount

\param yScale 
scales y by its amount

\param rotAngle
angle value to rotate

\param center
a point to rotate a texture

\param flip
flip by input fliptype
*/
/****************************************************************************/
void GraphicComponent::Render( int xPos, int yPos,
						 SDL_Rect* animeClip, double xScale ,
						 double yScale , double rotAngle,  
				         SDL_Point* center, SDL_RendererFlip flip)
{
	
	if((xPos!=NOT_DESIGNATED||yPos!=NOT_DESIGNATED)&&camX!=NULL)//cam dependent render
	{  
		Cam.x = xPos-((mWidth/2)*xScale)+(*camX);
	    Cam.y = yPos-((mHeight/2)*yScale)+(*camY);
		Cam.w = mWidth*xScale;
	    Cam.h = mHeight*yScale;
		//Set rendering space and render to screen
		if(animeClip)
		{
			mWidth = animeClip->w;
			mHeight = animeClip->h;
			Cam.x = xPos-((mWidth/2)*xScale)+(*camX);
			Cam.y = yPos-((mHeight/2)*yScale)+(*camY);
			Cam.w = animeClip->w*xScale;
			Cam.h = animeClip->h*yScale;
		}
		SDL_RenderCopyEx(App::GetAppInstance()->GFX.GetgRenderer(), mTexture, animeClip, &Cam,rotAngle,center,flip);
	}
	else if((xPos!=NOT_DESIGNATED||yPos!=NOT_DESIGNATED)&&camX==NULL&&camY==NULL)//render for HUD
	{
		 //Set rendering space and render to screen
		SDL_Rect renderQuad = { xPos-((mWidth/2)*xScale), yPos-((mHeight/2)*yScale), mWidth*xScale, mHeight*yScale };

		if(animeClip)
		{
			mWidth = animeClip->w;
			mHeight = animeClip->h;
			renderQuad.x = xPos-((mWidth/2)*xScale);
			renderQuad.y = yPos-((mHeight/2)*yScale);
			renderQuad.w = animeClip->w;
			renderQuad.h = animeClip->h;
		}

		SDL_RenderCopy( App::GetAppInstance()->GFX.GetgRenderer(), mTexture, animeClip, &renderQuad );
	}
	else//full screen render
	{
		//Render to screen 
		SDL_RenderCopy( App::GetAppInstance()->GFX.GetgRenderer(), mTexture, NULL, NULL );
	}
}

/****************************************************************************/
/*!
\brief
this function changes the color of texture 

\param res
red RGB rate

\param green
green RGB rate

\param blue
blue RGB rate
*/
/****************************************************************************/
void GraphicComponent::SetColor(Uint8 red,Uint8 green,Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture,red,green,blue);
}

/****************************************************************************/
/*!
\brief
this function sets the blendermode of texture 

\param blending
blendmode for blending
*/
/****************************************************************************/
void GraphicComponent::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture,blending);
}

/****************************************************************************/
/*!
\brief
this function sets the alpha of texture 

\param alpha
alpha element of texture

*/
/****************************************************************************/
void GraphicComponent::setAlpha(Uint8 alpha)
{
	//Modulation texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

/****************************************************************************/
/*!
\brief
this function fetches the width of the image
*/
/****************************************************************************/
int GraphicComponent::GetWidth()
{
	return mWidth;
}

/****************************************************************************/
/*!
\brief
this function fetches the height of the image
*/
/****************************************************************************/
int GraphicComponent::GetHeight()
{
	return mHeight;
}

/****************************************************************************/
/*!
\brief
this function fetches the height of the image
*/
/****************************************************************************/
void GraphicComponent::Init(const std::string sectionName, const std::string value)
{
	/* No Collision Block */
	if(value == "1")
	{
		LoadFromFile("DesertBlock//01.png");
	}
	/* One Collision Block on top edge of tile */
	else if(value == "2")
	{
		LoadFromFile("DesertBlock//02.png");
	}
	/* One Collision Block on right edge of tile */
	else if(value == "3")
	{
		LoadFromFile("DesertBlock//03.png");
	}
	/* One Collision Block on bottom edge of tile */
	else if(value == "4")
	{
		LoadFromFile("DesertBlock//04.png");
	}
	/* One Collision Block on left edge of tile */
	else if(value == "5")
	{
		LoadFromFile("DesertBlock//05.png");
	}
	/* two Collision Blocks on left and right edge of tile */
	else if(value == "6")
	{
		LoadFromFile("DesertBlock//06.png");
	}
	/* two Collision Blocks on left and bottom edge of tile */
	else if(value == "7")
	{
		LoadFromFile("DesertBlock//07.png");
	}
	/* two Collision Blocks on left and top edge of tile */
	else if(value == "8")
	{
		LoadFromFile("DesertBlock//08.png");
	}
	/* two Collision Blocks on top and right edge of tile */
	else if(value == "9")
	{
		LoadFromFile("DesertBlock//09.png");
	}
	/* two Collision Blocks on top and bottom edge of tile */
	else if(value == "10")
	{
		LoadFromFile("DesertBlock//10.png");
	}
	/* two Collision Blocks on bottom and right edge of tile */
	else if(value == "11")
	{
		LoadFromFile("DesertBlock//11.png");
	}
	/* three Collision Blocks on left, right and bottom edge of tile */
	else if(value == "12")
	{
		LoadFromFile("DesertBlock//12.png");
	}
	/* three Collision Blocks on right, top and bottom edge of tile */
	else if(value == "13")
	{
		LoadFromFile("DesertBlock//13.png");
	}
	/* three Collision Blocks on left, top and bottom edge of tile */
	else if(value == "14")
	{
		LoadFromFile("DesertBlock//14.png");
	}
	/* three Collision Blocks on left, top and right edge of tile */
	else if(value == "15")
	{
		LoadFromFile("DesertBlock//15.png");
	}
}
