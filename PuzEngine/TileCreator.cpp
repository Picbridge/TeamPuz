/******************************************************************************/
/*!
\file   TileCreator.cpp
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
This file contains functions that creates components.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "TileCreator.h"
#include "PuzApp.h"

/******************************************************************************/
/*!
Returns collision component that is created by factory.

\return CollisionComponent*
Pointer to CollisionComponent class that would be created by factory.
*/
/******************************************************************************/
CollisionComponent* CollisionCreator::Create(void)
{
	return new CollisionComponent();
}

GraphicComponent* GraphicCreator::Create(void)
{
	return new GraphicComponent(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
}