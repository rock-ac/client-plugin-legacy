// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "config.h"

std::string Config::URL_REPOSITORY = XorStr("https://rockac.stalker-rp.net/api");
std::string Config::AES_KEY		   = XorStr("68331F74E7F96F238FCB5517F3E7D298A704FFA75B1ABCB4850A6DAC2632A48B");
std::string Config::AES_IV		   = XorStr("8D85DDD410391A3353C181285BFDC1C9");

// TIMING
DWORD Config::MEMORY_CHECK_SLEEP			= 15000;
DWORD Config::WINDOW_CHECK_SLEEP			= 5000;
DWORD Config::MODULES_CHECK_SLEEP			= 5000;
DWORD Config::SAMPFUNCS_CHECK_SLEEP			= 30000;
DWORD Config::MEMORY_PATTERN_CHECK_SLEEP	= 5000;
DWORD Config::DEBUGGER_CHECK_SLEEP			= 5000;

DWORD Config::LONGPOOL_GET_SLEEP			= 1000;
DWORD Config::ACTIVITY_UPDATE_SLEEP			= 10000;