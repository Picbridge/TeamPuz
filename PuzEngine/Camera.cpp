/******************************************************************************/
/*!
file    Camera.cpp
\author Jihoon Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    2D Game Graphic Engine
\date   2014/09/21

This File contains all of the Functions for the camera
*/
/******************************************************************************/
#include "stdafx.h"
#include "PuzApp.h"
/****************************************************************************/
/*!
\brief
this function returns location of camera X-axis
\return
camera X-axis
*/
/****************************************************************************/
int& Camera::GetCamX(void)
{
	return camX;
}

/****************************************************************************/
/*!
\brief
this function returns location of camera Y-axis

\return
camera Y-axis
*/
/****************************************************************************/
int& Camera::GetCamY()
{
	return camY;
}

/****************************************************************************/
/*!
\brief
Set camera location to follow the character

\param CharX
character location x

\param CharX
character location y

\param LEVEL_WIDTH
width of the screen

\param LEVEL_HEIGHT
height of the screen
*/
/****************************************************************************/
void Camera::SetCharToCenter(int CharX,int CharY,int LEVEL_WIDTH,int LEVEL_HEIGHT)
{
	//Center the camera over the dot
	camX = -(( CharX ) - App::GetAppInstance()->GetWidth() / 2);
    camY = -(( CharY ) - App::GetAppInstance()->GetHeight() / 2);

    //Keep the camera in bounds
    if( camX < 0 )
    { 	
        camX = 0;
    }
    if( camY < 0 )
    {	
        camY = 0;
    }
    if( camX > LEVEL_WIDTH )
    {	
        camX = LEVEL_WIDTH;
    }
    if( camY > LEVEL_HEIGHT)
    {	
        camY = LEVEL_HEIGHT;
    }
}

/****************************************************************************/
/*!
\brief
Set new camera location

\param camMovX
new location to set
*/
/****************************************************************************/
void Camera::SetCamX(int camMovX) 
{
	camX = camMovX;
}


/****************************************************************************/
/*!
\brief
Set new camera location

\param camMovY
new location to set
*/
/****************************************************************************/
void Camera::SetCamY(int camMovY) 
{
	camY = camMovY;
}


