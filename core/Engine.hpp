#ifndef ENGINE_HPP
#define ENGINE_HPP


///// |----- HEADERS -----| /////


#include "utils/Logging.hpp"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TGUI/TGUI.hpp"

#include <iostream>


///// |----- HEADERS -----| /////


///// |----- DEFINITIONS -----| /////


#define MIMAX(num, min, max) (min < num && num < max)


///// |----- DEFINITIONS -----| /////


class Engine {

private:


	///// |----- VARIABLES -----| /////


	Logging log;

	sf::RenderWindow* rw;
	tgui::Gui gui;
	sf::Event ev;

	// DEFAULT CONSTRUCTOR PARAMS //

	sf::VideoMode w_def_vm = sf::VideoMode(600, 400);
	std::string w_def_title = "Default Title";
	unsigned int w_def_fps = 60;

	// GENERAL //

	sf::Color w_render_color = sf::Color::Black;
	bool hasStarted = false; // check in render etc if window is ready
	int max_scenes = 2; // needed for changeScene

	// CUSTOM WINDOW VARIABLES //

	bool isCustomWindow = false; // needed for resizing correctly
	sf::VideoMode w_cm_vm;
	std::string w_cm_title;
	sf::Uint32 w_cm_style;
	sf::ContextSettings w_cm_ctx;
	unsigned int w_cm_fps;


	///// |----- VARIABLES -----| /////


	///// |----- FUNCTIONS -----| /////


	/////////////////////////////////////////////////////////
	// \brief Run only once, at startup.
	/////////////////////////////////////////////////////////
	void initOnce();


	// EVENTS //

	/////////////////////////////////////////////////////////
	// \brief Clears and renders the window display.
	/////////////////////////////////////////////////////////
	void closedEvent();

	/////////////////////////////////////////////////////////
	// \brief Clears and renders the window display.
	/////////////////////////////////////////////////////////
	void keyPressedEvent();

	/////////////////////////////////////////////////////////
	// \brief Draws the project viewer.
	/////////////////////////////////////////////////////////
	void drawProjectViewer();

	/////////////////////////////////////////////////////////
	// \brief Draws the project editor.
	/////////////////////////////////////////////////////////
	void drawProjectEditor();


	///// |----- FUNCTIONS -----| /////


public:


	///// |----- ENUMERATIONS -----| /////


	enum Scene {
		Project_View = 0,
		Project_Editor = 1
	};


	///// |----- ENUMERATIONS -----| /////


	///// |----- VARIABLES -----| /////


	///// |----- VARIABLES -----| /////


	///// |----- CONSTRUCTORS & DESTRUCTOR -----| /////


	Engine();

	Engine(sf::VideoMode w_vm, std::string w_title, sf::Uint32 w_style = sf::Style::Default,const sf::ContextSettings w_ctx = sf::ContextSettings(), sf::Color w_col= sf::Color::Black, int fps = 60);

	virtual ~Engine();


	///// |----- CONSTRUCTORS & DESTRUCTOR -----| /////


	///// |----- FUNCTIONS -----| /////


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

	/////////////////////////////////////////////////////////
	// \brief Clears and renders the window display.
	/////////////////////////////////////////////////////////
	sf::VideoMode getWindowRect();

	/////////////////////////////////////////////////////////
	// \brief Changes the current engine scene.
	//
	// @param which: The scene's int number.
	/////////////////////////////////////////////////////////
	void changeScene(int which);


	///// |----- FUNCTIONS -----| /////


};

#endif