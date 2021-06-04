/******************************************************************************/
/*!
\file   Character.cpp
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
The Character contains function
that update physics of character for level state.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Character.h"
#include "Physics.h"
#include "Tile.h"
#include "TileFactory.h"
#include "Stair.h"
#include "PuzApp.h"

extern TileFactory factory;
extern TileData tileData;
extern Stair StairData;
extern bool CamYGoingUp;
extern enum fade{FADEIN,FADEOUT,NONE};
extern fade isFading;
CharacterData characterData;

void CharacterData::SetCharPos(float x, float y)
{
	m_charPos.m_x = x;
	m_charPos.m_y = y;
}

void CharacterData::Init(void)
{
	m_charPos.m_x = tileData.GetTilePosX(8);
	m_charPos.m_y = tileData.GetTilePosY(8);

	m_IsWalking = false;
}

void CharacterData::Update(void)
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

	for(int i = 0; i < NUM_OF_TILE; ++i)
	{
		if(temp[i] != NULL)
			collisionData[i] = dynamic_cast<CollisionComponent*>(temp[i]->getComponent("Collision Type"));
	}

	/*****************************************************************************************************/
	if(StairData.StairCharacterCollisionCheck(0))
	{
		SetCharPos(tileData.GetTilePosX(17), tileData.GetTilePosY(17));
		CamYGoingUp = true;
		isFading = FADEIN;
	}
	else if(StairData.StairCharacterCollisionCheck(1))
	{
		SetCharPos(tileData.GetTilePosX(8), tileData.GetTilePosY(8));
		CamYGoingUp = false;
		isFading = FADEIN;
	}
	/*****************************************************************************************************/

	bool collisionResult = !(collisionData[0]->CollisionCheck()  || collisionData[9] ->CollisionCheck()
						  || collisionData[1]->CollisionCheck()	 || collisionData[10]->CollisionCheck()
						  || collisionData[2]->CollisionCheck()	 || collisionData[11]->CollisionCheck()
						  || collisionData[3]->CollisionCheck()	 || collisionData[12]->CollisionCheck()
						  || collisionData[4]->CollisionCheck()	 || collisionData[13]->CollisionCheck()
						  || collisionData[5]->CollisionCheck()	 || collisionData[14]->CollisionCheck()
						  || collisionData[6]->CollisionCheck()	 || collisionData[15]->CollisionCheck()
						  || collisionData[7]->CollisionCheck()	 || collisionData[16]->CollisionCheck()
						  || collisionData[8]->CollisionCheck()	 || collisionData[17]->CollisionCheck()
						    );

	bool shrinkResult = !(tileData.GetShrinkedInfo(0)  || tileData.GetShrinkedInfo(9)
					   || tileData.GetShrinkedInfo(1)  || tileData.GetShrinkedInfo(10)
					   || tileData.GetShrinkedInfo(2)  || tileData.GetShrinkedInfo(11)
					   || tileData.GetShrinkedInfo(3)  || tileData.GetShrinkedInfo(12)
					   || tileData.GetShrinkedInfo(4)  || tileData.GetShrinkedInfo(13)
					   || tileData.GetShrinkedInfo(5)  || tileData.GetShrinkedInfo(14)
					   || tileData.GetShrinkedInfo(6)  || tileData.GetShrinkedInfo(15)
					   || tileData.GetShrinkedInfo(7)  || tileData.GetShrinkedInfo(16)
					   || tileData.GetShrinkedInfo(8)  || tileData.GetShrinkedInfo(17)
					     );

	if(CollisionComponent::GetSwitch() == false)
		collisionResult = !collisionResult;

	if(collisionResult && shrinkResult)
	{
		/*Input : Move up*/
		if (App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_UP))
		{
			m_IsWalking = true;

			/*Update character image depend on direction*/
			if(GetWhichStairCharacterIsOn() == 1)
			{
				//if(tileData.GetTilePosY(8) + 50.f >= characterData.GetCharPosY())
					characterData.SetCharPos(characterData.GetCharPosX(), characterData.GetCharPosY() - 10);
				//else
				//	characterData.SetCharPos(characterData.GetCharPosX(), tileData.GetTilePosY(8) + 49.f);
			}
			else if(GetWhichStairCharacterIsOn() == 2)
			{
				//if(tileData.GetTilePosY(17) + 50.f >= characterData.GetCharPosY())
					characterData.SetCharPos(characterData.GetCharPosX(), characterData.GetCharPosY() - 10);
				//else
				//	characterData.SetCharPos(characterData.GetCharPosX(), tileData.GetTilePosY(17) + 49.f);
			}
		}
		/*Input : Move down*/
		else if(App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_DOWN))
		{
			m_IsWalking = true;

			/*Update character image depend on direction*/
			if(GetWhichStairCharacterIsOn() == 1)
			{
				//if(tileData.GetTilePosY(0) - 50.f <= characterData.GetCharPosY())
					characterData.SetCharPos(characterData.GetCharPosX(), characterData.GetCharPosY() + 10);
				//else
				//	characterData.SetCharPos(characterData.GetCharPosX(), tileData.GetTilePosY(0) - 49.f);
			}
			else if(GetWhichStairCharacterIsOn() == 2)
			{
				//if(tileData.GetTilePosY(9) - 50.f <= characterData.GetCharPosY())
					characterData.SetCharPos(characterData.GetCharPosX(), characterData.GetCharPosY() + 10);
				//else
				//	characterData.SetCharPos(characterData.GetCharPosX(), tileData.GetTilePosY(9) - 49.f);
			}
		}

		/*Input : Move left*/
		else if(App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_LEFT))
		{
			m_IsWalking = true;

			/*Update character image depend on direction*/
			if(GetWhichStairCharacterIsOn() == 1)
			{
				//if(tileData.GetTilePosX(0) - 50.f <= characterData.GetCharPosX())
					characterData.SetCharPos(characterData.GetCharPosX() - 10, characterData.GetCharPosY());
				//else
				//	characterData.SetCharPos(tileData.GetTilePosX(0) - 49.f, characterData.GetCharPosY());
			}
			else if(GetWhichStairCharacterIsOn() == 2)
			{
				//if(tileData.GetTilePosX(9) - 50.f <= characterData.GetCharPosX())
					characterData.SetCharPos(characterData.GetCharPosX() - 10, characterData.GetCharPosY());
				//else
				//	characterData.SetCharPos(tileData.GetTilePosX(9) - 49.f, characterData.GetCharPosY());
			}
		}

		/*Input : Move right*/
		else if(App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_RIGHT))
		{
			m_IsWalking = true;

			/*Update character image depend on direction*/
			if(GetWhichStairCharacterIsOn() == 1)
			{
				//if(tileData.GetTilePosX(8) + 50.f >= characterData.GetCharPosX())
					characterData.SetCharPos(characterData.GetCharPosX() + 10, characterData.GetCharPosY());
				//else
				//	characterData.SetCharPos(tileData.GetTilePosX(8) + 49.f, characterData.GetCharPosY());
			}
			else if(GetWhichStairCharacterIsOn() == 2)
			{
				//if(tileData.GetTilePosX(17) + 50.f >= characterData.GetCharPosX())
					characterData.SetCharPos(characterData.GetCharPosX() + 10, characterData.GetCharPosY());
				//else
				//	characterData.SetCharPos(tileData.GetTilePosX(17) + 49.f, characterData.GetCharPosY());
			}
		}

		else
		{
			m_IsWalking = false;
		}
	}
	else if(!collisionResult)
	{
		float divider[MAX_NUM_OF_COLLISION_BOX * NUM_OF_TILE];
		Vector normalizedVector[MAX_NUM_OF_COLLISION_BOX * NUM_OF_TILE];

		for(int i = 0; i < NUM_OF_TILE; ++i)
		{
			for(int j = 0; j < MAX_NUM_OF_COLLISION_BOX; ++j)
			{
				divider[i*MAX_NUM_OF_COLLISION_BOX + j] 
				= sqrt((m_charPos.m_x - collisionData[i]->GetBlockPos(j).m_x)*(m_charPos.m_x - collisionData[i]->GetBlockPos(j).m_x)
				     + (m_charPos.m_y - collisionData[i]->GetBlockPos(j).m_y)*(m_charPos.m_y - collisionData[i]->GetBlockPos(j).m_y));

				if(divider[i*MAX_NUM_OF_COLLISION_BOX + j] == 0)
					continue;

				normalizedVector[i*MAX_NUM_OF_COLLISION_BOX + j].m_x = (m_charPos.m_x - collisionData[i]->GetBlockPos(j).m_x) / divider[i*MAX_NUM_OF_COLLISION_BOX + j];
				normalizedVector[i*MAX_NUM_OF_COLLISION_BOX + j].m_y = (m_charPos.m_y - collisionData[i]->GetBlockPos(j).m_y) / divider[i*MAX_NUM_OF_COLLISION_BOX + j];

				Vector lineStart;
				Vector lineEnd;

				if((j == CollisionComponent::RIGHT) || (j == CollisionComponent::LEFT))
				{
					lineStart.m_x = collisionData[i]->GetBlockPos(j).m_x;
					lineStart.m_y = collisionData[i]->GetBlockPos(j).m_y - collisionData[i]->GetBlockHeight(j)/2;

					lineEnd.m_x = collisionData[i]->GetBlockPos(j).m_x;
					lineEnd.m_y = collisionData[i]->GetBlockPos(j).m_y + collisionData[i]->GetBlockHeight(j)/2;

					if(GetDistancePointLine(m_charPos, lineStart, lineEnd) <= 54.f)
						m_charPos.m_x += normalizedVector[i*4 + j].m_x *10.f;
				}
				else
				{
					lineStart.m_x = collisionData[i]->GetBlockPos(j).m_x - collisionData[i]->GetBlockWidth(j)/2;
					lineStart.m_y = collisionData[i]->GetBlockPos(j).m_y;

					lineEnd.m_x = collisionData[i]->GetBlockPos(j).m_x + collisionData[i]->GetBlockWidth(j)/2;
					lineEnd.m_y = collisionData[i]->GetBlockPos(j).m_y;

					if(GetDistancePointLine(m_charPos, lineStart, lineEnd) <= 54.f)
						m_charPos.m_y += normalizedVector[i*4 + j].m_y *10.f;
				}
			}
		}
	}
}

int CharacterData::GetWhichStairCharacterIsOn(void)
{
	if(GetCharPosY() > tileData.GetTilePosY(0) - 50.f
	 &&GetCharPosY() < tileData.GetTilePosY(8) + 50.f)
	   return 1;
	else
	   return 2;
}