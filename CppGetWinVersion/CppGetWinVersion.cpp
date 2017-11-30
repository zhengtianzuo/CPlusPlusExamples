
#include <Windows.h>  
#include <string>
#include <iostream>

using namespace std;

//获取8.1以下版本操作系统名称
string GetSystemVersion()
{
	string strOSVersion = ("Unknown Microsoft Windows Version");

	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (!GetVersionEx((OSVERSIONINFO *)&os)) return(strOSVersion);

	switch (os.dwMajorVersion)
	{
	case 4:
		switch (os.dwMinorVersion)
		{
		case 0:
			if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
				strOSVersion = ("Microsoft Windows NT 4.0");
			else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
				strOSVersion = ("Microsoft Windows 95");
			break;
		case 10:
			strOSVersion = ("Microsoft Windows 98");
			break;
		case 90:
			strOSVersion = ("Microsoft Windows Me");
			break;
		}
		break;
	case 5:
		switch (os.dwMinorVersion)
		{
		case 0:
			strOSVersion = ("Microsoft Windows 2000");
			break;

		case 1:
			strOSVersion = ("Microsoft Windows XP");
			break;

		case 2:
		{
			SYSTEM_INFO info;
			GetSystemInfo(&info);
			if (os.wProductType == VER_NT_WORKSTATION
				&& info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			{
				strOSVersion = ("Microsoft Windows XP Professional x64 Edition");
			}
			else if (GetSystemMetrics(SM_SERVERR2) == 0)
				strOSVersion = ("Microsoft Windows Server 2003");
			else if (GetSystemMetrics(SM_SERVERR2) != 0)
				strOSVersion = ("Microsoft Windows Server 2003 R2");
		}
			break;
		}
		break;

	case 6:
		switch (os.dwMinorVersion)
		{
		case 0:
			if (os.wProductType == VER_NT_WORKSTATION)
				strOSVersion = ("Microsoft Windows Vista");
			else
				strOSVersion = ("Microsoft Windows Server 2008");
			break;
		case 1:
			if (os.wProductType == VER_NT_WORKSTATION)
				strOSVersion = ("Microsoft Windows 7");
			else
				strOSVersion = ("Microsoft Windows Server 2008 R2");
			break;
		case 2:
			if (os.wProductType == VER_NT_WORKSTATION)
				strOSVersion = ("Microsoft Windows 8");
			else
				strOSVersion = ("Microsoft Windows Server 2012");
			break;
		}
		break;
	}
	return(strOSVersion);
}

//获取8.1以上版本操作系统名称
string GetSystemVersionNew()
{
	string strOSVersion = "";

	typedef void(__stdcall*NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibraryA("ntdll.dll");
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)//win 8.1
	{
		if (dwBuildNumber == 4026541440)//WinServer2012R2的BuildNumber号
		{
			strOSVersion = "Microsoft Windows Server 2012 R2";
		}
		else
		{
			strOSVersion = "Microsoft Windows 8.1";
		}
	}
	else if (dwMajor == 10 && dwMinor == 0)//win 10
	{
		if (dwBuildNumber == 4026546233)//Win10的BuildNumber号
		{
			strOSVersion = "Microsoft Windows 10";
		}
		else
		{
			strOSVersion = "Microsoft Windows Server 2016";
		}
	}
	return(strOSVersion);
}

int main()
{
	string sysVersion = GetSystemVersionNew();
	cout << sysVersion << endl;
	if (sysVersion == "")
	{
		sysVersion = GetSystemVersion();
		cout << sysVersion << endl;
	}
}

