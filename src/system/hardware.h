/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

enum class WmiQueryError {
    None,
    BadQueryFailure,
    PropertyExtractionFailure,
    ComInitializationFailure,
    SecurityInitializationFailure,
    IWbemLocatorFailure,
    IWbemServiceConnectionFailure,
    BlanketProxySetFailure,
};

struct WmiQueryResult
{
    std::vector<std::wstring> ResultList;
    WmiQueryError Error = WmiQueryError::None;
};

class Hardware {
public:
	static std::vector<std::string> mac_address;
	static std::vector<std::string> guid_drives;
	static std::string cpu_hash;
	static std::string pc_name;
	static std::string user_guid;
    static std::string motherboard_serial;

    static WmiQueryResult getWmiQueryResult(std::wstring wmiQuery, std::wstring propNameOfResultObject, bool allowEmptyItems);

	static bool getMacAddress();
	static bool getDriveGUID();
	static bool getCPUHash();
	static bool getPCName();
    static bool getMotherboardSerial();
	static bool getUserGUID();
};