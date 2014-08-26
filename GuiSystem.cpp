#include "StdAfx.h"
#include "GuiSystem.h"

#include "MyFrameListener.h"
#include "ThreeDimentionalApplication.h"

GuiSystem* GuiSystem::ms_singleton = NULL;

GuiSystem::~GuiSystem(void)
{
	cegui_Destroy();
}

bool GuiSystem::cegui_Init()
{
	if (!mGUIRenderer)
	{
		// 初始化CEGUI渲染系统
		mGUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
		mGuiSystem = &CEGUI::System::getSingleton();

		// 定义logger（日志记录器）对象，有用信息将被记录（如创建对象）
		CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

		//加载GUI主题， 设置默认参数   
		CEGUI::Imageset::setDefaultResourceGroup("Imagesets");   
		CEGUI::Font::setDefaultResourceGroup("Fonts");   
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");   
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");   
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");  

		// 载入CEGUI scheme
		// The first thing to do is load a CEGUI 'scheme'. this is basically a file
		// that groups all the required resources and definitions for a particular
		// skin so they can be loaded / initialised easily.
		// 
		// So, we use the SchemeManager singleton to load in a scheme that loads the
		// imagery and registers widgets for the TaharezLook skin.  This scheme also
		// loads in a font that gets used as the system default.
//		CEGUI::SchemeManager::getSingleton().create("Xianjian.scheme");

		// 设置字体
// 		CEGUI::Font* font = &CEGUI::FontManager::getSingleton().create("Xianjian.font");
// 		mGuiSystem->setDefaultFont(font);

		// 设置默认鼠标指针图形
		// The TaharezLook Imageset contains an Image named "MouseArrow" which is
		// the ideal thing to have as a defult mouse cursor image.
//		mGuiSystem->setDefaultMouseCursor("Xianjian", "Xj4MainCur");
		// 设置GUI鼠标是否可见
//		cegui_ShowGuiCursor(true);

		// 创建窗口管理器
		// All windows and widgets are created via the WindowManager singleton.
		mWinMgr = CEGUI::WindowManager::getSingletonPtr();

		//CEGUI::Window* sheet =  winMgr.loadWindowLayout("MyUI.layout");    
		//CEGUI::System::getSingleton().setGUISheet(sheet);  

		// 创建一个DefaultWindow。
		// Here we create a "DeafultWindow".  This is a native type, that is, it does
		// not have to be loaded via a scheme, it is always available.  One common use
		// for the DefaultWindow is as a generic container for other windows.  Its
		// size defaults to 1.0f x 1.0f using the Relative metrics mode, which means
		// when it is set as the root GUI sheet window, it will cover the entire display.
		// The DefaultWindow does not perform any rendering of its own, so is invisible.
//		rootWindow = (CEGUI::DefaultWindow*)mWinMgr->createWindow("DefaultWindow", "RootWindow");

		// 设置GUI根窗口
		// set the GUI root window (also known as the GUI "sheet"), so the gui we set up
		// will be visible.
//		mGuiSystem->setGUISheet(rootWindow);

		// 创建一个FrameWindow。
		// A FrameWindow is a window with a frame and a titlebar which may be moved around
		// and resized.
//		CEGUI::FrameWindow* FWin = (CEGUI::FrameWindow*)mWinMgr->createWindow("Xianjian/Editbox", "Demo Window");

		// 将新窗口作为子窗口链接到默认窗口，此步骤后窗口即可显示出来
		// Here we attach the newly created FrameWindow to the previously created
		// DefaultWindow which we will be using as the root of the displayed gui.
//		rootWindow->addChildWindow(FWin);

		// 设置子窗口大小和位置（相对父窗口值）
		// Windows are in Relative metrics mode by default.  This means that we can
		// specify sizes and positions without having to know the exact pixel size
		// of the elements in advance.  The relative metrics mode co-ordinates are
		// relative to the parent of the window where the co-ordinates are being set.
		// This means that if 0.5f is specified as the width for a window, that window
		// will be half as its parent window.
//		FWin->setPosition(CEGUI::UVector2(cegui_reldim(0.0f), cegui_reldim(0.0f)));
		//FWin->setSize(CEGUI::UVector2(cegui_reldim(0.25f), cegui_reldim(0.5f)));

		// 设置子窗口最大、最小尺寸（相对显示屏幕值）
		// now we set the maximum and minum sizes for the new window.  These are
		// specified using relative co-ordinates, but the important thing to note
		// is that these settings are aways relative to the display rather than the
		// parent window.
//		FWin->setMaxSize(CEGUI::UVector2(cegui_reldim(1.0f), cegui_reldim(1.0f)));
//		FWin->setMinSize(CEGUI::UVector2(cegui_reldim(0.1f), cegui_reldim(0.1f)));

		// 设置子窗口标题
		// As a final step in the initialisation of our sample window, we set the window's
		// text, so that this text will appear as the caption in the FrameWindow's titlebar.
//		FWin->setText((CEGUI::utf8*)Ogre::UTFString(L"林林的图形用户界面Linlin's Gui Window. (don't know how to afford chinese character)").asUTF8_c_str()); // 的GUI窗口

//		cegui_CreateQuitBtn();

		return true;
	}
	return false;
}

void GuiSystem::cegui_Update(float timeSinceLastFrame)
{
	mGuiSystem->injectTimePulse(timeSinceLastFrame);
}

void GuiSystem::cegui_CreateImageset(const std::string& name, const std::string& filename)
{
	CEGUI::ImagesetManager::getSingleton().createFromImageFile(name, filename);
}

bool GuiSystem::cegui_LoadLayout(const std::string& layoutName, bool ifShow /* = true */)
{
	CEGUI::Window* guiSheet;
	// 检测给定layout的文件是否加载，没有则加载
	if (!cegui_GetGuiWindowMgr()->isWindowPresent("Root_" + layoutName))
	{
		// 从.layout脚本文件读取一个UI布局设计，并将其放置到GUI资源组中
		guiSheet = cegui_GetGuiWindowMgr()->loadWindowLayout(layoutName + ".layout");
	}
	else
	{
		// 如果已经加载则直接显示
		guiSheet = cegui_GetGuiWindowMgr()->getWindow("Root_" + layoutName);
	}
	// 通知CEGUI显示哪份UI布局。此显示的UI布局可随时更换。
	mGuiSystem->setGUISheet(guiSheet);
	// 显示UI布局
	if (ifShow == true)
		guiSheet->show();
	else
		guiSheet->hide();

	return true;
}

CEGUI::MouseButton GuiSystem::cegui_ConvertButton(OIS::MouseButtonID buttonId)
{
	switch (buttonId)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;
	case OIS::MB_Right:
		return CEGUI::RightButton;
	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
	default:
		return CEGUI::LeftButton;
	}
}

void GuiSystem::cegui_SubscribeEvent(const CEGUI::String& windowName, 
									 const CEGUI::String& eventName, 
									 const CEGUI::Event::Subscriber& subscriber)
{
	CEGUI::WindowManager::getSingleton().getWindow(CEGUI::String(windowName))
	//mWinMgr->createWindow("Xianjian/Button", (CEGUI::utf8*)"Quit");
	//mWinMgr->getWindow(CEGUI::String(windowName))
		->subscribeEvent(eventName, subscriber);
}

void GuiSystem::cegui_SetProperty(const std::string& windowName, 
								  const std::string& key, const std::string& value)
{
	GuiSystem::getSingletonPtr()->cegui_GetWindow(windowName)->setProperty(key, value);
}

const CEGUI::String& GuiSystem::cegui_showChinese(const Ogre::String& strChinese)
{
	return (CEGUI::utf8*)Ogre::UTFString(L"林林的图形用户界面Linlin's Gui Window. (don't know how to afford chinese character)").asUTF8_c_str();
}

bool GuiSystem::cegui_CreateQuitBtn(void)
{
	// 创建按钮
	CEGUI::PushButton* quitButton = (CEGUI::PushButton*)mWinMgr->createWindow("Xianjian/Button", (CEGUI::utf8*)"Quit");
	rootWindow->addChildWindow(quitButton);
	quitButton->setPosition(CEGUI::UVector2(cegui_reldim(0.15f), cegui_reldim(0.15f)));
	quitButton->setSize(CEGUI::UVector2(cegui_reldim(0.05f), cegui_reldim(0.05f)));
	quitButton->setText("Quit");
	//cegui_SubscribeEvent((CEGUI::utf8*)"Quit", CEGUI::PushButton::EventClicked, 
		//CEGUI::Event::Subscriber(&MyFrameListener::handleQuit, this));
	// 注册事件处理器
	//quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MyFrameListener::handleQuit, this));

	return true;
}

bool GuiSystem::cegui_DestroyWindow(const std::string& windowName)
{
	cegui_GetGuiWindowMgr()->destroyWindow(windowName);
	return true;
}

bool GuiSystem::cegui_Destroy()
{
	//if (mGuiSystem && mGUIRenderer)
	//	CEGUI::OgreRenderer::destroySystem();
	delete ms_singleton;
	ms_singleton = 0;

	return true;
}

