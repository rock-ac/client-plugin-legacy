// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "longpool.h"

std::string LongPool::lastReceive;

void LongPool::handleData()
{
	if (!(LongPool::lastReceive.empty()))
	{
		std::string str = LongPool::lastReceive;
		//std::string str = Core::xorDecrypt(LongPool::lastReceive);

		if (str == XorStr("0x000001a"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000001b"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000002a"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000002b"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000002c"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000003a"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000004a"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000004b"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000005a"))
			Game::TerminateGame(0, str);

		if (str == XorStr("0x0001488"))
			Game::TerminateGame(1, XorStr("\n\nВы получили бессрочную блокировку от Rock Anticheat.\n\nАнтичит использует мультикомплексную проверку игры, чтобы убедиться что сторонние программы не используются и не дают игрокам преимущества.\nЕсли система обнаружит подобную программу, на ваш аккаунт будет наложена перманентная блокировка.\n\n"));
	}
}

bool LongPool::getData()
{
	std::string url = Config::URL_REPOSITORY;
	url = url + XorStr("/sessions/") + Session::getSessionID() + XorStr("/");
	LongPool::lastReceive = Network::string_sendRequest(url.c_str());

	return true;
}

void LongPool::thread()
{
	DWORD pid = Core::getProcessID(XorStrW(L"gta_sa.exe"));
	do
	{
		LI_FN(Sleep).get()(Config::LONGPOOL_GET_SLEEP);
		LongPool::getData();

		LongPool::handleData();
	} while (pid != 0);
}