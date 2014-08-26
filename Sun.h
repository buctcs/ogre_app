#ifndef _FD_SUN_H_
#define _FD_SUN_H_

#pragma once

#include "stdafx.h"

class Sun
{
protected:
	long double sunMass; // 太阳质量
	long double sunVelocity; // 太阳速度
	long double sunAcc; // 太阳加速度
	Vector3 sunPosition; // 太阳位置

public:
	Sun(void);
	virtual ~Sun(void);

public:
	bool createSun(long double mass); // 创建太阳对象
	bool setSunMass(long double mass); // 设置太阳质量
	long double getSunMass(); // 获取太阳质量
	void destroySun(); // 销毁太阳对象
	char* getShowString(); // 获取太阳的各项参数和状态信息用于显示
};

#endif