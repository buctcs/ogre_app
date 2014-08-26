#include "ThreeDimentionalApplication.h"


void ThreeDimentionalApplication::go(void)
{
	if (!setup())
		return;

	startRendering();

	// clean up
	destroyScene();
}

bool ThreeDimentionalApplication::setup(void)
{

	String pluginsPath;
	// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
#if OGRE_DEBUG_MODE
	pluginsPath = mResourcePath + "plugins_d.cfg";
#else
	pluginsPath = mResourcePath + "plugins.cfg";
#endif
#endif

	// ����root����
	mRoot = OGRE_NEW Root(pluginsPath, 
		mConfigPath + "ogre.cfg", mResourcePath + "Ogre.log");
#ifdef OGRE_STATIC_LIB
	mStaticPluginLoader.load();//////////////////////////////////////////////////////////////
#endif
	setupResources();

	bool carryOn = configure();
	if (!carryOn) 
		return false;

	chooseSceneManager();
	createCamera();
	createViewports();
#ifdef USE_RTSHADER_SYSTEM
	// Initialize shader generator.
	carryOn = initializeShaderGenerator(mSceneMgr);////////////////////////////////////////////////////
	if (!carryOn) 
		return false;
#endif

	// Set default mipmap level (NB some APIs ignore this)
	TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create the scene
	createScene();

	createFrameListener();

	return true;

}

void ThreeDimentionalApplication::setupResources(void)
{
	// Load resource paths from config file
	ConfigFile cf;
#if OGRE_DEBUG_MODE
	cf.load(mResourcePath + "resources_d.cfg");
#else
	cf.load(mResourcePath + "resources.cfg");
#endif

	// Go through all sections & settings in the file
	ConfigFile::SectionIterator seci = cf.getSectionIterator();
	//section archive
	String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		// Returns the next(=current) key element in the collection, without advancing to the next.
		secName = seci.peekNextKey();
		// Returns the next(=current) value element in the collection, and advances to the next.
		ConfigFile::SettingsMultiMap *settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
			// OS X does not set the working directory relative to the app,
			// In order to make things portable on OS X we need to provide
			// the loading with it's own bundle path location
			if (!StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
				archName = String(macBundlePath() + "/" + archName);
#endif

			// add a resource location to for a given resource group.
			ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}

bool ThreeDimentionalApplication::configure(void)
{
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	// #if OGRE_DEBUG_MODE
	// 	if(mRoot->showConfigDialog())/////////////////////////////////////////////////////////////////////////////////////
	// #else
	if(mRoot->restoreConfig())
	//#endif
	{
		// If returned true, user clicked OK so initialise
		// �˴���ʼ������
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true, "Solar System - �ҵ���Ϸ");////////////////////////////////////////////////////////////////////////////
		return true;
	}
	else
	{
		return false;
	}
}

void ThreeDimentionalApplication::chooseSceneManager(void)
{
	 // Create the SceneManager, in this case a generic one
	mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "Final3DSMInstance");
}

void ThreeDimentionalApplication::createCamera(void)
{
	// ��Ĭ��λ�ô��������
	mCamera = mSceneMgr->createCamera("PlayerCamera");///////////////////////

	// ���������λ�úͷ���
	// Position it at 500 in Z direction
	mCamera->setPosition(Vector3(0,0,500));
	// Look back along -Z
	mCamera->lookAt(Vector3(0,0,-300));
	// ���ý��������
	mCamera->setNearClipDistance(5);
}

void ThreeDimentionalApplication::createViewports(void)
{
	// Create one viewport, entire window
	Viewport* mainVp = mWindow->addViewport(mCamera);
	// ���ñ���ɫ����ɫ͸����
	mainVp->setBackgroundColour(ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Real(mainVp->getActualWidth()) / Real(mainVp->getActualHeight()));
}

void ThreeDimentionalApplication::createScene(void)
{
	// ����ϵͳ��ʼ��
	myGuiSys->cegui_Init();

	// �������֣���ʼ��
	mySoundSys.fmod_Init();
// 	PlaySound("F:\\����ѧϰ\\something fun\\three-body simulation\\OgreSystem\\Sounds\\He's a Pirate.wav", NULL,  SND_FILENAME | SND_ALIAS  |SND_ASYNC | SND_LOOP); 
// 	_sleep(1000); 

	// �������߲�ѯ
//	gF3DParams.mRaySceneQuery = mSceneMgr->createRayQuery(Ray());

	// ��������ϵͳ
//	createParticle();

	// ����ϵͳʱ������ʵʱ���ٶȱ���
	gTimeFactor = 1000.0;

	// ���ð���������Ľڵ�
	//SceneNode* mMainCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MainCamNode", Vector3(0, 0, 230));
	//mMainCamNode->attachObject(mCamera);

	//init3dScene();

	/************************************************************************/
	/* ���Դ���                                                                     */
	/************************************************************************/
// 	gF3DParams.mCurrentNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
// 	gF3DParams.mCurrentNode = gF3DParams.EarthNode;
// 	gF3DParams.Earth->setQueryFlags(QUERY_MASK);
// 	mCamera->setQueryFlags(HIDE_MASK);

//	createTrackAnimation();

} // ����createScene����

void ThreeDimentionalApplication::createFrameListener(void)
{
	// ����֡����ʵ��
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
	mFrameListener= new ExampleFrameListener(mWindow, mCamera, true, true, true);
#else
	mFrameListener = new MyFrameListener(mWindow, mCamera, mSceneMgr);///////////////////////
#endif
	
	// ��֡����ע�ᵽRoot������
	mRoot->addFrameListener(mFrameListener);

} // ����createFrameListener����


void ThreeDimentionalApplication::startRendering(void)
{
	assert(mRoot->getRenderSystem() != 0);

	mRoot->getRenderSystem()->_initRenderTargets();

	// Clear event times
	mRoot->clearEventTimes();

	gameProgress();
}

void ThreeDimentionalApplication::gameProgress(void)
{
	// ������Ϸ��ʼʱ��GUI
	setupStartGui();

	// ������ѡ��
	setupMainMenu();

	// Infinite loop, until broken out of by frame listeners
	// or break out by calling queueEndRendering()
// 	while (gF3DParams.animInst1->isRunning())
// 	{
// 		if (!renderOneFrame())
// 			break;
// 	}

}
