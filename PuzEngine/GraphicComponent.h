/******************************************************************************/
/*!
file    GraphicComponent.h
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/10/05

Graphics class handling textures
*/
/******************************************************************************/
#ifndef GRAPHIC_COMP_H
#define GRAPHIC_COMP_H

#define NOT_DESIGNATED -1

#include "SDL.h"
#include "SDL_image.h"
#include "Component.h"

class GraphicComponent : public Component
{
public:
	//constructor for HUD
	GraphicComponent();
	//Initializes variables
	GraphicComponent(int *passed_CamX,int *passed_CamY);

	//Deallocates memory
	~GraphicComponent();

	//Loads image at specified path
	bool LoadFromFile( const char* fileName);

	//Deallocates texture
	void Free();

	//Renders texture at given point
	void Render( int xPos = NOT_DESIGNATED, int yPos = NOT_DESIGNATED,
				 SDL_Rect* animeClip = NULL, double xScale = 1.f,
				 double yScale = 1.f, double rotAngle = 0.f,  
				 SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	//void Render();
	void SetColor(Uint8 red,Uint8 green,Uint8 blue);
	//set blending
	void SetBlendMode(SDL_BlendMode);
	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

	virtual void Init(const std::string sectionName, const std::string value);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//camera
	int *camX;
	int *camY;
	SDL_Rect Cam;
	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif /* GRAPHIC_COMP_H */