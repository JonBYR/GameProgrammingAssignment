#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "stdio.h"
class LogTime
{
public:
	static bool getTime(char* buffer, int buffersize);
	void static write(std::string event, int ticks, std::string date);
	void static write(std::string event, int ticks, int enemy, std::string date);
	void static open();
	void static close();
	void static clear();
private:
	static std::ofstream logFile;
	static bool isOpen;
};

