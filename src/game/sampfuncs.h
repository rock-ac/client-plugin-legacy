/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

struct SF_PluginsIterator;

class SampFuncs {
public:
	static bool isDisabled;
	static std::vector<std::string> plugins;

	static bool iterPlugins();

	static HMODULE getSFModule();
	static bool isSAMPinitialized();

	static bool disableConsole();

	static void thread();
};