/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class Core
{
public:
	typedef struct {
		LPWSTR lpszProgramName;
	} SPROG_PUBLISHERINFO, * PSPROG_PUBLISHERINFO;

	/// <summary>
	/// Обертка для CURL, для получения NULL-ответа
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="(size_t size)">Размер ответа</param>
	/// <param name="(size_t nmemb)">Размер выделенной памяти</param>
	/// <returns>
	/// 	Возвращает NULL
	/// </returns>
	static size_t curlNullWrite(void* buffer, size_t size, size_t nmemb, void* userp);

	/// <summary>
	/// Обертка для CURL, для получения ответа и записи в файл
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="(void* ptr)">Указатель</param>
	/// <param name="(size_t size)">Размер ответа</param>
	/// <param name="(size_t nmemb)">Размер выделенной памяти</param>
	/// <param name="(FILE* stream)">Файл-стрим для записи (открытый через fopen)</param>
	/// <returns>
	/// 	Возвращает записанный файл
	/// </returns>
	static size_t curlWriteToFile(void* ptr, size_t size, size_t nmemb, FILE* stream);

	/// <summary>
	/// Обертка для CURL, для получения ответа в виде String
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="(void* contents)">Содержание ответа</param>
	/// <param name="(size_t size)">Размер ответа</param>
	/// <param name="(size_t nmemb)">Размер выделенной памяти</param>
	/// <param name="(void* userp)">Указатель на строку</param>
	/// <returns>
	/// 	Возвращает NULL
	/// </returns>
	static size_t curlWriteToString(void* contents, size_t size, size_t nmemb, void* userp);

	/// <summary>
	/// Конвертация из wstring в string
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="(const std::wstring s)">wide-строка</param>
	/// <returns>
	/// 	Возвращает строку
	/// </returns>
	static std::string UTF16ToUTF8(const std::wstring str);
	static std::wstring UTF8ToUTF16(const std::string str);

	static HMODULE GetCurrentModule();

	static DWORD getProcessID(const std::wstring& processName);

	static DWORD GetProgAndPublisherInfo(PCMSG_SIGNER_INFO pSignerInfo, Core::PSPROG_PUBLISHERINFO Info);

	static LPWSTR AllocateAndCopyWideString(LPCWSTR inputString);

	static std::string getCurrentDirectory();

	static std::string getWinVersion();

	static std::string getFileMD5(std::string path);

	static HWND getHWND(DWORD pid);

	static std::string getLastWriteTime(std::filesystem::file_time_type tp);

	static std::string getFilePermissions(std::filesystem::perms p);

	static std::string getCurrentModulePath();

	static bool comp(const std::string& lhs, const std::string& rhs);

	static std::string getUsername();

	static BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam);

	static std::string HWNDToString(HWND inputA);

	static BOOL IsElevated();

	std::string encryptAES(std::string content);
};