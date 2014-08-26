#ifndef __MyFrameListener_H__
#define __MyFrameListener_H__

#include "stdafx.h"
#include "defines.h"


class MyFrameListener: public ExampleFrameListener, public OIS::MouseListener,
    public OIS::KeyListener, public OIS::JoyStickListener/*, OgreBites::SdkTrayListener*/
{

public:
    MyFrameListener( RenderWindow* win, Camera* cam, SceneManager* sceneMgr/*, Final3DParams strF3DParams*/ );
    virtual ~MyFrameListener();

protected:
    // 开始渲染帧
    bool frameStarted( const FrameEvent& evt );
    /* 鼠标帧听器 */
    // 移动鼠标
    bool mouseMoved( const OIS::MouseEvent& MEve );
    // 按下鼠标
    bool mousePressed( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId );
    // 释放鼠标
    bool mouseReleased( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId );
    /* 键盘帧听器 */
    // 按下键盘键
    bool keyPressed( const OIS::KeyEvent& KEve );
    // 释放键盘键
    bool keyReleased( const OIS::KeyEvent& KEve );
    /* 手柄帧听器 */
    // 按下手柄键
    bool buttonPressed( const OIS::JoyStickEvent &JEve, int button );
    // 释放手柄键
    bool buttonReleased( const OIS::JoyStickEvent &JEve, int button );
    // 移动坐标
    bool axisMoved( const OIS::JoyStickEvent &JEve, int axis );
    // 移动视点
    bool povMoved( const OIS::JoyStickEvent &JEve, int pov );

protected:
    // 更新3D图像
    bool update3dRender( const FrameEvent& evt );

//     // 初始化ogre托盘
//     bool initOgreTray( void );
//     // 更新ogre托盘
//     bool updateOgreTray( const FrameEvent& evt );

    // 启动、初始化GUI动画
    void startGuiAnim( const std::string& animName, const std::string& targetWindow );
    /**
    开始轨迹动画
    params:
    @trackNode	动画跟踪节点
    @start			是否开始动画
    @loop			动画是否循环
    */
    void startTrackAnimation( SceneNode* trackNode, bool start, bool loop = false );

    // 将以秒为单位的时间转换为时、分、秒格式的字符串
    Ogre::String convertTime( float sec );
    // 以标准双位格式输出时间
    // example: 8 → "08"
    Ogre::String setTimeToStdFormat( WORD wTime );


protected:
    //bool mMouseDown; // 上一帧鼠标左键是否按下
    //Real mToggle; // 可以执行下次操作之前的时间（到下次触发开始前所剩余的时间）

    Real mRotate; // 旋转常量
    Real mMove; // 移动常量

    SceneManager* mSceneMgr; // 当前的场景管理器
//	SceneNode* mCamNode; // 当前绑定到摄像机的场景节点
    Vector3 mDirection; // 移动方向

    //Final3DParams gF3DParams; // 传递参数结构
    //SceneNode* mEarthNode; // 地球节点
private:
    bool mMouseLeftClicked; // 鼠标是否左击
    CEGUI::Animation* mGuiAnim; // GUI动画
    CEGUI::AnimationInstance* mGuiAnimInst; // GUI动画实例
};


#endif