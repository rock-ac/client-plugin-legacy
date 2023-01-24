/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class Modules
{
public:
	static bool inspectModules(DWORD pid);
	static long verifyMicrosoftSignature(LPCSTR path);
	static bool verifyPublisher(LPCSTR path);
	static std::string getPublisher(LPCSTR path);

	static void thread();
};