#include "defines.h"


SoundSystem mySoundSys; // 声音系统
GuiSystem* myGuiSys = GuiSystem::getSingletonPtr(); // 界面系统

float gTimeFactor = 1; // 系统时间与真实时间速度比例

Final3DParams gF3DParams; // // 传递参数结构

TimeDef gTimeDef = {0, 0, 0, 0, 0}; // 时间定义

PhaseMark gPhaseMark = HealthyGaming; // 游戏进行到各阶段的标志

// 一些物理学常量
long double gGfactor = 6.67259 / 100000000000.0; // 牛顿引力常数（单位为m^3/kg/s^2）
long double gSunMass = 1989 * pow(10.0, 27.0); // 太阳质量（单位为kg）
long double gSunRadius = 696 * pow(10.0, 6.0); // 太阳半径（单位为m）
long double gSun2Earth = 1.4959787 * pow(10.0, 11.0); // 日地平均距离（单位为m）
float gEarthRadius = 6378200.0; // 地球半径（单位为m）
float gMoonRadius = 1737400; // 月球半径（单位为m）
float gMoon2Earth = 384401000; // 地月平均距离（单位为m）