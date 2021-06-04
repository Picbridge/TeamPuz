/******************************************************************************/
/*!
file    PuzInput.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game Input system Manager
\date   2014/10/21

   Manage the Input system.
*/
/******************************************************************************/
#include "PuzInput.h"
#include "Debug.h"

/******************************************************************************/
/*!
\brief
Initialize function

\return
None.
*/
/******************************************************************************/
void inputData::Init(void)
{
	m_mouseX = 0;
	m_mouseY = 0;

	for(int i = 0; i < LAST; ++i)
	{
		m_triggered[i] = false;
		m_pressed[i]   = false;
	}
}

/******************************************************************************/
/*!
\brief
Get WParam and translate to use.

\param wPar
Get the key pressed.

\return
the key which is translated.
*/
/******************************************************************************/
inputData::KEYINDEX inputData::TranslateKey(WPARAM wPar)
{
	switch(wPar)
	{
	case VK_ESCAPE:
		return PUZ_ESCAPE;
	case VK_UP:
		return PUZ_ARROW_UP;
	case VK_DOWN:
		return PUZ_ARROW_DOWN;
	case VK_RIGHT:
		return PUZ_ARROW_RIGHT;
	case VK_LEFT:
		return PUZ_ARROW_LEFT;
	case 'A':
		return PUZ_A;
	case 'B':
		return PUZ_B;
	case 'C':
		return PUZ_C;
	case 'D':
		return PUZ_D;
	case 'E':
		return PUZ_E;
	case 'F':
		return PUZ_F;
	case 'G':
		return PUZ_G;
	case 'H':
		return PUZ_H;
	case 'I':
		return PUZ_I;
	case 'J':
		return PUZ_J;
	case 'K':
		return PUZ_K;
	case 'L':
		return PUZ_L;
	case 'M':
		return PUZ_M;
	case 'N':
		return PUZ_N;
	case 'O':
		return PUZ_O;
	case 'P':
		return PUZ_P;
	case 'Q':
		return PUZ_Q;
	case 'R':
		return PUZ_R;
	case 'S':
		return PUZ_S;
	case 'T':
		return PUZ_T;
	case 'U':
		return PUZ_U;
	case 'V':
		return PUZ_V;
	case 'W':
		return PUZ_W;
	case 'X':
		return PUZ_X;
	case 'Y':
		return PUZ_Y;
	case 'Z':
		return PUZ_Z;
	
	default:
		return INVALID;
	}
}

/******************************************************************************/
/*!
\brief
Set to key is pressed

\param key
The key which user is pressing.

\param express
Check if key is pressed or not

\return
None.
*/
/******************************************************************************/
void inputData::SetPressed(inputData::KEYINDEX key, bool express)
{
	if((key < INVALID) || (key >= LAST))
		return;

	if(express)
	{
		m_pressed[key]   = true;
		m_triggered[key] = true;
	}
	else
		m_Unpress.push_back(key);
}

/******************************************************************************/
/*!
\brief
Returns if the key has been pressed or not.

\param key
the key which is pressed by user

\return
TRUE if the key is pressed, FALSE otherwise.
*/
/******************************************************************************/
bool inputData::IsPressed(inputData::KEYINDEX key)
{
	DEBUG_ASSERT((key > INVALID) && (key < LAST), "key is out of range");

	return m_pressed[key];
}

/******************************************************************************/
/*!
\brief
Returns if the key has been triggered or not.

\param key
the key which is triggered by user

\return
TRUE if the key is triggered, FALSE otherwise.
*/
/******************************************************************************/
bool inputData::IsTriggered(inputData::KEYINDEX key)
{
	DEBUG_ASSERT((key > INVALID) && (key < LAST), "key is out of range");

	return m_triggered[key];
}

/******************************************************************************/
/*!
\brief
Input reset to use again.

\return
None.
*/
/******************************************************************************/
void inputData::InputReset(void)
{
	for(unsigned int i = 0; i < m_Unpress.size(); ++i)
		m_pressed[m_Unpress[i]] = false;
	
	m_Unpress.clear();

	for(int i = 0; i < LAST; ++i)
		m_triggered[i] = false;
}

/******************************************************************************/
/*!
\brief
Return mouse x-position

\return
Return mouse position.
*/
/******************************************************************************/
float inputData::GetMouseX(void)
{
	return m_mouseX;
}

/******************************************************************************/
/*!
\brief
Return mouse y-position

\return
Return mouse position.
*/
/******************************************************************************/
float inputData::GetMouseY(void)
{
	return m_mouseY;
}

/******************************************************************************/
/*!
\brief
Catch the mouse movement and give that x-position

\return
None.
*/
/******************************************************************************/
void inputData::SetMouseX(float x)
{
	m_mouseX = x;
}
/******************************************************************************/
/*!
\brief
Catch the mouse movement and give that y-position

\return
None.
*/
/******************************************************************************/
void inputData::SetMouseY(float y)
{
	m_mouseY = y;
}