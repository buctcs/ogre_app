#include "main.h"
#include "defines.h"

// 判断编译平台
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

// Win32平台
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
// 非Win32平台
int main(int argc, char** argv)

#endif

{
	// Create application object.
	OgreApp app;
	// 系统启动时间
	gTimeDef.startTime = GetTickCount() * 0.001f;
	// 执行go函数，开始应用程序过程
	app.go();

	return 0;
}