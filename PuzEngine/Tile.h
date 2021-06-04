/******************************************************************************/
/*!
\file   Tile.h
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
This file contains actual data of Tile entity
and functions that manage entity data
for level state.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef TILE_H
#define TILE_H

#include "Math.h"

#define NUM_OF_TILE 18

class TileData
{
public:
	void Init(void);
	void Update(void);

	/*************/
	void TileUpdate(int i);

	bool GetShrinkedInfo(int xth) { return m_IsTileShrinked[xth]; }

	float GetTilePosX(int xth) { return m_tilePos[xth].m_x; }
	float GetTilePosY(int xth) { return m_tilePos[xth].m_y; }
	Vector GetTilePos(int xth) { return m_tilePos[xth]; }
	void SetPos(int xth, float x, float y);

	float GetTileScaleX(int xth) { return m_tileScale[xth].m_x; }
	float GetTileScaleY(int xth) { return m_tileScale[xth].m_y; }

	float GetTileAngle(int xth) { return m_tileAngle[xth]; }

	bool GetTileIsRotating(int xth) { return m_IsTileRotating[xth]; }
	bool GetTileIsShrinked(int xth) { return m_IsTileShrinked[xth]; }
			
private:
	Vector m_tilePos[NUM_OF_TILE];
	Vector m_tilePosSave[NUM_OF_TILE];
	Vector m_tileScale[NUM_OF_TILE];
	Vector m_tileScaleSave[NUM_OF_TILE];

	float m_tileAngle[NUM_OF_TILE];
	float m_AngleSave[NUM_OF_TILE];

	bool m_IsTileShrinked[NUM_OF_TILE];
	bool m_IsTileRotating[NUM_OF_TILE];

	/**/
	bool m_TileCharacterON[NUM_OF_TILE];
};

#endif /* TILE_H */