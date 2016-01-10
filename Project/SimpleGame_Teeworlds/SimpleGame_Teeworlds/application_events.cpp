#include "application.h"


void Application::GetMouseCoords() {
	Vector2i pixelPos = Mouse::getPosition(*window);
	mousePos = window->mapPixelToCoords(pixelPos); 
}


void Application::ProcessEvents() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed) {
			appState = closeGame;
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::LShift) {
			if (world->slowMotion) {
				world->slowMotion = false;
			}
			else {
				world->slowMotion = true;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if ((event.key.code == sf::Keyboard::Space) && (appState != gameMenu)) {
				world->ShootEvent(mousePos);
			}
			if ((event.key.code == Keyboard::R)) {
				appState = startGame;
			}
			if (event.key.code == Keyboard::Pause) {
				if (appState == gameMenu) {
					appState = gaming;
				}
				else {
					appState = gameMenu;
				}
			}
		}
	}
}
