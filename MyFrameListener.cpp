#include "MyFrameListener.h"

MyFrameListener::MyFrameListener( RenderWindow* win,
                                  Camera* cam, SceneManager* sceneMgr
                                  /*Final3DParams strF3DParams*/ )
    : ExampleFrameListener( win, cam, true, // 使用带缓冲的键盘输入
                            true ), // 使用带缓冲的鼠标输入
    mMouseLeftClicked( false )
{

    // 键盘和鼠标状态追踪
    //mMouseDown = false;
    //mToggle = 0.0;

    // 获得绑定摄像机的父节点
//	mCamNode = cam->getParentSceneNode();
    // 获得场景管理器句柄
    mSceneMgr = sceneMgr;

    // 设置旋转和移动速度
    mRotate = 0.13;
    mMove = 1500000;

    // 继续渲染初值
    gF3DParams.mContinue = true;

    // 把帧监听器注册为鼠标、键盘和手柄监听器
    if ( mMouse )
        mMouse->setEventCallback( this );
    if ( mKeyboard )
        mKeyboard->setEventCallback( this );
    if ( mJoy )
        mJoy->setEventCallback( this );

    // 初始化移动方向向量为0向量
    mDirection = Vector3::ZERO;

    // 参数传递
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
    // 获取当前鼠标、键盘和手柄状态
    if ( mMouse )
        mMouse->capture();
    if ( mKeyboard )
        mKeyboard->capture();
    if ( mJoy )
        mJoy->capture();

    // 获取系统开启后经过的时间
    gTimeDef.systemTime = GetTickCount() * 0.001f - gTimeDef.startTime;
    // 获取实际日期、时间
    GetLocalTime( &gTimeDef.localTime );

    if ( ( gPhaseMark == MainMenu && gF3DParams.EarthNode ) || gPhaseMark == CreateChara )
    {
        // 地球自转动画（1恒星日=23小时56分4秒=86164s，平均每秒转动0.004178079012度）
        gF3DParams.EarthNode->yaw( Degree( 0.0004178 * evt.timeSinceLastFrame * gTimeFactor ) ); //*10000
    }


    // ogre实体动画
// 	if (gF3DParams.mStartTrack)
// 	{
// 		gF3DParams.mAnimState->addTime(evt.timeSinceLastFrame);
// 	}
    // GUI动画
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

    // 创建人物动画
    // 这里需要update否则Tooltip不会显示
    //myGuiSys->cegui_Update(evt.timeSinceLastFrame);
    // 这里需要addTime才能使动画动起来
// 	if (gF3DParams.mCharaAnimState)
// 		gF3DParams.mCharaAnimState->addTime(evt.timeSinceLastFrame);
// 	if (gF3DParams.mBackupCharaAnimState)
// 		gF3DParams.mBackupCharaAnimState->addTime(evt.timeSinceLastFrame);

    if ( gPhaseMark == MainMenu )
        mMove = 1500000;
    if ( gPhaseMark == BeginScene )
        update3dRender( evt );

    return gF3DParams.mContinue;
} // 函数frameStarted结束

bool MyFrameListener::mouseMoved( const OIS::MouseEvent& MEve )
{

    // 注入GUI鼠标
    myGuiSys->cegui_InjectMouseMove( MEve.state.X.rel, MEve.state.Y.rel );

    if ( gPhaseMark == CreateChara && MEve.state.buttonDown( OIS::MB_Right ) )
    {
        gF3DParams.mCharaNode->yaw( Degree( mRotate * MEve.state.X.rel ), Node::TS_LOCAL );
    }

    if ( gPhaseMark == BeginScene && gF3DParams.mExitUI == true )
    {
        // 自由视角移动
        gF3DParams.mCamNode->yaw( Degree( -mRotate * MEve.state.X.rel ), Node::TS_WORLD );
        gF3DParams.mCamNode->pitch( Degree( -mRotate * MEve.state.Y.rel ), Node::TS_LOCAL );
    }


    return true;
}

bool MyFrameListener::mousePressed( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId )
{
    // 注入GUI鼠标
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
// 			// 按深度排序，得到最近的物体
// 			gF3DParams.mRaySceneQuery->setSortByDistance(true);
// 			gF3DParams.mRaySceneQuery->setQueryMask(QUERY_MASK);
// 			Ogre::RaySceneQueryResult& result = gF3DParams.mRaySceneQuery->execute();
// 			RaySceneQueryResult::iterator itr = result.begin();
// 			if (itr != result.end() && itr->movable)
// 			{
// 				gF3DParams.mCurrentNode = itr->movable->getParentSceneNode();
// 				gF3DParams.mCurrentNode->showBoundingBox(true);
// 				// 开始轨迹动画
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
    // 注入GUI鼠标
    myGuiSys->cegui_InjectMouseBtnUp( GuiSystem::cegui_ConvertButton( MId ) );
    if ( MId = OIS::MB_Left )
        mMouseLeftClicked = false;



    return true;
}

/**
按键说明：
K:显示、隐藏时间板、帧信息板、摄像器信息板和ogre标志
F:打开、关闭高级帧信息，初始为关闭
G:循环打开摄像机信息板和时间板，初始为时间板
H:打开、关闭帧信息板，初始为打开
R:循环设置多边形渲染模式：Solid，Wireframe，Points，初始为Solid
T:循环设置纹理滤波平滑模式：Bilinear，Trilinear，Anisotropic，None，初始为Bilinear
L:打开、关闭ogre标志，初始为打开
Esc:退出游戏
1:移动到地球位置（有bug）
2:移动到太阳位置（有bug）
3:移动到太阳系观测点（有bug）
W/↑:向前移动
S/↓:向后移动
A/←:向左移动
D/→:向右移动
Q:向上移动
E:向下移动
PgUp:加快移动速度（有bug，不可持续按）
PgDn:减小移动速度（有bug，不可持续按）
End:切换移动速度，可在近地速度（较慢）和行星航行速度（较快）间切换，初始为近地速度（有bug，不可持续按）
*/
bool MyFrameListener::keyPressed( const OIS::KeyEvent& KEve )
{
    // 注入GUI键盘事件和keychar事件
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
                    // 移动摄像机
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

                    case OIS::KC_PGUP: // 加快移动速度
                        //std::cout<<"my my!";
                        mMove += 10000000;
                        if ( mMove < 0 )
                            mMove = 0;
                        break;

                    case OIS::KC_PGDOWN:  // 减慢移动速度
                        mMove -= 100000;
                        if ( mMove < 0 )
                            mMove = 0;
                        break;

                    case OIS::KC_END: // 设置两种移动速度
                        if ( mMove == 1500000 )
                            mMove = 5000000000;
                        else
                            mMove = 1500000; // 靠近地球时的速度
                        break;

                } // switch key
                break;
            }
    } // switch phase mark


    return true;
}

bool MyFrameListener::keyReleased( const OIS::KeyEvent& KEve )
{
    // 注入GUI事件响应
    CEGUI::System::getSingleton().injectKeyUp( KEve.key );
    if ( gPhaseMark == BeginScene )
    {
        switch ( KEve.key )
        {
            // 释放按键时停止移动摄像机
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

/* 手柄控制函数 */
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

//-------------------以下为3d游戏场景实现---------------------------------------------------------//

bool MyFrameListener::update3dRender( const FrameEvent& evt )
{
    if ( gF3DParams.mExitUI )
    {
        // 地球自转动画（1恒星日=23小时56分4秒=86164s，平均每秒转动0.004178079012度）
        gF3DParams.EarthNode->yaw( Degree( 0.004178079012 * evt.timeSinceLastFrame * gTimeFactor ) ); //*10000

        // 地球及标志星公转动画（1恒星年=365日6时9分10秒=31558150s，平均每秒转动1.14075128*10^-5度）
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

        // 使用“本地”变换空间，将作用于场景节点的旋转也作用于平移向量上，
        // 以防旋转后改变x、y、z向量方向，使之后的平移出错
        gF3DParams.mCamNode->translate( mDirection * evt.timeSinceLastFrame, Node::TS_LOCAL );




        /*

        // 创建三维向量保存平移方位
        Vector3 transVector = Vector3::ZERO;

        */

        /*
        // 用鼠标控制观察的方向
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



//-------------------------以下为GUI相关实现----------------------------------------------------//

void MyFrameListener::startGuiAnim( const std::string& animName, const std::string& targetWindow )
{
    mGuiAnim = CEGUI::AnimationManager::getSingleton().getAnimation( animName );
    // 实例化动画
    mGuiAnimInst = CEGUI::AnimationManager::getSingleton().instantiateAnimation( mGuiAnim );
    // 动画的应用窗口
    mGuiAnimInst->setTargetWindow( myGuiSys->cegui_GetWindow( targetWindow ) );
    // 动画开始
    mGuiAnimInst->start();
}

void MyFrameListener::startTrackAnimation( SceneNode* trackNode, bool start, bool loop /* = false */ )
{
    // 设置摄像机的自动跟踪节点
    mCamera->setAutoTracking( start, trackNode );
    // 设置动画状态
    gF3DParams.mAnimState->setTimePosition( 0 );
    gF3DParams.mAnimState->setEnabled( start );
    gF3DParams.mAnimState->setLoop( loop );
}

//--------------------------------以下为其他辅助功能-----------------------------------------------//

Ogre::String MyFrameListener::convertTime( float sec )
{
    int intPart = ( int )sec; // 整数部分
    WORD fractPart = WORD( ( sec - intPart ) * 10 ); // 小数部分
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

