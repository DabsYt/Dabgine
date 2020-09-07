#include "Engine.hpp"


///// |----- PRIVATE FUNCTIONS -----| /////


void Engine::initOnce() {
	log.log("Dabgine starting...");
	
	// Check stuff first here (files, projects, settings etc.)
	checkCoreFiles();

	// Other
	gui.setTarget(*rw);
	gui.setTabKeyUsageEnabled(false); // baaad tab keys
	gui.unfocusAllWidgets(); // maybe to prevent editbox from focusing?
	hasStarted = true;
	changeScene(0); // project view on startup

	while (running()) { render(); }

	// nothing here
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
	tgui::Theme theme("Themes/Black.txt"); // main theme for btns etc

	// Pseudo main bg color
	auto view_main_group = tgui::Group::create({ "100%", "100%" });
	view_main_group->getRenderer();

	////////////////// ADD IT LATER PLS FOR GODS SAKE////////////////////////////

	auto view_logo = tgui::Label::create("Dabgine");
	view_logo->setAutoSize(false);
	view_logo->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	view_logo->getRenderer()->setTextColor(sf::Color::White);
	view_logo->getRenderer()->setTextOutlineThickness(1);
	view_logo->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	view_logo->setTextSize(25);
	view_logo->setPosition(0, 0);
	view_logo->setSize("100%", "35");
	view_logo->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	view_logo->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

	auto view_btn_create = tgui::Button::create("Create Project");
	view_btn_create->setRenderer(theme.getRenderer("Button"));
	view_btn_create->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	view_btn_create->getRenderer()->setTextColor(tgui::Color::White);
	view_btn_create->getRenderer()->setTextOutlineThickness(1);
	view_btn_create->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	view_btn_create->setTextSize(25);
	view_btn_create->setPosition((rw->getSize().x - 250) / 2, "93%"); // TODO: Fix x to be resized in resizeEvent
	view_btn_create->setSize(250, 40);
	view_btn_create->connect("pressed", [=] () { } );
	
	// Start adding the projects to a list
	auto view_proj_list = tgui::ListView::create();
	view_proj_list->setAutoScroll(false);
	view_proj_list->setPosition(10, 40);
	view_proj_list->setSize("97%", "85%");
	view_proj_list->getRenderer()->setBackgroundColor(tgui::Color("#18191a")); // color picker
	view_proj_list->getRenderer()->setBackgroundColorHover(tgui::Color("#202121"));
	view_proj_list->getRenderer()->setSelectedBackgroundColor(tgui::Color("#252626"));
	view_proj_list->getRenderer()->setSelectedBackgroundColorHover(tgui::Color("#2f3030"));
	view_proj_list->getRenderer()->setTextColor(tgui::Color("#76787a"));
	view_proj_list->getRenderer()->setTextColorHover(tgui::Color("#a2a4a6"));
	view_proj_list->getRenderer()->setSelectedTextColor(tgui::Color("#cccecf"));
	view_proj_list->getRenderer()->setSelectedTextColorHover(tgui::Color("#d7dadb"));
	view_proj_list->getRenderer()->setFont("Fonts/Alata-Regular.ttf");
	view_proj_list->getRenderer()->setHeaderTextColor(tgui::Color("#78797a"));
	view_proj_list->getRenderer()->setHeaderBackgroundColor(tgui::Color("#111112"));
	view_proj_list->getRenderer()->setBorders({ 2, 2, 2, 2 });
	view_proj_list->getRenderer()->setBorderColor(tgui::Color("#252729"));
	view_proj_list->getRenderer()->setGridLinesColor(tgui::Color("#222426"));
	view_proj_list->setTextSize(15);
	view_proj_list->setHeaderHeight(30);
	view_proj_list->setHeaderSeparatorHeight(1);
	view_proj_list->setSeparatorWidth(1);
	view_proj_list->setHeaderTextSize(20);
	view_proj_list->setGridLinesWidth(1);
	view_proj_list->getRenderer()->setPadding({ 0, 0, 0, 0 });

	// List signals

	view_proj_list->connect("RightClicked", [=] () {
		log.log("Right clicked!"); 
	});

	view_proj_list->connect("DoubleClicked", [=] () {
		log.log("Double clicked!");
	});

	std::ifstream proj_file_list(proj_file_path);

	json j;

	j = j.parse(proj_file_list);
	
	// List project details

	// Columns
	auto list_column_name = view_proj_list->addColumn("Project Name");
	view_proj_list->setColumnWidth(list_column_name, 150);

	auto list_column_desc = view_proj_list->addColumn("Project Description");
	view_proj_list->setExpandLastColumn(true); // instead of trying out custom width to fill

	// Iterate for values
	for (auto element : j["projects"].items()) {
		auto proj_name = element.value()["name"].dump(); // dump for making it usable as a string
		proj_name.erase(std::remove(proj_name.begin(), proj_name.end(), '"'), proj_name.end()); // remove the " from the json string

		auto proj_desc = element.value()["description"].dump();
		proj_desc.erase(std::remove(proj_desc.begin(), proj_desc.end(), '"'), proj_desc.end());

		// Set item names to the corresponding collumn
		view_proj_list->addItem(std::vector<sf::String> {proj_name, proj_desc} );
		
	}

	proj_file_list.close();

	// Add first
	gui.add(view_logo);
	gui.add(view_proj_list);
	gui.add(view_btn_create);

	// Then animate everything
	view_logo->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
	view_proj_list->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
	view_btn_create->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
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


void Engine::pollEvents() {
	while (rw->pollEvent(ev)) {
		switch (ev.type) {

		case sf::Event::Closed:
			closedEvent();
			break;

		case sf::Event::KeyPressed:
			keyPressedEvent();
			break;

		case sf::Event::Resized:
			rw->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(ev.size.width), static_cast<float>(ev.size.height))));
			gui.setView(rw->getView());
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


void Engine::checkCoreFiles() {
	
	// Individual checks

	log.log("Working path: " + std::experimental::filesystem::current_path().string());
	if (!fs::exists(proj_file_path)) {
		log.log(proj_file_path + " doesnt exist, creating...");

		// Open the file
		std::ofstream proj_file(proj_file_path);
		
		// Create a json object
		json j;

		// Create the default project json code
		j["projects"]["Default Game"]["name"] = "Default Game";
		j["projects"]["Default Game"]["description"] = "The default Dabgine Game project.";
		fs::create_directory("Default Game");

		// Save to file
		proj_file << j;

		// Close the file
		proj_file.close();
	}
	
}


///// |----- PUBLIC FUNCTIONS -----| /////