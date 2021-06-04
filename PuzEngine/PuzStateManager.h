/******************************************************************************/
/*!
file    PuzStateManager.h
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Game State Manager
\date   2014/10/16

   Game state manager function prototype.
*/
/******************************************************************************/
#ifndef PUZSTATEMANAGER_H
#define PUZSTATEMANAGER_H

class PuzState
{
public:
	virtual void Init()           = 0;
	virtual void Update(float dt) = 0;
	virtual void Shutdown()       = 0;

private:

};

class Logo : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};

class Menu : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};

class Village : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};

class Lv1 : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};

/*******/
class HighConcept : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};
class WhatWeDid : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};
class MileStone : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};
/*******/

class Win : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};
class Lose : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};
class ShutDown : public PuzState
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Shutdown();

private:

};

class PuzStateMgr
{
public:
	enum Stage{LOGO, MENU, VILLAGE, LV1, HIGHCONCEPT, WHATWEDID, MILESTONE, WIN, LOSE, SHUTDOWN};

	PuzStateMgr();
	~PuzStateMgr();

	void Init(void);
	void Update(void);

	void ChangeState();

	bool StateMgrGetQuit();
	void StateMgrSetQuit(bool express);

	void ChangeNextState(int state);
	void SetRestart(bool exp);

private:
	int m_currState;
	int m_nextState;
	bool m_quit;
	bool m_restart;

	PuzState* pState;
};

#endif /*PUZSTATEMANAGER_H*/