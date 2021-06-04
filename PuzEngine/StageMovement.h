/******************************************************************************/
/*!
file    StageMovement.h
\author Jihoon.Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    Blendering for stage movement
\date   2014/11/27

This file fades in and out while moving the camera to other floor.
*/
/******************************************************************************/
#ifndef STGMV_H
#define STGMV_H

class FadeData
{
public:
	FadeData():isFading(NONE){};
	~FadeData();
	
	void FadeUpdate();

	enum fade{FADEIN,FADEOUT,NONE};
private:
	fade isFading;
};

#endif /*STGMV_H*/
