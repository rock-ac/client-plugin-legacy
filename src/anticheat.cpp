// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "anticheat.h"

HWND AntiCheat::gtaHwnd;

void AntiCheat::Load()
{
	LI_FN(AllocConsole).get()();
	freopen("CONOUT$", "w", stdout);

	auto kernel_dll = LI_FN(LoadLibraryA)(XorStr("kernel32.dll"));
	if (kernel_dll == NULL)
	{
		Report::ErrorInfo info;
		info.error = std::to_string(GetLastError());
		info.call = XorStr("LoadLibraryA(\"kernel32.dll\")");
		info.ret = XorStr("NULL");
		info.wh = XorStr("AntiCheat::Load()");
		Report::sendErrorReport(&info);

		Game::TerminateGame(1, XorStr("0x1000013"));
	}

	auto user_dll	= LI_FN(LoadLibraryA)(XorStr("User32.dll"));
	if (user_dll == NULL)
	{
		Report::ErrorInfo info;
		info.error = std::to_string(GetLastError());
		info.call = XorStr("LoadLibraryA(\"User32.dll\")");
		info.ret = XorStr("NULL");
		info.wh = XorStr("AntiCheat::Load()");
		Report::sendErrorReport(&info);

		Game::TerminateGame(1, XorStr("0x1000013"));
	}

	auto psapi_dll = LI_FN(LoadLibraryA)(XorStr("Psapi.dll"));
	if (psapi_dll == NULL)
	{
		Report::ErrorInfo info;
		info.error = std::to_string(GetLastError());
		info.call = XorStr("LoadLibraryA(\"Psapi.dll\")");
		info.ret = XorStr("NULL");
		info.wh = XorStr("AntiCheat::Load()");
		Report::sendErrorReport(&info);

		Game::TerminateGame(1, XorStr("0x1000013"));
	}

	auto advapi_dll = LI_FN(LoadLibraryA)(XorStr("Advapi32.dll"));
	if (advapi_dll == NULL)
	{
		Report::ErrorInfo info;
		info.error = std::to_string(GetLastError());
		info.call = XorStr("LoadLibraryA(\"Advapi32.dll\")");
		info.ret = XorStr("NULL");
		info.wh = XorStr("AntiCheat::Load()");
		Report::sendErrorReport(&info);

		Game::TerminateGame(1, XorStr("0x1000013"));
	}

	auto iphlpapi_dll = LI_FN(LoadLibraryA)(XorStr("Iphlpapi.dll"));
	if (iphlpapi_dll == NULL)
	{
		Report::ErrorInfo info;
		info.error = std::to_string(GetLastError());
		info.call = XorStr("LoadLibraryA(\"Iphlpapi.dll\")");
		info.ret = XorStr("NULL");
		info.wh = XorStr("AntiCheat::Load()");
		Report::sendErrorReport(&info);

		Game::TerminateGame(1, XorStr("0x1000013"));
	}

	auto libcurl_dll = LI_FN(LoadLibraryA)((Core::getCurrentDirectory() + XorStr("\\libcurl.dll")).c_str());
	if (libcurl_dll == NULL)
	{
		Report::ErrorInfo info;
		info.error = std::to_string(GetLastError());
		info.call = XorStr("LoadLibraryA(\"libcurl.dll\")");
		info.ret = XorStr("NULL");
		info.wh = XorStr("AntiCheat::Load()");
		Report::sendErrorReport(&info);

		Game::TerminateGame(1, XorStr("0x1000013"));
	}

	const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, Core::getProcessID(XorStrW(L"rockACService.exe")));
	LI_FN(TerminateProcess).get()(explorer, 1);
	LI_FN(CloseHandle).get()(explorer);

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	std::wstring path = Core::string_to_wstring(Core::getCurrentDirectory() + XorStr("/rockACService.exe"));
	std::wstring cmd = XorStrW(L"");

	if (!LI_FN(CreateProcessW).get()(path.c_str(), &cmd[0], nullptr, nullptr, false, DETACHED_PROCESS, nullptr, nullptr, &info, &processInfo))
	{
		Game::TerminateGame(1, XorStr("0x1000012"));
	}

	/*if (!Core::IsElevated())
	{
		Game::TerminateGame(1, XorStr("Необходим запуск от имени администратора!"));
	}*/

	if (!Hardware::getMacAddress())
	{
		Game::TerminateGame(1, XorStr("0x7000001"));
	}
	if (!Hardware::getDriveGUID())
	{
		Game::TerminateGame(1, XorStr("0x7000002"));
	}
	if (!Hardware::getCPUHash())
	{
		Game::TerminateGame(1, XorStr("0x7000003"));
	}
	if (!Hardware::getPCName())
	{
		Game::TerminateGame(1, XorStr("0x7000004"));
	}
	if (!Hardware::getUserGUID()) 
	{
		Game::TerminateGame(1, XorStr("0x7000005"));
	}
	if (!Hardware::getMotherboardSerial())
	{
		Game::TerminateGame(1, XorStr("0x7000006"));
	}

	if (!Session::sessionStart())
	{
		Game::TerminateGame(1, XorStr("0x1000010"));
	}

	std::thread patternThread(Pattern::thread);
	patternThread.detach();

	std::thread debuggerThread(AntiDebugger::thread);
	debuggerThread.detach();

	std::thread sampfuncsThread(SampFuncs::thread);
	sampfuncsThread.detach();

	//std::thread patchesThread(Patches::thread);
	//patchesThread.detach();

	// activity thread
	std::thread activityThread(Session::thread);
	activityThread.detach();

	GameVirtual::checkVirtualMachine();

	// check Memory thread
	std::thread checkMemory(GameMemory::thread);
	checkMemory.detach();

	// check window list
	std::thread windowThread(GameWindow::check);
	windowThread.detach();

	// check cleo folder
	GameCleo::checkCleo();

	std::thread checkModule(Modules::thread);
	checkModule.detach();

	// longpool thread
	std::thread longpoolThread(LongPool::thread);
	longpoolThread.detach();
}

void AntiCheat::Unload()
{
}