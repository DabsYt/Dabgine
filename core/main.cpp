/*
	Made by Dabs Yt ( 3 / 9 / 2020 11:44 ) without copyright.
*/

// Self-made headers
#include "Engine.h"

// 3rd-party headers
// none needed in main

// Compiler headers
// none needed also

int WinMain() {

	sf::ContextSettings ctx = sf::ContextSettings();
	ctx.majorVersion = 2;
	ctx.minorVersion = 0; // opengl 2
	Engine engine(sf::VideoMode(800, 600), "Dabgine", sf::Style::Titlebar | sf::Style::Close, ctx, sf::Color::Blue, 60);

	while (engine.running()) {
		engine.render();
	}

	return 0;
}

int main() {

	sf::ContextSettings ctx = sf::ContextSettings();
	ctx.majorVersion = 2;
	ctx.minorVersion = 0; // opengl 2
	Engine engine(sf::VideoMode(800, 600), "Dabgine", sf::Style::Titlebar | sf::Style::Close, ctx, sf::Color::Blue, 60);

	while (engine.running()) {
		engine.render();
	}

	return 0;
}