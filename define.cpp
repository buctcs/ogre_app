#include "defines.h"


SoundSystem mySoundSys; // ����ϵͳ
GuiSystem* myGuiSys = GuiSystem::getSingletonPtr(); // ����ϵͳ

float gTimeFactor = 1; // ϵͳʱ������ʵʱ���ٶȱ���

Final3DParams gF3DParams; // // ���ݲ����ṹ

TimeDef gTimeDef = {0, 0, 0, 0, 0}; // ʱ�䶨��

PhaseMark gPhaseMark = HealthyGaming; // ��Ϸ���е����׶εı�־

// һЩ����ѧ����
long double gGfactor = 6.67259 / 100000000000.0; // ţ��������������λΪm^3/kg/s^2��
long double gSunMass = 1989 * pow(10.0, 27.0); // ̫����������λΪkg��
long double gSunRadius = 696 * pow(10.0, 6.0); // ̫���뾶����λΪm��
long double gSun2Earth = 1.4959787 * pow(10.0, 11.0); // �յ�ƽ�����루��λΪm��
float gEarthRadius = 6378200.0; // ����뾶����λΪm��
float gMoonRadius = 1737400; // ����뾶����λΪm��
float gMoon2Earth = 384401000; // ����ƽ�����루��λΪm��