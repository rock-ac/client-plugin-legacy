// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "log.h"

void Log::openLog()
{
	std::ofstream logFile;
	char buf[1024];

	sprintf(buf, "%s/rockAC.log", Core::getCurrentDirectory().c_str());
	logFile.open(buf);

	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	sprintf(buf, "[%d-%d-%d-%d-%d-%d] RockAC start.", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
	std::string buffer(buf);

	mine::AES aesManager;
	buffer = aesManager.encrypt(buffer, Config::AES_KEY, Config::AES_IV, mine::MineCommon::Encoding::Raw, mine::MineCommon::Encoding::Base64);

	logFile << buffer.c_str();
	logFile << XorStr("\n");

	logFile.close();
}

void Log::write(const char* fmt, ...)
{
	std::ofstream logFile;
	char buf[4096];

	va_list args;
	va_start(args, fmt);

	sprintf(buf, "%s/rockAC.log", Core::getCurrentDirectory().c_str());
	logFile.open(buf, std::ios::app);

	// time
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

	char buff[4096];

	vsprintf(buff, fmt, args);
	sprintf(buf, "[%d-%d-%d-%d-%d-%d] %s", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, buff);

	std::string buffer(buf);

	//printf("%s\n", buffer.c_str());

	mine::AES aesManager;
	buffer = aesManager.encrypt(buffer, Config::AES_KEY, Config::AES_IV, mine::MineCommon::Encoding::Raw, mine::MineCommon::Encoding::Base64);

	logFile << buffer.c_str();
	logFile << XorStr("\n");
	logFile.close();
	va_end(args);
}

void Log::closeLog()
{
	std::ofstream logFile;
	char buf[MAX_PATH];

	sprintf(buf, "%s/rockAC.log", Core::getCurrentDirectory().c_str());
	logFile.open(buf, std::ios::app);

	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	sprintf(buf, "\n--------------\n[%d-%d-%d-%d-%d-%d] RockAC end.\n", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);

	std::string buffer(buf);

	mine::AES aesManager;
	buffer = aesManager.encrypt(buffer, Config::AES_KEY, Config::AES_IV, mine::MineCommon::Encoding::Raw, mine::MineCommon::Encoding::Base64);

	logFile << buffer.c_str();

	logFile.close();

}