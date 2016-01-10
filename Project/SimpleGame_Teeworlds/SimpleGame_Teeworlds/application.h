#pragma once
#include "menu.h"
#include "world.h"

struct Application {
	RenderWindow *window;
	View view;
	Clock clock;
	Vector2f mousePos;
	float gameSpeed;
	Text gameOver;
	Text restart;
	RectangleShape plashRect;
	World *world;

	enum {
		startGame,
		gaming,
		gameMenu,
		closeGame
	} appState;

	Application();
private:
	unique_ptr<Menu> menu;
	void InitMenu();
	void Run();
	void ProcessEvents();
	void Render();
	void Update(float time);
	void GetMouseCoords();
	void GameOver();
};
