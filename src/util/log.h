/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class Log
{
public:
	static void openLog();
	static void write(const char* fmt, ...);
	static void closeLog();
};