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
        // 初始化资源、设置文件路径
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

    // 开始程序/程序入口
    virtual void go( void );

protected:
    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    virtual bool setup( void );
    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources( void );
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure( void );
    // 选择场景管理器
    virtual void chooseSceneManager( void );
    // 创建摄像机
    virtual void createCamera( void );
    // 创建视口
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
    // 创建场景
    virtual void createScene( void );
    // 创建帧听器
    virtual void createFrameListener( void );
    // 开始渲染
    void startRendering( void );
    /**
    游戏执行流程
    此函数实现游戏从开始到结束的整个逻辑流程，由startRendering()调用
    逻辑包含GUI、声音、3d动画等
    */
    virtual void gameProgress( void );
    // 渲染一帧动画，在设定好资源和渲染内容后调用，一般要循环一定次数
    bool renderOneFrame( void )
    {
        //Pump messages in all registered RenderWindow windows
        WindowEventUtilities::messagePump();
        return mRoot->renderOneFrame();
    }
    virtual void destroyScene( void ) {}  // Optional to override this


protected:
    // 设置游戏开始时的GUI
    virtual void setupStartGui( void ) {}
    // 设置主选单
    virtual void setupMainMenu( void ) {}

    // 初始化3D场景
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

    CEGUI::Animation* anim; // GUI动画
    CEGUI::AnimationInstance* animInst; // GUI动画实例
    CEGUI::AnimationInstance* animInst2; // GUI动画实例备用
    CEGUI::AnimationInstance* animInst3;
    SceneNode* node; // 场景节点
    Entity* ent; // 实体

};


#endif