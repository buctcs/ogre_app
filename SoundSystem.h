/**
Sound System:
@author: 
*/

#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include "stdafx.h"
//#include "defines.h"


class SoundSystem
{
public:
	SoundSystem() {}
	~SoundSystem() {}

public:
	bool fmod_Init();
	inline FMOD::System* fmod_GetSystem() { return system; }	
	bool fmod_CreateSound(const char *name_or_data, FMOD_MODE mode, int num);
	bool fmod_PlaySound(int num = 0, bool isfinite = true, int loopCount = 0);
	bool fmod_StopSound(int num);
	bool fmod_PauseSound(int num);
	bool fmod_GoOnSound(int num);

protected:
#define soundNum 10
	FMOD::System* system;
	FMOD_RESULT result;
	unsigned int version;
	int numdrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];
	FMOD::Sound* sound[soundNum];
	FMOD::Channel* channel[soundNum];
	FMOD::ChannelGroup* groupA, * groupB, *masterGroup;
	bool ifStart[soundNum]; // flag是判断声音是否已经开始的标志
};


#endif