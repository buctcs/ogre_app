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
		// ��ʼ���켣������UI����
		gF3DParams.mStartTrack = false;
		gF3DParams.mExitUI = true;

		// ��ʼ������ɫGUI�Ĳ���
		gF3DParams.mCharaAnimState = NULL;
		gF3DParams.mBackupCharaAnimState = NULL;
	}

	virtual ~OgreApp(void) {}

protected:
	void gameProgress(void);
	// ������Ϸ��ʼʱ��GUI
	void setupStartGui(void);
	// ������ѡ��
	void setupMainMenu(void);
	// ��ѡ���п��ظ����õ�����
	void initMainMenu(void);
	// ���ô�����ɫ����
	void setupCharaGui();
	// ��GUI������ɫ
	void createChara(CharaType charaType);
	// ���ÿ�ʼ��Ϸ���UI
	void setupGamingUI(void);
	// ��ʼ��3D����
	void init3dScene(void);


	// �����켣����
	void createTrackAnimation();
	// ��������ϵͳ
	virtual void createParticle();



public:
	// ���˵�������ƶ�����ťʱ��Ӧ
	bool mainMenuBtnHover(const CEGUI::EventArgs& e);
	// ���˵�������Ƴ���ťʱ��Ӧ
	bool mainMenuBtnBack(const CEGUI::EventArgs& e);
	// ���˵��������ťʱ��Ӧ
	bool mainMenuBtnDwn(const CEGUI::EventArgs& e);
	// �˳����ڣ��˳���Ϸ��Ӧ
	bool QuitGame(const CEGUI::EventArgs& e);
	// �˳����ڣ�ȡ���˳���Ϸ��Ӧ
	bool CancelQuit(const CEGUI::EventArgs& e);
	// δ�����ʾ���ڣ�����
	bool CancelReady(const CEGUI::EventArgs& e);
	// δ�����ʾ���ڣ����ȡ����ťʱ�ľ�����Ӧ
	bool NotReadyWarn(const CEGUI::EventArgs& e);
	// δ�����ʾ���ڣ�����������Ӧ
	bool StopWarn(const CEGUI::EventArgs& e);
	// ������ɫ�¼���Ӧ
	bool charaSelectedHandler(const CEGUI::EventArgs& e);
	// ������ɫ���棬��������е��ı��仯ʱ�������¼�
	bool inputAcceptedHandler(const CEGUI::EventArgs& e);
	// ������ɫ���棬��ʼ��ť�¼���Ӧ
	bool startHandler(const CEGUI::EventArgs& e);
	// ������ɫ���棬���������水ť�¼���Ӧ
	bool backToMain(const CEGUI::EventArgs& e);
	// ������ɫ���棬�������ģ�����¼���Ӧ
	bool enterCharaArea(const CEGUI::EventArgs& e);
	// ������ɫ���棬����Ƴ�ģ�����¼���Ӧ
	bool leaveCharaArea(const CEGUI::EventArgs& e);
	// ��ϷUI���˳�UI��������Ϸ�¼���Ӧ
	bool backGaming(const CEGUI::EventArgs& e);



	// �˳���ť�¼���Ӧ
	//	bool quit(const CEGUI::EventArgs& e);
	// ���NPC�¼���Ӧ
	//	bool know(const CEGUI::EventArgs& e);

protected:
	bool isMainCreated; // �������Ƿ��Ѵ���
	bool isCharaWinCreated; // ��ɫ���������Ƿ��Ѵ���

	Ogre::String mCharaName; // ��ɫ����
	Ogre::Entity* mCharaEntA; // ��ɫAʵ��
	Ogre::Entity* mCharaEntB; // ��ɫBʵ��
	Ogre::Entity* mCharaEntC; // ��ɫCʵ��
	CharaType mCharaType; // ����ѡ��Ľ�ɫ����
	bool isCharaRollable; // ��ɫģ���Ƿ������ת

	SceneNode* mEarthNode; // ����ڵ�

	CEGUI::OgreRenderer* mGUIRenderer;
	CEGUI::Window* mEditorGuiSheet;

private:

};

#endif