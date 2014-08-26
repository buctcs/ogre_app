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
    // ��ʼ��Ⱦ֡
    bool frameStarted( const FrameEvent& evt );
    /* ���֡���� */
    // �ƶ����
    bool mouseMoved( const OIS::MouseEvent& MEve );
    // �������
    bool mousePressed( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId );
    // �ͷ����
    bool mouseReleased( const OIS::MouseEvent& MEve, OIS::MouseButtonID MId );
    /* ����֡���� */
    // ���¼��̼�
    bool keyPressed( const OIS::KeyEvent& KEve );
    // �ͷż��̼�
    bool keyReleased( const OIS::KeyEvent& KEve );
    /* �ֱ�֡���� */
    // �����ֱ���
    bool buttonPressed( const OIS::JoyStickEvent &JEve, int button );
    // �ͷ��ֱ���
    bool buttonReleased( const OIS::JoyStickEvent &JEve, int button );
    // �ƶ�����
    bool axisMoved( const OIS::JoyStickEvent &JEve, int axis );
    // �ƶ��ӵ�
    bool povMoved( const OIS::JoyStickEvent &JEve, int pov );

protected:
    // ����3Dͼ��
    bool update3dRender( const FrameEvent& evt );

//     // ��ʼ��ogre����
//     bool initOgreTray( void );
//     // ����ogre����
//     bool updateOgreTray( const FrameEvent& evt );

    // ��������ʼ��GUI����
    void startGuiAnim( const std::string& animName, const std::string& targetWindow );
    /**
    ��ʼ�켣����
    params:
    @trackNode	�������ٽڵ�
    @start			�Ƿ�ʼ����
    @loop			�����Ƿ�ѭ��
    */
    void startTrackAnimation( SceneNode* trackNode, bool start, bool loop = false );

    // ������Ϊ��λ��ʱ��ת��Ϊʱ���֡����ʽ���ַ���
    Ogre::String convertTime( float sec );
    // �Ա�׼˫λ��ʽ���ʱ��
    // example: 8 �� "08"
    Ogre::String setTimeToStdFormat( WORD wTime );


protected:
    //bool mMouseDown; // ��һ֡�������Ƿ���
    //Real mToggle; // ����ִ���´β���֮ǰ��ʱ�䣨���´δ�����ʼǰ��ʣ���ʱ�䣩

    Real mRotate; // ��ת����
    Real mMove; // �ƶ�����

    SceneManager* mSceneMgr; // ��ǰ�ĳ���������
//	SceneNode* mCamNode; // ��ǰ�󶨵�������ĳ����ڵ�
    Vector3 mDirection; // �ƶ�����

    //Final3DParams gF3DParams; // ���ݲ����ṹ
    //SceneNode* mEarthNode; // ����ڵ�
private:
    bool mMouseLeftClicked; // ����Ƿ����
    CEGUI::Animation* mGuiAnim; // GUI����
    CEGUI::AnimationInstance* mGuiAnimInst; // GUI����ʵ��
};


#endif