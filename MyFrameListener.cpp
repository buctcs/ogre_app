#include "MyFrameListener.h"

MyFrameListener::MyFrameListener( RenderWindow* win,
                                  Camera* cam, SceneManager* sceneMgr
                                  /*Final3DParams strF3DParams*/ )
    : ExampleFrameListener( win, cam, true, // ʹ�ô�����ļ�������
                            true ), // ʹ�ô�������������
    mMouseLeftClicked( false )
{

    // ���̺����״̬׷��
    //mMouseDown = false;
    //mToggle = 0.0;

    // ��ð�������ĸ��ڵ�
//	mCamNode = cam->getParentSceneNode();
    // ��ó������������
    mSceneMgr = sceneMgr;

    // ������ת���ƶ��ٶ�
    mRotate = 0.13;
    mMove = 1500000;

    // ������Ⱦ��ֵ
    gF3DParams.mContinue = true;

    // ��֡������ע��Ϊ��ꡢ���̺��ֱ�������
    if ( mMouse )
        mMouse->setEventCallback( this );
    if ( mKeyboard )
        mKeyboard->setEventCallback( this );
    if ( mJoy )
        mJoy->setEventCallback( this );

    // ��ʼ���ƶ���������Ϊ0����
    mDirection = Vector3::ZERO;

    // ��������
    //gF3DParams = strF3DParams;

}

MyFrameListener::~MyFrameListener()
{
    if ( gF3DParams.mRaySceneQuery )
    {
        mSceneMgr->destroyQuery( gF3DParams.mRaySceneQuery );
    }
}

bool MyFrameListener::frameStarted( const FrameEvent& evt )
{
    // ��ȡ��ǰ��ꡢ���̺��ֱ�״̬
    if ( mMouse )
        mMouse->capture();
    if ( mKeyboard )
        mKeyboard->capture();
    if ( mJoy )
        mJoy->capture();

    // ��ȡϵͳ�����󾭹���ʱ��
    gTimeDef.systemTime = GetTickCount() * 0.001f - gTimeDef.startTime;
    // ��ȡʵ�����ڡ�ʱ��
    GetLocalTime( &gTimeDef.localTime );

    if ( ( gPhaseMark == MainMenu && gF3DParams.EarthNode ) || gPhaseMark == CreateChara )
    {
        // ������ת������1������=23Сʱ56��4��=86164s��ƽ��ÿ��ת��0.004178079012�ȣ�
        gF3DParams.EarthNode->yaw( Degree( 0.0004178 * evt.timeSinceLastFrame * gTimeFactor ) ); //*10000
    }


    // ogreʵ�嶯��
// 	if (gF3DParams.mStartTrack)
// 	{
// 		gF3DParams.mAnimState->addTime(evt.timeSinceLastFrame);
// 	}
    // GUI����
    myGuiSys->cegui_Update( evt.timeSinceLastFrame );

// 	if (!gF3DParams.animInst1->isRunning())
// 	{
// // 		if (bbbbbbb == false)
// // 		{
// //		myGuiSys->cegui_GetWindow("Start/FinalLogo")->show();
// //			gF3DParams.animInstShow->start(true);
// // 			if (!gF3DParams.animInstShow->isRunning())
// // 			{
// // 				bbbbbbb = true;
// // 			}
// //		}
// 	}

    // �������ﶯ��
    // ������Ҫupdate����Tooltip������ʾ
    //myGuiSys->cegui_Update(evt.timeSinceLastFrame);
    // ������ҪaddTime����ʹ����������
// 	if (gF3DParams.mCharaAnimState)
// 		gF3DParams.mCharaAnimState->addTime(evt.timeSinceLastFrame);
// 	if (gF3DParams.mBackupCharaAnimState)
// 		gF3DParams.mBackupCharaAnimState->addTime(evt.timeSinceLastFrame);

    if ( gPhaseMark == MainMenu )
        mMove = 1500000;
    if ( gPhaseMark == BeginScene )
        update3dRender( evt );

    return gF3DParams.mContinue;
} // ����frameStarted����

bool MyFrameListener::mouseMoved( const OIS::MouseEvent& MEve )
{

    // ע��GUI���
    myGuiSys->cegui_InjectMouseMove( MEve.state.X.rel, MEve.state.Y.rel );

    if ( gPhaseMark == CreateChara && MEve.state.buttonDown( OIS::MB_Right ) )
    {
        gF3DParams.mCharaNode->yaw( Degree( mRotate * MEve.state.X.rel ), Node::TS_LOCAL );
    }

    if ( gPhaseMark == BeginScene && gF3DParams.mExitUI == true )
    {
        // �����ӽ��ƶ�
        gF3DParams.mCamNode->yaw( Degree( -mRotate * MEve.state.X.rel ), Node::TS_WORLD );
        gF3DParams.mCamNode->pitch( Degree( -mRotate * MEve.state.Y.rel ), Node::TS_LOCAL );
    }


    return true;
}

bool MyFrameListener::mousePressed( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId )
{
    // ע��GUI���
    myGuiSys->cegui_InjectMouseBtnDwn( GuiSystem::cegui_ConvertButton( MId ) );
// 	if (MId == OIS::MB_Left)
// 	{
// 		if (!gF3DParams.mStartTrack && !gF3DParams.mExitUI)
// 		{
// 			mMouseLeftClicked = true;
// 			CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
// 			Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x / float(MEve.state.width),
// 				mousePos.d_y / float(MEve.state.height));
// 			gF3DParams.mRaySceneQuery->setRay(mouseRay);
// 			// ��������򣬵õ����������
// 			gF3DParams.mRaySceneQuery->setSortByDistance(true);
// 			gF3DParams.mRaySceneQuery->setQueryMask(QUERY_MASK);
// 			Ogre::RaySceneQueryResult& result = gF3DParams.mRaySceneQuery->execute();
// 			RaySceneQueryResult::iterator itr = result.begin();
// 			if (itr != result.end() && itr->movable)
// 			{
// 				gF3DParams.mCurrentNode = itr->movable->getParentSceneNode();
// 				gF3DParams.mCurrentNode->showBoundingBox(true);
// 				// ��ʼ�켣����
// 				gF3DParams.mStartTrack = true;
// 				startTrackAnimation(gF3DParams.mCurrentNode, true);
// 				// 				startGuiAnim("DialogAnim", "DialogWindow/DialogBgImg/DialogText");
// 				// 				myGuiSys->cegui_LoadLayout("DialogWindow");
// 			}
// 			else
// 			{
// 				gF3DParams.mCurrentNode->showBoundingBox(false);
// 				mCamera->setAutoTracking(false);
// 			}
// 		}
// 	}


    return true;
}

bool MyFrameListener::mouseReleased( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId )
{
    // ע��GUI���
    myGuiSys->cegui_InjectMouseBtnUp( GuiSystem::cegui_ConvertButton( MId ) );
    if ( MId = OIS::MB_Left )
        mMouseLeftClicked = false;



    return true;
}

/**
����˵����
K:��ʾ������ʱ��塢֡��Ϣ�塢��������Ϣ���ogre��־
F:�򿪡��رո߼�֡��Ϣ����ʼΪ�ر�
G:ѭ�����������Ϣ���ʱ��壬��ʼΪʱ���
H:�򿪡��ر�֡��Ϣ�壬��ʼΪ��
R:ѭ�����ö������Ⱦģʽ��Solid��Wireframe��Points����ʼΪSolid
T:ѭ�����������˲�ƽ��ģʽ��Bilinear��Trilinear��Anisotropic��None����ʼΪBilinear
L:�򿪡��ر�ogre��־����ʼΪ��
Esc:�˳���Ϸ
1:�ƶ�������λ�ã���bug��
2:�ƶ���̫��λ�ã���bug��
3:�ƶ���̫��ϵ�۲�㣨��bug��
W/��:��ǰ�ƶ�
S/��:����ƶ�
A/��:�����ƶ�
D/��:�����ƶ�
Q:�����ƶ�
E:�����ƶ�
PgUp:�ӿ��ƶ��ٶȣ���bug�����ɳ�������
PgDn:��С�ƶ��ٶȣ���bug�����ɳ�������
End:�л��ƶ��ٶȣ����ڽ����ٶȣ������������Ǻ����ٶȣ��Ͽ죩���л�����ʼΪ�����ٶȣ���bug�����ɳ�������
*/
bool MyFrameListener::keyPressed( const OIS::KeyEvent& KEve )
{
    // ע��GUI�����¼���keychar�¼�
    CEGUI::System::getSingleton().injectKeyDown( KEve.key );
    CEGUI::System::getSingleton().injectChar( KEve.text );
    //if (KEve.key == OIS::KC_ESCAPE)



    switch ( gPhaseMark )
    {
        case HealthyGaming:
        case FinalLogo:
        case OgreLogo:
#if OGRE_DEBUG_MODE
            switch ( KEve.key )
            {
                case OIS::KC_ESCAPE:
                    gF3DParams.mContinue = false;
                case OIS::KC_SPACE:
                    gPhaseMark = MainMenu;
            }
#endif
            break;

        case MainMenu:
            switch ( KEve.key )
            {
                case OIS::KC_SPACE:
                    gF3DParams.eggCount ++;
                    break;
                case OIS::KC_ESCAPE:
                    {
#if OGRE_DEBUG_MODE
                        gF3DParams.mContinue = false;
#else
                        if ( myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->isVisible() )
                        {
                            myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->hide();
                            myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->enable();
                            myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->enable();
                            myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->enable();
                            myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->enable();
                        }
                        else
                        {
                            myGuiSys->cegui_GetWindow( "MainMenu/QuitWin" )->show();
                            myGuiSys->cegui_GetWindow( "MainMenu/Start/Star" )->disable();
                            myGuiSys->cegui_GetWindow( "MainMenu/Load/Star" )->disable();
                            myGuiSys->cegui_GetWindow( "MainMenu/Setup/Star" )->disable();
                            myGuiSys->cegui_GetWindow( "MainMenu/Quit/Star" )->disable();
                        }

#endif
                        break;
                    }
            }
            break;

        case CreateChara:
            switch ( KEve.key )
            {
#if OGRE_DEBUG_MODE
                case OIS::KC_ESCAPE:
                    gF3DParams.mContinue = false;
                    break;
#endif
            }
            break;

        case IntroChara:
            switch ( KEve.key )
            {
                case OIS::KC_ESCAPE:
#if OGRE_DEBUG_MODE
                    gF3DParams.mContinue = false;
#else
                    gPhaseMark = FinishIntro;
#endif
                    break;
            }
            break;

        case  BeginScene:
            {
                switch ( KEve.key )
                {

                    case OIS::KC_R: // cycle polygon rendering mode
                        {
                            Ogre::String newVal;
                            Ogre::PolygonMode pm;

                            switch ( mCamera->getPolygonMode() )
                            {
                                case Ogre::PM_SOLID:
                                    newVal = "Wireframe";
                                    pm = Ogre::PM_WIREFRAME;
                                    break;
                                case Ogre::PM_WIREFRAME:
                                    newVal = "Points";
                                    pm = Ogre::PM_POINTS;
                                    break;
                                default:
                                    newVal = "Solid";
                                    pm = Ogre::PM_SOLID;
                            }

                            mCamera->setPolygonMode( pm );
                            break;
                        }

                    case OIS::KC_ESCAPE:
                        {
                            gF3DParams.mExitUI = !gF3DParams.mExitUI;
                            if ( gF3DParams.mExitUI )
                            {
                                myGuiSys->cegui_GetWindow( "Root_GamingUI" )->hide();
                                myGuiSys->cegui_ShowGuiCursor( false );
                                mySoundSys.fmod_GoOnSound( SpaceSound );
                            }
                            else
                            {
                                myGuiSys->cegui_GetWindow( "Root_GamingUI" )->show();
                                myGuiSys->cegui_ShowGuiCursor( true );
                                mySoundSys.fmod_PauseSound( SpaceSound );
                            }
                            //gF3DParams.mContinue = false;
                        }
                        break;
                    // �ƶ������
                    case OIS::KC_UP:
                    case OIS::KC_W:
                        mDirection.z -= mMove;
                        break;

                    case OIS::KC_DOWN:
                    case OIS::KC_S:
                        mDirection.z += mMove;
                        break;

                    case OIS::KC_LEFT:
                    case OIS::KC_A:
                        mDirection.x -= mMove;
                        break;

                    case OIS::KC_RIGHT:
                    case OIS::KC_D:
                        mDirection.x += mMove;
                        break;

                    case OIS::KC_E:
                        mDirection.y -= mMove;
                        break;

                    case OIS::KC_Q:
                        mDirection.y += mMove;
                        break;

                    case OIS::KC_PGUP: // �ӿ��ƶ��ٶ�
                        //std::cout<<"my my!";
                        mMove += 10000000;
                        if ( mMove < 0 )
                            mMove = 0;
                        break;

                    case OIS::KC_PGDOWN:  // �����ƶ��ٶ�
                        mMove -= 100000;
                        if ( mMove < 0 )
                            mMove = 0;
                        break;

                    case OIS::KC_END: // ���������ƶ��ٶ�
                        if ( mMove == 1500000 )
                            mMove = 5000000000;
                        else
                            mMove = 1500000; // ��������ʱ���ٶ�
                        break;

                } // switch key
                break;
            }
    } // switch phase mark


    return true;
}

bool MyFrameListener::keyReleased( const OIS::KeyEvent& KEve )
{
    // ע��GUI�¼���Ӧ
    CEGUI::System::getSingleton().injectKeyUp( KEve.key );
    if ( gPhaseMark == BeginScene )
    {
        switch ( KEve.key )
        {
            // �ͷŰ���ʱֹͣ�ƶ������
            case OIS::KC_UP:
            case OIS::KC_W:
                mDirection.z += mMove;
                break;

            case OIS::KC_DOWN:
            case OIS::KC_S:
                mDirection.z -= mMove;
                break;

            case OIS::KC_LEFT:
            case OIS::KC_A:
                mDirection.x += mMove;
                break;

            case OIS::KC_RIGHT:
            case OIS::KC_D:
                mDirection.x -= mMove;
                break;

            case OIS::KC_E:
                mDirection.y += mMove;
                break;

            case OIS::KC_Q:
                mDirection.y -= mMove;
                break;

            case OIS::KC_PGUP:
                //	mMove -= 10000000;
                //	if (mMove <0)
                //		mMove = 0;
                break;

            case OIS::KC_PGDOWN:
                //	mMove += 10000000;
                break;

        } //switch
    }

    return true;
}

/* �ֱ����ƺ��� */
bool MyFrameListener::buttonPressed( const OIS::JoyStickEvent &JEve, int button )
{
    //mDirection.z -= mMove;
    //switch (JEve.state.mButtons)
    //case OIS::
    return true;
}

bool MyFrameListener::buttonReleased( const OIS::JoyStickEvent &JEve, int button )
{
    //mDirection.z -= mMove;
    return true;
}

bool MyFrameListener::axisMoved( const OIS::JoyStickEvent &JEve, int axis )
{
    //mDirection.z -= mMove;
    //switch (JEve.state.mAxes[axis].)
    return true;
}

bool MyFrameListener::povMoved( const OIS::JoyStickEvent &JEve, int pov )
{
    //mDirection.z -= mMove;
    //if( JEve.state.mPOV[pov].direction == OIS::Pov::North )
    //mDirection.z -= mMove;// mCamNode->yaw(Degree(-mRotate), Node::TS_WORLD);
    return true;
}

//-------------------����Ϊ3d��Ϸ����ʵ��---------------------------------------------------------//

bool MyFrameListener::update3dRender( const FrameEvent& evt )
{
    if ( gF3DParams.mExitUI )
    {
        // ������ת������1������=23Сʱ56��4��=86164s��ƽ��ÿ��ת��0.004178079012�ȣ�
        gF3DParams.EarthNode->yaw( Degree( 0.004178079012 * evt.timeSinceLastFrame * gTimeFactor ) ); //*10000

        // ���򼰱�־�ǹ�ת������1������=365��6ʱ9��10��=31558150s��ƽ��ÿ��ת��1.14075128*10^-5�ȣ�
        gF3DParams.RevSunNode->
        yaw( Degree( evt.timeSinceLastFrame * 1.14075128 * pow( 10.0, -5.0 ) * gTimeFactor ), Node::TS_LOCAL );


        AxisAlignedBox CameraBox = gF3DParams.mCamNode->_getWorldAABB();
        AxisAlignedBox Earthbox = gF3DParams.EarthNode->_getWorldAABB();
        AxisAlignedBox MoonBox = gF3DParams.MoonNode->_getWorldAABB();
        AxisAlignedBox SunBox = gF3DParams.SunNode->_getWorldAABB();
        if( Earthbox.intersects( CameraBox ) )
        {
            //mMove = 0;
//			mySoundSys.fmod_PlaySound(EarthSound, false);
            //gF3DParams.Earth->setMaterialName("Sun/SunSurface");
            //		mSceneMgr->getRootSceneNode()->removeChild(gF3DParams.mCamNode);
            //		gF3DParams.EarthNode->addChild(gF3DParams.mCamNode);
        }
        else if ( MoonBox.intersects( CameraBox ) )
        {
//			mySoundSys.fmod_PlaySound(MoonSound, false);
        }
        else if ( SunBox.intersects( CameraBox ) )
        {
//			mySoundSys.fmod_PlaySound(SunSound, false);
        }
        else
        {
//			mySoundSys.fmod_PlaySound(SpaceSound, false);
            //gF3DParams.Earth->setMaterialName("Earth/Surface");
            //gF3DParams.EarthNode->removeChild(mCamNode);
            //mSceneMgr->getRootSceneNode()->addChild(mCamNode);
        }

        // ʹ�á����ء��任�ռ䣬�������ڳ����ڵ����תҲ������ƽ�������ϣ�
        // �Է���ת��ı�x��y��z��������ʹ֮���ƽ�Ƴ���
        gF3DParams.mCamNode->translate( mDirection * evt.timeSinceLastFrame, Node::TS_LOCAL );




        /*

        // ������ά��������ƽ�Ʒ�λ
        Vector3 transVector = Vector3::ZERO;

        */

        /*
        // �������ƹ۲�ķ���
        if (mMouse->getMouseState().buttonDown(OIS::MB_Right))
        {
        mCamNode->yaw(Degree(-mRotate * mMouse->getMouseState().X.rel), Node::TS_WORLD);
        mCamNode->pitch(Degree(-mRotate * mMouse->getMouseState().Y.rel), Node::TS_LOCAL);
        }
        }

        return true;

        */
    }
    return true;
}



//-------------------------����ΪGUI���ʵ��----------------------------------------------------//

void MyFrameListener::startGuiAnim( const std::string& animName, const std::string& targetWindow )
{
    mGuiAnim = CEGUI::AnimationManager::getSingleton().getAnimation( animName );
    // ʵ��������
    mGuiAnimInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation( mGuiAnim );
    // ������Ӧ�ô���
    mGuiAnimInst->setTargetWindow( myGuiSys->cegui_GetWindow( targetWindow ) );
    // ������ʼ
    mGuiAnimInst->start();
}

void MyFrameListener::startTrackAnimation( SceneNode* trackNode, bool start, bool loop /* = false */ )
{
    // ������������Զ����ٽڵ�
    mCamera->setAutoTracking( start, trackNode );
    // ���ö���״̬
    gF3DParams.mAnimState->setTimePosition( 0 );
    gF3DParams.mAnimState->setEnabled( start );
    gF3DParams.mAnimState->setLoop( loop );
}

//--------------------------------����Ϊ������������-----------------------------------------------//

Ogre::String MyFrameListener::convertTime( float sec )
{
    int intPart = ( int )sec; // ��������
    WORD fractPart = WORD( ( sec - intPart ) * 10 ); // С������
    WORD hour = ( WORD )( intPart / 3600 );
    WORD minute = ( WORD )( ( intPart - hour * 3600 ) / 60 );
    WORD second = intPart - hour * 3600 - minute * 60;
    Ogre::String strHour = setTimeToStdFormat( hour );
    Ogre::String strMinute = setTimeToStdFormat( minute );
    Ogre::String strSecond = setTimeToStdFormat( second );
    return strHour + ":" + strMinute + ":" + strSecond;
}

Ogre::String MyFrameListener::setTimeToStdFormat( WORD wTime )
{
    if ( wTime < 10 )
        return "0" + Ogre::StringConverter::toString( wTime );
    else
        return Ogre::StringConverter::toString( wTime );
}

