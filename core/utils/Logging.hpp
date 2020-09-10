#ifndef LOGGING_HPP
#define LOGGING_HPP


///// |----- HEADERS -----| /////


#include <iostream>


///// |----- HEADERS -----| /////


class Logging {

private:


	///// |----- VARIABLES -----| /////


	bool debugMode = true; // disable / enable outputting logs and more


	///// |----- VARIABLES -----| /////


public:


	///// |----- FUNCTIONS -----| /////


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


	///// |----- FUNCTIONS -----| /////


};

#endif