// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "game.h"

bool Game::sendServiceMessage(int mode, const char* msg)
{
	HANDLE hPipe;
	DWORD dwWritten;

	hPipe = LI_FN(CreateFileW).get()(XorStrW(TEXT("\\\\.\\pipe\\rockAnticheat")),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hPipe != INVALID_HANDLE_VALUE)
	{
		char buf[256];
		switch (mode)
		{
			case 0:
				sprintf(buf, XorStr("detect^%s"), msg);
				break;

			case 1:
				sprintf(buf, XorStr("error^%s"), msg);
				break;
		}
		
		LI_FN(WriteFile).get()(hPipe,
			buf,
			strlen(buf),   // = length of string + terminating '\0' !!!
			&dwWritten,
			NULL);

		LI_FN(CloseHandle).get()(hPipe);
		return true;
	}
	
	return false;
}

bool Game::TerminateGame(int mode, std::string info)
{
	bool res = Game::sendServiceMessage(mode, info.c_str());

	const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, Core::getProcessID(XorStrW(L"gta_sa.exe")));
	LI_FN(TerminateProcess).get()(explorer, 1);
	LI_FN(CloseHandle).get()(explorer);

	exit(1);
}

unsigned int Game::getGameState()
{
	return *reinterpret_cast<unsigned int*>(0xC8D4C0);
}