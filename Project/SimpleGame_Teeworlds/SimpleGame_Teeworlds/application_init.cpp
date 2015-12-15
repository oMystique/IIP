#include "application.h"


Application::Application() : World(),
	window(new RenderWindow(sf::VideoMode(1280, 720), "FirstGame. Ildarkin Alexey; PS-22.", Style::Close)) {
	InitMenu();
}


void Application::InitMenu() {
	unique_ptr<Image> menuImage = make_unique<Image>();
	menuImage->loadFromFile("images/bgmenu.png");
	menu = make_unique<Menu>(*menuImage, 1280, 720);
	menu->DrawMenu(*window);
	Run();
}

void Application::Run() {
	window->setMouseCursorVisible(false);
	InitWorldObjects();
	view.reset(FloatRect(player->x, player->y, 880, 370));
	while ((window->isOpen()) && (!player->missionComplete)) {
		float time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / GAME_SPEED;
		GetMouseCoords();
		ProcessEvents();
		InteractObjects(time);
		Update(time);
		Render();
	}
	delete window;
	entities.clear();
}