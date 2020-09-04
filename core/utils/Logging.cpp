#include "Logging.hpp"

void Logging::log(std::string logText, int logLevel) {
	if (debugMode) { if (logLevel > minLevel) { std::cout << logText << std::endl; } }
}

void Logging::setDebug(bool state) { debugMode = state; if (state) { log("Logging ON"); } }

bool Logging::getDebug() { return debugMode; std::cout << debugMode; }

void Logging::setMinLevel(int newLevel) { minLevel = newLevel; }

int Logging::getMinLevel() { return minLevel; }