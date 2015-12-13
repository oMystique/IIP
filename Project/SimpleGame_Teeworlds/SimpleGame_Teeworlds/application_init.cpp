#include "application.h"


Application::Application() : World(),
	window(new RenderWindow(sf::VideoMode(1280, 720), "FirstGame. Ildarkin Alexey; PS-22.", Style::Close)) {
}


void Application::Run() {
	window->setMouseCursorVisible(false);
	InitWorldObjects();
	view.reset(FloatRect(player->x, player->y, 880, 370));
	while (window->isOpen()) {
		float time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / GAME_SPEED;
		GetMouseCoords();
		ProcessEvents();
		InteractObjects();
		Update(time);
		Render();
	}
	delete window;
}