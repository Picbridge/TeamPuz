/******************************************************************************/
/*!
file    Lever.h
\author Jihoon.Bae
\par    email: aky2000kr@gmail.com
\par    GAM200
\par    Lever system
\date   2014/10/21

   This file has funtions' prototype
*/
/******************************************************************************/
#ifndef LEVER_H
#define LEVER_H

#include "Math.h"

class LeverData
{
public:
	LeverData();
	~LeverData();
	void Init(void);

	Vector GetPos(void) { return leverPos; }
	bool IsMouseOnLever();
	bool IsleverClicked(){return m_isLeverClicked;}
	void SetLeverClickedBool(bool booltype);
private:
	Vector leverPos;
	bool m_isLeverClicked;
};

#endif /*LEVER_H*/