/******************************************************************************/
/*!
file    Lever.cpp
\author Jihoon Bae
\par    email:aky2000kr@gmail.com
\par    GAM200
\par    Lever system
\date   

   Lever is a button that player can rotate the tile. This file treat lever.
*/
/******************************************************************************/
#include "Lever.h"
#include "Physics.h"

LeverData leverData;

/******************************************************************************/
/*!
\brief
default constructor for LeverData

\return
None.
*/
/******************************************************************************/
LeverData::LeverData()
{
	leverPos.m_x = 0;
	leverPos.m_y = 0;
	m_isLeverClicked = false;
}
/******************************************************************************/
/*!
\brief
destructor for LeverData

\return
None.
*/
/******************************************************************************/
LeverData::~LeverData()
{
}
/******************************************************************************/
/*!
\brief
Initialize function

\return
None.
*/
/******************************************************************************/
void LeverData::Init(void)
{
	leverPos.m_x = 100;
	leverPos.m_y = 200;
}

/******************************************************************************/
/*!
\brief
check if mouse is on lever

\return
true or false.
*/
/******************************************************************************/
bool LeverData::IsMouseOnLever()
{
	CollisionComponent collisionData;
	if(collisionData.MouseCollisionCheck(leverPos))
	{
		return true;
	}
	else 
		return false;
}
/******************************************************************************/
/*!
\brief
set clicked as true if lever is clicked

\return
None.
*/
/******************************************************************************/
void LeverData::SetLeverClickedBool(bool booltype)
{
	m_isLeverClicked = booltype;
}