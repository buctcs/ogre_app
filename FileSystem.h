/**
File System:
@description: This section executes the file input and output, i.e., saving and
	loading data.
@created: 2013.8.27
@author: 贾林林
@reference:
	1. 游戏程序设计概论, P132-137, 
*/

// Start of FinalEngine namespace section
namespace FinalEngine
{

	// 储存游戏进度
	void SaveGame(void)
	{
		HANDLE hFile;
		SECURITY_ATTRIBUTES sa;
		DWORD dwNum;

		memset(&sa, 0, sizeof(sa));

		// 创建存档文件
		hFile = CreateFile("SaveGame.save", 
			GENERIC_WRITE, FILE_SHARE_READ, &sa, OPEN_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, "读取数据文件失败！", "Game Error", MB_ICONINFORMATION | MB_OK);
				return;
		}
	}

} // End of FinalEngine namespace section