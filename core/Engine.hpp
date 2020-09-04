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

	// Default constructor params
	sf::VideoMode w_def_vm = sf::VideoMode(600, 400);
	std::string w_def_title = "Default Title";
	unsigned int w_def_fps = 60;

	// General variables
	sf::Color w_render_color = sf::Color::Black;
	bool hasStarted = false; // check in render etc if window is ready
	
	// Custom window variables
	bool isCustomWindow = false; // needed for resizing correctly
	sf::VideoMode w_cm_vm;
	std::string w_cm_title;
	sf::Uint32 w_cm_style;
	sf::ContextSettings w_cm_ctx;
	unsigned int w_cm_fps;

	// Other

	// Functions

	/////////////////////////////////////////////////////////
	// \brief Run only once, at startup.
	/////////////////////////////////////////////////////////
	void initOnce();

public:

	// Constructors

	/////////////////////////////////////////////////////////
	// \brief The default engine constructor.		
	/////////////////////////////////////////////////////////
	Engine();

	Engine(sf::VideoMode w_vm, std::string w_title, sf::Uint32 w_style = sf::Style::Default,const sf::ContextSettings w_ctx = sf::ContextSettings(), sf::Color w_col= sf::Color::Black, int fps = 60);

	/////////////////////////////////////////////////////////
	// \brief The engine destructor.
	/////////////////////////////////////////////////////////
	virtual ~Engine();

	// Functions

	/////////////////////////////////////////////////////////
	// \brief Resizes the current window.
	/////////////////////////////////////////////////////////
	void resize(sf::VideoMode w_vm);

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

	/////////////////////////////////////////////////////////
	// \brief Changes the current render color.
	//
	// @param newColor: The new render color.
	/////////////////////////////////////////////////////////
	void setRenderColor(sf::Color newColor);

	/////////////////////////////////////////////////////////
	// \brief Gets the current render color.
	//
	// @return sf::Color: The current render color.
	/////////////////////////////////////////////////////////
	sf::Color getRenderColor();

};
#endif