#include "Stair.h"
#include "Tile.h"
#include "Character.h"

extern TileData tileData;
extern CharacterData characterData;

void Stair::Init(void)
{
	m_stairCollisionHeight = 40.f;
	m_stairCollisionWidth = 90.f;
	SetStairPos(0, tileData.GetTilePosX(8)  +80.f, tileData.GetTilePosY(8)  +50.f);
	SetStairPos(1, tileData.GetTilePosX(17) +80.f, tileData.GetTilePosY(17) +50.f);
}

void Stair::SetStairPos(int i, float x, float y)
{
	m_stairPos[i].m_x = x;
	m_stairPos[i].m_y = y;
}

bool Stair::StairCharacterCollisionCheck(int i)
{
	return IsIntersecting(characterData.GetCharPos(), 2.f, 2.f, GetStairPos(i), m_stairCollisionWidth, m_stairCollisionHeight);
}

void Stair::SetNewCollision(void)
{
	float swap = m_stairCollisionWidth;
	m_stairCollisionWidth  = m_stairCollisionHeight;
	m_stairCollisionHeight = swap;
}

void Stair::SetRotatedStairData(void)
{
	if(tileData.GetTileAngle(8) == 90 || tileData.GetTileAngle(17) == 90)
	{
		SetStairPos(0, tileData.GetTilePosX(8)  -90.f, tileData.GetTilePosY(8)  + 60.f);
		SetStairPos(1, tileData.GetTilePosX(17) -90.f, tileData.GetTilePosY(17) + 60.f);
	}
	else if(tileData.GetTileAngle(8) == 180 || tileData.GetTileAngle(17) == 180)
	{
		SetStairPos(0, tileData.GetTilePosX(8)  -70.f, tileData.GetTilePosY(8)  -100.f);
		SetStairPos(1, tileData.GetTilePosX(17) -70.f, tileData.GetTilePosY(17) -100.f);
	}
	else if(tileData.GetTileAngle(8) == 270 || tileData.GetTileAngle(17) == 270)
	{
		SetStairPos(0, tileData.GetTilePosX(8)  +90.f, tileData.GetTilePosY(8)  -90.f);
		SetStairPos(1, tileData.GetTilePosX(17) +90.f, tileData.GetTilePosY(17) -90.f);
	}
	else if(tileData.GetTileAngle(8) == 360 || tileData.GetTileAngle(17) == 360)
	{
		SetStairPos(0, tileData.GetTilePosX(8)  +80.f, tileData.GetTilePosY(8)  +50.f);
		SetStairPos(1, tileData.GetTilePosX(17) +80.f, tileData.GetTilePosY(17) +50.f);
	}		
}