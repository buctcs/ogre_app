#include "main.h"
#include "defines.h"

// �жϱ���ƽ̨
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

// Win32ƽ̨
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
// ��Win32ƽ̨
int main(int argc, char** argv)

#endif

{
	// Create application object.
	OgreApp app;
	// ϵͳ����ʱ��
	gTimeDef.startTime = GetTickCount() * 0.001f;
	// ִ��go��������ʼӦ�ó������
	app.go();

	return 0;
}