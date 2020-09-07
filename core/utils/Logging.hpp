#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>

class Logging {

private:

	// Variables

	bool debugMode = true; // disable / enable outputting logs and more

	// Functions

public:

	// Functions

	/////////////////////////////////////////////////////////
	// \brief Logs a message to the console.		
	//
	// @param logText: The log text.
	/////////////////////////////////////////////////////////
	void log(std::string logText);

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

};
#endif