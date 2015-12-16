#include "application.h"


void Application::GetMouseCoords() {
	Vector2i pixelPos = Mouse::getPosition(*window); //забираем коорд курсора
	Vector2f pos = window->mapPixelToCoords(pixelPos); //переводим их в игровые (уходим от коорд окна)
	mousePos = pos;
}


void Application::ProcessEvents() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed) {
			window->close();
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space) {
				Shoot("player", mousePos);
			}
		}
	}
}
