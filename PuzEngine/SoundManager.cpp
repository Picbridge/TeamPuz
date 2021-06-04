/******************************************************************************/
/*!
\file   SoundManager.cpp
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
#include "SoundManager.h"
/******************************************************************************/
/*!
Default constructor of sound manager
*/
/******************************************************************************/
Sound::Sound(void)
{
	m_SoundID     = 0;
	m_SoundVolume = 1.f;
	m_paused      = false;
}
/******************************************************************************/
/*!
Check if there is any error

\param result
The result of fmod function
*/
/******************************************************************************/
void Sound::ERRCHECK(void)
{
	/*Alert if fmod is not working*/
    if (result != FMOD_OK)
    {
        DEBUG_PRINT("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}
/******************************************************************************/
/*!
Initialize data for sound manager
*/
/******************************************************************************/
void Sound::Init(void)
{
	unsigned int version;

	m_SoundID = 0;

	/* Create a System object and initialize. */
	result = FMOD::System_Create(&SoundSystem);
	ERRCHECK();

	result = SoundSystem->getVersion(&version);
    ERRCHECK();

	if (version < FMOD_VERSION)
    {
        DEBUG_PRINT("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return;
    }

	result = SoundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, NULL);
    ERRCHECK();
}
/******************************************************************************/
/*!
Load sound file (Loop X)

\param filename
location of the file
*/
/******************************************************************************/
int Sound::Load(const char* filename)
{
	/*Create Sound*/
	result = SoundSystem->createSound(filename, FMOD_DEFAULT, 0, &sound[m_SoundID]);
    ERRCHECK();

	DEBUG_ASSERT(m_SoundID <= SOUND_CHANNEL, "Sound Load is not working");

	/*Increase index of sound list*/
	++m_SoundID;
	return m_SoundID -1;
}
/******************************************************************************/
/*!
Load sound file (Loop O)

\param filename
location of the file
*/
/******************************************************************************/
int Sound::LoadLoop(const char* filename)
{
	/*Create Sound*/
	result = SoundSystem->createSound(filename, FMOD_LOOP_NORMAL, 0, &sound[m_SoundID]);
    ERRCHECK();

	DEBUG_ASSERT(m_SoundID <= SOUND_CHANNEL, "Sound Load is not working");

	/*Increase index of sound list*/
	++m_SoundID;
	return m_SoundID -1;
}
/******************************************************************************/
/*!
Update sound system
*/
/******************************************************************************/
void Sound::Update(void)
{
	SoundSystem->update();
}
/******************************************************************************/
/*!
Play sound effect

\param soundID
The index of sound list
*/
/******************************************************************************/
void Sound::Play(int soundID)
{
	/*Set volume of sound*/
	channel[soundID]->setVolume(m_SoundVolume);

	/*Play sound*/
	result = SoundSystem->playSound(FMOD_CHANNEL_FREE, sound[soundID], false, &channel[soundID]);
    ERRCHECK();
}
/******************************************************************************/
/*!
Pause if sound is playing.
Resume if sound is not paused.

\param soundID
The index of sound list
*/
/******************************************************************************/
void Sound::PauseAndResume(int soundID)
{
	/*Get information if sound is paused or not*/
	result = channel[soundID]->getPaused(&m_paused);
	ERRCHECK();

	/*Switch state*/
	m_paused = !m_paused;

	/*Pause the sound*/
	result = channel[soundID]->setPaused(m_paused);
	ERRCHECK();
}
/******************************************************************************/
/*!
Stop sound effect

\param soundID
The index of sound list
*/
/******************************************************************************/
void Sound::Stop(int soundID)
{
	result = channel[soundID]->stop();
	ERRCHECK();
}
/******************************************************************************/
/*!
Release sound effect
*/
/******************************************************************************/
void Sound::Release(void)
{
	for(int i=0; i<m_SoundID; i++)
	{
		result = sound[i]->release();
		ERRCHECK();
	}

	m_SoundID = 0;
}
/******************************************************************************/
/*!
Shutdown data for sound manager
*/
/******************************************************************************/
void Sound::ShutDown(void)
{
	/*Close a System object*/
	result = SoundSystem->close();
    ERRCHECK();

	/*Release a System object*/
	result = SoundSystem->release();
    ERRCHECK();
}