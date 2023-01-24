// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "antidebug.h"

bool AntiDebugger::closeDebuggers()
{
	int closed = 0;

	// PD64
	DWORD pd64_pid;
	pd64_pid = Core::getProcessID(XorStrW(L"pd64.exe"));
	if (pd64_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, pd64_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("pd64");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// Process Hacker
	DWORD ph_pid;
	ph_pid = Core::getProcessID(XorStrW(L"ProcessHacker.exe"));
	if (ph_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, ph_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("Process Hacker");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// IDA
	DWORD ida_pid;
	ida_pid = Core::getProcessID(XorStrW(L"ida.exe"));
	if (ida_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, ida_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("IDA");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// IDA64
	DWORD ida64_pid;
	ida64_pid = Core::getProcessID(XorStrW(L"ida64.exe"));
	if (ida64_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, ida64_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("IDA x64");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// dumpcap
	DWORD dumpcap_pid;
	dumpcap_pid = Core::getProcessID(XorStrW(L"dumpcap.exe"));
	if (dumpcap_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, dumpcap_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("dumpcap");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// Wireshark
	DWORD wireshark_pid;
	wireshark_pid = Core::getProcessID(XorStrW(L"Wireshark.exe"));
	if (wireshark_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, wireshark_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("Wireshark");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// tcpdump
	DWORD tcpdump_pid;
	tcpdump_pid = Core::getProcessID(XorStrW(L"tcpdump.exe"));
	if (tcpdump_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, tcpdump_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("tcpdump");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	// WinDBG
	DWORD windbg_pid;
	windbg_pid = Core::getProcessID(XorStrW(L"windbg.exe"));
	if (windbg_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, windbg_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("WinDBG");
		Report::sendDebuggerReport(&info);
		
		closed++;
	}

	// OllyDBG
	DWORD ollydbg_pid;
	ollydbg_pid = Core::getProcessID(XorStrW(L"OLLYDBG.EXE"));
	if (ollydbg_pid != 0)
	{
		const auto explorer = LI_FN(OpenProcess).get()(PROCESS_TERMINATE, false, ollydbg_pid);
		LI_FN(TerminateProcess).get()(explorer, 1);
		LI_FN(CloseHandle).get()(explorer);

		Report::DebuggerInfo info;
		info.method = XorStr("OllyDBG");
		Report::sendDebuggerReport(&info);

		closed++;
	}

	return (closed > 0);
}

bool AntiDebugger::checkPEB()
{
	BOOL found = FALSE;

	_asm
	{
		xor eax, eax;
		mov eax, fs: [0x30] ;
		mov eax, [eax + 0x02];
		and eax, 0x000000FF;
		mov found, eax;
	}

	return found;
}

bool AntiDebugger::checkRemoteDebugger()
{
	HANDLE process = INVALID_HANDLE_VALUE;
	BOOL found = false;

	process = LI_FN(GetCurrentProcess).get();
	LI_FN(CheckRemoteDebuggerPresent).get()(process, &found);

	return found;
}

bool AntiDebugger::checkDebugger()
{
	return LI_FN(IsDebuggerPresent).get()();
}

bool AntiDebugger::checkHandleException()
{
	HANDLE h_invalid = (HANDLE)0xDEADBEEF;

	__try
	{
		LI_FN(CloseHandle).get()(h_invalid);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return true;
	}

	return false;
}

bool AntiDebugger::checkSingleStep()
{
	BOOL debugger_present = TRUE;
	__try
	{
		__asm
		{
			pushfd
			or dword ptr[esp], 0x100
			popfd
			nop
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { debugger_present = FALSE; }

	return debugger_present;
}

bool AntiDebugger::int3()
{
	__try
	{
		_asm
		{
			int 3;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }

	return true;
}

bool AntiDebugger::int2d()
{
	BOOL found = false;
	__try
	{
		_asm
		{
			int 0x2D;
		}
	}

	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	__try
	{
		__asm
		{
			xor eax, eax;
			int  2dh;
			inc  eax;
			mov found, eax;
		}
	}

	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	return true;
}

bool AntiDebugger::sendDebugString()
{
	LI_FN(SetLastError).get()(0);

	LI_FN(OutputDebugStringA).get()(XorStr("rockAC"));

	return (LI_FN(GetLastError).get()() != 0);
}

void AntiDebugger::thread()
{
	while (true)
	{
		if (closeDebuggers())
		{
			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (checkPEB())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("PEB");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (checkRemoteDebugger())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("IsRemoteDebuggerPresent");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (checkDebugger())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("IsDebuggerPresent");
			Report::sendDebuggerReport(&info);
			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (checkHandleException())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("HandleException");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (checkSingleStep())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("SingleStep");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (int3())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("int3");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (int2d())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("int2d");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		if (sendDebugString())
		{
			Report::DebuggerInfo info;
			info.method = XorStr("DebugString");
			Report::sendDebuggerReport(&info);

			Game::TerminateGame(0, XorStr("0x1000009"));
		}

		LI_FN(Sleep).safe()(Config::DEBUGGER_CHECK_SLEEP);
	}
}