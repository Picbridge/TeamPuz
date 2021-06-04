#include "Debug.h"
#include "PuzApp.h"
#include "Math.h"

static GraphicComponent WWDTexture(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent BackButton(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent Dog2(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

static Vector Mouse;
static Vector ButtonPos;

/******************************************************************************/
/*!
\brief
Check mouse is on button.

\return
return true if mouse intersect with button.
*/
/******************************************************************************/
bool MouseCollisionInWWD(Vector ButtonPosi)
{
	return IsIntersecting(Mouse, 1.f, 1.f, ButtonPosi, 60.f, 60.f);
}

/******************************************************************************/
/*!
\brief
Updating button's states

\return
None.
*/
/******************************************************************************/
void ButtonUpdateInWWD()
{
	Mouse.m_x = App::GetAppInstance()->Input.GetMouseX();
	Mouse.m_y = App::GetAppInstance()->Input.GetMouseY();

	if(MouseCollisionInWWD(ButtonPos) == true
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_MOUSE_LEFT))
	{
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.MENU);
	}
}

/******************************************************************************/
/*!
\brief
Initialize function.

\return
None.
*/
/******************************************************************************/
void WhatWeDid::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is What We Did State");

	WWDTexture.LoadFromFile("whatdid.png");
	BackButton.LoadFromFile("ArrowBack.png");
	Dog2.LoadFromFile("charDog2.png");

	ButtonPos.m_x = 25;
	ButtonPos.m_y = 25;
}

/******************************************************************************/
/*!
\brief
Update all that we need to update.

\return
None.
*/
/******************************************************************************/
void WhatWeDid::Update(float dt)
{
	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	ButtonUpdateInWWD();

	App::GetAppInstance()->GFX.StartDraw();
	WWDTexture.Render(450,350);
	Dog2.Render(1050,400);
	BackButton.Render(ButtonPos.m_x, ButtonPos.m_y, 0, 1.f, 1.f, 0);
	App::GetAppInstance()->GFX.EndDraw();
}

/******************************************************************************/
/*!
\brief
Shutdown function.

\return
None.
*/
/******************************************************************************/
void WhatWeDid::Shutdown()
{
	WWDTexture.Free();
	Dog2.Free();
	BackButton.Free();
	DEBUG_DESTROY_CONSOLE();
}