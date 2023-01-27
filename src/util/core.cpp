// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#include "core.h"

size_t Core::curlNullWrite(void* buffer, size_t size, size_t nmemb, void* userp)
{
	return size * nmemb;
}
size_t Core::curlWriteToFile(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}
size_t Core::curlWriteToString(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string Core::UTF16ToUTF8(const std::wstring str)
{
	std::string convertedString;
	int requiredSize = LI_FN(WideCharToMultiByte).get()(1251, 0, str.c_str(), -1, NULL, 0, 0, NULL);
	if (requiredSize > 0) {
		std::vector<wchar_t> buffer(requiredSize);
		LI_FN(WideCharToMultiByte).get()(1251, 0, str.c_str(), -1, &buffer[0], requiredSize, 0, NULL);
		convertedString.assign(buffer.begin(), buffer.end() - 1);
	}
	return convertedString;
}

std::wstring Core::UTF8ToUTF16(std::string str) 
{
	std::wstring convertedString;
	int requiredSize = LI_FN(MultiByteToWideChar).get()(NULL, 0, str.c_str(), -1, 0, 0);
	if (requiredSize > 0) {
		std::vector<wchar_t> buffer(requiredSize);
		LI_FN(MultiByteToWideChar).get()(NULL, 0, str.c_str(), -1, &buffer[0], requiredSize);
		convertedString.assign(buffer.begin(), buffer.end() - 1);
	}
	return convertedString;
}

#ifndef _delayimp_h
extern "C" IMAGE_DOS_HEADER __ImageBase;
#endif
HMODULE Core::GetCurrentModule()
{
    return reinterpret_cast<HMODULE>(&__ImageBase);
}

DWORD Core::getProcessID(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = LI_FN(CreateToolhelp32Snapshot).get()(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	LI_FN(Process32FirstW).get()(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		LI_FN(CloseHandle).get()(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (LI_FN(Process32NextW).get()(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			LI_FN(CloseHandle).get()(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	LI_FN(CloseHandle).get()(processesSnapshot);
	return 0;
}

LPWSTR Core::AllocateAndCopyWideString(LPCWSTR inputString)
{
	LPWSTR outputString = NULL;

	outputString = (LPWSTR)LI_FN(LocalAlloc).get()(LPTR,
		(wcslen(inputString) + 1) * sizeof(WCHAR));
	if (outputString != NULL)
	{
		lstrcpyW(outputString, inputString);
	}
	return outputString;
}

DWORD Core::GetProgAndPublisherInfo(PCMSG_SIGNER_INFO pSignerInfo, Core::PSPROG_PUBLISHERINFO Info)
{
	BOOL fReturn = FALSE;
	PSPC_SP_OPUS_INFO OpusInfo = NULL;
	DWORD dwData;
	BOOL fResult;


	__try
	{
		for (DWORD n = 0; n < pSignerInfo->AuthAttrs.cAttr; n++)
		{
			if (lstrcmpA(SPC_SP_OPUS_INFO_OBJID,
				pSignerInfo->AuthAttrs.rgAttr[n].pszObjId) == 0)
			{
				// Get Size of SPC_SP_OPUS_INFO structure.
				fResult = LI_FN(CryptDecodeObject).get()(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
					SPC_SP_OPUS_INFO_OBJID,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].pbData,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].cbData,
					0,
					NULL,
					&dwData);
				if (!fResult) return LI_FN(GetLastError).get()();

				// Allocate memory for SPC_SP_OPUS_INFO structure.
				OpusInfo = (PSPC_SP_OPUS_INFO)LI_FN(LocalAlloc).get()(LPTR, dwData);
				if (!OpusInfo) return LI_FN(GetLastError).get()();

				// Decode and get SPC_SP_OPUS_INFO structure.
				fResult = LI_FN(CryptDecodeObject).get()(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
					SPC_SP_OPUS_INFO_OBJID,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].pbData,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].cbData,
					0,
					OpusInfo,
					&dwData);
				if (!fResult) return LI_FN(GetLastError).get()();

				// Fill in Program Name if present.
				if (OpusInfo->pwszProgramName)
				{
					Info->lpszProgramName =
						AllocateAndCopyWideString(OpusInfo->pwszProgramName);
				}
				else
					Info->lpszProgramName = NULL;

				break;
			}             
		}
	}
	__finally
	{
		if (OpusInfo != NULL) LI_FN(LocalFree).get()(OpusInfo);
	}

	return LI_FN(GetLastError).get()();
}

std::string Core::getCurrentDirectory() {
	TCHAR buffer[MAX_PATH] = { 0 };
	LI_FN(GetModuleFileNameW).get()(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	std::wstring ws(buffer);
	std::string s(ws.begin(), ws.end());

	return s.substr(0, pos);
}

std::string Core::getWinVersion()
{
	if (IsWindows10OrGreater())
	{
		return XorStr("WIN10");
	}
	else if (IsWindows8Point1OrGreater())
	{
		return XorStr("WIN81");
	}
	else if (IsWindows8OrGreater())
	{
		return XorStr("WIN8");
	}
	else if (IsWindows7OrGreater())
	{
		return XorStr("WIN7");
	}
	else if (IsWindowsVistaSP1OrGreater())
	{
		return XorStr("WINVISTASP1");
	}
	else if (IsWindowsVistaSP2OrGreater())
	{
		return XorStr("WINVISTASP2");
	}
	else if (IsWindowsVistaOrGreater())
	{
		return XorStr("WINVISTA");
	}
	else if (IsWindowsXPSP1OrGreater())
	{
		return XorStr("WINXPSP1");
	}
	else if (IsWindowsXPSP2OrGreater())
	{
		return XorStr("WINXPSP2");
	}
	else if (IsWindowsXPSP3OrGreater())
	{
		return XorStr("WINXPSP3");
	}
	else if (IsWindowsXPOrGreater())
	{
		return XorStr("WINXP");
	}
	else if (IsWindowsServer())
	{
		return XorStr("WINSERVER");
	}
	else
	{
		return XorStr("UNKNOWN");
	}
}

std::string Core::getUsername()
{
	HKEY hKey;
	DWORD len = 1024;
	DWORD readDataLen = len;
	PWCHAR readBuffer = (PWCHAR)malloc(sizeof(PWCHAR) * len);

	// Чуществует ли конфиг?
	DWORD ConfigRegistry = LI_FN(RegOpenKeyExW).get()(
		HKEY_CURRENT_USER,
		XorStrW(L"Software\\Stalker-RP.net"),
		0,
		KEY_READ | KEY_WOW64_64KEY,
		&hKey
	);
	if (ConfigRegistry == ERROR_SUCCESS)
	{
		ConfigRegistry = LI_FN(RegQueryValueExW).get()(
			hKey,
			XorStrW(L"Nickname"),
			NULL,
			NULL,
			NULL,
			NULL
		);
		if (ConfigRegistry == ERROR_SUCCESS)
		{
			ConfigRegistry = LI_FN(RegQueryValueExW).get()(
				hKey,
				XorStrW(L"Nickname"),
				NULL,
				NULL,
				(BYTE*)readBuffer,
				&readDataLen
			);
			if (ConfigRegistry == ERROR_SUCCESS)
			{
				std::wstring wstr(readBuffer);
				std::string str(wstr.begin(), wstr.end());

				return str;
			}
		}
	}
	return XorStr("None");
	//delete readBuffer;
	LI_FN(RegCloseKey).get()(hKey);
}

std::string Core::getFileMD5(std::string path)
{
	MD5 M;
	std::ifstream mFile;
	std::istream* input = NULL;
	const size_t BufferSize = 65536;
	char* buffer = new char[BufferSize];

	mFile.open(path.c_str(), std::ios::in | std::ios::binary);
	input = &mFile;

	// process file
	while (*input)
	{
		input->read(buffer, BufferSize);
		std::size_t numBytesRead = size_t(input->gcount());
		M.add(buffer, numBytesRead);
	}

	return M.getHash();
}

HWND g_HWND = NULL;
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	// Чуществует ли конфиг?

	LI_FN(GetWindowThreadProcessId).get()(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		g_HWND = hwnd;
		return FALSE;
	}
	return TRUE;
}
HWND Core::getHWND(DWORD pid)
{
	LI_FN(EnumWindows).get()(EnumWindowsProcMy, pid);
	
	return g_HWND;
}

std::string Core::getLastWriteTime(std::filesystem::file_time_type tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - std::filesystem::file_time_type::clock::now()
		+ system_clock::now());
	std::time_t tt = system_clock::to_time_t(sctp);
	std::tm* gmt = std::gmtime(&tt);
	std::stringstream buffer;
	buffer << std::put_time(gmt, XorStr("%d/%B/%Y:%H/%M"));
	std::string formattedFileTime = buffer.str();

	return formattedFileTime;
}

std::string Core::getFilePermissions(std::filesystem::perms p)
{
	std::string returnPerm;
	returnPerm = ((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? XorStr("r") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? XorStr("w") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? XorStr("x") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::group_read) != std::filesystem::perms::none ? XorStr("r") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? XorStr("w") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? XorStr("x") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::others_read) != std::filesystem::perms::none ? XorStr("r") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? XorStr("w") : XorStr("-"));
	returnPerm = returnPerm + ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? XorStr("x") : XorStr("-"));

	return returnPerm;
}

std::string Core::getCurrentModulePath()
{
	TCHAR buffer[MAX_PATH] = { 0 };

	LI_FN(GetModuleFileNameW).get()(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(XorStrW(L"\\/"));
	std::wstring test = std::wstring(buffer).substr(0, pos);
	std::string s(test.begin(), test.end());
	return s;
}

bool Core::comp(const std::string& lhs, const std::string& rhs)
{
	if (lhs == "") return false;
	return rhs == "" || !(rhs < lhs);
}

BOOL CALLBACK Core::EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	LI_FN(GetWindowThreadProcessId).get()(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		AntiCheat::gtaHwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}

std::string Core::HWNDToString(HWND inputA)
{
	std::wstring s;
	int len = LI_FN(GetWindowTextLengthW).get()(inputA);
	if (len > 0)
	{
		s.resize(len + 1);
		len = LI_FN(GetWindowTextW).get()(inputA, &s[0], s.size());
		s.resize(len);
	}
	return Core::utf16ToUTF8(s);
}

BOOL Core::IsElevated() 
{
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (LI_FN(OpenProcessToken).get()(LI_FN(GetCurrentProcess).get()(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (LI_FN(GetTokenInformation).get()(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		LI_FN(CloseHandle).get()(hToken);
	}
	return fRet;
}

std::string Core::encryptAES(std::string content)
{

}