#include "Engine.hpp"

// Constructors

Engine::Engine() {
	rw = new sf::RenderWindow(w_def_vm, w_def_title);
	rw->setFramerateLimit(w_def_fps);
	gui.setTarget(*rw);
	log.log("Dabgine starting...");
}

Engine::Engine(sf::VideoMode w_vm, std::string w_title, sf::Uint32 w_style, const sf::ContextSettings w_ctx, sf::Color w_col, int fps) {
	rw = new sf::RenderWindow(w_vm, w_title, w_style, w_ctx);
	rw->setFramerateLimit(fps);
	gui.setTarget(*rw);
	w_def_color = w_col; // change current default color with provided
	log.log("Dabgine starting...");
}

// Destructor
Engine::~Engine() {
	delete rw;
}


// Functions

void Engine::pollEvents() {
	while (rw->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			// log and save everything
			log.log("Dabgine closing...");
			rw->close();
			break;
		case sf::Event::KeyPressed:
			log.setDebug(!log.getDebug());
		}
	}
}

void Engine::update() {
	pollEvents();
}

void Engine::render() {
	update();

	rw->clear(w_def_color);

	// Draw everything
	gui.draw();

	rw->display();
}

// Variables

const bool Engine::running() { return rw->isOpen(); }

// TODO: Setters and getters for everything :>