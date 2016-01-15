#include "application.h"

void UpdateAppSpeed(bool const isMotion, float &gameSpeed) {
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

void Application::CheckWorldState() {
	if (!world->player->life) {
		appState = gameMenu;
	}
	else if ((world->countEnemies == 0) && (world->player->missionComplete)) {
		if (numberLevel < GET_THIRD) {
			numberLevel++;
			appState = startGame;
		}
		else {
			appState = gameMenu;
			numberLevel = 1;
		}
	}
}

void Application::Render() {
	window->setView(view);
	window->clear();
	world->DrawObjects(window);
	window->display();
}