/******************************************************************************/
/*!
\file   Character.h
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
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Math.h"

class CharacterData
{
public:
	void SetCharPos(float x, float y);
	float GetCharPosX(void) { return m_charPos.m_x; }
	float GetCharPosY(void) { return m_charPos.m_y; }

	Vector GetCharPos(void) { return m_charPos; }

	bool GetWalkingInfo(void) { return m_IsWalking; }

	int GetWhichStairCharacterIsOn(void);

	void Init(void);
	void Update(void);
	
private:
	Vector m_charPos;

	bool m_IsWalking;
};

void CharacterUpdate();

#endif /* CHARACTER_H */