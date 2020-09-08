#ifndef ENGINE_HPP
#define ENGINE_HPP


///// |----- HEADERS -----| /////


#include "utils/Logging.hpp"
#include "utils/Math.hpp"
#include "Constants.hpp"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TGUI/TGUI.hpp"
#include "nlohmann\json.hpp"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

using json = nlohmann::json;

namespace fs = std::experimental::filesystem;


///// |----- HEADERS -----| /////


///// |----- DEFINITIONS -----| /////


///// |----- DEFINITIONS -----| /////


class Engine {

private:


	///// |----- VARIABLES -----| /////


	Logging log;
	
	json j;

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
	std::string proj_file_path = "projects.json";
	std::string error_str;
	bool errorBool;
	//bool* isErrored = false;

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

	/////////////////////////////////////////////////////////
	// \brief Sets up the main variables.
	/////////////////////////////////////////////////////////
	void setupVars();

	/////////////////////////////////////////////////////////
	// \brief Checks all the necessary files.
	/////////////////////////////////////////////////////////
	void checkCoreFiles();

	/////////////////////////////////////////////////////////
	// \brief Draws the project viewer.
	/////////////////////////////////////////////////////////
	void drawProjectViewer();

	/////////////////////////////////////////////////////////
	// \brief Draws the project editor.
	/////////////////////////////////////////////////////////
	void drawProjectEditor();

	/////////////////////////////////////////////////////////
	// \brief Creates a new project with the desired params.
	//
	// @param j: The json object to update if the creation was successful.
	// @param projName: The project's name.
	// @param projDescription: The project's description.
	// @param projPath: The project's path.
	// @param logError: If an error occurs, save the error to a string.
	//
	// @return bool: Whether the creation was successful.
	/////////////////////////////////////////////////////////
	bool createProject(json j, std::string proj_name, std::string proj_description, std::string proj_path, std::string& log_error);

	/////////////////////////////////////////////////////////
	// \brief Checks if any error occured.
	/////////////////////////////////////////////////////////
	void checkHasErrored();

	// EVENTS //

	/////////////////////////////////////////////////////////
	// \brief Called when the window is closing.
	/////////////////////////////////////////////////////////
	void closedEvent();

	/////////////////////////////////////////////////////////
	// \brief Called when a key is being pressed.
	/////////////////////////////////////////////////////////
	void keyPressedEvent();

	/////////////////////////////////////////////////////////
	// \brief Called when the window is resizing.
	/////////////////////////////////////////////////////////
	void resizeEvent();


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
	// \brief Gets the current window's video mode.
	//
	// @return sf::VideoMode: The window's VideoMode.
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