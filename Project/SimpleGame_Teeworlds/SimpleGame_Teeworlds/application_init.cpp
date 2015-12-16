#include "application.h"


Application::Application() : World(),
	window(new RenderWindow(VideoMode(unsigned int(DEFAULT_WINDOW_SIZE.x), unsigned int(DEFAULT_WINDOW_SIZE.y)), "FirstGame. Ildarkin Alexey; PS-22.")) {
	InitMenu();
	Run();
}


void Application::InitMenu() {
	unique_ptr<Image> menuImage = make_unique<Image>();
	menuImage->loadFromFile("images/bgmenu.png");
	menu = make_unique<Menu>(*menuImage, Vector2f(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y));
	menu->DrawMenu(*window);
}

void Application::Run() {
	window->setMouseCursorVisible(false);
	InitWorldObjects();
	view.reset(FloatRect(player->rect.left, player->rect.top, DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y));
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
	entities.clear();
}