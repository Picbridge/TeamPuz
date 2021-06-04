/******************************************************************************/
/*!
file    PuzApp.h
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game system Manager
\date   2014/10/27

  System function prototype
*/
/******************************************************************************/
#ifndef PUZAPP_H
#define PUZAPP_H

#include "SoundManager.h"
#include <WindowsX.h>
#include "PuzStateManager.h"
#include "PuzInput.h"
#include "PuzTimer.h"
#include "stdafx.h"

class App
{
public:
	static LRESULT CALLBACK WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp);
	static void Init(HINSTANCE instance);
	static void AppUpdate(void);
	static void WindowUpdate(void);
	static void Shutdown(void);
	static bool GetAppQuit(void);

	static int GetWidth(void);
	static int GetHeight(void);
	static HWND GetWindow(void);

private:
	static bool				m_quit;        /* A variable to hold the quit state of the game*/
	static int	    		m_height;      /* To hold the height of the client area of the window */
	static int				m_width;       /* To hold the width of the client area of the window */
	static LPCTSTR    		m_title;       /* To hold the title of the window */
	static WNDCLASS	    	m_wndClass;    /* To hold the window class for creating the window*/
	static HWND		    	m_hWnd;        /* To hold the window after creating it*/
	static HINSTANCE		m_hInstance;   /* To hold the instance from WinMain*/
	static DWORD			m_style;       /* To hold my selected style */
	static bool		    	m_fullScreen;  /* If the window is in full screen or not*/

public:
	//Publiic Data
	Sound PuzSound;
	PuzStateMgr StateMgr;
	Timer timer;
	inputData Input;
	Graphics GFX;
	WMinfo sdlWndInfo;
	Camera CAM;

public:
	~App(void);
	static App* GetAppInstance(void);

private:
	//Private Constructor
	App(void) {}

	//Actual instance
	static App* m_appInstance;	
};

#endif /*PUZAPP_H*/