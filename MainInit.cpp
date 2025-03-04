#include "stdafx.h"
#include "MainInit.h"

int MainInit::Init()
{
	std::wstring driveList(MAX_PATH, 0);
	driveList.resize((size_t)GetLogicalDriveStringsW((int)driveList.size(), &driveList[0]));
	if (!driveList.empty())
	{
		std::wstring fullPath(MAX_PATH, 0);
		std::wstring drive = driveList;
		while (!drive.empty())
		{
			int driveType = GetDriveTypeW(drive.c_str());
			if (driveType == DRIVE_CDROM || driveType == DRIVE_REMOVABLE) {
				if (Grass7API::FileManagement::FindFile(drive.c_str(), L"gr7setup.exe", &fullPath[0]))
				{
					std::wstring path = L"\"" + fullPath + L"\"";
					STARTUPINFO info = { sizeof(info) };
					PROCESS_INFORMATION processInfo;
					if (CreateProcessW(nullptr, &path[0], nullptr, nullptr, TRUE, 0, nullptr, nullptr, &info, &processInfo))
					{
						WaitForSingleObject(processInfo.hProcess, INFINITE);
						CloseHandle(processInfo.hProcess);
						CloseHandle(processInfo.hThread);
					}
					drive.clear();
				}
			}
			std::wstring string1 = &drive[0];
			drive.erase(0, string1.size() + 1);
		}
	}

	return 0;
}