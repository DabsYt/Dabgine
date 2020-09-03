#ifndef ENGINE_H
#define ENGINE_H

#include "utils/Logging.hpp"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp" // window
#include "TGUI/TGUI.hpp"

#include <iostream>

class Engine {

private:

	// Variables

	Logging log;
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

	/////////////////////////////////////////////////////////
	// \brief The default engine constructor.		
	/////////////////////////////////////////////////////////
	Engine();

	Engine(sf::VideoMode, std::string, sf::Uint32 = sf::Style::Default,const sf::ContextSettings = sf::ContextSettings(), sf::Color = sf::Color::Black, int = 60);

	/////////////////////////////////////////////////////////
	// \brief The engine destructor.
	/////////////////////////////////////////////////////////
	virtual ~Engine();

	// Functions
	
	/////////////////////////////////////////////////////////
	// \brief Polls all current events such as input.
	/////////////////////////////////////////////////////////
	void pollEvents();

	/////////////////////////////////////////////////////////
	// \brief Updates the current UI,events etc.
	/////////////////////////////////////////////////////////
	void update();

	/////////////////////////////////////////////////////////
	// \brief Clears and renders the window display.
	/////////////////////////////////////////////////////////
	void render();
	
	// Variables
	/////////////////////////////////////////////////////////
	// \brief Gets the current window's state.	
	//
	// @return const bool: The window's state.
	/////////////////////////////////////////////////////////
	const bool running();
};
#endif