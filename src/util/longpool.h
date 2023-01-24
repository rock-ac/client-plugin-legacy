/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class LongPool
{
private:
	static std::string lastReceive;

public:
	static void handleData();
	static bool getData();
	static void thread();
};