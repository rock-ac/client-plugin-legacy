/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class Session
{
private:
	static std::string uniqueSesionID;
	static bool cheatAllowed;

public:
	static bool sessionStart();
	static std::string getSessionID();
	static void updateActivity();

	static void thread();
};