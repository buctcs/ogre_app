#pragma once
#ifndef __OGRE_APP_H__
#define __OGRE_APP_H__


#include "stdafx.h"
#include "defines.h"
#include "ThreeDimentionalApplication.h"

using namespace Ogre;
class OgreApp :
	public ThreeDimentionalApplication
{
	enum CharaType
	{
		CHARA_A,
		CHARA_B,
		CHARA_C
	};

public:
	OgreApp(void)
	{
		// 初始化轨迹动画和UI参数
		gF3DParams.mStartTrack = false;
		gF3DParams.mExitUI = true;

		// 初始创建角色GUI的参数
		gF3DParams.mCharaAnimState = NULL;
		gF3DParams.mBackupCharaAnimState = NULL;
	}

	virtual ~OgreApp(void) {}

protected:
	void gameProgress(void);
	// 设置游戏开始时的GUI
	void setupStartGui(void);
	// 设置主选单
	void setupMainMenu(void);
	// 主选单中可重复调用的内容
	void initMainMenu(void);
	// 设置创建角色界面
	void setupCharaGui();
	// 从GUI创建角色
	void createChara(CharaType charaType);
	// 设置开始游戏后的UI
	void setupGamingUI(void);
	// 初始化3D场景
	void init3dScene(void);


	// 创建轨迹动画
	void createTrackAnimation();
	// 创建粒子系统
	virtual void createParticle();



public:
	// 主菜单，鼠标移动到按钮时响应
	bool mainMenuBtnHover(const CEGUI::EventArgs& e);
	// 主菜单，鼠标移出按钮时响应
	bool mainMenuBtnBack(const CEGUI::EventArgs& e);
	// 主菜单，点击按钮时响应
	bool mainMenuBtnDwn(const CEGUI::EventArgs& e);
	// 退出窗口，退出游戏响应
	bool QuitGame(const CEGUI::EventArgs& e);
	// 退出窗口，取消退出游戏响应
	bool CancelQuit(const CEGUI::EventArgs& e);
	// 未完成提示窗口，返回
	bool CancelReady(const CEGUI::EventArgs& e);
	// 未完成提示窗口，点击取消按钮时的警告响应
	bool NotReadyWarn(const CEGUI::EventArgs& e);
	// 未完成提示窗口，结束警告响应
	bool StopWarn(const CEGUI::EventArgs& e);
	// 创建角色事件响应
	bool charaSelectedHandler(const CEGUI::EventArgs& e);
	// 创建角色界面，当输入框中的文本变化时触发的事件
	bool inputAcceptedHandler(const CEGUI::EventArgs& e);
	// 创建角色界面，开始按钮事件响应
	bool startHandler(const CEGUI::EventArgs& e);
	// 创建角色界面，返回主界面按钮事件响应
	bool backToMain(const CEGUI::EventArgs& e);
	// 创建角色界面，鼠标移入模型区事件响应
	bool enterCharaArea(const CEGUI::EventArgs& e);
	// 创建角色界面，鼠标移出模型区事件响应
	bool leaveCharaArea(const CEGUI::EventArgs& e);
	// 游戏UI，退出UI，返回游戏事件响应
	bool backGaming(const CEGUI::EventArgs& e);



	// 退出按钮事件响应
	//	bool quit(const CEGUI::EventArgs& e);
	// 点击NPC事件响应
	//	bool know(const CEGUI::EventArgs& e);

protected:
	bool isMainCreated; // 主界面是否已创建
	bool isCharaWinCreated; // 角色创建界面是否已创建

	Ogre::String mCharaName; // 角色名字
	Ogre::Entity* mCharaEntA; // 角色A实体
	Ogre::Entity* mCharaEntB; // 角色B实体
	Ogre::Entity* mCharaEntC; // 角色C实体
	CharaType mCharaType; // 保存选择的角色类型
	bool isCharaRollable; // 角色模型是否可以旋转

	SceneNode* mEarthNode; // 地球节点

	CEGUI::OgreRenderer* mGUIRenderer;
	CEGUI::Window* mEditorGuiSheet;

private:

};

#endif