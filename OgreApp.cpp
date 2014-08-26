#include "OgreApp.h"

void OgreApp::gameProgress( void )
{
    // 载入游戏开始时的GUI
    setupStartGui();

    // 设置主选单
    isMainCreated = false;
    isCharaWinCreated = false;
    setupMainMenu();
}

//-----------------------------以下为3d游戏场景初始化相关实现-----------------------------------//

void OgreApp::init3dScene( void )
{
    mSceneMgr->destroyAllLights();
    mSceneMgr->destroyAllEntities();
    mSceneMgr->destroySceneNode( gF3DParams.EarthNode );

    // 创建太阳实体
   

    // 音效
    mySoundSys.fmod_CreateSound( "../media/sounds/He's a Pirate.mp3",
                                 FMOD_LOOP_NORMAL, SpaceSound );
    mySoundSys.fmod_PlaySound( SpaceSound, false );
    mySoundSys.fmod_CreateSound( "../media/sounds/Going Home.mp3",
                                 FMOD_LOOP_NORMAL, EarthSound );
    mySoundSys.fmod_CreateSound( "../media/sounds/Fly Me To The Moon.mp3",
                                 FMOD_LOOP_NORMAL, MoonSound );
    mySoundSys.fmod_CreateSound( "../media/sounds/I See The Light.mp3",
                                 FMOD_LOOP_NORMAL, SunSound );

    mRoot->clearEventTimes();
    while ( gPhaseMark != MainMenu )
    {
        if ( !renderOneFrame() )
            break;
    }

    if ( gF3DParams.mContinue == true )
        setupMainMenu(); // 返回主菜单
}


//----------------------以下为GUI初始化相关实现-------------------------------------------//

void OgreApp::setupStartGui()
{

    // 初始化资源
    CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme","Schemes" );
    CEGUI::Font* font = &CEGUI::FontManager::getSingleton().create( "Xianjian.font" );
    myGuiSys->cegui_GetSystem()->setDefaultFont( font );
    CEGUI::ImagesetManager::getSingleton().create( "Xianjian.imageset" );
    myGuiSys->cegui_GetSystem()->setDefaultMouseCursor( "Xianjian", "Xj4MainCur" );
    CEGUI::MouseCursor::getSingleton().setExplicitRenderSize( CEGUI::Size( 32, 32 ) );

	if (gPhaseMark == HealthyGaming)
	{
		myGuiSys->cegui_ShowGuiCursor(false); // 隐藏o鼠标
		// 载入、创建图片集
		myGuiSys->cegui_CreateImageset("HealthyGaming", "healthyGaming.jpg");
		CEGUI::ImagesetManager::getSingleton().create("startGui.imageset");
		myGuiSys->cegui_CreateImageset("FinalLogo", "finalLogo.jpg");
		// 载入StartGui布局
		myGuiSys->cegui_LoadLayout("StartGui");
		// 从XML载入动画
		CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("StartGui_Anim.xml","Animations");
		gPhaseMark = HealthyGaming;
		// 健康游戏公告动画
		// 得到动画
		anim = CEGUI::AnimationManager::getSingleton().getAnimation("HealthyGaming");
		// 实例化动画
		animInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation(anim);
		// 动画的应用窗口
		animInst->setTargetWindow(myGuiSys->cegui_GetWindow("Start/HealthyGaming"));
		// 动画开始
		animInst->start();
		mRoot->clearEventTimes();
		// 渲染循环
		while (animInst->isRunning() /*&& gPhaseMark == HealthyGaming*/)
		{
			if (!renderOneFrame())
				break;
		}
	}

	// 载入final标志动画
	if (gPhaseMark == HealthyGaming)
		gPhaseMark = FinalLogo;
	if (gPhaseMark == FinalLogo)
	{
		anim = CEGUI::AnimationManager::getSingleton().getAnimation("ShowFinalLogo");
		animInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation(anim);
		animInst->setTargetWindow(myGuiSys->cegui_GetWindow("Start/FinalLogo"));
		CEGUI::AnimationInstance* animInstX[10];
		anim = CEGUI::AnimationManager::getSingleton().getAnimation("FinalLogoJumpInLeft");
		for (int i = 0; i < 5; i ++)
		{
			animInstX[i] = CEGUI::AnimationManager::getSingleton().instantiateAnimation(anim);
		}
		anim = CEGUI::AnimationManager::getSingleton().getAnimation("FinalLogoJumpInRight");
		for (int i = 5; i < 10; i ++)
		{
			animInstX[i] = CEGUI::AnimationManager::getSingleton().instantiateAnimation(anim);
		}
		animInstX[0]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoF"));
		animInstX[1]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoI"));
		animInstX[2]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoN"));
		animInstX[3]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoA"));
		animInstX[4]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoL"));
		animInstX[5]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoD"));
		animInstX[6]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoR"));
		animInstX[7]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoE"));
		animInstX[8]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoA2"));
		animInstX[9]->setTargetWindow(myGuiSys->cegui_GetWindow("Start/LogoM"));
		for (int i = 0; i < 10; i ++)
		{
			animInstX[i]->start();
		}
		animInst->start();
		for (int i = 0; i < 9; i ++) // logo跳跃声音的初始化
			mySoundSys.fmod_CreateSound("../media/sounds/logo jump.mp3",
			FMOD_LOOP_NORMAL, i);
		//	mySoundSys.fmod_CreateSound("../media/sounds/plantgrow.wav",
		//		FMOD_LOOP_NORMAL, 9);
		mRoot->clearEventTimes();
		while ((animInstX[0]->isRunning() || animInst->isRunning()) /*&& gPhaseMark == FinalLogo*/)
		{
			if (!renderOneFrame())
				break;

			if (animInst->getPosition() > 0.4) // 播放跳跃声音（比着地时间延迟0.05s）
				mySoundSys.fmod_PlaySound();
			if (animInst->getPosition() > 1.3)
				mySoundSys.fmod_PlaySound(1);
			if (animInst->getPosition() > 2.2)
				mySoundSys.fmod_PlaySound(2);
			if (animInst->getPosition() > 3.1)
				mySoundSys.fmod_PlaySound(3);
			if (animInst->getPosition() > 0.31) // 右入
				mySoundSys.fmod_PlaySound(4);
			if (animInst->getPosition() > 1.03)
				mySoundSys.fmod_PlaySound(5);
			if (animInst->getPosition() > 1.75)
				mySoundSys.fmod_PlaySound(6);
			if (animInst->getPosition() > 2.47)
				mySoundSys.fmod_PlaySound(7);
			if (animInst->getPosition() > 3.19)
				mySoundSys.fmod_PlaySound(8);
			if (animInst->getPosition() > 3.19)
				mySoundSys.fmod_PlaySound(8);
		}
		// 	for (int i = 0; i < 10; i ++) // 销毁指针
		// 		if (animInstX[i])
		// 			delete animInstX[i];
	}

	// 载入ogre标志动画
	if (gPhaseMark == FinalLogo)
		gPhaseMark = OgreLogo;
	if (gPhaseMark == OgreLogo)
	{
		anim = CEGUI::AnimationManager::getSingleton().getAnimation("HealthyGaming");
		animInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation(anim);
		animInst->setTargetWindow(myGuiSys->cegui_GetWindow("Start/OgreLogo"));
		animInst->start();
		mySoundSys.fmod_CreateSound("../media/sounds/ogre roar.mp3",
			FMOD_LOOP_NORMAL, 0);
		mRoot->clearEventTimes();
		while (animInst->isRunning()/* && gPhaseMark == OgreLogo*/)
		{
			if (!renderOneFrame())
				break;

			mySoundSys.fmod_PlaySound();
		}
	}
	myGuiSys->cegui_GetGuiWindowMgr()->destroyAllWindows();

}

void OgreApp::setupMainMenu()
{
    // 载入主选单
    gPhaseMark = MainMenu;
    myGuiSys->cegui_ShowGuiCursor( true );

    CEGUI::ImagesetManager::getSingleton().create( "mainMenu.imageset" ); // gui
    myGuiSys->cegui_LoadLayout( "MainMenu" );

    initMainMenu();
}

void OgreApp::initMainMenu()
{
    gPhaseMark = MainMenu;

    if ( isMainCreated == false )
    {
        CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML( "MainMenu_Anim.xml" );
        anim = CEGUI::AnimationManager::getSingleton().getAnimation( "OgreSystem" ); // 标题
        animInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
        animInst->setTargetWindow( myGuiSys->cegui_GetWindow( "MainMenu/OgreSystem" ) );
        animInst->start();
    }
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "ShootingStar" ); // 流星效果
    animInst2 = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInst2->setTargetWindow( myGuiSys->cegui_GetWindow( "MainMenu/ShootingStar" ) );
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "EggCross" ); // 彩蛋动画
    animInst3 = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInst3->setTargetWindow( myGuiSys->cegui_GetWindow( "MainMenu/Egg" ) );
    gF3DParams.eggCount = 0; // 彩蛋计数赋初值
    myGuiSys->cegui_GetWindow( "MainMenu/Label" )->hide(); // 隐藏标签
    myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->hide(); // 隐藏退出窗口
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady" )->hide(); // 隐藏”此路不通“窗口
    myGuiSys->cegui_GetWindow( "MainMenu/Waiting" )->hide(); // 隐藏等待窗口

//	mSceneMgr->destroyAllLights();
//	mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();
//	if (gF3DParams.EarthNode)
//		mSceneMgr->destroySceneNode(gF3DParams.EarthNode);
    // 地球模型，作为背景
    gF3DParams.EarthNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "EarthNode" );
    gF3DParams.Earth = mSceneMgr->createEntity( "EarthModel", "Earth.mesh" );
    gF3DParams.Earth->setMaterialName( "Earth/Surface" );
    gF3DParams.EarthNode->attachObject( gF3DParams.Earth );
    gF3DParams.EarthNode->scale( 0.000043f, 0.000043f, 0.000043f );
    gF3DParams.EarthNode->setPosition( -300.0f, 0.0f, 0.0f );
    gF3DParams.EarthNode->roll( Degree( -703 / 30 ), Node::TS_LOCAL ); // 黄赤交角平均为23度26分
    SceneNode* nodeX = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // 背景：月球
    // 创建月球实体
//  	gF3DParams.MoonNode = gF3DParams.EarthNode->createChildSceneNode("MoonNode", Vector3(670.0f, 100.0f, -200.0f));
//  	Entity* mMoon = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
//  	mMoon->setMaterialName("Moon/MoonSurface");
//  	gF3DParams.MoonNode->attachObject(mMoon);
// 	gF3DParams.MoonNode->setInheritScale(false);
//	if (isMainCreated == false)
    mSceneMgr->getRootSceneNode()->createChildSceneNode( "CamNode" )->attachObject( mCamera ); // 设置摄像机位置
    mCamera->getParentSceneNode()->resetOrientation();
    mCamera->getParentSceneNode()->scale( 1, 1, 1 );
    mCamera->getParentSceneNode()->setPosition( 0, 0, 230 );
    mSceneMgr->setAmbientLight( ColourValue( 0.25, 0.25, 0.25 ) ); // 环境光
    mSceneMgr->setShadowTechnique( SHADOWTYPE_STENCIL_ADDITIVE ); // 设置加成模板阴影
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // 小星球节点
    ent = mSceneMgr->createEntity( SceneManager::PT_SPHERE ); // 小星球
    node->attachObject( ent );
    ent->setVisible( false ); // 隐藏模型
    if ( isMainCreated == false )
    {
        // 按钮响应
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Start/Star", CEGUI::Window::EventMouseEnters, // 鼠标移入按钮
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Load/Star", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Setup/Star", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Quit/Star", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Start/Star", CEGUI::Window::EventMouseLeaves, // 鼠标移出按钮
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Load/Star", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Setup/Star", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Quit/Star", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Start/Star", CEGUI::Window::EventMouseClick, // 点击按钮按钮
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Load/Star", CEGUI::Window::EventMouseClick,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Setup/Star", CEGUI::Window::EventMouseClick,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Quit/Star", CEGUI::Window::EventMouseClick,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/QuitWin/Quit", CEGUI::PushButton::EventMouseClick, // 退出游戏响应
                                         CEGUI::Event::Subscriber( &OgreApp::QuitGame, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/QuitWin/Cancel", CEGUI::PushButton::EventMouseClick, // 取消退出游戏响应
                                         CEGUI::Event::Subscriber( &OgreApp::CancelQuit, this ) );

        // 主旋律
        mySoundSys.fmod_CreateSound( "../media/sounds/Halo Theme Mjolnir.mp3",
                                     FMOD_LOOP_NORMAL, 0 );
        mySoundSys.fmod_PlaySound( 0, false );
    }

    isMainCreated = true;
    mRoot->clearEventTimes();
    while ( gPhaseMark != CreateChara )
    {
        if ( !renderOneFrame() )
            break;

        if ( gF3DParams.eggCount > 10 )
        {
            if ( !animInst3->isRunning() )
                animInst3->start();
            gF3DParams.eggCount = 0;
        }
    }

    // 初始化3d场景
    if ( gF3DParams.mContinue == true )
        setupCharaGui();
}

void OgreApp::setupCharaGui()
{

//	myGuiSys->cegui_ShowGuiCursor(true);

    gPhaseMark = CreateChara;
    isCharaRollable = false; // 模型不可旋转
    // 创建角色GUI所使用的模型
    mCharaEntA = mSceneMgr->createEntity( "sinbad", "sinbad.mesh" );
    mCharaEntB = mSceneMgr->createEntity( "jaiqua", "jaiqua.mesh" );
    mCharaEntC = mSceneMgr->createEntity( "ninja", "ninja.mesh" );
    mSceneMgr->createLight()->setPosition( 20, 80, 200 ); // 灯光
    gF3DParams.mCharaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    if ( isCharaWinCreated == false )
    {
        // 角色图片按钮的Imageset创建
        CEGUI::ImagesetManager::getSingleton().create( "char_image.imageset" );
        // 载入角色创建窗口
        myGuiSys->cegui_LoadLayout( "CharaCreateWindow" );
        myGuiSys->cegui_GetWindow( "StartBtn" )->hide();
        // 创建图片资源
        GuiSystem::cegui_CreateImageset( "CharaIntroA", "chara_introa.jpg" );
        GuiSystem::cegui_CreateImageset( "CharaIntroB", "chara_introb.jpg" );
        GuiSystem::cegui_CreateImageset( "CharaIntroC", "chara_introc.jpg" );
        // 从XML载入动画
        CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML( "Intro_Anim.xml" );

        // 创建角色事件
        GuiSystem::cegui_SubscribeEvent( "CharaImgBtnA", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::charaSelectedHandler, this ) );
        GuiSystem::cegui_SubscribeEvent( "CharaImgBtnB", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::charaSelectedHandler, this ) );
        GuiSystem::cegui_SubscribeEvent( "CharaImgBtnC", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::charaSelectedHandler, this ) );
        // 当输入框中的文本变化时触发的事件
        GuiSystem::cegui_SubscribeEvent( "NameInputBox", CEGUI::Editbox::EventTextChanged,
                                         CEGUI::Event::Subscriber( &OgreApp::inputAcceptedHandler, this ) );
        // 开始按钮事件
        GuiSystem::cegui_SubscribeEvent( "StartBtn", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::startHandler, this ) );
        // 返回主界面按钮事件
        GuiSystem::cegui_SubscribeEvent( "BackToMainBtn", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::backToMain, this ) );
        // 鼠标移入模型区事件
        GuiSystem::cegui_SubscribeEvent( "CharaArea", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::enterCharaArea, this ) );
        // 鼠标移出模型区事件
        GuiSystem::cegui_SubscribeEvent( "CharaArea", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::leaveCharaArea, this ) );
    }
    else
    {
        myGuiSys->cegui_LoadLayout( "IntroWindow" ); // 场景开始，载入介绍GUI
        // 重置介绍文本窗口的Alpha，以符合下面循环的跳出条件
        myGuiSys->cegui_GetWindow( "IntroText" )->setAlpha( 1 );
        myGuiSys->cegui_LoadLayout( "CharaCreateWindow" );
        myGuiSys->cegui_GetWindow( "NameInputBox" )->setText( "" );
        myGuiSys->cegui_GetWindow( "CharaDetailText" )->setText(
            ( CEGUI::utf8* )Ogre::UTFString( L"创建人物" ).asUTF8_c_str() );
    }

    mRoot->clearEventTimes();
    while ( gPhaseMark != MainMenu )
    {
        if ( !renderOneFrame() )
            break;

        if ( myGuiSys->cegui_GetGuiWindowMgr()->isWindowPresent( "IntroText" ) )
            if ( myGuiSys->cegui_GetWindow( "IntroText" )->getAlpha() < 0.5f )
                gPhaseMark = FinishIntro;
        if ( gPhaseMark == FinishIntro )
            break;
    }

    if ( gF3DParams.mContinue == true )
    {
        if ( gPhaseMark == MainMenu )
            setupMainMenu();
        else
            setupGamingUI();
    }
}

void OgreApp::createTrackAnimation()
{
	// 设置3秒的动画
	Animation* anim = mSceneMgr->createAnimation("CameraTrack", 3);
	// 设置动画的Translation变化模式为样条线变化
	anim->setInterpolationMode(Animation::IM_SPLINE);
	// 创建节点轨迹动画
	NodeAnimationTrack* track = anim->createNodeTrack(0, mCamera->getParentSceneNode());
	// 关键帧信息
	track->createNodeKeyFrame(0)->setTranslate(Vector3(0, 0, 230));
	track->createNodeKeyFrame(1)->setTranslate(Vector3(-15, 0, 120));
	track->createNodeKeyFrame(2)->setTranslate(Vector3(-20, 0, 90));
	track->createNodeKeyFrame(3)->setTranslate(Vector3(-22, 0, 70));
	gF3DParams.mAnimState = mSceneMgr->createAnimationState("CameraTrack");
}

void OgreApp::createParticle()
{
	// 创建一个粒子系统
	Ogre::ParticleSystem* particle = mSceneMgr->createParticleSystem("chara_particle", "chara_particle");
	SceneNode* particleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	particleNode->attachObject(particle);
	particleNode->setPosition(0, -25, 0);
}

void OgreApp::createChara( CharaType charaType )
{
    // 因为只用一个场景节点绑定对象，所以这里要重置所有位置、方位、和缩放参数
    gF3DParams.mCharaNode->detachAllObjects();
    gF3DParams.mCharaNode->resetOrientation();
    gF3DParams.mCharaNode->setPosition( 0, 0, 0 );
    gF3DParams.mCharaNode->setScale( 0, 0, 0 );
    // 根据角色类型创建角色，并设定参数使得角色正好在屏幕中央出现且大小适中。
    switch ( charaType )
    {
    case CHARA_A:
        mCharaType = CHARA_A;
        gF3DParams.mCharaNode->attachObject( mCharaEntA );
        gF3DParams.mCharaNode->setScale( 30, 30, 30 );
        gF3DParams.mCharaNode->setPosition( 170, 100, 0 );
        // sinbad有上下2部分的动画，所以这里分开使用
        gF3DParams.mCharaAnimState = mCharaEntA->getAnimationState( "IdleBase" );
        gF3DParams.mBackupCharaAnimState = mCharaEntA->getAnimationState( "IdleTop" );
        gF3DParams.mBackupCharaAnimState->setLoop( true );
        gF3DParams.mBackupCharaAnimState->setEnabled( true );
        break;

    case CHARA_B:
        mCharaType = CHARA_B;
        gF3DParams.mCharaNode->attachObject( mCharaEntB );
        gF3DParams.mCharaNode->setScale( 7, 7, 7 );
        gF3DParams.mCharaNode->setPosition( 100, -15, 0 );
        gF3DParams.mCharaNode->yaw( Ogre::Degree( 180 ) );
        gF3DParams.mCharaAnimState = 0;//mCharaEntB->getAnimationState("Turn");
        gF3DParams.mBackupCharaAnimState = 0;
        break;

    case CHARA_C:
        mCharaType = CHARA_C;
        gF3DParams.mCharaNode->attachObject( mCharaEntC );
        gF3DParams.mCharaNode->setScale( 1.5, 1.5, 1.5 );
        gF3DParams.mCharaNode->setPosition( 170, -55, 0 );
        gF3DParams.mCharaNode->yaw( Ogre::Degree( 180 ) );
        gF3DParams.mCharaAnimState = 0;//mCharaEntC->getAnimationState("Idle3");
        gF3DParams.mBackupCharaAnimState = 0;
        break;
    }
    if ( gF3DParams.mCharaAnimState )
    {
        gF3DParams.mCharaAnimState->setLoop( true );
        gF3DParams.mCharaAnimState->setEnabled( true );
    }
    gF3DParams.mCharaNode->setVisible( true );
}

void OgreApp::setupGamingUI()
{
    gPhaseMark = BeginScene;

    myGuiSys->cegui_LoadLayout( "GamingUI", false );
    GuiSystem::cegui_SubscribeEvent( "GamingUI/QuitWin/Quit", CEGUI::PushButton::EventMouseClick,
                                     CEGUI::Event::Subscriber( &OgreApp::QuitGame, this ) );
    GuiSystem::cegui_SubscribeEvent( "GamingUI/QuitWin/ToMain", CEGUI::PushButton::EventMouseClick,
                                     CEGUI::Event::Subscriber( &OgreApp::backToMain, this ) );
    GuiSystem::cegui_SubscribeEvent( "GamingUI/QuitWin/Cancel", CEGUI::PushButton::EventMouseClick,
                                     CEGUI::Event::Subscriber( &OgreApp::backGaming, this ) );
    gF3DParams.mExitUI = true; // 关闭游戏UI

    init3dScene();
}


// ---------------------------以下为GUI控件事件响应函数-----------------------------------------//

bool OgreApp::mainMenuBtnHover( const CEGUI::EventArgs& e )
{
    // 根据参数e得到获得事件的窗口
    const CEGUI::WindowEventArgs& windowArgs = static_cast<const CEGUI::WindowEventArgs&>( e );
    CEGUI::String buttonName = windowArgs.window->getName();
    //node->scale(1, 1, 1);
    if ( buttonName == "MainMenu/Start/Star" )
    {
        node->setPosition( 370, 100, -200 );
        ent->setMaterialName( "MainMenu/Start" );
        myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->setAlpha( 0 );
        myGuiSys->cegui_SetProperty( "MainMenu/ShootingStar", "UnifiedAreaRect",
                                     "{{0.784,0},{0.25,0},{0.998,0},{0.50,0}}" ); //{0.78,0},{0.3,0},{0.968,0},{0.45,0}
        myGuiSys->cegui_SetProperty( "MainMenu/Label", "UnifiedAreaRect",
                                     "{{0.784,0},{0.25,0},{0.998,0},{0.50,0}}" );
        myGuiSys->cegui_GetWindow( "MainMenu/Label/Text" )->setText( "New Game" );
    }
    else if ( buttonName == "MainMenu/Load/Star" )
    {
        node->setPosition( 340, -20, -200 );
        ent->setMaterialName( "MainMenu/Load" );
        myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->setAlpha( 0 );
        myGuiSys->cegui_SetProperty( "MainMenu/ShootingStar", "UnifiedAreaRect",
                                     "{{0.774,0},{0.4,0},{0.988,0},{0.65,0}}" ); //{0.77,0},{0.45,0},{0.958,0},{0.6,0}
        myGuiSys->cegui_SetProperty( "MainMenu/Label", "UnifiedAreaRect",
                                     "{{0.774,0},{0.4,0},{0.988,0},{0.65,0}}" );
        myGuiSys->cegui_GetWindow( "MainMenu/Label/Text" )->setText( "Load Game" );
    }
    else if ( buttonName ==  "MainMenu/Setup/Star" )
    {
        node->setPosition( 310, -140, -200 );
        ent->setMaterialName( "MainMenu/Setup" );
        myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->setAlpha( 0 );
        myGuiSys->cegui_SetProperty( "MainMenu/ShootingStar", "UnifiedAreaRect",
                                     "{{0.754,0},{0.57,0},{0.968,0},{0.82,0}}" ); //{0.75,0},{0.6,0},{0.938,0},{0.75,0}
        myGuiSys->cegui_SetProperty( "MainMenu/Label", "UnifiedAreaRect",
                                     "{{0.754,0},{0.57,0},{0.968,0},{0.82,0}}" );
        myGuiSys->cegui_GetWindow( "MainMenu/Label/Text" )->setText( "Setup" );
    }
    else if ( buttonName == "MainMenu/Quit/Star" )
    {
        node->setPosition( 275, -260, -200 );
        ent->setMaterialName( "MainMenu/Quit" );
        myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->setAlpha( 0 );
        myGuiSys->cegui_SetProperty( "MainMenu/ShootingStar", "UnifiedAreaRect",
                                     "{{0.724,0},{0.73,0},{0.938,0},{0.98,0}}" ); //{0.72,0},{0.75,0},{0.908,0},{0.9,0}
        myGuiSys->cegui_SetProperty( "MainMenu/Label", "UnifiedAreaRect",
                                     "{{0.724,0},{0.73,0},{0.938,0},{0.98,0}}" );
        myGuiSys->cegui_GetWindow( "MainMenu/Label/Text" )->setText( "Quit Game" );

    }
    animInst2->start();
    ent->setVisible( true );
    myGuiSys->cegui_GetWindow( "MainMenu/Label" )->show();
    return true;
}

bool OgreApp::mainMenuBtnBack( const CEGUI::EventArgs& e )
{
    const CEGUI::WindowEventArgs& windowArgs = static_cast<const CEGUI::WindowEventArgs&>( e );
    CEGUI::String buttonName = windowArgs.window->getName();
    windowArgs.window->setAlpha( 1 );
    ent->setVisible( false );
    myGuiSys->cegui_GetWindow( "MainMenu/Label" )->hide();
    return true;
}

bool OgreApp::mainMenuBtnDwn( const CEGUI::EventArgs& e )
{
    const CEGUI::WindowEventArgs& windowArgs = static_cast<const CEGUI::WindowEventArgs&>( e );
    CEGUI::String buttonName = windowArgs.window->getName();
    if ( buttonName == "MainMenu/Start/Star" )
    {
//		myGuiSys->cegui_GetWindow("MainMenu/Waiting")->show();
        gPhaseMark = CreateChara;
    }
    else if ( buttonName == "MainMenu/Load/Star" )
    {
        myGuiSys->cegui_GetWindow( "MainMenu/NotReady" )->show();
        myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->disable();
        CEGUI::MouseCursor::getSingleton().setPosition( CEGUI::Vector2(
                    mWindow->getWidth() / 2, mWindow->getHeight() / 2 ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseClick, // 取消响应
                                         CEGUI::Event::Subscriber( &OgreApp::CancelReady, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::NotReadyWarn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::StopWarn, this ) );
    }
    else if ( buttonName ==  "MainMenu/Setup/Star" )
    {
        myGuiSys->cegui_GetWindow( "MainMenu/NotReady" )->show();
        myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->disable();
        CEGUI::MouseCursor::getSingleton().setPosition( CEGUI::Vector2(
                    mWindow->getWidth() / 2, mWindow->getHeight() / 2 ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseClick, // 取消响应
                                         CEGUI::Event::Subscriber( &OgreApp::CancelReady, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::NotReadyWarn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::StopWarn, this ) );
    }
    else if ( buttonName == "MainMenu/Quit/Star" )
    {
        myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->show();
        myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->disable();
        myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->disable();
        CEGUI::MouseCursor::getSingleton().setPosition( CEGUI::Vector2(
                    mWindow->getWidth() / 2, mWindow->getHeight() / 2 ) );
    }
    return true;
}

bool OgreApp::QuitGame( const CEGUI::EventArgs& e )
{
    gF3DParams.mContinue = false;
    return true;
}

bool OgreApp::CancelQuit( const CEGUI::EventArgs& e )
{
    myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->hide();
    myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->enable();
    myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->enable();
    myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->enable();
    myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->enable();
    return true;
}

bool OgreApp::CancelReady( const CEGUI::EventArgs& e )
{
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady/Text" )->setText(
        ( CEGUI::utf8* )Ogre::UTFString( L"没做好呢！急什么急！" ).asUTF8_c_str() );
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady" )->hide();
    myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->enable();
    myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->enable();
    myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->enable();
    myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->enable();
    return true;
}

bool OgreApp::NotReadyWarn( const CEGUI::EventArgs& e )
{
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady/Text" )->setText( ( CEGUI::utf8* )Ogre::UTFString(
                L"警告：按此键将会发生不可预测之灾难，一切责任本游戏概不负责。" ).asUTF8_c_str()
                                                                  );
    return true;
}

bool OgreApp::StopWarn( const CEGUI::EventArgs& e )
{
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady/Text" )->setText(
        ( CEGUI::utf8* )Ogre::UTFString( L"没做好呢！急什么急！" ).asUTF8_c_str() );
    return true;
}

bool OgreApp::charaSelectedHandler( const CEGUI::EventArgs& e )
{
    // 根据参数e得到获得事件的窗口
    const CEGUI::WindowEventArgs& windowArgs = static_cast<const CEGUI::WindowEventArgs&>( e );
    CEGUI::String charaType = windowArgs.window->getName();
    CEGUI::String charaDetail;
    if ( charaType == "CharaImgBtnA" )
    {
        charaDetail = ( CEGUI::utf8* )Ogre::UTFString( L"花似伊，柳似伊" ).asUTF8_c_str();
        createChara( CHARA_A );
    }
    if ( charaType == "CharaImgBtnB" )
    {
        charaDetail = ( CEGUI::utf8* )Ogre::UTFString( L"老夫聊发少年狂" ).asUTF8_c_str();
        createChara( CHARA_B );
    }
    if ( charaType == "CharaImgBtnC" )
    {
        charaDetail = ( CEGUI::utf8* )Ogre::UTFString( L"千里茫茫若梦，双眸粲粲如星" ).asUTF8_c_str();
        createChara( CHARA_C );
    }
    myGuiSys->cegui_GetWindow( "CharaDetailText" )->setText( charaDetail );
    // 是否显示“开始游戏”按钮
    inputAcceptedHandler( e );
    return true;
}

bool OgreApp::startHandler( const CEGUI::EventArgs& e )
{
    gPhaseMark = IntroChara;
    mySoundSys.fmod_StopSound( 0 ); // 停止播放主题曲
    // 清理工作
    //mSceneMgr->clearScene();
    // 清除指针，否则会有退出错误
    //gF3DParams.mCharaAnimState = gF3DParams.mBackupCharaAnimState = 0;
    myGuiSys->cegui_LoadLayout( "IntroWindow" ); // 场景开始，载入介绍GUI
    myGuiSys->cegui_ShowGuiCursor( false ); // 隐藏鼠标
    CEGUI::String str = ""; // 介绍文本
    switch ( mCharaType )
    {
    case CHARA_A:
        GuiSystem::cegui_SetProperty( "IntroTopImg", "Image", "set: CharaIntroA image: full_image" );
        str = ( CEGUI::utf8* )Ogre::UTFString
              ( L"很久很久以前........\n\n在神界的神树上......\n\n结出了一个\n\n雪见......" ).asUTF8_c_str();
        break;
    case CHARA_B:
        GuiSystem::cegui_SetProperty( "IntroTopImg", "Image", "set: CharaIntroB image: full_image" );
        str = ( CEGUI::utf8* )Ogre::UTFString
              ( L"很久很久以前........\n\n在中土的大地上\n\n人类与神龙\n\n展开生死决战......\n\n\n龙裔\n\n神龙的血脉......" )
              .asUTF8_c_str();
        break;
    case  CHARA_C:
        GuiSystem::cegui_SetProperty( "IntroTopImg", "Image", "set: CharaIntroC image: full_image" );
        str = ( CEGUI::utf8* )Ogre::UTFString
              ( L"很久很久以前........\n\n\n\n\n\n\n\n\n\n巧笑倩兮，美目盼兮......\n\n\n\n\n\n\n\n\n\n\n\其实......\n\n这个故事......\n\n我也\n\n不\n\n知\n\n道......" )
              .asUTF8_c_str();
        break;
    }
    myGuiSys->cegui_GetWindow( "IntroText" )->setText( str );
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "IntroTextAnim" ); // 文字运动动画
    CEGUI::AnimationInstance* animInstX = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInstX->setTargetWindow( myGuiSys->cegui_GetWindow( "IntroText" ) );
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "IntroTextPanel" ); // 文字底板动画
    CEGUI::AnimationInstance* animInstX2 = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInstX2->setTargetWindow( myGuiSys->cegui_GetWindow( "IntroBottomImg" ) );
    animInstX->start();
    animInstX2->start();
    return true;
}

bool OgreApp::inputAcceptedHandler( const CEGUI::EventArgs& e )
{
    mCharaName = myGuiSys->cegui_GetWindow( "NameInputBox" )->getText().c_str();
    CEGUI::String mCharaDetailText = myGuiSys->cegui_GetWindow( "CharaDetailText" )->getText();
    CEGUI::String str = ( CEGUI::utf8* )Ogre::UTFString( L"创建人物" ).asUTF8_c_str();
    if ( ( mCharaName != "" ) && ( mCharaDetailText != str ) )
    {
        // 若输入框有文本且已选择角色，则显示开始按钮
        myGuiSys->cegui_GetWindow( "StartBtn" )->show();
    }
    else
        // 否则隐藏按钮
        myGuiSys->cegui_GetWindow( "StartBtn" )->hide();
    return true;
}

bool OgreApp::backToMain( const CEGUI::EventArgs& e )
{
    if ( gPhaseMark == BeginScene )
    {
        mySoundSys.fmod_StopSound( SpaceSound );
        mySoundSys.fmod_CreateSound( "../media/sounds/Halo Theme Mjolnir.mp3",
                                     FMOD_LOOP_NORMAL, 0 );
        mySoundSys.fmod_PlaySound( 0, false );
    }
    gPhaseMark = MainMenu;
    isCharaWinCreated = true;
//	gF3DParams.mCharaNode->setVisible(false);
//	setupMainMenu();
    return true;
}

bool OgreApp::enterCharaArea( const CEGUI::EventArgs& e )
{
    isCharaRollable = true;
    CEGUI::MouseCursor::getSingleton().setExplicitRenderSize( CEGUI::Size( 64, 32 ) );
    myGuiSys->cegui_SetDefaultMouseCursor( "Xianjian", "RotateCur" );
    return true;
}

bool OgreApp::leaveCharaArea( const CEGUI::EventArgs& e )
{
    isCharaRollable = false;
    CEGUI::MouseCursor::getSingleton().setExplicitRenderSize( CEGUI::Size( 32, 32 ) );
    myGuiSys->cegui_SetDefaultMouseCursor( "Xianjian", "Xj4MainCur" );
    return true;
}

bool OgreApp::backGaming( const CEGUI::EventArgs& e )
{
    myGuiSys->cegui_GetWindow( "Root_GamingUI" )->hide();
    myGuiSys->cegui_ShowGuiCursor( false );
    gF3DParams.mExitUI = true;
    mySoundSys.fmod_GoOnSound( SpaceSound );
    return true;
}


















// bool OgreApp::quit(const CEGUI::EventArgs& e)
// {
// 	gF3DParams.mContinue = false;
// 	return true;
// }
//
// bool OgreApp::know(const CEGUI::EventArgs& e)
// {
// 	myGuiSys->cegui_GetWindow("DialogWindow")->hide();
// 	gF3DParams.mStartTrack = false;
// 	gF3DParams.mExitUI = false;
// 	return true;
// }

/************************************************************************/
/* 测试代码                                                                     */
/************************************************************************/
// 	myGuiSys->cegui_LoadLayout("DialogWindow");
// //	myGuiSys->cegui_LoadLayout("MyRoot");
// 	// 设置图片资源
// 	GuiSystem::cegui_CreateImageset("bgImg", "bg.jpg");
// 	GuiSystem::cegui_CreateImageset("npcpic", "npcpic.png");
// 	// 设置图片属性，并添加给Static Image类型的窗口
// //	GuiSystem::cegui_SetProperty("Root/BgImg", "Image", "set:bgImg image:full_image");
// //	GuiSystem::cegui_SetProperty("DialogWindow/NPCPic", "Image", "set:npcpic image:full_image");
// 	// 一开始隐藏ESCAPE的UI
// //	myGuiSys->cegui_GetWindow("MyRoot")->hide();
// 	// 对话框设置
// 	CEGUI::MultiLineEditbox* dialogBox = static_cast<CEGUI::MultiLineEditbox*>(myGuiSys
// 		->cegui_GetWindow("DialogWindow/DialogBgImg/DialogText"));
// 	dialogBox->setSize(CEGUI::UVector2(cegui_reldim(0.5f), cegui_reldim(0.25f)));
// 	//dialogBox->hide();
// 	// 只读，无法编辑
// 	dialogBox->setReadOnly(true);
// //	dialogBox->setWordWrapping(true);
// 	CEGUI::String str = (CEGUI::utf8*)Ogre::UTFString(L"你好，朋友，我是你的家乡地球，有什么可以帮忙的吗？").asUTF8_c_str();
// 	dialogBox->setText(str);
// 	// 从XML载入动画
// 	//CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("ExitUI_Anim.xml");
// 	CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("Dialog_Anim.xml");


