#include "application.h"

void UpdateAppSpeed(bool isMotion, float &gameSpeed) {
	if (!isMotion) {
		gameSpeed = DEFAULT_GAME_SPEED;
	}
	else {
		gameSpeed = SLOW_GAME_SPEED;
	}
}


void Application::Update(float time) {
	UpdateAppSpeed(world->slowMotion, gameSpeed);
	world->UpdateWorld(time, mousePos, view, *window);
}


void Application::Render() {
	window->setView(view);
	window->clear();
	world->DrawObjects(window);
	window->display();
}