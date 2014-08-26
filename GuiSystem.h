
#ifndef __GUISYSTEM_H_
#define __GUISYSTEM_H_

class GuiSystem
{
public:
	//GuiSystem(void);
	virtual ~GuiSystem(void);

public:
	// ��ʼ��CEGUI�� ������RenderWindow��ʼ���ʼ, ֻ�ڵ�һ�ε�����Ч
	bool cegui_Init();
	// GUI����
	void cegui_Update(float timeSinceLastFrame);
	// ��OIS�����IDת����CEGUI�����ID
	static CEGUI::MouseButton cegui_ConvertButton(OIS::MouseButtonID buttonId);
	// ������Դ
	bool cegui_Destroy();

	/**
	����ͼƬ����Imageset
	params:
	@name		������Imageset���ƣ�ȫ��Ψһ
	@filename	����Imageset��ͼƬ����
	*/
	static void cegui_CreateImageset(const std::string& name, const std::string& filename);
	// ����layout
	bool cegui_LoadLayout(const std::string& layoutName, bool ifShow = true);
	/** 
	ж��layout��������layout�ĸ�����
	params:
	@layoutName	Ҫж�ص�layout
	return:
	@0				layoutж�سɹ�
	@1				layout�ѱ�ж��
	*/
//	BOOL cegui_UnloadLayout(const std::string& layoutName);
	// �õ�ָ�����ƵĴ���
	inline CEGUI::Window* cegui_GetWindow(const std::string& windowName)
	{
		return cegui_GetGuiWindowMgr()->getWindow(windowName);
	}
	// ����ָ�����ƵĴ���
	bool cegui_DestroyWindow(const std::string& windowName);
	/**
	��ָ�����ƵĴ����趨����
	params:
	@windowName		��������
	@key					XML��ǩ		keyֵ
	@value				XML��ǩ		valueֵ
	*/
	static void cegui_SetProperty(const std::string& windowName, const std::string& key, 
		const std::string& value);
	/**
	ע��CEGUI�ؼ��¼�
	params:
	@windowName		Ҫע���¼��Ŀؼ�����
	@eventName		ע��Ŀؼ��¼�
	@subscriber		�¼�����ʱ�Ļص�����
	*/
	static void cegui_SubscribeEvent(const CEGUI::String& windowName, 
		const CEGUI::String& eventName, 
		const CEGUI::Event::Subscriber& subscriber);
	// �õ�system
	inline CEGUI::System* cegui_GetSystem()
	{
		return mGuiSystem;
	}
	// �õ����ڹ�������������ȡ����GUI�Ĵ��ڶ���Ĺ�����
	inline CEGUI::WindowManager* cegui_GetGuiWindowMgr()
	{
		return mWinMgr->getSingletonPtr();
	}
	// ע��CEGUI������¼�
	bool cegui_InjectMouseBtnDwn(CEGUI::MouseButton id)
	{
		return mGuiSystem->injectMouseButtonDown(id);
	}
	bool cegui_InjectMouseBtnUp(CEGUI::MouseButton id)
	{
		return mGuiSystem->injectMouseButtonUp(id);
	}
	// ע��CEGUI����ƶ��¼�
	bool cegui_InjectMouseMove(float xRel, float yRel)
	{
		return mGuiSystem->injectMouseMove(xRel, yRel);
	}
	// ��ʾ/����GUI���
	inline void cegui_ShowGuiCursor(bool showCursor)
	{
		if (showCursor)
			CEGUI::MouseCursor::getSingleton().show();
		else
			CEGUI::MouseCursor::getSingleton().hide();
		// ����ϵͳ���
		//ShowCursor(false);
	}
	/**
	����Ĭ�������ʽ
	params:
	@schemeName		��ʽ����
	@mouseName		��ʽ�е��������
	*/
	inline void cegui_SetDefaultMouseCursor(const std::string& schemeName, const std::string& mouseName)
	{
		CEGUI::System::getSingleton().setDefaultMouseCursor(schemeName, mouseName);
		CEGUI::MouseCursor::getSingleton().setImage(mGuiSystem->getDefaultMouseCursor());
	}
	// ��������ַ�
	const CEGUI::String& cegui_showChinese(const Ogre::String& strChinese);

	bool cegui_CreateQuitBtn(void); // �����˳���ť

public:
	/**
	����ʵ������
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
	// ����ʵ��ָ��
	static GuiSystem* ms_singleton;
private:
	/**
	˽�л�ʵ��������ʵ�ֵ���
	*/
	GuiSystem()
		:mGUIRenderer(0), mGuiSystem(0)
	{}
	GuiSystem(const GuiSystem&);
	GuiSystem& operator=(const GuiSystem&);

private:
	CEGUI::OgreRenderer* mGUIRenderer; // Cegui��Ⱦ����
	CEGUI::System* mGuiSystem; // ��Ⱦϵͳ
	CEGUI::WindowManager* mWinMgr; // ���ڹ�����
	CEGUI::DefaultWindow* rootWindow; // �����ڣ�����ʾ
};

#endif