/******************************************************************************/
/*!
\file   Tile.cpp
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
#include "Tile.h"
#include "Lv1.h"
#include "Physics.h"
#include "TileFactory.h"
#include "Stair.h"
#include "Lever.h"
#include "PuzApp.h"

TileData tileData;
extern TileFactory factory;
extern Stair StairData;
extern LeverData leverData;

void TileData::Init(void)
{
	m_tilePos[0].m_x = 415;		m_tilePos[0].m_y = 125;
	m_tilePos[1].m_x = 640;		m_tilePos[1].m_y = 125;
	m_tilePos[2].m_x = 865;		m_tilePos[2].m_y = 125;
	m_tilePos[3].m_x = 415;		m_tilePos[3].m_y = 350; 
	m_tilePos[4].m_x = 640;		m_tilePos[4].m_y = 350;
	m_tilePos[5].m_x = 865;		m_tilePos[5].m_y = 350;
	m_tilePos[6].m_x = 415;		m_tilePos[6].m_y = 575;
	m_tilePos[7].m_x = 640;		m_tilePos[7].m_y = 575; 
	m_tilePos[8].m_x = 865;		m_tilePos[8].m_y = 575; 

	m_tilePos[9].m_x  = GetTilePosX(0);		m_tilePos[9].m_y  = GetTilePosY(0) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight();
	m_tilePos[10].m_x = GetTilePosX(1);		m_tilePos[10].m_y = GetTilePosY(1) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight();
	m_tilePos[11].m_x = GetTilePosX(2);		m_tilePos[11].m_y = GetTilePosY(2) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight();
	m_tilePos[12].m_x = GetTilePosX(3);		m_tilePos[12].m_y = GetTilePosY(3) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight(); 
	m_tilePos[13].m_x = GetTilePosX(4);		m_tilePos[13].m_y = GetTilePosY(4) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight();
	m_tilePos[14].m_x = GetTilePosX(5);		m_tilePos[14].m_y = GetTilePosY(5) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight();
	m_tilePos[15].m_x = GetTilePosX(6);		m_tilePos[15].m_y = GetTilePosY(6) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight();
	m_tilePos[16].m_x = GetTilePosX(7);		m_tilePos[16].m_y = GetTilePosY(7) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight(); 
	m_tilePos[17].m_x = GetTilePosX(8);		m_tilePos[17].m_y = GetTilePosY(8) -App::GetAppInstance()->sdlWndInfo.GetwindowHeight(); 

	for(int i = 0; i < NUM_OF_TILE; ++i)
	{
		m_tileAngle[i] = 0.f;
		m_tileScale[i].m_x = 0.75f;
		m_tileScale[i].m_y = 0.75f;
		m_IsTileShrinked[i] = false;
		m_IsTileRotating[i] = false;
		m_AngleSave[i] = m_tileAngle[i];
	}
}

void TileData::TileUpdate(int i)
{
	CollisionComponent* collisionData[NUM_OF_TILE];
	TileEntity* temp[NUM_OF_TILE];
	
	temp[0] = factory.GetEntityList()["FIR_First Tile"];
	temp[1] = factory.GetEntityList()["FIR_Second Tile"];
	temp[2] = factory.GetEntityList()["FIR_Third Tile"];
	temp[3] = factory.GetEntityList()["FIR_Fourth Tile"];
	temp[4] = factory.GetEntityList()["FIR_Fifth Tile"];
	temp[5] = factory.GetEntityList()["FIR_Sixth Tile"];
	temp[6] = factory.GetEntityList()["FIR_Seventh Tile"];
	temp[7] = factory.GetEntityList()["FIR_Eighth Tile"];
	temp[8] = factory.GetEntityList()["FIR_Nineth Tile"];

	temp[9]  = factory.GetEntityList()["SEC_First Tile"];
	temp[10] = factory.GetEntityList()["SEC_Second Tile"];
	temp[11] = factory.GetEntityList()["SEC_Third Tile"];
	temp[12] = factory.GetEntityList()["SEC_Fourth Tile"];
	temp[13] = factory.GetEntityList()["SEC_Fifth Tile"];
	temp[14] = factory.GetEntityList()["SEC_Sixth Tile"];
	temp[15] = factory.GetEntityList()["SEC_Seventh Tile"];
	temp[16] = factory.GetEntityList()["SEC_Eighth Tile"];
	temp[17] = factory.GetEntityList()["SEC_Nineth Tile"];

	for(int j = 0; j < NUM_OF_TILE; ++j)
	{
		if(temp[j] != NULL)
			collisionData[j] = dynamic_cast<CollisionComponent*>(temp[j]->getComponent("Collision Type"));
	}
	if(leverData.IsMouseOnLever() == true)
	{
		/*Tile Shrinking*/
		if((collisionData[i]->CharacterCollisionCheck(m_tilePos[i]) == true)
			&& (m_IsTileShrinked[i] == false))
		{
			m_tileScale[i].m_x *= 0.9f;
			m_tileScale[i].m_y *= 0.9f;

			m_IsTileShrinked[i] = true;
		}
	}
	else if(leverData.IsMouseOnLever() == false
		&& (m_IsTileShrinked[i] == true)
		&& (m_IsTileRotating[i] == false))
	{
		m_tileScale[i].m_x /= 0.9f;
		m_tileScale[i].m_y /= 0.9f;

		m_IsTileShrinked[i] = false;
	}
	/*Tile Rotating*/
	if((m_IsTileShrinked[i] == true)
		&& (leverData.IsleverClicked() == false)
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_MOUSE_LEFT))
	{
		leverData.SetLeverClickedBool(true);
	}

	if(leverData.IsleverClicked() == true && m_IsTileShrinked[i] == true)
	{
		m_tileAngle[i] += 5.f;
		
		if(i <= 8)
			m_tileAngle[i + 9] += 5.f;
		else if(i >= 9)
			m_tileAngle[i - 9] += 5.f;

		m_IsTileRotating[i] = true;

		if(m_tileAngle[i] >= m_AngleSave[i] + 90.f)
		{
			m_tileAngle[i] = m_AngleSave[i] + 90.f;

			collisionData[i]->SetBlockPos(CollisionComponent::TOP,    m_tilePos[i].m_x +95.f, m_tilePos[i].m_y -10.f);
			collisionData[i]->SetBlockPos(CollisionComponent::RIGHT,  m_tilePos[i].m_x,       m_tilePos[i].m_y +80.f);
			collisionData[i]->SetBlockPos(CollisionComponent::BOTTOM, m_tilePos[i].m_x -95.f, m_tilePos[i].m_y -10.f);
			collisionData[i]->SetBlockPos(CollisionComponent::LEFT,   m_tilePos[i].m_x,       m_tilePos[i].m_y -110.f);

			collisionData[i]->SetNewCollision(CollisionComponent::TOP);
			collisionData[i]->SetNewCollision(CollisionComponent::RIGHT);
			collisionData[i]->SetNewCollision(CollisionComponent::BOTTOM);
			collisionData[i]->SetNewCollision(CollisionComponent::LEFT);

			collisionData[i]->SetRotatedBlockData();

			m_AngleSave[i] = m_tileAngle[i];

			if(i <= 8)
			{
				m_tileAngle[i + 9] = m_AngleSave[i + 9] + 90.f;

				collisionData[i + 9]->SetBlockPos(CollisionComponent::TOP,    m_tilePos[i + 9].m_x +95.f, m_tilePos[i + 9].m_y -10.f);
				collisionData[i + 9]->SetBlockPos(CollisionComponent::RIGHT,  m_tilePos[i + 9].m_x,       m_tilePos[i + 9].m_y +80.f);
				collisionData[i + 9]->SetBlockPos(CollisionComponent::BOTTOM, m_tilePos[i + 9].m_x -95.f, m_tilePos[i + 9].m_y -10.f);
				collisionData[i + 9]->SetBlockPos(CollisionComponent::LEFT,   m_tilePos[i + 9].m_x,       m_tilePos[i + 9].m_y -110.f);

				collisionData[i + 9]->SetNewCollision(CollisionComponent::TOP);
				collisionData[i + 9]->SetNewCollision(CollisionComponent::RIGHT);
				collisionData[i + 9]->SetNewCollision(CollisionComponent::BOTTOM);
				collisionData[i + 9]->SetNewCollision(CollisionComponent::LEFT);

				collisionData[i + 9]->SetRotatedBlockData();

				m_tileAngle[i + 9] = m_tileAngle[i + 9];

				m_AngleSave[i + 9] = m_tileAngle[i + 9];
			}
			else if(i >= 9)
			{
				m_tileAngle[i - 9] = m_AngleSave[i - 9] + 90.f;

				collisionData[i - 9]->SetBlockPos(CollisionComponent::TOP,    m_tilePos[i - 9].m_x +95.f, m_tilePos[i - 9].m_y -10.f);
				collisionData[i - 9]->SetBlockPos(CollisionComponent::RIGHT,  m_tilePos[i - 9].m_x,       m_tilePos[i - 9].m_y +80.f);
				collisionData[i - 9]->SetBlockPos(CollisionComponent::BOTTOM, m_tilePos[i - 9].m_x -95.f, m_tilePos[i - 9].m_y -10.f);
				collisionData[i - 9]->SetBlockPos(CollisionComponent::LEFT,   m_tilePos[i - 9].m_x,       m_tilePos[i - 9].m_y -110.f);

				collisionData[i - 9]->SetNewCollision(CollisionComponent::TOP);
				collisionData[i - 9]->SetNewCollision(CollisionComponent::RIGHT);
				collisionData[i - 9]->SetNewCollision(CollisionComponent::BOTTOM);
				collisionData[i - 9]->SetNewCollision(CollisionComponent::LEFT);

				collisionData[i - 9]->SetRotatedBlockData();

				m_tileAngle[i - 9] = m_tileAngle[i - 9];

				m_AngleSave[i - 9] = m_tileAngle[i - 9];
			}

			if(i == 8 || i == 17)
			{
				StairData.SetRotatedStairData();
				StairData.SetNewCollision();
			}

			leverData.SetLeverClickedBool(false);
			m_IsTileRotating[i] = false;
		}

		if(m_tileAngle[i] == 360)
		{
			m_tileAngle[i] -= 360.f;
			m_AngleSave[i] -= 360.f;
		}
	}

	if(m_IsTileRotating[i] == true)
		CollisionComponent::SetSwitch(false);
	else
		CollisionComponent::SetSwitch(true);
}
void TileData::Update(void)
{
	Level1Data::GetInstance()->SetMousePos(App::GetAppInstance()->Input.GetMouseX(), App::GetAppInstance()->Input.GetMouseY());

	TileUpdate(0);
	TileUpdate(1);
	TileUpdate(2);
	TileUpdate(3);
	TileUpdate(4);
	TileUpdate(5);
	TileUpdate(6);
	TileUpdate(7);
	TileUpdate(8);

	TileUpdate(9);
	TileUpdate(10);
	TileUpdate(11);
	TileUpdate(12);
	TileUpdate(13);
	TileUpdate(14);
	TileUpdate(15);
	TileUpdate(16);
	TileUpdate(17);
}

void TileData::SetPos(int xth, float x, float y)
{
	m_tilePos[xth].m_x = x;
	m_tilePos[xth].m_y = y;
}