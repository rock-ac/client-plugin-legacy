/*
RockAnticheat - multicomplex SA:MP anti-cheat system
with innovative technologies and infallible verdicts.

Developed by savvin & 0Z0SK0

(c) 2023
*/
#pragma once

#include "../../includes.h"

class Network
{
private:
	/// <summary>
	/// Устанавливает дефолтные настройки CURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="CURL* curl">Указатель на инициализированный CURL</param>
	/// <returns>
	/// 	Ничего не возвращает
	/// </returns>
	static void setDefaultCURLOptions(CURL* curl);

public:
	static long lastError;
	/// <summary>
	/// Загружает файл из интернета при помощи libCURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="const char* url">Адрес загрузки.</param>
	/// <param name="const char* out">Путь вывода файла.</param>
	/// <returns>
	/// 	<c>true</c> если http-код 200; иначе, <c>false</c>.
	/// </returns>
	static bool file_sendRequest(const char* url, const char* out);

	/// <summary>
	/// Отправляет HTTPS-запрос при помощи libCURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="const char* url">URL-адрес</param>
	/// <returns>
	/// 	<c>Ничего не возвращает</c>.
	/// </returns>
	static void void_sendRequest(const char* url);

	/// <summary>
	/// Отправляет HTTPS-запрос при помощи libCURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="const char* url">URL-адрес</param>
	/// <returns>
	/// 	Возвращает ответ сервера в виде <c>int</c>.
	/// </returns>
	static int int_sendRequest(const char* url);

	/// <summary>
	/// Отправляет HTTPS-запрос при помощи libCURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="const char* url">URL-адрес</param>
	/// <returns>
	/// 	Возвращает ответ сервера в виде <c>bool</c>.
	/// </returns>
	static bool bool_sendRequest(const char* url, bool out);

	/// <summary>
	/// Отправляет HTTPS-запрос при помощи libCURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="const char* url">URL-адрес</param>
	/// <returns>
	/// 	Возвращает ответ сервера в виде <c>string</c>.
	/// </returns>
	static std::string string_sendRequest(const char* url);

	/// <summary>
	/// Отправляет HTTPS-запрос при помощи libCURL
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="const char* url">URL-адрес</param>
	/// <returns>
	/// 	Возвращает ответ сервера в виде vector-массива, типа <c>string</c>.
	/// </returns>
	static bool vectorstring_sendRequest(const char* url, std::vector<std::string> &out);
};