/******************************************************************************/
/*!
file    PuzTimer.h
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game Timer
\date   2014/10/16

  PuzTimer functions' prototypes
*/
/******************************************************************************/
#ifndef PUZTIMER_H
#define PUZTIMER_H

#include <windows.h>

class Timer
{
public:
	void Init();
	void StartFrame(void);
	float EndFrame(void);
	void ShutDown();

private:
	LARGE_INTEGER m_frameStart;
	LARGE_INTEGER m_frameEnd;
	LARGE_INTEGER m_frequency;
};


#endif /*PUZTIMER_H*/