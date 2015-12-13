#include "application.h"


void Application::GetMouseCoords() {
	Vector2i pixelPos = Mouse::getPosition(*window); //�������� ����� �������
	Vector2f pos = window->mapPixelToCoords(pixelPos); //��������� �� � ������� (������ �� ����� ����)
	mouseX = pos.x;
	mouseY = pos.y;
}


void Application::ProcessEvents() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed) {
			window->close();
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space) {
				Shoot("player", mouseX, mouseY);
			}
		}
	}
}
