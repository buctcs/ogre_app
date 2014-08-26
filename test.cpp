#include "stdafx.h"

using namespace Ogre;

void startRendering(void)
{
	Root* ogreRoot;
	bool mQueuedEnd;

	assert(ogreRoot->getRenderSystem() != 0);

	ogreRoot->getRenderSystem()->_initRenderTargets();////////////////////////////////////////////////////////��

	// Clear event times
	ogreRoot->clearEventTimes(); //////////////////////////////////////////////////////�ص�

	// Infinite loop, until broken out of by frame listeners
	// or break out by calling queueEndRendering()
	mQueuedEnd = false;

	while( !mQueuedEnd )
	{
		//Pump messages in all registered RenderWindow windows
		WindowEventUtilities::messagePump();////////////////////////////////////////////////////////ÿ֡�ص�

		if (!ogreRoot->renderOneFrame())////////////////////////////////////////////////////////��
			break;
	}
}