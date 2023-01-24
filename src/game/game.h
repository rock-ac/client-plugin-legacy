/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class Game
{
public:
	static bool sendServiceMessage(int mode, const char* msg);
	static bool TerminateGame(int mode, std::string info);
	static unsigned int getGameState();
};