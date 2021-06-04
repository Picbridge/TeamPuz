/******************************************************************************/
/*!
\file   Physics.cpp
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
This file contains functions that manages collision components.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Physics.h"
#include "Character.h"
#include "Lv1.h"
#include "Tile.h"

extern CharacterData characterData;
extern TileData tileData;

/* Initialize static variable */
bool CollisionComponent::m_IsCollisionSwitchOn = true;

/******************************************************************************/
/*!
Return true if there is collsion between character and collision box.

\return bool
If there is collsion between character and collision box return true
otherwise false.
*/
/******************************************************************************/
bool CollisionComponent::CollisionCheck(void)
{
	bool result = false;

	for(int i = 0; i < MAX_NUM_OF_COLLISION_BOX; ++i)
	{
		if(m_collisionBlockWidth[i] == 0 || m_collisionBlockHeight[i] == 0)
			continue;

		result = IsIntersecting(m_collisionBlockPos[i], m_collisionBlockWidth[i], m_collisionBlockHeight[i],
			                     characterData.GetCharPos(), 2.f, 2.f);

		/* if there is at least one collision then return true */
		if(result == true)
			return result;
	}
	/* otherwise return false */
	return result;
}
/******************************************************************************/
/*!
Return true if there is collsion between mouse and given vector.

\param pos
Vector of position that would be checked.

\return bool
If there is collsion between mouse and given vector return true
otherwise false.
*/
/******************************************************************************/
bool CollisionComponent::MouseCollisionCheck(Vector Pos)
{
	return IsIntersecting(Level1Data::GetInstance()->GetMousePos(), 1.f, 1.f, Pos, 150.f, 150.f);
}
/******************************************************************************/
/*!
Return true if there is collsion between Character and given vector.

\param pos
Vector of position that would be checked.

\return bool
If there is collsion between mouse and given vector return true
otherwise false.
*/
/******************************************************************************/
bool CollisionComponent::CharacterCollisionCheck(Vector Pos)
{
	return IsIntersecting(characterData.GetCharPos(), 1.f, 1.f, Pos, 150.f, 150.f);
}
/******************************************************************************/
/*!
Change width and height of collision box.

\param blockPos
Position of collision block.
*/
/******************************************************************************/
void CollisionComponent::SetNewCollision(int blockPos)
{
	float swap = m_collisionBlockWidth[blockPos];
	m_collisionBlockWidth[blockPos]  = m_collisionBlockHeight[blockPos];
	m_collisionBlockHeight[blockPos] = swap;
}
/******************************************************************************/
/*!
Set new position of collision box.

\param blockPos
Original position of collision block.

\param x
X component of new position.

\param y
Y component of new position.
*/
/******************************************************************************/
void CollisionComponent::SetBlockPos(int blockPos, float x, float y)
{
	m_collisionBlockPos[blockPos].m_x = x;
	m_collisionBlockPos[blockPos].m_y = y;
}
/******************************************************************************/
/*!
Change switch of collision.

\param expression
If expression is true then collision switch is on
otherwise off
*/
/******************************************************************************/
void CollisionComponent::SetSwitch(bool expression)
{
	m_IsCollisionSwitchOn = expression;
}
/******************************************************************************/
/*!
Swap the data of collision box for rotating.
*/
/******************************************************************************/
void CollisionComponent::SetRotatedBlockData(void)
{
	Vector swap = m_collisionBlockPos[LEFT];

	m_collisionBlockPos[LEFT]   = m_collisionBlockPos[BOTTOM];
	m_collisionBlockPos[BOTTOM] = m_collisionBlockPos[RIGHT];
	m_collisionBlockPos[RIGHT]  = m_collisionBlockPos[TOP];
	m_collisionBlockPos[TOP]    = swap;

	float swap2 = m_collisionBlockWidth[LEFT];

	m_collisionBlockWidth[LEFT]   = m_collisionBlockWidth[BOTTOM];   
	m_collisionBlockWidth[BOTTOM] = m_collisionBlockWidth[RIGHT]; 
	m_collisionBlockWidth[RIGHT]  = m_collisionBlockWidth[TOP];  
	m_collisionBlockWidth[TOP]    = swap2;   

	float swap3 = m_collisionBlockHeight[LEFT];

	m_collisionBlockHeight[LEFT]   = m_collisionBlockHeight[BOTTOM];  
	m_collisionBlockHeight[BOTTOM] = m_collisionBlockHeight[RIGHT];
	m_collisionBlockHeight[RIGHT]  = m_collisionBlockHeight[TOP]; 
	m_collisionBlockHeight[TOP]    = swap3;  
}
/******************************************************************************/
/*!
Initialize all the components in the entity.

\param sectionName
A string that is section name (Which tile is)

\param value
Type of collision
*/
/******************************************************************************/
void CollisionComponent::Init(const std::string sectionName, const std::string value)
{
	enum SECTION_NAME { FLOOR1_FIRST, FLOOR1_SECOND, FLOOR1_THIRD, FLOOR1_FOURTH, FLOOR1_FIFTH, FLOOR1_SIXTH, FLOOR1_SEVENTH, FLOOR1_EIGHTH, FLOOR1_NINETH,
						FLOOR2_FIRST, FLOOR2_SECOND, FLOOR2_THIRD, FLOOR2_FOURTH, FLOOR2_FIFTH, FLOOR2_SIXTH, FLOOR2_SEVENTH, FLOOR2_EIGHTH, FLOOR2_NINETH	};

	int myTile;

	if(sectionName == "FIR_First Tile")
		myTile = FLOOR1_FIRST;
	else if(sectionName == "FIR_Second Tile")
		myTile = FLOOR1_SECOND;
	else if(sectionName == "FIR_Third Tile")
		myTile = FLOOR1_THIRD;
	else if(sectionName == "FIR_Fourth Tile")
		myTile = FLOOR1_FOURTH;
	else if(sectionName == "FIR_Fifth Tile")
		myTile = FLOOR1_FIFTH;
	else if(sectionName == "FIR_Sixth Tile")
		myTile = FLOOR1_SIXTH;
	else if(sectionName == "FIR_Seventh Tile")
		myTile = FLOOR1_SEVENTH;
	else if(sectionName == "FIR_Eighth Tile")
		myTile = FLOOR1_EIGHTH;
	else if(sectionName == "FIR_Nineth Tile")
		myTile = FLOOR1_NINETH;

	else if(sectionName == "SEC_First Tile")
		myTile = FLOOR2_FIRST;
	else if(sectionName == "SEC_Second Tile")
		myTile = FLOOR2_SECOND;
	else if(sectionName == "SEC_Third Tile")
		myTile = FLOOR2_THIRD;
	else if(sectionName == "SEC_Fourth Tile")
		myTile = FLOOR2_FOURTH;
	else if(sectionName == "SEC_Fifth Tile")
		myTile = FLOOR2_FIFTH;
	else if(sectionName == "SEC_Sixth Tile")
		myTile = FLOOR2_SIXTH;
	else if(sectionName == "SEC_Seventh Tile")
		myTile = FLOOR2_SEVENTH;
	else if(sectionName == "SEC_Eighth Tile")
		myTile = FLOOR2_EIGHTH;
	else if(sectionName == "SEC_Nineth Tile")
		myTile = FLOOR2_NINETH;

	/* No Collision Block */
	if(value == "1")
	{
		/* Set collision box with 0 size */
		for(int i = 0; i < MAX_NUM_OF_COLLISION_BOX; ++i)
		{
			m_collisionBlockWidth[i]  = 0.f;
			m_collisionBlockHeight[i] = 0.f;
		}
		return;
	}
	/* One Collision Block on top edge of tile */
	else if(value == "2")
	{
		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[RIGHT]   = 0.f;
		m_collisionBlockHeight[RIGHT]  = 0.f;
		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
		m_collisionBlockWidth[LEFT]    = 0.f;
		m_collisionBlockHeight[LEFT]   = 0.f;
	}
	/* One Collision Block on right edge of tile */
	else if(value == "3")
	{
		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[TOP]     = 0.f;
		m_collisionBlockHeight[TOP]    = 0.f;
		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
		m_collisionBlockWidth[LEFT]    = 0.f;
		m_collisionBlockHeight[LEFT]   = 0.f;
	}
	/* One Collision Block on bottom edge of tile */
	else if(value == "4")
	{
		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[TOP]    = 0.f;
		m_collisionBlockHeight[TOP]   = 0.f;
		m_collisionBlockWidth[RIGHT]  = 0.f;
		m_collisionBlockHeight[RIGHT] = 0.f;
		m_collisionBlockWidth[LEFT]   = 0.f;
		m_collisionBlockHeight[LEFT]  = 0.f;
	}
	/* One Collision Block on left edge of tile */
	else if(value == "5")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[TOP]     = 0.f;
		m_collisionBlockHeight[TOP]    = 0.f;
		m_collisionBlockWidth[RIGHT]   = 0.f;
		m_collisionBlockHeight[RIGHT]  = 0.f;
		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
	}
	/* two Collision Blocks on left and right edge of tile */
	else if(value == "6")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;
		
		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[TOP]     = 0.f;
		m_collisionBlockHeight[TOP]    = 0.f;
		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
	}
	/* two Collision Blocks on left and bottom edge of tile */
	else if(value == "7")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;
		
		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[TOP]    = 0.f;
		m_collisionBlockHeight[TOP]   = 0.f;
		m_collisionBlockWidth[RIGHT]  = 0.f;
		m_collisionBlockHeight[RIGHT] = 0.f;
	}
	/* two Collision Blocks on left and top edge of tile */
	else if(value == "8")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[RIGHT]   = 0.f;
		m_collisionBlockHeight[RIGHT]  = 0.f;
		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
	}
	/* two Collision Blocks on top and right edge of tile */
	else if(value == "9")
	{
		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
		m_collisionBlockWidth[LEFT]    = 0.f;
		m_collisionBlockHeight[LEFT]   = 0.f;
	}
	/* two Collision Blocks on top and bottom edge of tile */
	else if(value == "10")
	{
		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[RIGHT]  = 0.f;
		m_collisionBlockHeight[RIGHT] = 0.f;
		m_collisionBlockWidth[LEFT]   = 0.f;
		m_collisionBlockHeight[LEFT]  = 0.f;
	}
	/* two Collision Blocks on bottom and right edge of tile */
	else if(value == "11")
	{
		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;

		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[TOP]   = 0.f;
		m_collisionBlockHeight[TOP]  = 0.f;
		m_collisionBlockWidth[LEFT]  = 0.f;
		m_collisionBlockHeight[LEFT] = 0.f;
	}
	/* three Collision Blocks on left, right and bottom edge of tile */
	else if(value == "12")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;
		
		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[TOP]  = 0.f;
		m_collisionBlockHeight[TOP] = 0.f;
	}
	/* three Collision Blocks on right, top and bottom edge of tile */
	else if(value == "13")
	{
		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[LEFT]  = 0.f;
		m_collisionBlockHeight[LEFT] = 0.f;	
	}
	/* three Collision Blocks on left, top and bottom edge of tile */
	else if(value == "14")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockPos[BOTTOM].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[BOTTOM].m_y = tileData.GetTilePosY(myTile) + 80.f;

		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[BOTTOM]  = 230.f;
		m_collisionBlockHeight[BOTTOM] = 60.f;

		m_collisionBlockWidth[RIGHT]  = 0.f;
		m_collisionBlockHeight[RIGHT] = 0.f;
	}
	/* three Collision Blocks on left, top and right edge of tile */
	else if(value == "15")
	{
		m_collisionBlockPos[LEFT].m_x = tileData.GetTilePosX(myTile) - 95.f;
		m_collisionBlockPos[LEFT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockPos[TOP].m_x = tileData.GetTilePosX(myTile);
		m_collisionBlockPos[TOP].m_y = tileData.GetTilePosY(myTile) - 110.f;

		m_collisionBlockPos[RIGHT].m_x = tileData.GetTilePosX(myTile) + 95.f;
		m_collisionBlockPos[RIGHT].m_y = tileData.GetTilePosY(myTile) - 10.f;

		m_collisionBlockWidth[LEFT]  = 60.f;
		m_collisionBlockHeight[LEFT] = 230.f;

		m_collisionBlockWidth[TOP]  = 230.f;
		m_collisionBlockHeight[TOP] = 60.f;

		m_collisionBlockWidth[RIGHT]  = 60.f;
		m_collisionBlockHeight[RIGHT] = 230.f;

		m_collisionBlockWidth[BOTTOM]  = 0.f;
		m_collisionBlockHeight[BOTTOM] = 0.f;
	}
}