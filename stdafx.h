#pragma once
#ifndef __STDAFX_H__
#define __STDAFX_H__

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

//#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include <stdio.h>
#include <string.h>
#include <math.h>

// OGRE headers needed.
#include <Ogre.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreLogManager.h>

#include <ExampleApplication.h>
#include <ExampleFrameListener.h>

// Output/Input system.
#include <OIS.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

// CEGUI Hearder needed.
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <elements/CEGUIPushButton.h>

// Any other header can be included, as usual.
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

//#include "mmsystem.h" // 导入声音头文件 
//#pragma comment(lib,"winmm.lib") // 导入声音头文件库

// Supporting headers of FMOD（音效）
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_codec.h>
#include <fmod_dsp.h>
#include <fmod_output.h>
#include <fmod_memoryinfo.h>
#include <fmod_errors.h>
//#include "SoundManager.h"

#endif