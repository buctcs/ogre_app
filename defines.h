#ifndef __DEFINES_H_
#define __DEFINES_H_

#include "stdafx.h"
#include "SoundSystem.h"
#include "GuiSystem.h"

// 一些外部声明
extern SoundSystem mySoundSys;
extern GuiSystem* myGuiSys;
extern float gTimeFactor;

struct TimeDef // 定义各阶段所需的时间参数
{
	float startTime; // 系统启动时间（相对于计算机启动时间）
	float gameStartTime; // 开始进行游戏内容的时间（相对于计算机启动时间）
	float systemTime; // 系统时间，系统启动后经过的时间
	float gameTime; // 游戏经过的时间
	SYSTEMTIME localTime; // 当地实际时间
	float finalLogoStartTime; // 
};
extern TimeDef gTimeDef;

struct Final3DParams // 用于Application和FrameListener之间传递参数的结构（创建帧听器时）
{
	/** 
	以下各项均是传递的参数
	*/
	SceneNode* EarthNode; // 地球节点
	Entity* Earth; // 地球实体
	SceneNode* MoonNode; // 月球节点
	SceneNode* SunNode; // 太阳节点
	SceneNode* RevSunNode; // 绕日公转节点（太阳节点的子节点），所有需要绕日公转的星球均挂在其下。
	Ogre::RaySceneQuery* mRaySceneQuery; // 射线查询
	Ogre::AnimationState* mAnimState; // ogre实体动画状态
	bool mContinue; // 是否继续渲染
	bool mStartTrack; // 是否开始轨迹动画
	bool mExitUI; // 是否退出UI
	SceneNode* mCurrentNode; // 当前点击节点
	Ogre::AnimationState* mCharaAnimState; // 角色动画状态
	Ogre::AnimationState* mBackupCharaAnimState; // 备用角色动画状态
	CEGUI::AnimationInstance* animInst1;
	CEGUI::AnimationInstance* animInstShow;
	int eggCount; // 主菜单时计数空格键按下次数，以激活彩蛋
	SceneNode* mCharaNode; // 创建角色时的角色节点
	SceneNode* mCamNode; // 当前绑定到摄像机的场景节点
};
extern Final3DParams gF3DParams;

// 声音内容的定义
enum SoundID
{
	SpaceSound = 0,	// He's a Pirate.mp3
	EarthSound = 1,	// Going Home.mp3
	MoonSound = 2,	// Fly Me To The Moon.mp3
	SunSound = 3,	// I See The Light.mp3
	MarsSound = 4,	// A Thousand Years.mp3(电影Red Planet插曲)
	EarthSound2 = 5	// far away from home.mp3
};

// 射线查询，用于区分不同种射线
enum QueryMask
{
	QUERY_MASK = 1<<0,	// 可查询
	HIDE_MASK = 1<<1		// 不可查询
};

// 游戏进行到各阶段的标志
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