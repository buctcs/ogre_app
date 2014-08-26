#include "SoundSystem.h"


void ERRCHECK(FMOD_RESULT result);

void ERRCHECK1(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
// 		MessageBox( NULL, FMOD_ErrorString(result), "FMOD: An exception has occured11!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
// 		exit(-1);
std::cout<<"FMOD: An exception has occured!";
	}
}

bool SoundSystem::fmod_Init()
{
 	/*
 	Create a System object and initialize.
 	*/
 	result = FMOD::System_Create(&system); // 创建FMOD系统
 	ERRCHECK(result);
 
  	result = system->getVersion(&version); // 获取系统版本号
  	ERRCHECK(result);
  
  	if (version < FMOD_VERSION) // 版本不够
  	{
  		printf("Error! You are using an old version of FMOD %08x. This program requires %08x.\nPS: FMOD is the sound system.",
  			version, FMOD_VERSION);
  		return 0;
  	}
  
  	result = system->getNumDrivers(&numdrivers);
  	ERRCHECK(result);
  
  	if (numdrivers == 0)
  	{
  		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
  		ERRCHECK(result);
  	}
  	else
  	{
  		result = system->getDriverCaps(0, &caps, 0, &speakerMode);
  		ERRCHECK(result);
  
  		/*
  		Set the user selected speaker mode.
  		*/
  		result = system->setSpeakerMode(speakerMode);
  		ERRCHECK(result);
  
  		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
  		{
  			/*
  			The user has the 'Acceleration' slider set to off! This is really bad
  			for latency! You might want to warn the user about this.
  			*/
  			result = system->setDSPBufferSize(1024, 10);
  			ERRCHECK(result);
  		}
  
  		result = system->getDriverInfo(0, name, 256, 0);
  		ERRCHECK(result);
  
  		if (strstr(name, "SigmaTel"))
  		{
  			/*
  			Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
  			PCM floating point output seems to solve it.
  			*/
  			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
  			ERRCHECK(result);
  		}
  	}
  
  	// 初始化系统
  	result = system->init(100, FMOD_INIT_NORMAL, 0);
  	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
  	{
  		/*
  		Ok, the speaker mode selected isn't supported by this soundcard. Switch it
  		back to stereo...
  		*/
  		result  = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
  		ERRCHECK(result);
  
  		/*
  		... and re-init.
  		*/
  		result = system->init(100, FMOD_INIT_NORMAL, 0);
  	}
  	ERRCHECK(result);

	// 创建声音，载入歌曲
// 	result = system->createSound("../media/sounds/He's a Pirate.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[0]); // 宇宙空间航行配乐
// 	ERRCHECK(result);
// 	result = system->createSound("../media/sounds/Going Home.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[1]); // 地球配乐
// 	ERRCHECK(result);
// 	result = system->createSound("../media/sounds/Fly Me To The Moon.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[2]); // 月亮配乐
// 	ERRCHECK(result);
// 	result = system->createSound("../media/sounds/I See The Light.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[3]); // 太阳配乐
// 	ERRCHECK(result);
// 	result = system->createSound("../media/sounds/A Thousand Years.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[4]); // 火星配乐
// 	ERRCHECK(result);
// 	result = system->createSound("../media/sounds/far away from home.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[5]); // 地球配乐2（候选）
// 	ERRCHECK(result);
// 	result = system->createSound("../media/sounds/Never Grow Old.mp3",
// 		FMOD_LOOP_NORMAL, 0, &sound[6]); // 
// 	ERRCHECK(result);

	// 创建通道组
// 	result = system->createChannelGroup("Group A", &groupA);
// 	ERRCHECK(result);
// 	result = system->createChannelGroup("Group B", &groupB);
// 	ERRCHECK(result);
// 	result = system->getMasterChannelGroup(&masterGroup); // 主通道
// 	ERRCHECK(result);
// 
// 	/*
// 	Instead of being independent, set the group A and B to be children of the master group.
// 	*/
// 	result = masterGroup->addGroup(groupA);
// 	ERRCHECK(result);
// 	result = masterGroup->addGroup(groupB);
// 	ERRCHECK(result);

	// 初始化音乐开始标志
// 	for (int i = 0; i < soundNum; i ++)
// 	{
// 		ifStart[i] = false;
// 	}

	/*
	开始播放所有歌曲
	*/
// 	for (count = 0; count < soundNum; count ++)
// 	{
// 		result = system->playSound(FMOD_CHANNEL_FREE, sound[count], TRUE, &channel[count]);
// 		ERRCHECK(result);
// 		if (count < 3)
// 			result = channel[count]->setChannelGroup(groupA);
// 		else
// 			result = channel[count]->setChannelGroup(groupB);
// 		ERRCHECK(result);
// 		result = channel[count]->setPaused(false);
// 		ERRCHECK(result);
// 	}

	/*
	Change the volume of each group, just because we can!  (And makes it less of a loud noise).
	改变各音轨组的音量。
	*/
	//result = groupA->setVolume(0.5f);
	//ERRCHECK(result);
	//result = groupB->setVolume(0.5f);
	//ERRCHECK(result);

	return 1;
}

bool SoundSystem::fmod_CreateSound(const char *name_or_data, FMOD_MODE mode, int num)
{
	result = system->createSound(name_or_data, mode, 0, &sound[num]);
	ifStart[num] = false;
	return true;
}

bool SoundSystem::fmod_PlaySound(int num /* = 0 */, bool isfinite /* = true */, int loopCount /* = 0 */)
{
	if (ifStart[num] == false)
	{
		result = system->playSound(FMOD_CHANNEL_FREE, sound[num], FALSE, &channel[num]);
		ERRCHECK(result);
		if (isfinite == true)
		{
			result = channel[num]->setLoopCount(loopCount);
			ERRCHECK(result);
		}
		ifStart[num] = true;
// 		for (int i = 0; i < soundNum; i ++)
// 		{
// 			if (ifStart[i] == true)
// 			{
// 				result = channel[i]->stop();
// 				ifStart[i] = false;
// 			}
// 		}
		
		//if (num < 3)
			//result = channel[num]->setChannelGroup(groupA);
	//	else
		//	result = channel[num]->setChannelGroup(groupB);
		//ERRCHECK(result);
	}
	return true;
}

bool SoundSystem::fmod_StopSound(int num)
{
	result = channel[num]->stop();
	ERRCHECK(result);
	return true;
}

bool SoundSystem::fmod_PauseSound(int num)
{
	result = channel[num]->setPaused(true);
	ERRCHECK(result);
	return true;
}

bool SoundSystem::fmod_GoOnSound(int num)
{
	result = channel[num]->setPaused(false);
	ERRCHECK(result);
	return true;
}

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
// 		MessageBox( NULL, FMOD_ErrorString(result), "FMOD: An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
// 		exit(-1);
		std::cout<<"FMOD: An exception has occured!";
	}
}
