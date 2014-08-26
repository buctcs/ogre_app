
#ifndef __GUISYSTEM_H_
#define __GUISYSTEM_H_

class GuiSystem
{
public:
	//GuiSystem(void);
	virtual ~GuiSystem(void);

public:
	// 初始化CEGUI， 必须在RenderWindow创始后初始, 只在第一次调用有效
	bool cegui_Init();
	// GUI更新
	void cegui_Update(float timeSinceLastFrame);
	// 把OIS的鼠标ID转换成CEGUI的鼠标ID
	static CEGUI::MouseButton cegui_ConvertButton(OIS::MouseButtonID buttonId);
	// 销毁资源
	bool cegui_Destroy();

	/**
	根据图片构造Imageset
	params:
	@name		创建的Imageset名称，全局唯一
	@filename	创建Imageset的图片名称
	*/
	static void cegui_CreateImageset(const std::string& name, const std::string& filename);
	// 加载layout
	bool cegui_LoadLayout(const std::string& layoutName, bool ifShow = true);
	/** 
	卸载layout，即销毁layout的根窗口
	params:
	@layoutName	要卸载的layout
	return:
	@0				layout卸载成功
	@1				layout已被卸载
	*/
//	BOOL cegui_UnloadLayout(const std::string& layoutName);
	// 得到指定名称的窗口
	inline CEGUI::Window* cegui_GetWindow(const std::string& windowName)
	{
		return cegui_GetGuiWindowMgr()->getWindow(windowName);
	}
	// 销毁指定名称的窗口
	bool cegui_DestroyWindow(const std::string& windowName);
	/**
	给指定名称的窗口设定属性
	params:
	@windowName		窗口名称
	@key					XML标签		key值
	@value				XML标签		value值
	*/
	static void cegui_SetProperty(const std::string& windowName, const std::string& key, 
		const std::string& value);
	/**
	注册CEGUI控件事件
	params:
	@windowName		要注册事件的控件名称
	@eventName		注册的控件事件
	@subscriber		事件触发时的回调函数
	*/
	static void cegui_SubscribeEvent(const CEGUI::String& windowName, 
		const CEGUI::String& eventName, 
		const CEGUI::Event::Subscriber& subscriber);
	// 得到system
	inline CEGUI::System* cegui_GetSystem()
	{
		return mGuiSystem;
	}
	// 得到窗口管理器，用来获取管理GUI的窗口对象的管理器
	inline CEGUI::WindowManager* cegui_GetGuiWindowMgr()
	{
		return mWinMgr->getSingletonPtr();
	}
	// 注入CEGUI鼠标点击事件
	bool cegui_InjectMouseBtnDwn(CEGUI::MouseButton id)
	{
		return mGuiSystem->injectMouseButtonDown(id);
	}
	bool cegui_InjectMouseBtnUp(CEGUI::MouseButton id)
	{
		return mGuiSystem->injectMouseButtonUp(id);
	}
	// 注入CEGUI鼠标移动事件
	bool cegui_InjectMouseMove(float xRel, float yRel)
	{
		return mGuiSystem->injectMouseMove(xRel, yRel);
	}
	// 显示/隐藏GUI鼠标
	inline void cegui_ShowGuiCursor(bool showCursor)
	{
		if (showCursor)
			CEGUI::MouseCursor::getSingleton().show();
		else
			CEGUI::MouseCursor::getSingleton().hide();
		// 隐藏系统鼠标
		//ShowCursor(false);
	}
	/**
	设置默认鼠标样式
	params:
	@schemeName		样式名称
	@mouseName		样式中的鼠标名称
	*/
	inline void cegui_SetDefaultMouseCursor(const std::string& schemeName, const std::string& mouseName)
	{
		CEGUI::System::getSingleton().setDefaultMouseCursor(schemeName, mouseName);
		CEGUI::MouseCursor::getSingleton().setImage(mGuiSystem->getDefaultMouseCursor());
	}
	// 输出中文字符
	const CEGUI::String& cegui_showChinese(const Ogre::String& strChinese);

	bool cegui_CreateQuitBtn(void); // 创建退出按钮

public:
	/**
	单件实例方法
	*/
	static GuiSystem* getSingletonPtr()
	{
		if (ms_singleton == NULL)
		{
			ms_singleton = new GuiSystem;
		}
		return ms_singleton;
	}
private:
	// 单件实例指针
	static GuiSystem* ms_singleton;
private:
	/**
	私有化实例函数，实现单件
	*/
	GuiSystem()
		:mGUIRenderer(0), mGuiSystem(0)
	{}
	GuiSystem(const GuiSystem&);
	GuiSystem& operator=(const GuiSystem&);

private:
	CEGUI::OgreRenderer* mGUIRenderer; // Cegui渲染环境
	CEGUI::System* mGuiSystem; // 渲染系统
	CEGUI::WindowManager* mWinMgr; // 窗口管理器
	CEGUI::DefaultWindow* rootWindow; // 根窗口，不显示
};

#endif