// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "session.h"

std::string Session::uniqueSesionID;

bool Session::sessionStart()
{
	const auto p1 = std::chrono::system_clock::now();
	int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();

	std::string sessionHash;
	sessionHash = std::to_string(timestamp) + XorStr("glock2022prod!)stalker");
	std::size_t str_hash = std::hash<std::string>{}(sessionHash);
	sessionHash = std::to_string(str_hash);

	Session::uniqueSesionID = sessionHash;

	// create session
	std::string url = Config::URL_REPOSITORY + XorStr("/session.php?start=accept");
	url = url + XorStr("&sessionId=") + getSessionID();
	url = url + XorStr("&cpu_hash=") + Hardware::cpu_hash;
	url = url + XorStr("&pc_name=") + Hardware::pc_name;

	// mac
	url = url + XorStr("&mac_len=") + std::to_string(Hardware::mac_address.size());
	for (std::vector<std::string>::iterator i = Hardware::mac_address.begin(); i != Hardware::mac_address.end(); ++i) {
		url = url + XorStr("&mac_") + std::to_string(std::distance(Hardware::mac_address.begin(), i)) + "=" + *i;
	}

	// hwid
	url = url + XorStr("&hwid_len=") + std::to_string(Hardware::guid_drives.size());
	for (std::vector<std::string>::iterator i = Hardware::guid_drives.begin(); i != Hardware::guid_drives.end(); ++i) {
		url = url + XorStr("&hwid_") + std::to_string(std::distance(Hardware::guid_drives.begin(), i)) + "=" + *i;
	}

	url = url + XorStr("&guid=") + Hardware::user_guid;
	url = url + XorStr("&motherboard=") + Hardware::motherboard_serial;
	url = url + XorStr("&username=") + Core::getUsername();

	Network::void_sendRequest(url.c_str());

	if (Network::lastError != 200)
	{
		return false;
	}
	return true;
}

void Session::updateActivity()
{
	std::string url = Config::URL_REPOSITORY + XorStr("/session.php?start=update");

	url = url + XorStr("&sessionId=") + getSessionID();

	Network::void_sendRequest(url.c_str());
}
void Session::thread()
{
	DWORD pid = Core::getProcessID(XorStrW(L"gta_sa.exe"));
	do
	{
		Session::updateActivity();
		LI_FN(Sleep).get()(Config::ACTIVITY_UPDATE_SLEEP);
	} while (pid != 0);
}

std::string Session::getSessionID()
{
	return Session::uniqueSesionID;
}
