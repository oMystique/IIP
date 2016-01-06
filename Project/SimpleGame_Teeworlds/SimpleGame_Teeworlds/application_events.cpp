#include "application.h"


void Application::GetMouseCoords() {
	Vector2i pixelPos = Mouse::getPosition(*window);
	Vector2f pos = window->mapPixelToCoords(pixelPos); 
	mousePos = pos;
}


void Application::ProcessEvents() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed) {
			appState = closeGame;
		}
		if (event.type == Event::Resized) {
			system("pause");
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space) {
				world->Shoot("player", mousePos);
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if ((event.key.code == Keyboard::R)) {
				appState = startGame;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == Keyboard::Pause) {
				appState = gameMenu;
			}
		}
	}
}
