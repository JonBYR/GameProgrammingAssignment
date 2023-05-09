#include "LogTime.h"
bool LogTime::isOpen = false;
std::ofstream LogTime::logFile;
bool LogTime::getTime(char* buffer, int buffersize) 
{
	time_t currentTime = std::time(0);
	struct tm* info = localtime(&currentTime);
	size_t written = strftime(buffer, buffersize, "%d/%m/%y %T", info);
	return written != 0;
}
void LogTime::clear() 
{
	remove("LogFile.txt");
}
void LogTime::open() 
{
	logFile.open("LogFile.txt", std::fstream::trunc);
	isOpen = true;
}
void LogTime::close() 
{
	logFile.close();
}
void LogTime::write(std::string event, int ticks, std::string date) 
{
	if (isOpen == true) logFile << date << " " << event << " " << ticks << std::endl;
}
void LogTime::write(std::string event, int ticks, int enemy, std::string date) 
{
	if (isOpen == true) logFile << date << " " << event << " " << enemy << " " << ticks << std::endl;
}