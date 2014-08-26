/**
File System:
@description: This section executes the file input and output, i.e., saving and
	loading data.
@created: 2013.8.27
@author: ������
@reference:
	1. ��Ϸ������Ƹ���, P132-137, 
*/

// Start of FinalEngine namespace section
namespace FinalEngine
{

	// ������Ϸ����
	void SaveGame(void)
	{
		HANDLE hFile;
		SECURITY_ATTRIBUTES sa;
		DWORD dwNum;

		memset(&sa, 0, sizeof(sa));

		// �����浵�ļ�
		hFile = CreateFile("SaveGame.save", 
			GENERIC_WRITE, FILE_SHARE_READ, &sa, OPEN_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, "��ȡ�����ļ�ʧ�ܣ�", "Game Error", MB_ICONINFORMATION | MB_OK);
				return;
		}
	}

} // End of FinalEngine namespace section