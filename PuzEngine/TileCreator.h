/******************************************************************************/
/*!
\file   TileCreator.h
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
#ifndef TILE_CREATOR_H
#define TILE_CREATOR_H

#include "Component.h"
#include "Physics.h"
#include "GraphicComponent.h"

class TileCreator
{
public:
	virtual Component* Create(void) = 0;
};

class CollisionCreator : public TileCreator
{
public:
	virtual CollisionComponent* Create(void);
};

class GraphicCreator : public TileCreator
{
public:
	virtual GraphicComponent* Create(void);
};

#endif /* TILE_CREATOR_H */
