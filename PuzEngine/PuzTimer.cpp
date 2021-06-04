/******************************************************************************/
/*!
file    PuzTimer.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game Timer
\date   2014/10/16


*/
/******************************************************************************/
#include "PuzTimer.h"

/******************************************************************************/
/*!
\brief
Initialize function

\return
None.
*/
/******************************************************************************/
void Timer::Init()
{
	QueryPerformanceFrequency(&m_frequency);
	
	m_frameStart.QuadPart = 0;
	m_frameEnd.QuadPart   = 0;
}

/******************************************************************************/
/*!
\brief

\return
None.
*/
/******************************************************************************/
void Timer::StartFrame(void)
{
	QueryPerformanceCounter(&m_frameStart);
}

/******************************************************************************/
/*!
\brief

\return
*/
/******************************************************************************/
float Timer::EndFrame(void)
{
	QueryPerformanceCounter(&m_frameEnd);

	float frameTime = (float)(m_frameEnd.QuadPart - m_frameStart.QuadPart) / m_frequency.QuadPart;

	return frameTime;
}

/******************************************************************************/
/*!
\brief
Reset to zero.

\return
None.
*/
/******************************************************************************/
void Timer::ShutDown()
{
	m_frameStart.QuadPart = 0;
	m_frameEnd.QuadPart   = 0;
	m_frequency.QuadPart  = 0;
}