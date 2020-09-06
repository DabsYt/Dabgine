/*
	Made by Dabs Yt ( 3 / 9 / 2020 11:44 ) without copyright.
*/

// Self-made headers
#include "Engine.hpp"

// 3rd-party headers
// none needed in main

// Compiler headers
// none needed also

/////////////////////////////////////////////////////////
// \brief Shared startup func to minimise repetition.
/////////////////////////////////////////////////////////
void startup() {
	sf::ContextSettings ctx = sf::ContextSettings();
	ctx.majorVersion = 2;
	ctx.minorVersion = 0; // opengl 2
	Engine engine(sf::VideoMode(800, 600), "Dabgine", sf::Style::Titlebar | sf::Style::Close, ctx, sf::Color::Black, 60);
}

// Entry function for RELEASE config.
int WinMain() {

	startup();

	return 0;
}

// Entry function for DEBUG config, used to open the console for debugging purposes rather than just a window, like RELEASE does.
int main() {
	
	startup();

	return 0;
}