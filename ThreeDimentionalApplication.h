#pragma once
#ifndef __ThreeDimentionalApplication_H__
#define __ThreeDimentionalApplication_H__

#include "defines.h"
#include "SoundSystem.h"
#include "MyFrameListener.h"

using namespace Ogre;

class ThreeDimentionalApplication
{
public:
    ThreeDimentionalApplication()
        : mFrameListener( 0 ), mRoot( 0 )
    {
        // ��ʼ����Դ�������ļ�·��
        // Provide a nice cross platform solution for locating the configuration files
        // On windows files are searched for in the current working directory, on OS X however
        // you must provide the full path, the helper function macBundlePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        mResourcePath = macBundlePath() + "/Contents/Resources/";////////////////////////////////////
        mConfigPath = mResourcePath;
#elif OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
        mResourcePath = macBundlePath() + "/";///////////////////////////////////////////////////////////
        mConfigPath = mResourcePath;
#else
        mResourcePath = "";
        mConfigPath = mResourcePath;
#endif

#ifdef USE_RTSHADER_SYSTEM
        mShaderGenerator	 = NULL;		///////////////////////////////////////////////////////////////////
        mMaterialMgrListener = NULL;///////////////////////////////////////////////////////////////////////
#endif
    }

    virtual ~ThreeDimentionalApplication()
    {
        if ( mFrameListener )
            delete mFrameListener;
        if ( mRoot )
        {
            OGRE_DELETE mRoot;
        }

#ifdef OGRE_STATIC_LIB
        mStaticPluginLoader.unload(); //////////////////////////////////////////////////////////////////////////////
#endif
    }

    // ��ʼ����/�������
    virtual void go( void );

protected:
    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    virtual bool setup( void );
    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources( void );
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure( void );
    // ѡ�񳡾�������
    virtual void chooseSceneManager( void );
    // ���������
    virtual void createCamera( void );
    // �����ӿ�
    virtual void createViewports( void );
    // Optional override method where you can create resource listeners (e.g. for loading screens)
    virtual void createResourceListener( void ) {}
    /// Optional override method where you can perform resource group loading
    /// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    virtual void loadResources( void )
    {
        // Initialise, parse scripts etc
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }
    // ��������
    virtual void createScene( void );
    // ����֡����
    virtual void createFrameListener( void );
    // ��ʼ��Ⱦ
    void startRendering( void );
    /**
    ��Ϸִ������
    �˺���ʵ����Ϸ�ӿ�ʼ�������������߼����̣���startRendering()����
    �߼�����GUI��������3d������
    */
    virtual void gameProgress( void );
    // ��Ⱦһ֡���������趨����Դ����Ⱦ���ݺ���ã�һ��Ҫѭ��һ������
    bool renderOneFrame( void )
    {
        //Pump messages in all registered RenderWindow windows
        WindowEventUtilities::messagePump();
        return mRoot->renderOneFrame();
    }
    virtual void destroyScene( void ) {}  // Optional to override this


protected:
    // ������Ϸ��ʼʱ��GUI
    virtual void setupStartGui( void ) {}
    // ������ѡ��
    virtual void setupMainMenu( void ) {}

    // ��ʼ��3D����
    virtual void init3dScene( void ) {}

protected:
    Root* mRoot;
#ifdef OGRE_STATIC_LIB
    StaticPluginLoader mStaticPluginLoader;//////////////////////////////////////////////////////////
#endif
    Camera* mCamera;
    SceneManager* mSceneMgr;
    ExampleFrameListener* mFrameListener;
    RenderWindow* mWindow;
    Ogre::String mResourcePath;
    Ogre::String mConfigPath;
#ifdef USE_RTSHADER_SYSTEM
    RTShader::ShaderGenerator*					mShaderGenerator;			// The Shader generator instance.//////////////////////
    ShaderGeneratorTechniqueResolverListener*	mMaterialMgrListener;		// Material manager listener.	///////////////////////
#endif

    CEGUI::Animation* anim; // GUI����
    CEGUI::AnimationInstance* animInst; // GUI����ʵ��
    CEGUI::AnimationInstance* animInst2; // GUI����ʵ������
    CEGUI::AnimationInstance* animInst3;
    SceneNode* node; // �����ڵ�
    Entity* ent; // ʵ��

};


#endif