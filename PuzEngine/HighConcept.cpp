/******************************************************************************/
/*!
file    HighConcept.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    High concept state
\date   2014/11/06

   This file to show our high concept.
*/
/******************************************************************************/
#include "Debug.h"
#include "PuzApp.h"
#include "Math.h"

static GraphicComponent HCTexture(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent BackButton(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent Dog(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

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
bool MouseCollisionInHC(Vector ButtonPosi)
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
void ButtonUpdateInHC()
{
	Mouse.m_x = App::GetAppInstance()->Input.GetMouseX();
	Mouse.m_y = App::GetAppInstance()->Input.GetMouseY();

	if(MouseCollisionInHC(ButtonPos) == true
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
void HighConcept::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is High Concept State");

	HCTexture.LoadFromFile("concept.png");
	BackButton.LoadFromFile("ArrowBack.png");
	Dog.LoadFromFile("charDog.png");

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
void HighConcept::Update(float dt)
{
	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	ButtonUpdateInHC();

	App::GetAppInstance()->GFX.StartDraw();
	HCTexture.Render(450,350);
	Dog.Render(1050,400);
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
void HighConcept::Shutdown()
{
	HCTexture.Free();
	BackButton.Free();
	Dog.Free();
	DEBUG_DESTROY_CONSOLE();
}