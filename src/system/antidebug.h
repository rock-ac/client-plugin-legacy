/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class AntiDebugger {
public:
	static bool closeDebuggers();

	static bool checkPEB();
	static bool checkRemoteDebugger();
	static bool checkDebugger();
	static bool checkHandleException();
	static bool checkSingleStep();

	static bool int3();
	static bool int2d();

	static bool sendDebugString();

	static void thread();
};