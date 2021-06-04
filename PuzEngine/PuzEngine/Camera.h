/******************************************************************************/
/*!
file    Camera.h
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/10/14

   Camera Functions
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "SDL_image.h"
#include "Math.h"

class Camera
{
public:
	Camera():camX(0),camY(0){};
	//getter,setter for camera
	int& GetCamX();
	int& GetCamY();

	void SetCamX(int) ;
	void SetCamY(int) ;
	void SetCharToCenter(int CharX,int CharY,int LEVEL_WIDTH,int LEVEL_HEIGHT);
private:

	int camX;
	int camY;
};
#endif /* CAMERA_H */