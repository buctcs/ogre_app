#include "OgreApp.h"

void OgreApp::gameProgress( void )
{
    // ������Ϸ��ʼʱ��GUI
    setupStartGui();

    // ������ѡ��
    isMainCreated = false;
    isCharaWinCreated = false;
    setupMainMenu();
}

//-----------------------------����Ϊ3d��Ϸ������ʼ�����ʵ��-----------------------------------//

void OgreApp::init3dScene( void )
{
    mSceneMgr->destroyAllLights();
    mSceneMgr->destroyAllEntities();
    mSceneMgr->destroySceneNode( gF3DParams.EarthNode );

    // ����̫��ʵ��
   

    // ��Ч
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
        setupMainMenu(); // �������˵�
}


//----------------------����ΪGUI��ʼ�����ʵ��-------------------------------------------//

void OgreApp::setupStartGui()
{

    // ��ʼ����Դ
    CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme","Schemes" );
    CEGUI::Font* font = &CEGUI::FontManager::getSingleton().create( "Xianjian.font" );
    myGuiSys->cegui_GetSystem()->setDefaultFont( font );
    CEGUI::ImagesetManager::getSingleton().create( "Xianjian.imageset" );
    myGuiSys->cegui_GetSystem()->setDefaultMouseCursor( "Xianjian", "Xj4MainCur" );
    CEGUI::MouseCursor::getSingleton().setExplicitRenderSize( CEGUI::Size( 32, 32 ) );

	if (gPhaseMark == HealthyGaming)
	{
		myGuiSys->cegui_ShowGuiCursor(false); // ����o���
		// ���롢����ͼƬ��
		myGuiSys->cegui_CreateImageset("HealthyGaming", "healthyGaming.jpg");
		CEGUI::ImagesetManager::getSingleton().create("startGui.imageset");
		myGuiSys->cegui_CreateImageset("FinalLogo", "finalLogo.jpg");
		// ����StartGui����
		myGuiSys->cegui_LoadLayout("StartGui");
		// ��XML���붯��
		CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("StartGui_Anim.xml","Animations");
		gPhaseMark = HealthyGaming;
		// ������Ϸ���涯��
		// �õ�����
		anim = CEGUI::AnimationManager::getSingleton().getAnimation("HealthyGaming");
		// ʵ��������
		animInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation(anim);
		// ������Ӧ�ô���
		animInst->setTargetWindow(myGuiSys->cegui_GetWindow("Start/HealthyGaming"));
		// ������ʼ
		animInst->start();
		mRoot->clearEventTimes();
		// ��Ⱦѭ��
		while (animInst->isRunning() /*&& gPhaseMark == HealthyGaming*/)
		{
			if (!renderOneFrame())
				break;
		}
	}

	// ����final��־����
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
		for (int i = 0; i < 9; i ++) // logo��Ծ�����ĳ�ʼ��
			mySoundSys.fmod_CreateSound("../media/sounds/logo jump.mp3",
			FMOD_LOOP_NORMAL, i);
		//	mySoundSys.fmod_CreateSound("../media/sounds/plantgrow.wav",
		//		FMOD_LOOP_NORMAL, 9);
		mRoot->clearEventTimes();
		while ((animInstX[0]->isRunning() || animInst->isRunning()) /*&& gPhaseMark == FinalLogo*/)
		{
			if (!renderOneFrame())
				break;

			if (animInst->getPosition() > 0.4) // ������Ծ���������ŵ�ʱ���ӳ�0.05s��
				mySoundSys.fmod_PlaySound();
			if (animInst->getPosition() > 1.3)
				mySoundSys.fmod_PlaySound(1);
			if (animInst->getPosition() > 2.2)
				mySoundSys.fmod_PlaySound(2);
			if (animInst->getPosition() > 3.1)
				mySoundSys.fmod_PlaySound(3);
			if (animInst->getPosition() > 0.31) // ����
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
		// 	for (int i = 0; i < 10; i ++) // ����ָ��
		// 		if (animInstX[i])
		// 			delete animInstX[i];
	}

	// ����ogre��־����
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
    // ������ѡ��
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
        anim = CEGUI::AnimationManager::getSingleton().getAnimation( "OgreSystem" ); // ����
        animInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
        animInst->setTargetWindow( myGuiSys->cegui_GetWindow( "MainMenu/OgreSystem" ) );
        animInst->start();
    }
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "ShootingStar" ); // ����Ч��
    animInst2 = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInst2->setTargetWindow( myGuiSys->cegui_GetWindow( "MainMenu/ShootingStar" ) );
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "EggCross" ); // �ʵ�����
    animInst3 = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInst3->setTargetWindow( myGuiSys->cegui_GetWindow( "MainMenu/Egg" ) );
    gF3DParams.eggCount = 0; // �ʵ���������ֵ
    myGuiSys->cegui_GetWindow( "MainMenu/Label" )->hide(); // ���ر�ǩ
    myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->hide(); // �����˳�����
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady" )->hide(); // ���ء���·��ͨ������
    myGuiSys->cegui_GetWindow( "MainMenu/Waiting" )->hide(); // ���صȴ�����

//	mSceneMgr->destroyAllLights();
//	mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();
//	if (gF3DParams.EarthNode)
//		mSceneMgr->destroySceneNode(gF3DParams.EarthNode);
    // ����ģ�ͣ���Ϊ����
    gF3DParams.EarthNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "EarthNode" );
    gF3DParams.Earth = mSceneMgr->createEntity( "EarthModel", "Earth.mesh" );
    gF3DParams.Earth->setMaterialName( "Earth/Surface" );
    gF3DParams.EarthNode->attachObject( gF3DParams.Earth );
    gF3DParams.EarthNode->scale( 0.000043f, 0.000043f, 0.000043f );
    gF3DParams.EarthNode->setPosition( -300.0f, 0.0f, 0.0f );
    gF3DParams.EarthNode->roll( Degree( -703 / 30 ), Node::TS_LOCAL ); // �Ƴཻ��ƽ��Ϊ23��26��
    SceneNode* nodeX = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // ����������
    // ��������ʵ��
//  	gF3DParams.MoonNode = gF3DParams.EarthNode->createChildSceneNode("MoonNode", Vector3(670.0f, 100.0f, -200.0f));
//  	Entity* mMoon = mSceneMgr->createEntity(SceneManager::PT_SPHERE);
//  	mMoon->setMaterialName("Moon/MoonSurface");
//  	gF3DParams.MoonNode->attachObject(mMoon);
// 	gF3DParams.MoonNode->setInheritScale(false);
//	if (isMainCreated == false)
    mSceneMgr->getRootSceneNode()->createChildSceneNode( "CamNode" )->attachObject( mCamera ); // ���������λ��
    mCamera->getParentSceneNode()->resetOrientation();
    mCamera->getParentSceneNode()->scale( 1, 1, 1 );
    mCamera->getParentSceneNode()->setPosition( 0, 0, 230 );
    mSceneMgr->setAmbientLight( ColourValue( 0.25, 0.25, 0.25 ) ); // ������
    mSceneMgr->setShadowTechnique( SHADOWTYPE_STENCIL_ADDITIVE ); // ���üӳ�ģ����Ӱ
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // С����ڵ�
    ent = mSceneMgr->createEntity( SceneManager::PT_SPHERE ); // С����
    node->attachObject( ent );
    ent->setVisible( false ); // ����ģ��
    if ( isMainCreated == false )
    {
        // ��ť��Ӧ
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Start/Star", CEGUI::Window::EventMouseEnters, // ������밴ť
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Load/Star", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Setup/Star", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Quit/Star", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnHover, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Start/Star", CEGUI::Window::EventMouseLeaves, // ����Ƴ���ť
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Load/Star", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Setup/Star", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Quit/Star", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnBack, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Start/Star", CEGUI::Window::EventMouseClick, // �����ť��ť
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Load/Star", CEGUI::Window::EventMouseClick,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Setup/Star", CEGUI::Window::EventMouseClick,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/Quit/Star", CEGUI::Window::EventMouseClick,
                                         CEGUI::Event::Subscriber( &OgreApp::mainMenuBtnDwn, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/QuitWin/Quit", CEGUI::PushButton::EventMouseClick, // �˳���Ϸ��Ӧ
                                         CEGUI::Event::Subscriber( &OgreApp::QuitGame, this ) );
        GuiSystem::cegui_SubscribeEvent( "MainMenu/QuitWin/Cancel", CEGUI::PushButton::EventMouseClick, // ȡ���˳���Ϸ��Ӧ
                                         CEGUI::Event::Subscriber( &OgreApp::CancelQuit, this ) );

        // ������
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

    // ��ʼ��3d����
    if ( gF3DParams.mContinue == true )
        setupCharaGui();
}

void OgreApp::setupCharaGui()
{

//	myGuiSys->cegui_ShowGuiCursor(true);

    gPhaseMark = CreateChara;
    isCharaRollable = false; // ģ�Ͳ�����ת
    // ������ɫGUI��ʹ�õ�ģ��
    mCharaEntA = mSceneMgr->createEntity( "sinbad", "sinbad.mesh" );
    mCharaEntB = mSceneMgr->createEntity( "jaiqua", "jaiqua.mesh" );
    mCharaEntC = mSceneMgr->createEntity( "ninja", "ninja.mesh" );
    mSceneMgr->createLight()->setPosition( 20, 80, 200 ); // �ƹ�
    gF3DParams.mCharaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    if ( isCharaWinCreated == false )
    {
        // ��ɫͼƬ��ť��Imageset����
        CEGUI::ImagesetManager::getSingleton().create( "char_image.imageset" );
        // �����ɫ��������
        myGuiSys->cegui_LoadLayout( "CharaCreateWindow" );
        myGuiSys->cegui_GetWindow( "StartBtn" )->hide();
        // ����ͼƬ��Դ
        GuiSystem::cegui_CreateImageset( "CharaIntroA", "chara_introa.jpg" );
        GuiSystem::cegui_CreateImageset( "CharaIntroB", "chara_introb.jpg" );
        GuiSystem::cegui_CreateImageset( "CharaIntroC", "chara_introc.jpg" );
        // ��XML���붯��
        CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML( "Intro_Anim.xml" );

        // ������ɫ�¼�
        GuiSystem::cegui_SubscribeEvent( "CharaImgBtnA", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::charaSelectedHandler, this ) );
        GuiSystem::cegui_SubscribeEvent( "CharaImgBtnB", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::charaSelectedHandler, this ) );
        GuiSystem::cegui_SubscribeEvent( "CharaImgBtnC", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::charaSelectedHandler, this ) );
        // ��������е��ı��仯ʱ�������¼�
        GuiSystem::cegui_SubscribeEvent( "NameInputBox", CEGUI::Editbox::EventTextChanged,
                                         CEGUI::Event::Subscriber( &OgreApp::inputAcceptedHandler, this ) );
        // ��ʼ��ť�¼�
        GuiSystem::cegui_SubscribeEvent( "StartBtn", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::startHandler, this ) );
        // ���������水ť�¼�
        GuiSystem::cegui_SubscribeEvent( "BackToMainBtn", CEGUI::PushButton::EventClicked,
                                         CEGUI::Event::Subscriber( &OgreApp::backToMain, this ) );
        // �������ģ�����¼�
        GuiSystem::cegui_SubscribeEvent( "CharaArea", CEGUI::Window::EventMouseEnters,
                                         CEGUI::Event::Subscriber( &OgreApp::enterCharaArea, this ) );
        // ����Ƴ�ģ�����¼�
        GuiSystem::cegui_SubscribeEvent( "CharaArea", CEGUI::Window::EventMouseLeaves,
                                         CEGUI::Event::Subscriber( &OgreApp::leaveCharaArea, this ) );
    }
    else
    {
        myGuiSys->cegui_LoadLayout( "IntroWindow" ); // ������ʼ���������GUI
        // ���ý����ı����ڵ�Alpha���Է�������ѭ������������
        myGuiSys->cegui_GetWindow( "IntroText" )->setAlpha( 1 );
        myGuiSys->cegui_LoadLayout( "CharaCreateWindow" );
        myGuiSys->cegui_GetWindow( "NameInputBox" )->setText( "" );
        myGuiSys->cegui_GetWindow( "CharaDetailText" )->setText(
            ( CEGUI::utf8* )Ogre::UTFString( L"��������" ).asUTF8_c_str() );
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
	// ����3��Ķ���
	Animation* anim = mSceneMgr->createAnimation("CameraTrack", 3);
	// ���ö�����Translation�仯ģʽΪ�����߱仯
	anim->setInterpolationMode(Animation::IM_SPLINE);
	// �����ڵ�켣����
	NodeAnimationTrack* track = anim->createNodeTrack(0, mCamera->getParentSceneNode());
	// �ؼ�֡��Ϣ
	track->createNodeKeyFrame(0)->setTranslate(Vector3(0, 0, 230));
	track->createNodeKeyFrame(1)->setTranslate(Vector3(-15, 0, 120));
	track->createNodeKeyFrame(2)->setTranslate(Vector3(-20, 0, 90));
	track->createNodeKeyFrame(3)->setTranslate(Vector3(-22, 0, 70));
	gF3DParams.mAnimState = mSceneMgr->createAnimationState("CameraTrack");
}

void OgreApp::createParticle()
{
	// ����һ������ϵͳ
	Ogre::ParticleSystem* particle = mSceneMgr->createParticleSystem("chara_particle", "chara_particle");
	SceneNode* particleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	particleNode->attachObject(particle);
	particleNode->setPosition(0, -25, 0);
}

void OgreApp::createChara( CharaType charaType )
{
    // ��Ϊֻ��һ�������ڵ�󶨶�����������Ҫ��������λ�á���λ�������Ų���
    gF3DParams.mCharaNode->detachAllObjects();
    gF3DParams.mCharaNode->resetOrientation();
    gF3DParams.mCharaNode->setPosition( 0, 0, 0 );
    gF3DParams.mCharaNode->setScale( 0, 0, 0 );
    // ���ݽ�ɫ���ʹ�����ɫ�����趨����ʹ�ý�ɫ��������Ļ��������Ҵ�С���С�
    switch ( charaType )
    {
    case CHARA_A:
        mCharaType = CHARA_A;
        gF3DParams.mCharaNode->attachObject( mCharaEntA );
        gF3DParams.mCharaNode->setScale( 30, 30, 30 );
        gF3DParams.mCharaNode->setPosition( 170, 100, 0 );
        // sinbad������2���ֵĶ�������������ֿ�ʹ��
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
    gF3DParams.mExitUI = true; // �ر���ϷUI

    init3dScene();
}


// ---------------------------����ΪGUI�ؼ��¼���Ӧ����-----------------------------------------//

bool OgreApp::mainMenuBtnHover( const CEGUI::EventArgs& e )
{
    // ���ݲ���e�õ�����¼��Ĵ���
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
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseClick, // ȡ����Ӧ
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
        GuiSystem::cegui_SubscribeEvent( "MainMenu/NotReady/Cancel", CEGUI::PushButton::EventMouseClick, // ȡ����Ӧ
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
        ( CEGUI::utf8* )Ogre::UTFString( L"û�����أ���ʲô����" ).asUTF8_c_str() );
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
                L"���棺���˼����ᷢ������Ԥ��֮���ѣ�һ�����α���Ϸ�Ų�����" ).asUTF8_c_str()
                                                                  );
    return true;
}

bool OgreApp::StopWarn( const CEGUI::EventArgs& e )
{
    myGuiSys->cegui_GetWindow( "MainMenu/NotReady/Text" )->setText(
        ( CEGUI::utf8* )Ogre::UTFString( L"û�����أ���ʲô����" ).asUTF8_c_str() );
    return true;
}

bool OgreApp::charaSelectedHandler( const CEGUI::EventArgs& e )
{
    // ���ݲ���e�õ�����¼��Ĵ���
    const CEGUI::WindowEventArgs& windowArgs = static_cast<const CEGUI::WindowEventArgs&>( e );
    CEGUI::String charaType = windowArgs.window->getName();
    CEGUI::String charaDetail;
    if ( charaType == "CharaImgBtnA" )
    {
        charaDetail = ( CEGUI::utf8* )Ogre::UTFString( L"��������������" ).asUTF8_c_str();
        createChara( CHARA_A );
    }
    if ( charaType == "CharaImgBtnB" )
    {
        charaDetail = ( CEGUI::utf8* )Ogre::UTFString( L"�Ϸ��ķ������" ).asUTF8_c_str();
        createChara( CHARA_B );
    }
    if ( charaType == "CharaImgBtnC" )
    {
        charaDetail = ( CEGUI::utf8* )Ogre::UTFString( L"ǧ��ãã���Σ�˫����������" ).asUTF8_c_str();
        createChara( CHARA_C );
    }
    myGuiSys->cegui_GetWindow( "CharaDetailText" )->setText( charaDetail );
    // �Ƿ���ʾ����ʼ��Ϸ����ť
    inputAcceptedHandler( e );
    return true;
}

bool OgreApp::startHandler( const CEGUI::EventArgs& e )
{
    gPhaseMark = IntroChara;
    mySoundSys.fmod_StopSound( 0 ); // ֹͣ����������
    // ������
    //mSceneMgr->clearScene();
    // ���ָ�룬��������˳�����
    //gF3DParams.mCharaAnimState = gF3DParams.mBackupCharaAnimState = 0;
    myGuiSys->cegui_LoadLayout( "IntroWindow" ); // ������ʼ���������GUI
    myGuiSys->cegui_ShowGuiCursor( false ); // �������
    CEGUI::String str = ""; // �����ı�
    switch ( mCharaType )
    {
    case CHARA_A:
        GuiSystem::cegui_SetProperty( "IntroTopImg", "Image", "set: CharaIntroA image: full_image" );
        str = ( CEGUI::utf8* )Ogre::UTFString
              ( L"�ܾúܾ���ǰ........\n\n������������......\n\n�����һ��\n\nѩ��......" ).asUTF8_c_str();
        break;
    case CHARA_B:
        GuiSystem::cegui_SetProperty( "IntroTopImg", "Image", "set: CharaIntroB image: full_image" );
        str = ( CEGUI::utf8* )Ogre::UTFString
              ( L"�ܾúܾ���ǰ........\n\n�������Ĵ����\n\n����������\n\nչ��������ս......\n\n\n����\n\n������Ѫ��......" )
              .asUTF8_c_str();
        break;
    case  CHARA_C:
        GuiSystem::cegui_SetProperty( "IntroTopImg", "Image", "set: CharaIntroC image: full_image" );
        str = ( CEGUI::utf8* )Ogre::UTFString
              ( L"�ܾúܾ���ǰ........\n\n\n\n\n\n\n\n\n\n��Цٻ�⣬��Ŀ����......\n\n\n\n\n\n\n\n\n\n\n\��ʵ......\n\n�������......\n\n��Ҳ\n\n��\n\n֪\n\n��......" )
              .asUTF8_c_str();
        break;
    }
    myGuiSys->cegui_GetWindow( "IntroText" )->setText( str );
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "IntroTextAnim" ); // �����˶�����
    CEGUI::AnimationInstance* animInstX = CEGUI::AnimationManager::getSingleton().instantiateAnimation( anim );
    animInstX->setTargetWindow( myGuiSys->cegui_GetWindow( "IntroText" ) );
    anim = CEGUI::AnimationManager::getSingleton().getAnimation( "IntroTextPanel" ); // ���ֵװ嶯��
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
    CEGUI::String str = ( CEGUI::utf8* )Ogre::UTFString( L"��������" ).asUTF8_c_str();
    if ( ( mCharaName != "" ) && ( mCharaDetailText != str ) )
    {
        // ����������ı�����ѡ���ɫ������ʾ��ʼ��ť
        myGuiSys->cegui_GetWindow( "StartBtn" )->show();
    }
    else
        // �������ذ�ť
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
/* ���Դ���                                                                     */
/************************************************************************/
// 	myGuiSys->cegui_LoadLayout("DialogWindow");
// //	myGuiSys->cegui_LoadLayout("MyRoot");
// 	// ����ͼƬ��Դ
// 	GuiSystem::cegui_CreateImageset("bgImg", "bg.jpg");
// 	GuiSystem::cegui_CreateImageset("npcpic", "npcpic.png");
// 	// ����ͼƬ���ԣ�����Ӹ�Static Image���͵Ĵ���
// //	GuiSystem::cegui_SetProperty("Root/BgImg", "Image", "set:bgImg image:full_image");
// //	GuiSystem::cegui_SetProperty("DialogWindow/NPCPic", "Image", "set:npcpic image:full_image");
// 	// һ��ʼ����ESCAPE��UI
// //	myGuiSys->cegui_GetWindow("MyRoot")->hide();
// 	// �Ի�������
// 	CEGUI::MultiLineEditbox* dialogBox = static_cast<CEGUI::MultiLineEditbox*>(myGuiSys
// 		->cegui_GetWindow("DialogWindow/DialogBgImg/DialogText"));
// 	dialogBox->setSize(CEGUI::UVector2(cegui_reldim(0.5f), cegui_reldim(0.25f)));
// 	//dialogBox->hide();
// 	// ֻ�����޷��༭
// 	dialogBox->setReadOnly(true);
// //	dialogBox->setWordWrapping(true);
// 	CEGUI::String str = (CEGUI::utf8*)Ogre::UTFString(L"��ã����ѣ�������ļ��������ʲô���԰�æ����").asUTF8_c_str();
// 	dialogBox->setText(str);
// 	// ��XML���붯��
// 	//CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("ExitUI_Anim.xml");
// 	CEGUI::AnimationManager::getSingleton().loadAnimationsFromXML("Dialog_Anim.xml");


