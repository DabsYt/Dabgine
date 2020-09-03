#ifndef ENGINE_h
#define ENGINE_H

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TGUI/TGUI.hpp"

#include <iostream>

class Engine {
private:

	// Variables
	sf::RenderWindow* rw;
	tgui::Gui gui;
	sf::Event ev;
	sf::VideoMode w_def_vm = sf::VideoMode(600, 400);
	std::string w_def_title = "Default Title";
	sf::Color w_def_color = sf::Color::Black;
	int w_def_fps = 60;

	// Functions

public:

	// Constructors
	Engine();
	Engine(sf::VideoMode, std::string, sf::Uint32 = sf::Style::Default,const sf::ContextSettings = sf::ContextSettings(), sf::Color = sf::Color::Black, int = 60);

	// Variables

	// Functions
	
	// Gets all input
	void pollEvents();
	// Updates the engine's UI etc.
	void update();
	// Renders the engine's UI etc.
	void render();
	
	// Variables
	// Returns the state of the window.
	const bool running();
};
#endif