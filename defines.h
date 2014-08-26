#ifndef __DEFINES_H_
#define __DEFINES_H_

#include "stdafx.h"
#include "SoundSystem.h"
#include "GuiSystem.h"

// һЩ�ⲿ����
extern SoundSystem mySoundSys;
extern GuiSystem* myGuiSys;
extern float gTimeFactor;

struct TimeDef // ������׶������ʱ�����
{
	float startTime; // ϵͳ����ʱ�䣨����ڼ��������ʱ�䣩
	float gameStartTime; // ��ʼ������Ϸ���ݵ�ʱ�䣨����ڼ��������ʱ�䣩
	float systemTime; // ϵͳʱ�䣬ϵͳ�����󾭹���ʱ��
	float gameTime; // ��Ϸ������ʱ��
	SYSTEMTIME localTime; // ����ʵ��ʱ��
	float finalLogoStartTime; // 
};
extern TimeDef gTimeDef;

struct Final3DParams // ����Application��FrameListener֮�䴫�ݲ����Ľṹ������֡����ʱ��
{
	/** 
	���¸�����Ǵ��ݵĲ���
	*/
	SceneNode* EarthNode; // ����ڵ�
	Entity* Earth; // ����ʵ��
	SceneNode* MoonNode; // ����ڵ�
	SceneNode* SunNode; // ̫���ڵ�
	SceneNode* RevSunNode; // ���չ�ת�ڵ㣨̫���ڵ���ӽڵ㣩��������Ҫ���չ�ת��������������¡�
	Ogre::RaySceneQuery* mRaySceneQuery; // ���߲�ѯ
	Ogre::AnimationState* mAnimState; // ogreʵ�嶯��״̬
	bool mContinue; // �Ƿ������Ⱦ
	bool mStartTrack; // �Ƿ�ʼ�켣����
	bool mExitUI; // �Ƿ��˳�UI
	SceneNode* mCurrentNode; // ��ǰ����ڵ�
	Ogre::AnimationState* mCharaAnimState; // ��ɫ����״̬
	Ogre::AnimationState* mBackupCharaAnimState; // ���ý�ɫ����״̬
	CEGUI::AnimationInstance* animInst1;
	CEGUI::AnimationInstance* animInstShow;
	int eggCount; // ���˵�ʱ�����ո�����´������Լ���ʵ�
	SceneNode* mCharaNode; // ������ɫʱ�Ľ�ɫ�ڵ�
	SceneNode* mCamNode; // ��ǰ�󶨵�������ĳ����ڵ�
};
extern Final3DParams gF3DParams;

// �������ݵĶ���
enum SoundID
{
	SpaceSound = 0,	// He's a Pirate.mp3
	EarthSound = 1,	// Going Home.mp3
	MoonSound = 2,	// Fly Me To The Moon.mp3
	SunSound = 3,	// I See The Light.mp3
	MarsSound = 4,	// A Thousand Years.mp3(��ӰRed Planet����)
	EarthSound2 = 5	// far away from home.mp3
};

// ���߲�ѯ���������ֲ�ͬ������
enum QueryMask
{
	QUERY_MASK = 1<<0,	// �ɲ�ѯ
	HIDE_MASK = 1<<1		// ���ɲ�ѯ
};

// ��Ϸ���е����׶εı�־
enum PhaseMark
{
	HealthyGaming,
	FinalLogo,
	OgreLogo,
	MainMenu,
	CreateChara,
	IntroChara,
	FinishIntro,
	BeginScene,

	FinalLogoJumpIn,
	FinalLogoShade
};
extern PhaseMark gPhaseMark;

#endif