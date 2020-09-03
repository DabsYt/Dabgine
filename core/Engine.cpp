#include "Engine.h"

// Constructors

Engine::Engine() {
	rw = new sf::RenderWindow(w_def_vm, w_def_title);
	rw->setFramerateLimit(w_def_fps);
	gui.setTarget(*rw);
	std::cout << "Dabgine starting..." << std::endl;
}

Engine::Engine(sf::VideoMode w_vm, std::string w_title, sf::Uint32 w_style, const sf::ContextSettings w_ctx, sf::Color w_col, int fps) {
	rw = new sf::RenderWindow(w_vm, w_title, w_style, w_ctx);
	rw->setFramerateLimit(fps);
	gui.setTarget(*rw);
	w_def_color = w_col; // change current default color with provided
	std::cout << "Dabgine starting..." << std::endl;

}

// Functions

void Engine::pollEvents() {
	while (rw->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			// log and save everything
			std::cout << "Dabgine closing..." << std::endl;
			rw->close();
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