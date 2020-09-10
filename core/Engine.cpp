#include "Engine.hpp"


///// |----- PRIVATE FUNCTIONS -----| /////


void Engine::initOnce() {
	log.log("Dabgine starting...");

	// Check stuff first here (files, projects, settings etc.)
	setupVars();
	preloadUI(); // load ui first!
	//check core files in preloadProjectView for efficiency

	// Other
	gui.setTarget(*rw);
	hasStarted = true;
	changeScene(0); // project view on startup

	while (running()) {
		render(); 
	}

	// nothing here
}

void Engine::setupVars() {
	log.log("Setting up vars...");
	log.log("Working path: " + fs::current_path().string());
	proj_file_path = fs::current_path().string() + "\\projects.json"; //change with absolute C:/Program Files/Dabs Yt/Dabgine/projects.json
	if (fs::exists(proj_file_path)) {
		std::ifstream proj_file(proj_file_path);
		proj_file >> j;
		proj_file.close();
	} else {
		j = {}; // usable as a dict in projectView
	}
}

void Engine::checkCoreFiles() {

	// Individual checks
	if (!fs::exists(proj_file_path) || fs::file_size(proj_file_path) == 0) {
		log.log("projects.json doesnt exist, creating together with a default project.");

		createProject(j, "Default Game", "The default Dabgine game project.", fs::current_path().string() + "\\Default Game");

		// update dict
		std::ifstream proj_file(proj_file_path);
		j = j.parse(proj_file);
		proj_file.close();
	}

}

void Engine::preloadUI() {
	preloadDialog();
	preloadProjectCreate();
	preloadProjectEdit();
	preloadProjectView();
	preloadProjectEditor();
	preloadOther();
	log.log("Preloading UI done.");
}

void Engine::preloadDialog() {
	log.log("Preloading dialog...");

	tgui::Theme theme("Themes/Black.txt");

	dialog_bg->getRenderer()->setBackgroundColor(tgui::Color(1, 1, 1, 125));

	dialog->setRenderer(theme.getRenderer("ChildWindow"));
	dialog->setInheritedFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	dialog->setTitle("Dialog Title");
	dialog->setTitleAlignment(tgui::ChildWindow::TitleAlignment::Center);
	dialog->setResizable(false);
	dialog->setPositionLocked(true);
	dialog->setPosition("11%", "13%");
	dialog->setSize("80%", "70%");
	dialog->setTitleButtons(tgui::ChildWindow::TitleButton::Close);
	dialog->getRenderer()->setBorders({ 3, 3, 3, 3 });
	dialog->getRenderer()->setBorderColor(tgui::Color("#252525"));
	dialog->getRenderer()->setDistanceToSide(5);
	dialog->getRenderer()->setBorderBelowTitleBar(1.5);
	dialog->getRenderer()->setOpacity(0.8f);
	dialog->getRenderer()->setPaddingBetweenButtons(5);
	//dialog->getRenderer()->setTitleBarHeight(25); // make it auto size
	dialog->getRenderer()->setTitleColor(tgui::Color("#bbbbbb"));
	dialog->getRenderer()->setBackgroundColor(tgui::Color("#242629"));

	dialog->connect("closed", [=]() {
		closeDialog();
		});

	dialog->connect("EscapeKeyPressed", [=]() {
		closeDialog();
		});

	dialog_bg->add(dialog);
}

void Engine::preloadProjectCreate() {
	log.log("Preloading projectCreate...");

	create_name_box = tgui::EditBox::create();
	create_name_box->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	create_name_box->getRenderer()->setTextColor(tgui::Color("#bababf"));
	create_name_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
	create_name_box->getRenderer()->setBackgroundColorHover(tgui::Color("#54575c"));
	create_name_box->getRenderer()->setBackgroundColorFocused(tgui::Color("#585b61"));
	create_name_box->getRenderer()->setDefaultTextColor(tgui::Color("#838487"));
	create_name_box->setTextSize(16);
	//create_name_box->setInputValidator("[a-zA-Z][a-zA-Z0-9]*");
	create_name_box->setMaximumCharacters(20);
	create_name_box->setSize("40%", "8%");
	create_name_box->setPosition(0, 0);
	create_name_box->getRenderer()->setBorders({ 1, 1, 1, 1 });
	create_name_box->getRenderer()->setBorderColor(tgui::Color::Black);
	create_name_box->setDefaultText("Project Name");

	create_description_box = tgui::EditBox::create();
	create_description_box->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	create_description_box->getRenderer()->setTextColor(tgui::Color("#bababf"));
	create_description_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
	create_description_box->getRenderer()->setBackgroundColorHover(tgui::Color("#54575c"));
	create_description_box->getRenderer()->setBackgroundColorFocused(tgui::Color("#585b61"));
	create_description_box->getRenderer()->setDefaultTextColor(tgui::Color("#838487"));
	create_description_box->setTextSize(16);
	//create_description_box->setInputValidator("[a-zA-Z][a-zA-Z0-9]*");
	create_description_box->setMaximumCharacters(50);
	create_description_box->setSize("70%", "8%");
	create_description_box->setPosition(0, "10%");
	create_description_box->getRenderer()->setBorders({ 1, 1, 1, 1 });
	create_description_box->getRenderer()->setBorderColor(tgui::Color::Black);
	create_description_box->setDefaultText("Project Description");

	create_path_box = tgui::EditBox::create();
	create_path_box->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	create_path_box->getRenderer()->setTextColor(tgui::Color("#bababf"));
	create_path_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
	create_path_box->getRenderer()->setBackgroundColorHover(tgui::Color("#54575c"));
	create_path_box->getRenderer()->setBackgroundColorFocused(tgui::Color("#585b61"));
	create_path_box->getRenderer()->setDefaultTextColor(tgui::Color("#838487"));
	create_path_box->setTextSize(16);
	//create_path_box->setInputValidator("[a-zA-Z][a-zA-Z0-9]*");
	create_path_box->setMaximumCharacters(0);
	create_path_box->setSize("70%", "8%");
	create_path_box->setPosition(0, "20%");
	create_path_box->getRenderer()->setBorders({ 1, 1, 1, 1 });
	create_path_box->getRenderer()->setBorderColor(tgui::Color::Black);
	create_path_box->setDefaultText("Project Path");

	tgui::Theme theme("Themes/Black.txt");

	create_btn = tgui::Button::create("Create");
	create_btn->setRenderer(theme.getRenderer("Button"));
	create_btn->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	create_btn->getRenderer()->setTextColor(tgui::Color::White);
	create_btn->getRenderer()->setTextOutlineThickness(1);
	create_btn->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	create_btn->setTextSize(25);
	create_btn->setSize("50%", "10%");
	create_btn->setPosition("25%", "90%");

	create_name_box->connect("TextChanged", [=]() {
		create_name_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
		});

	create_description_box->connect("TextChanged", [=]() {
		create_description_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
		});

	create_name_box->connect("TextChanged", [=]() {
		create_description_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
		});

	create_btn->connect("Clicked", [=]() {
		if (!create_name_box->getText().isEmpty()) {
			if (!create_description_box->getText().isEmpty()) {
				if (!create_path_box->getText().isEmpty()) {
					//createProject(j, create_name_box->getText(), create_description_box->getText(), create_path_box->getText());
				} else {
					create_path_box->getRenderer()->setBackgroundColor(tgui::Color::Red);
				}
			} else {
				create_description_box->getRenderer()->setBackgroundColor(tgui::Color::Red);
			}
		} else {
			create_name_box->getRenderer()->setBackgroundColor(tgui::Color::Red);
		}
		});
}

void Engine::preloadProjectEdit() {
	log.log("Preloading projectEdit...");

	edit_btn = tgui::Button::copy(create_btn);
	edit_btn->setText("Update Project");

	edit_btn->connect("Clicked", [=]() {
		if (!create_name_box->getText().isEmpty()) {
			if (!create_description_box->getText().isEmpty()) {
				std::string edit_proj_name = create_name_box->getText();
				std::string edit_proj_desc = create_description_box->getText();
				editProject(j, curr_edit_project_name, edit_proj_name, edit_proj_desc);
			} else {
				create_description_box->getRenderer()->setBackgroundColor(tgui::Color::Red);
			}
		} else {
			create_name_box->getRenderer()->setBackgroundColor(tgui::Color::Red);
		}
		});
}

void Engine::preloadProjectView() {
	log.log("Preloading projectView...");

	// New widgets
	tgui::Theme theme("Themes/Black.txt"); // main theme for btns etc

	// Pseudo main bg color
	view_main_panel = tgui::Panel::create();
	view_main_panel->getRenderer()->setBackgroundColor(tgui::Color("#111112"));

	view_logo = tgui::Label::create("Dabgine");
	view_logo->setAutoSize(false);
	view_logo->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	view_logo->getRenderer()->setTextColor(sf::Color::White);
	view_logo->getRenderer()->setTextOutlineThickness(1);
	view_logo->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	view_logo->setTextSize(30);
	view_logo->setPosition(0, 0);
	view_logo->setSize("100%", 38);
	view_logo->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	view_logo->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

	view_btn_create = tgui::Button::create("Create Project");
	view_btn_create->setRenderer(theme.getRenderer("Button"));
	view_btn_create->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	view_btn_create->getRenderer()->setTextColor(tgui::Color::White);
	view_btn_create->getRenderer()->setTextOutlineThickness(1);
	view_btn_create->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	view_btn_create->setTextSize(25);
	view_btn_create->setPosition("35%", "92%");
	view_btn_create->setSize("30%", 40);

	// Start adding the projects to a list
	view_proj_list = tgui::ListView::create();
	view_proj_list->setAutoScroll(false);
	view_proj_list->setPosition(10, 40);
	view_proj_list->setSize("97%", "85%");
	view_proj_list->getRenderer()->setBackgroundColor(tgui::Color("#18191a")); // color picker
	view_proj_list->getRenderer()->setBackgroundColorHover(tgui::Color("#292b2b"));
	view_proj_list->getRenderer()->setSelectedBackgroundColor(tgui::Color("#343838"));
	view_proj_list->getRenderer()->setSelectedBackgroundColorHover(tgui::Color("#353838"));
	view_proj_list->getRenderer()->setTextColor(tgui::Color("#9a9da1"));
	view_proj_list->getRenderer()->setTextColorHover(tgui::Color("#b9bbbd"));
	view_proj_list->getRenderer()->setSelectedTextColor(tgui::Color("#cccecf"));
	view_proj_list->getRenderer()->setSelectedTextColorHover(tgui::Color("#d7dadb"));
	view_proj_list->getRenderer()->setFont("Fonts/Alata-Regular.ttf");
	view_proj_list->getRenderer()->setHeaderTextColor(tgui::Color("#9ca1a6"));
	view_proj_list->getRenderer()->setHeaderBackgroundColor(tgui::Color("#131414"));
	view_proj_list->getRenderer()->setBorders({ 3, 3, 3, 3 });
	view_proj_list->getRenderer()->setBorderColor(tgui::Color("#2b2e30"));
	view_proj_list->getRenderer()->setGridLinesColor(tgui::Color("#27292b"));
	view_proj_list->setTextSize(16);
	view_proj_list->setHeaderHeight(25);
	view_proj_list->setHeaderSeparatorHeight(1);
	view_proj_list->getRenderer()->setSeparatorColor(tgui::Color("#27292b"));
	view_proj_list->setSeparatorWidth(2);
	view_proj_list->setHeaderTextSize(20);
	view_proj_list->setShowVerticalGridLines(true);
	//view_proj_list->setShowHorizontalGridLines(true); // buggy
	view_proj_list->setGridLinesWidth(1);
	view_proj_list->getRenderer()->setPadding({ 1, 0, 1, 5 });

	// List signals

	checkCoreFiles(); // recheck since we preloaded the error dialog

	view_proj_list->connect("RightClicked", [=](int itemindex) {
		if (MIMAX(itemindex, -1, view_proj_list->getItemCount())) {
			if (j.contains("projects")) { // prevent empty projects.json error
				std::string proj_path = j["projects"][view_proj_list->getItem(itemindex)]["path"].dump();
				proj_path.erase(std::remove(proj_path.begin(), proj_path.end(), '"'), proj_path.end());
				std::string proj_name = j["projects"][view_proj_list->getItem(itemindex)]["name"].dump();
				proj_name.erase(std::remove(proj_name.begin(), proj_name.end(), '"'), proj_name.end());
				view_proj_list->setSelectedItem(itemindex);
				createProjectEditDialog(view_proj_list->getItem(itemindex));
			}
		}
		});

	view_proj_list->connect("DoubleClicked", [=](int itemindex) {
		if (j.contains("projects")) {
			std::string proj_name = j["projects"][view_proj_list->getItem(itemindex)]["name"].dump();
			proj_name.erase(std::remove(proj_name.begin(), proj_name.end(), '"'), proj_name.end());
			showDialog("Opening '" + proj_name + "' ...", 15);
		}
		});

	view_btn_create->connect("pressed", [=]() {
		createProjectDialog();
		});

	// List project details

	// Columns
	auto list_column_name = view_proj_list->addColumn("Project Name", 150, tgui::ListView::ColumnAlignment::Center);
	view_proj_list->setColumnWidth(list_column_name, 150);

	auto list_column_desc = view_proj_list->addColumn("Project Description", 0, tgui::ListView::ColumnAlignment::Center);
	view_proj_list->setExpandLastColumn(true); // instead of trying out custom width to fill

	// Iterate for values
	if (j.contains("projects")) {
		for (auto element : j["projects"].items()) {
			auto proj_name = element.value()["name"].dump(); // dump for making it usable as a string
			proj_name.erase(std::remove(proj_name.begin(), proj_name.end(), '"'), proj_name.end()); // remove the " from the json string

			auto proj_desc = element.value()["description"].dump();
			proj_desc.erase(std::remove(proj_desc.begin(), proj_desc.end(), '"'), proj_desc.end());

			// Set item names to the corresponding collumn
			view_proj_list->addItem(std::vector<sf::String> {proj_name, proj_desc});

			log.log("Loaded project '" + proj_name + "' to the list.");
		}
	}

}

void Engine::preloadProjectEditor() {
	log.log("Preloading projectEditor...");
}

void Engine::preloadOther() {
	log.log("Preloading other stuff...");
}

void Engine::drawProjectViewer() {
	// Clear previous widgets
	gui.removeAllWidgets();

	// Add first
	view_main_panel->add(view_logo);
	view_main_panel->add(view_proj_list);
	view_main_panel->add(view_btn_create);
	gui.add(view_main_panel);

	// Then animate everything
	view_logo->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
	view_proj_list->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
	view_btn_create->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(2));
}

void Engine::drawProjectEditor() {
	gui.removeAllWidgets();
}

void Engine::createProject(json j, std::string proj_name, std::string proj_description, std::string proj_path) {

	// prevent duplicate project
	for (auto element : j["projects"].items()) {
		/*std::string element_path = element.value()["path"].dump();
		// remove all / to compare strings
		element_path.erase(std::remove(element_path.begin(), element_path.end(), "/"), element_path.end());
		std::string proj_path_original = proj_path;
		proj_path.erase(std::remove(proj_path.begin(), proj_path.end(), "/"), proj_path.end());
		if (element_path == proj_path) {
			createErrorDialog("A project already exists at the specified path.");
			return void();
		}*/
	}

	// passing to create the project
	j["projects"][proj_name];
	j["projects"][proj_name]["name"] = proj_name;
	j["projects"][proj_name]["description"] = proj_description;
	j["projects"][proj_name]["path"] = proj_path;

	fs::create_directory(proj_path);

	std::ofstream proj_file(proj_file_path);

	proj_file << j;

	proj_file.close();
}

void Engine::editProject(json j, std::string proj_name, std::string proj_new_name, std::string proj_new_description) {
	log.log(j["projects"][proj_name].dump());
	if (j["projects"].contains(proj_name)) {
		j["projects"][proj_name]["name"] = proj_new_name;
		j["projects"][proj_name]["description"] = proj_new_description;
		j["projects"][proj_name] = proj_new_name;

		std::ofstream proj_file(proj_file_path);
		proj_file << j;
		proj_file.close();

		log.log("Edited project '" + proj_name + "' \nNew name: " + proj_new_name + " \nNew description: " + proj_new_description);
	}
}

void Engine::showDialog(std::string title,int title_size, tgui::Layout size_w, tgui::Layout size_h, tgui::ChildWindow::TitleButton dialog_btns) {
	dialog->setTitle(title);
	dialog->setTitleTextSize(title_size);
	dialog->setTitleButtons(dialog_btns);
	dialog->setSize(size_w, size_h);
	gui.add(dialog_bg);
	dialog_bg->showWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(dialogShowTime));
	dialog->setFocused(true);
}

void Engine::closeDialog() {
	dialog_bg->hideWithEffect(tgui::ShowAnimationType::Fade, sf::seconds(dialogShowTime));
	dialog->removeAllWidgets();
}

void Engine::createProjectDialog() {
	dialog->add(create_name_box);
	dialog->add(create_description_box);
	dialog->add(create_path_box);
	dialog->add(create_btn);

	create_name_box->setFocused(false);
	create_description_box->setFocused(false);
	create_path_box->setFocused(false);
	create_name_box->setText("");
	create_description_box->setText("");
	create_path_box->setText("");
	create_name_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
	create_description_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));
	create_path_box->getRenderer()->setBackgroundColor(tgui::Color("#42454a"));

	showDialog("Create Project", 20);
}

void Engine::createProjectEditDialog(std::string proj_name) {
	// dont be confused, we are using the project create ui to ease our work in editing..
	curr_edit_project_name = proj_name;
	dialog->add(create_name_box);
	dialog->add(create_description_box);
	dialog->add(edit_btn);

	create_name_box->setFocused(false);
	create_description_box->setFocused(false);
	create_name_box->setText(j["projects"][proj_name]["name"].dump());
	create_description_box->setText(j["projects"][proj_name]["description"].dump());

	showDialog("Editing '" + proj_name + "'", 20);
}

void Engine::createErrorDialog(std::string error_str) {
	auto error_creating = tgui::Label::create(error_str);
	error_creating->getRenderer()->setFont(tgui::Font("Fonts/Alata-Regular.ttf"));
	error_creating->setSize("100%", "100%");
	error_creating->setTextSize(20);
	error_creating->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	error_creating->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

	dialog->add(error_creating);

	showDialog("Dabgine encountered an error.", 20);
}

//////////////// TODO //////////////////
/*void Engine::checkHasErrored() {
	if (isErrored) {
		// open dialog to show error
		log.log(error_str);
		isErrored = false;
	}
}*/

// Events
void Engine::closedEvent() {
	log.log("Dabgine stopping...");
	gui.removeAllWidgets();
	rw->close();
}

void Engine::keyPressedEvent() {
	switch (ev.key.code) {

	}
}

void Engine::resizeEvent() {
	rw->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(ev.size.width), static_cast<float>(ev.size.height))));
	gui.setView(rw->getView());
}

void Engine::mouseMovedEvent() {

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

		case sf::Event::Resized:
			resizeEvent();
			break;

		case sf::Event::MouseMoved:
			mouseMovedEvent();
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

const bool Engine::running() {
	return rw->isOpen();
}

void Engine::setRenderColor(sf::Color newColor) {
	w_render_color = newColor;
}

sf::Color Engine::getRenderColor() {
	return w_render_color;
}

sf::VideoMode Engine::getWindowRect() {
	if (isCustomWindow) {
		return w_cm_vm; 
	} else {
		return w_def_vm;
	}
}

void Engine::changeScene(int which) {
	if (MIMAX(which, -1, max_scenes)) {
		switch (which) {

		case Scene::Project_View:

			log.log("Opening project viewer...");
			
			drawProjectViewer();
			current_scene = Scene::Project_View;

			break;

		case Scene::Project_Editor:

			log.log("Opening project editor...");
			
			drawProjectEditor();
			current_scene = Scene::Project_Editor;

			break;

		}
	}
}


///// |----- PUBLIC FUNCTIONS -----| /////