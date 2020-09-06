#include "Engine.hpp"


///// |----- PRIVATE FUNCTIONS -----| /////


void Engine::initOnce() {
	log.log("Dabgine starting...");
	gui.setTarget(*rw);
	gui.setTabKeyUsageEnabled(false); // baaad tab keys
	gui.unfocusAllWidgets(); // maybe to prevent editbox from focsing?
	hasStarted = true;
	changeScene(0); // project view on startup

	while (running()) { render(); }
}

// Events
void Engine::closedEvent() {
	log.log("Dabgine stopping...");
	gui.removeAllWidgets();
	rw->close();
}

void Engine::keyPressedEvent() {
	// some cool event
}

void Engine::drawProjectViewer() {
	// Clear previous widgets
	gui.removeAllWidgets();

	// New widgets
	auto view_main_lin = tgui::VerticalLayout::create();

	auto view_top_lin = tgui::HorizontalLayout::create();

	auto view_logo = tgui::Label::create("Dabgine");
	view_logo->setAutoSize(false);
	view_logo->getRenderer()->setTextColor(sf::Color::White);
	view_logo->setTextSize(25);
	view_logo->setSize("100%", "35");
	view_logo->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	view_logo->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));

	auto view_proj_list = tgui::ListView::create();

	auto view_bottom_lin = tgui::HorizontalLayout::create();

	auto view_btn_create = tgui::Button::create("Create Project");

	view_top_lin->add(view_logo);

	view_bottom_lin->add(view_btn_create);

	view_main_lin->add(view_top_lin);
	//view_main_lin->add(view_proj_list);
	//view_main_lin->add(view_bottom_lin);

	gui.add(view_main_lin);
	
	view_logo->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
	
	// replace with list from a file
	/*for (int x = 0; x < 3; x++) {
		view_main_lin->add(tgui::Button::create("Button " + std::to_string(x)), "btn_" + std::to_string(x));
	}*/

}

void Engine::drawProjectEditor() {

}


///// |----- PRIVATE FUNCTIONS -----| /////


///// |----- CONSTRUCTORS & DESTRUCTOR -----| /////


Engine::Engine() {
	rw = new sf::RenderWindow(w_def_vm, w_def_title);
	rw->setFramerateLimit(w_def_fps);
	initOnce();
}

Engine::Engine(sf::VideoMode w_vm, std::string w_title, sf::Uint32 w_style, const sf::ContextSettings w_ctx, sf::Color w_col, int fps) {
	rw = new sf::RenderWindow(w_vm, w_title, w_style, w_ctx);
	rw->setFramerateLimit(fps);
	w_render_color = w_col; // change current render color with the provided one
	w_cm_vm = w_vm;
	w_cm_title = w_title;
	w_cm_style = w_style;
	w_cm_ctx = w_ctx;
	w_cm_fps = fps;
	isCustomWindow = true;
	initOnce();
}

Engine::~Engine() {
	delete rw;
}


///// |----- CONSTRUCTORS & DESTRUCTOR -----| /////


///// |----- PUBLIC FUNCTIONS -----| /////


void Engine::resize(sf::VideoMode w_vm) {
	log.log("Dabgine resizing...");
	if (isCustomWindow) { rw->create(w_vm, w_cm_title, w_cm_style, w_cm_ctx); rw->setFramerateLimit(w_cm_fps); }
	else { rw->create(w_vm, w_def_title); rw->setFramerateLimit(w_def_fps); }
}

void Engine::pollEvents() {
	while (rw->pollEvent(ev)) {
		switch (ev.type) {

		case sf::Event::Closed:
			closedEvent();
			break;

		case sf::Event::KeyPressed:
			keyPressedEvent();
			break;

		}

		gui.handleEvent(ev);
	}
}

void Engine::update() {
	pollEvents();
}

void Engine::render() {
	if (hasStarted) {
		update();

		rw->clear(w_render_color);

		// Draw everything
		gui.draw();

		rw->display();
	}
}

const bool Engine::running() { return rw->isOpen(); }

void Engine::setRenderColor(sf::Color newColor) { w_render_color = newColor; }

sf::Color Engine::getRenderColor() { return w_render_color; }

sf::VideoMode Engine::getWindowRect() {
	if (isCustomWindow) { return w_cm_vm;  }
	else { return w_def_vm;  }
}

void Engine::changeScene(int which) {
	if (MIMAX(which, -1, max_scenes)) {
		switch (which) {

		case Scene::Project_View:

			log.log("Opening project viewer...");
			
			hasStarted = false; // delay render to draw everything first
			drawProjectViewer();
			hasStarted = true; //keep rendering

			break;

		case Scene::Project_Editor:

			log.log("Opening project editor...");
			
			hasStarted = false;
			drawProjectEditor();
			hasStarted = true;

			break;

		}
	}
}


///// |----- PUBLIC FUNCTIONS -----| /////