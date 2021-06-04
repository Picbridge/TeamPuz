/******************************************************************************/
/*!
file    Menu.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Menu state
\date   2014/11/06

   This file will call when start the game.
*/
/******************************************************************************/
#include "Debug.h"
#include "PuzApp.h"
#include "Math.h"

static GraphicComponent TeamName(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent TeamRoster(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent Button1(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

static GraphicComponent Button2(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent Button3(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent Button4(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

static Vector Mouse;
static Vector TeamNamePos;
static Vector TeamRosterPos;
static Vector Button1Pos;
static Vector Button1Scale;

static bool Button1Grow;

static bool Button2Grow;
static bool Button3Grow;
static bool Button4Grow;
static Vector Button2Pos;
static Vector Button3Pos;
static Vector Button4Pos;
static Vector Button2Scale;
static Vector Button3Scale;
static Vector Button4Scale;

/******************************************************************************/
/*!
\brief
Check mouse is on button.

\return
return true if mouse intersect with button.
*/
/******************************************************************************/
bool MouseCollision(Vector ButtonPos)
{
	return IsIntersecting(Mouse, 1.f, 1.f, ButtonPos, 60.f, 60.f);
}

/******************************************************************************/
/*!
\brief
Updating button's states

\return
None.
*/
/******************************************************************************/
void ButtonUpdate()
{
	Mouse.m_x = App::GetAppInstance()->Input.GetMouseX();
	Mouse.m_y = App::GetAppInstance()->Input.GetMouseY();

	if(MouseCollision(Button1Pos) == true 
		&& Button1Grow == false)
	{
		Button1Scale.m_x *= 1.5f;
		Button1Scale.m_y *= 1.5f;
		Button1Pos.m_x -= 8.f;
		Button1Pos.m_y -= 7.f;

		Button1Grow = true;
	}
	if(MouseCollision(Button1Pos) == false
		&& Button1Grow == true)
	{
		Button1Scale.m_x /= 1.5f;
		Button1Scale.m_y /= 1.5f;
		Button1Pos.m_x += 8.f;
		Button1Pos.m_y += 7.f;

		Button1Grow = false;
	}

	if(MouseCollision(Button2Pos) == true 
		&& Button2Grow == false)
	{
		Button2Scale.m_x *= 1.5f;
		Button2Scale.m_y *= 1.5f;
		Button2Pos.m_x -= 8.f;
		Button2Pos.m_y -= 7.f;

		Button2Grow = true;
	}
	if(MouseCollision(Button2Pos) == false
		&& Button2Grow == true)
	{
		Button2Scale.m_x /= 1.5f;
		Button2Scale.m_y /= 1.5f;
		Button2Pos.m_x += 8.f;
		Button2Pos.m_y += 7.f;

		Button2Grow = false;
	}
	if(MouseCollision(Button3Pos) == true 
		&& Button3Grow == false)
	{
		Button3Scale.m_x *= 1.5f;
		Button3Scale.m_y *= 1.5f;
		Button3Pos.m_x -= 8.f;
		Button3Pos.m_y -= 7.f;

		Button3Grow = true;
	}
	if(MouseCollision(Button3Pos) == false
		&& Button3Grow == true)
	{
		Button3Scale.m_x /= 1.5f;
		Button3Scale.m_y /= 1.5f;
		Button3Pos.m_x += 8.f;
		Button3Pos.m_y += 7.f;

		Button3Grow = false;
	}
	if(MouseCollision(Button4Pos) == true 
		&& Button4Grow == false)
	{
		Button4Scale.m_x *= 1.5f;
		Button4Scale.m_y *= 1.5f;
		Button4Pos.m_x -= 8.f;
		Button4Pos.m_y -= 7.f;

		Button4Grow = true;
	}
	if(MouseCollision(Button4Pos) == false
		&& Button4Grow == true)
	{
		Button4Scale.m_x /= 1.5f;
		Button4Scale.m_y /= 1.5f;
		Button4Pos.m_x += 8.f;
		Button4Pos.m_y += 7.f;

		Button4Grow = false;
	}

	if(MouseCollision(Button1Pos) == true
		&& Button1Grow == true
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_MOUSE_LEFT))
	{
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.HIGHCONCEPT);
	}

	if(MouseCollision(Button2Pos) == true
		&& Button2Grow == true
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_MOUSE_LEFT))
	{
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.WHATWEDID);
	}
	if(MouseCollision(Button3Pos) == true
		&& Button3Grow == true
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_MOUSE_LEFT))
	{
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.LV1);
	}
	if(MouseCollision(Button4Pos) == true
		&& Button4Grow == true
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_MOUSE_LEFT))
	{
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.MILESTONE);
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
void Menu::Init()
{
	/*DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is Menu State");*/

	TeamName.LoadFromFile("Team.png");
	TeamRoster.LoadFromFile("Member.png");
	Button1.LoadFromFile("HighConcept.png");

	Button2.LoadFromFile("WhatWeDid.png");
	Button3.LoadFromFile("Button.png");
	Button4.LoadFromFile("Milestone.png");

	TeamNamePos.m_x = 300;
	TeamNamePos.m_y = 180;

	TeamRosterPos.m_x = 1000;
	TeamRosterPos.m_y = 500;

	Button1Pos.m_x = 110;
	Button1Pos.m_y = 550;

	Button1Scale.m_x = 1.1f;
	Button1Scale.m_y = 1.1f;

	Button2Pos.m_x = Button1Pos.m_x + 90;
	Button2Pos.m_y = Button1Pos.m_y;
	Button3Pos.m_x = Button2Pos.m_x + 90;
	Button3Pos.m_y = Button2Pos.m_y;
	Button4Pos.m_x = Button3Pos.m_x + 90;
	Button4Pos.m_y = Button3Pos.m_y;
	Button2Scale.m_x = 1.1f;
	Button2Scale.m_y = 1.1f;
	Button3Scale.m_x = 1.1f;
	Button3Scale.m_y = 1.1f;
	Button4Scale.m_x = 1.1f;
	Button4Scale.m_y = 1.1f;

	Button1Grow      = false;

	Button2Grow      = false;
	Button3Grow      = false;
	Button4Grow      = false;
}

/******************************************************************************/
/*!
\brief
Update all that we need to update.

\return
None.
*/
/******************************************************************************/
void Menu::Update(float dt)
{
	/*DEBUG_PRINT("Mouse Pos x :%f\n", Mouse.m_x);
	DEBUG_PRINT("Mouse Pos y :%f\n", Mouse.m_y);
	DEBUG_CLEAR();*/

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_P))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.LOGO);
	
	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	ButtonUpdate();

	App::GetAppInstance()->GFX.StartDraw();

	TeamName.Render(TeamNamePos.m_x, TeamNamePos.m_y, 0, 1.f, 1.f, 0);
	TeamRoster.Render(TeamRosterPos.m_x, TeamRosterPos.m_y, 0, 1.f, 1.f, 0);
	Button1.Render(Button1Pos.m_x, Button1Pos.m_y, 0, Button1Scale.m_x, Button1Scale.m_y, 0);
	Button2.Render(Button2Pos.m_x, Button2Pos.m_y, 0, Button2Scale.m_x, Button2Scale.m_y, 0);
	Button3.Render(Button3Pos.m_x, Button3Pos.m_y, 0, Button3Scale.m_x, Button3Scale.m_y, 0);
	Button4.Render(Button4Pos.m_x, Button4Pos.m_y, 0, Button4Scale.m_x, Button4Scale.m_y, 0);

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
void Menu::Shutdown()
{
	TeamName.Free();
	TeamRoster.Free();
	Button1.Free();
	Button2.Free();
	Button3.Free();
	Button4.Free();
	//DEBUG_DESTROY_CONSOLE();
}
