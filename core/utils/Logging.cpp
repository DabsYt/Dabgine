#include "Logging.hpp"

void Logging::log(std::string logText) {
	if (debugMode) { std::cout << logText << std::endl; }
}

void Logging::setDebug(bool state) { debugMode = state; if (state) { log("Logging ON"); } }

bool Logging::getDebug() { return debugMode; std::cout << debugMode; }