#ifndef _FD_SUN_H_
#define _FD_SUN_H_

#pragma once

#include "stdafx.h"

class Sun
{
protected:
	long double sunMass; // ̫������
	long double sunVelocity; // ̫���ٶ�
	long double sunAcc; // ̫�����ٶ�
	Vector3 sunPosition; // ̫��λ��

public:
	Sun(void);
	virtual ~Sun(void);

public:
	bool createSun(long double mass); // ����̫������
	bool setSunMass(long double mass); // ����̫������
	long double getSunMass(); // ��ȡ̫������
	void destroySun(); // ����̫������
	char* getShowString(); // ��ȡ̫���ĸ��������״̬��Ϣ������ʾ
};

#endif