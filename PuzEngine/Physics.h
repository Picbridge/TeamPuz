/******************************************************************************/
/*!
\file   Physics.h
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
#ifndef PHYSICS_H
#define PHYSICS_H

#include "Math.h"
#include "Component.h"
#include "Tile.h"

#define MAX_NUM_OF_COLLISION_BOX 4

class CollisionComponent : public Component
{
public:
	enum COLLISION_BLOCK_POS { TOP, RIGHT, BOTTOM, LEFT };

	bool CollisionCheck(void);
	bool MouseCollisionCheck(Vector Pos);
	bool CharacterCollisionCheck(Vector Pos);
	void SetNewCollision(int blockPos);

	Vector GetBlockPos(int blockPos) { return m_collisionBlockPos[blockPos]; }
	void SetBlockPos(int blockPos, float x, float y);

	float GetBlockWidth(int blockPos) { return m_collisionBlockWidth[blockPos]; }
	float GetBlockHeight(int blockPos) { return m_collisionBlockHeight[blockPos]; }
	
	void SetRotatedBlockData(void);

	static bool GetSwitch(void) { return m_IsCollisionSwitchOn; }
	static void SetSwitch(bool expression);

	virtual void Init(const std::string sectionName, const std::string value);

private:
	float m_collisionBlockWidth[MAX_NUM_OF_COLLISION_BOX];
	float m_collisionBlockHeight[MAX_NUM_OF_COLLISION_BOX];
	
	Vector m_collisionBlockPos[MAX_NUM_OF_COLLISION_BOX];

	static bool m_IsCollisionSwitchOn;
};

#endif /*PHYSICS_H*/