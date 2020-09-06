#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>

class Logging {

private:

	// Variables

	bool debugMode = true; // disable / enable outputting logs and more
	int minLevel = -1; // -1 to 2 where 2 = no logs and -1 = show all logs 

	// Functions

public:

	// Functions

	/////////////////////////////////////////////////////////
	// \brief Logs a message to the console.		
	//
	// @param logText: The log text.
	// @param logLevel: The log level[0=info|1=warn|2=err]
	/////////////////////////////////////////////////////////
	void log(std::string logText, int logLevel = 0);

	/////////////////////////////////////////////////////////
	// \brief Changes the current debug mode.
	//
	// @param state: The new state of the debug mode.
	/////////////////////////////////////////////////////////
	void setDebug(bool state);

	/////////////////////////////////////////////////////////
	// \brief Gets the current debug mode state.		
	//
	// @return bool: The current debug state.
	/////////////////////////////////////////////////////////
	bool getDebug();

	/////////////////////////////////////////////////////////
	// \brief Sets the new min level for logs.		
	//
	// @param newLevel: The new min level.
	/////////////////////////////////////////////////////////
	void setMinLevel(int newLevel);

	/////////////////////////////////////////////////////////
	// \brief Gets the current min level for logs.	
	//
	// @return int: The current min level.
	/////////////////////////////////////////////////////////
	int getMinLevel();

};
#endif