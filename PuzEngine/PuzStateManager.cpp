/******************************************************************************/
/*!
file    PuzStateManager.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game State Manager
\date   2014/10/16

   Manage the game states.
*/
/******************************************************************************/
#include <Windows.h> 

#include "PuzApp.h"
/******************************************************************************/
/*!
\brief
default Constructor.

\return
None.
*/
/******************************************************************************/
PuzStateMgr::PuzStateMgr()
{
	m_currState = 0;
	m_nextState = 0;
	m_quit      = false;
	m_restart   = false;
}

/******************************************************************************/
/*!
\brief
Destructor.

\return
None.
*/
/******************************************************************************/
PuzStateMgr::~PuzStateMgr()
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
void PuzStateMgr::Init(void)
{
	pState = new Logo;
}

/******************************************************************************/
/*!
\brief
This function controls the main game loop.  It will update the application,
initialize, update and shutdown all states.  This must be called Every 
GameLoop.

\return
None.
*/
/******************************************************************************/
void PuzStateMgr::Update(void)
{
	float frameTime = 0.0f;
	float Time = 0.0f;

	pState->Init();

	while((!StateMgrGetQuit()) && (!m_restart)
		&& (m_currState == m_nextState))
	{
		App::GetAppInstance()->Input.InputReset();
		App::WindowUpdate();
		do
		{
			App::GetAppInstance()->timer.StartFrame();
			Time += App::GetAppInstance()->timer.EndFrame();
		}while(Time <= 0.016667f);
		frameTime = Time;
		pState->Update(frameTime);
		Time = 0.f;

	}

	pState->Shutdown();

	delete pState;
	ChangeState();
}

/******************************************************************************/
/*!
\brief
Used to change the state ids after the state has shutdown.

\return
None.
*/
/******************************************************************************/
void PuzStateMgr::ChangeState()
{
	m_currState = m_nextState;
	SetRestart(false);

	switch(m_currState)
	{
	case LOGO:
		pState = new Logo;
		break;

	case MENU:
		pState = new Menu;
		break;

	case VILLAGE:
		pState = new Village;
		break;

	case LV1:
		pState = new Lv1;
		break;

	case HIGHCONCEPT:
		pState = new HighConcept;
		break;

	case WHATWEDID:
		pState = new WhatWeDid;
		break;

	case MILESTONE:
		pState = new MileStone;
		break;

	case WIN:
		pState = new Win;
		break;

	case LOSE:
		pState = new Lose;
		break;

	case SHUTDOWN:
		pState = new ShutDown;
		break;

	default:
		break;

	}
}

/******************************************************************************/
/*!
\brief
Returns if the Game state manager has been set to quit or not.

\return
TRUE if the manager has been set to quit, FALSE otherwise.
*/
/******************************************************************************/
bool PuzStateMgr::StateMgrGetQuit()
{
	return m_quit;
}

/******************************************************************************/
/*!
\brief
Sets if the game state manager should quit.  Use this to exit the game from 
inside a state.

\par express
TRUE if the game manager should quit, FALSE otherwise

\return
None.
*/
/******************************************************************************/
void PuzStateMgr::StateMgrSetQuit(bool express)
{
	m_quit = express;
}

/******************************************************************************/
/*!
\brief
Go to state which you want.

\par state
the state which you want to go.

\return
None.
*/
/******************************************************************************/
void PuzStateMgr::ChangeNextState(int state)
{
	m_nextState = state;
}

/******************************************************************************/
/*!
\brief
Make state restarted or not

\attention 
This does not restart that game.  It calls shutdown, then init on the current 
state, and continues updating.

\par exp
expression is true if state should be restarted
otherwise false.

\return
None.
*/
/******************************************************************************/
void PuzStateMgr::SetRestart(bool exp)
{
	m_restart = exp;
}