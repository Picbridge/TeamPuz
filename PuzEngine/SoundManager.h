/******************************************************************************/
/*!
\file   SoundManager.h
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief
The SoundManager contains function
that can load, play, stop, release the music and manage the channel for sound.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "Debug.h"

#define MAX_CHANNEL 32
#define SOUND_CHANNEL 4

class Sound
{
public:
	Sound(void);
	void ERRCHECK(void);
	void Init(void);
	int Load(const char* filename);
	int LoadLoop(const char* filename);
	void Update(void);
	void Play(int soundID);
	void PauseAndResume(int soundID);
	void Stop(int soundID);
	void Release(void);
	void ShutDown(void);

private:
	FMOD::System  *SoundSystem;
	FMOD::Sound   *sound[SOUND_CHANNEL];
	FMOD::Channel *channel[SOUND_CHANNEL];
	FMOD_RESULT   result;

	int   m_SoundID;
	float m_SoundVolume;
	bool  m_paused;
};

#endif /*SOUND_MANAGER_H*/