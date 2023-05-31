// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "longpool.h"

std::string LongPool::lastReceive = "";

void LongPool::handleData()
{
	if (!(LongPool::lastReceive.empty()))
	{
		std::string str = LongPool::lastReceive;
		//std::string str = Core::xorDecrypt(LongPool::lastReceive);

		if (str == XorStr("0x000001a"))
			Log::write(XorStr("[ERROR] Called error 0x000001a (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000001b"))
			Log::write(XorStr("[ERROR] Called error 0x000001b (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000002a"))
			Log::write(XorStr("[ERROR] Called error 0x000002a (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000002b"))
			Log::write(XorStr("[ERROR] Called error 0x000002b (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000002c"))
			Log::write(XorStr("[ERROR] Called error 0x000002c (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000003a"))
			Log::write(XorStr("[ERROR] Called error 0x000003a (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000004a"))
			Log::write(XorStr("[ERROR] Called error 0x000004a (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000004b"))
			Log::write(XorStr("[ERROR] Called error 0x000004b (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x000005a"))
			Log::write(XorStr("[ERROR] Called error 0x000005a (LongPool::handleData())"));
			Game::TerminateGame(0, str);

		if (str == XorStr("0x0001488"))
			Log::write(XorStr("[ERROR] Called error 0x0001488 - User banned (LongPool::handleData())"));
			Game::TerminateGame(1, XorStr("\n\nВы получили бессрочную блокировку от Rock Anticheat.\n\nАнтичит использует мультикомплексную проверку игры, чтобы убедиться что сторонние программы не используются и не дают игрокам преимущества.\nЕсли система обнаружит подобную программу, на ваш аккаунт будет наложена перманентная блокировка.\n\n"));
	}
}

bool LongPool::getData()
{
	std::string url = Config::URL_REPOSITORY;
	url = url + XorStr("/sessions/") + Session::getSessionID() + XorStr("/");
	std::string tmp = Network::string_sendRequest(url.c_str());

	if (tmp == "SESNF")
	{
		Log::write(XorStr("[ERROR] Called error 0x1000016 - Session not found (LongPool::getData())"));
		if (!Session::sessionStart())
		{
			Log::write(XorStr("[ERROR] Called error: 0x1000010 (Session::sessionStart()) lastNetworkError: %ld"), Network::lastError);
			Game::TerminateGame(1, XorStr("0x1000010"));
		}
	}
	else
	{
		LongPool::lastReceive = tmp;
	}

	return true;
}

void LongPool::thread()
{
	Log::write(XorStr("LongPool::thread() started"));
	DWORD pid = Core::getProcessID(XorStrW(L"gta_sa.exe"));
	do
	{
		LI_FN(Sleep).get()(Config::LONGPOOL_GET_SLEEP);
		if (LongPool::getData())
		{
			LongPool::handleData();
		}
	} while (pid != 0);
}