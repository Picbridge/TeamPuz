/******************************************************************************/
/*!
file    PuzApp.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game system Manager
\date   2014/10/27

   Manage the whole system
*/
/******************************************************************************/
#include <Windows.h>
#include "PuzApp.h"

LPCTSTR CLASS_NAME = TEXT("GAM200_PUZ");
static const DWORD FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
static const DWORD WINDOW_STYLE   = WS_POPUP | WS_CAPTION;

bool App::m_quit           = false;
int	App::m_height          = 0;
int	App::m_width           = 0;
LPCTSTR	App::m_title       = 0;
WNDCLASS App::m_wndClass   = {0};
HWND App::m_hWnd           = 0;
HINSTANCE App::m_hInstance = 0;
DWORD App::m_style         = 0;
bool App::m_fullScreen     = false;
App* App::m_appInstance    = NULL;

App* App::GetAppInstance(void)
{
	if(!m_appInstance)
	{
		m_appInstance = new App;
	}

	return m_appInstance;
}

App::~App(void)
{
	if(m_appInstance)
		delete m_appInstance;
}

/******************************************************************************/
/*!
\brief
Initialize function(set window elements and call another init functions)

\param instance


\return
None.
*/
/******************************************************************************/
void App::Init(HINSTANCE instance)
{
	/**/
	m_height     = 720;
	m_width      = 1280;
	/**/
	m_title      = TEXT("DetectDog");
	m_hInstance  = instance;
	m_fullScreen = false;
	m_style      = WINDOW_STYLE;

	m_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.cbClsExtra    = 0;
	m_wndClass.cbWndExtra    = 0;
	m_wndClass.hInstance     = instance;  /*This is the instance from WinMain*/
	m_wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	m_wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_wndClass.lpszMenuName  = NULL;
	m_wndClass.lpszClassName = CLASS_NAME;
	m_wndClass.lpfnWndProc   = App::WinProc;

	RegisterClass(&m_wndClass);
	
	m_hWnd = CreateWindow(
		CLASS_NAME,
		m_title,
		m_style,
		200, 200,
		m_width,
		m_height,
		0, 0,
		m_hInstance,
		0
		);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	GetAppInstance()->StateMgr.Init();
	
	GetAppInstance()->timer.Init();

	GetAppInstance()->Input.Init();

	GetAppInstance()->sdlWndInfo.GetSystemData();
	
	GetAppInstance()->PuzSound.Init();
	
	GetAppInstance()->GFX.InitGraphics();
}

/******************************************************************************/
/*!
\brief
Window update using peek message

\return
None.
*/
/******************************************************************************/
void App::WindowUpdate(void)
{
	MSG msg;

	while(PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

/******************************************************************************/
/*!
\brief

\return
None.
*/
/******************************************************************************/
void App::AppUpdate(void)
{
	while(!GetAppQuit())
	{
		GetAppInstance()->StateMgr.Update();

		if(GetAppInstance()->StateMgr.StateMgrGetQuit())
			SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
}

/******************************************************************************/
/*!
\brief

\return
*/
/******************************************************************************/
LRESULT CALLBACK App::WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg)
	{
	case WM_CREATE:
		{
			/*Once the window is create we can start graphics*/
			break;
		}
	case WM_DESTROY:
		{
			/*Clean resources here*/
			GetAppInstance()->PuzSound.ShutDown();// This code should be here
			
			m_quit = true;
			m_hWnd = 0;
			PostQuitMessage(0);
			break;
		}
	case WM_CLOSE:
		{
			/*If we want to quit, destroy graphics and the window*/
			DestroyWindow(win);
			break;
		}
	case WM_KEYDOWN:
		GetAppInstance()->Input.SetPressed(GetAppInstance()->Input.TranslateKey(wp), true);
		break;
	case WM_KEYUP:
		GetAppInstance()->Input.SetPressed(GetAppInstance()->Input.TranslateKey(wp), false);
		break;
	case WM_LBUTTONDOWN:
		GetAppInstance()->Input.SetPressed(GetAppInstance()->Input.PUZ_MOUSE_LEFT, true);
		break;
	case WM_LBUTTONUP:
		GetAppInstance()->Input.SetPressed(GetAppInstance()->Input.PUZ_MOUSE_LEFT, false);
		break;
	case WM_MOUSEMOVE:
		GetAppInstance()->Input.SetMouseX(GET_X_LPARAM(lp));
		GetAppInstance()->Input.SetMouseY(GET_Y_LPARAM(lp));
		break;

	default: 
		return DefWindowProc(win, msg, wp, lp);
	}

	return 0;
}

/******************************************************************************/
/*!
\brief
Shutdown the window

\return
None
*/
/******************************************************************************/
void App::Shutdown(void)
{
	GetAppInstance()->timer.ShutDown();
	GetAppInstance()->GFX.ShutdownGraphics();
	UnregisterClass(NULL, m_hInstance);
}
/******************************************************************************/
/*!
\brief
Returns if the window has been set to quit or not.

\return
TRUE if the window has been set to quit, FALSE otherwise.
*/
/******************************************************************************/
bool App::GetAppQuit(void)
{
	return m_quit;
}

/******************************************************************************/
/*!
\brief
Get window's width

\return
return window width
*/
/******************************************************************************/
int App::GetWidth(void)
{
	return m_width;
}

/******************************************************************************/
/*!
\brief
Get window's height

\return
return window height
*/
/******************************************************************************/
int App::GetHeight(void)
{
	return m_height;
}

/******************************************************************************/
/*!
\brief
Get window handler

\return
return window handler
*/
/******************************************************************************/
HWND App::GetWindow(void)
{
	return m_hWnd;
}