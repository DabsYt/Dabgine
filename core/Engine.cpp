#include "Engine.hpp"

// Private functions

void Engine::initOnce() {
	log.log("Dabgine starting...");
	gui.setTarget(*rw);
	hasStarted = true;
}

// Constructors

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

// Destructor
Engine::~Engine() {
	delete rw;
}


// Functions

void Engine::resize(sf::VideoMode w_vm) {
	log.log("Dabgine resizing...");
	if (isCustomWindow) { rw->create(w_vm, w_cm_title, w_cm_style, w_cm_ctx); rw->setFramerateLimit(w_cm_fps); }
	else { rw->create(w_vm, w_def_title); rw->setFramerateLimit(w_def_fps); }
}

void Engine::pollEvents() {
	while (rw->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			// log and save everything
			log.log("Dabgine closing...");
			rw->close();
			break;
		case sf::Event::KeyPressed:
			setRenderColor(sf::Color::White);
			break;
		}
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

// Variables

const bool Engine::running() { return rw->isOpen(); }

void Engine::setRenderColor(sf::Color newColor) {
	w_render_color = newColor;
}

sf::Color Engine::getRenderColor() {
	return w_render_color;
}


// TODO: Setters and getters for everything :>