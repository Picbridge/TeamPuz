/******************************************************************************/
/*!
file    PuzInput.h
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game Input system Manager
\date   2014/10/21

  Input function prototypes.
*/
/******************************************************************************/
#ifndef PUZINPUT_H
#define PUZINPUT_H

#include<Windows.h>
#include <vector>

class inputData
{
public:
	/* key index that you can use */
	enum KEYINDEX
	{
		INVALID,
		PUZ_ESCAPE,
		PUZ_ARROW_UP,
		PUZ_ARROW_DOWN,
		PUZ_ARROW_RIGHT,
		PUZ_ARROW_LEFT,
		PUZ_MOUSE_LEFT,
		PUZ_A,
		PUZ_B,
		PUZ_C,
		PUZ_D,
		PUZ_E,
		PUZ_F,
		PUZ_G,
		PUZ_H,
		PUZ_I,
		PUZ_J,
		PUZ_K,
		PUZ_L,
		PUZ_M,
		PUZ_N,
		PUZ_O,
		PUZ_P,
		PUZ_Q,
		PUZ_R,
		PUZ_S,
		PUZ_T,
		PUZ_U,
		PUZ_V,
		PUZ_W,
		PUZ_X,
		PUZ_Y,
		PUZ_Z,
		LAST
	};

	void Init(void);
	KEYINDEX TranslateKey(WPARAM wPar);
	void SetPressed(KEYINDEX key, bool express);
	bool IsPressed(KEYINDEX key);
	bool IsTriggered(KEYINDEX key);
	void InputReset(void);
	float GetMouseX(void);
	float GetMouseY(void);
	void SetMouseX(float x);
	void SetMouseY(float y);

private:
	bool m_triggered[LAST];
	bool m_pressed[LAST];

	float m_mouseX;
	float m_mouseY;

	std::vector<inputData::KEYINDEX> m_Unpress;
};

#endif /* PUZINPUT_H */