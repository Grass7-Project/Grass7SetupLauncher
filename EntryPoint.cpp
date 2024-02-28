#include "stdafx.h"
#include "MainInit.h"
#include <winioctl.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(nCmdShow);
	UNREFERENCED_PARAMETER(hPrevInstance);

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
					/*STARTUPINFO info = { sizeof(info) };
					PROCESS_INFORMATION processInfo;
					SetCurrentDirectoryW(launchpath2);
					if (CreateProcessW(NULL, lp2, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
					{
					WaitForSingleObject(processInfo.hProcess, INFINITE);
					CloseHandle(processInfo.hProcess);
					CloseHandle(processInfo.hThread);
					}*/
					break;
				}
			}
			drive += (lstrlenW(drive) + 1);
		}
	}

	return 0;
}