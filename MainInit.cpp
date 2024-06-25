#include "stdafx.h"
#include "MainInit.h"

int MainInit::Init(MSG &msg, HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow)
{
	WCHAR drives[256] = {};
	if (GetLogicalDriveStringsW(256, drives))
	{
		WCHAR fullPath[MAX_PATH] = {};

		LPWSTR drive = drives;
		while (*drive)
		{
			int driveType = GetDriveTypeW(drive);
			if (driveType == DRIVE_CDROM || driveType == DRIVE_REMOVABLE) {
				if (Grass7API::FileManagement::FindFile(drive, L"gr7setup.exe", fullPath))
				{
					STARTUPINFO info = { sizeof(info) };
					PROCESS_INFORMATION processInfo;
					if (CreateProcessW(NULL, fullPath, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
					{
						WaitForSingleObject(processInfo.hProcess, INFINITE);
						CloseHandle(processInfo.hProcess);
						CloseHandle(processInfo.hThread);
					}
				}
			}
			drive += (lstrlenW(drive) + 1);
		}
	}

	return 0;
}