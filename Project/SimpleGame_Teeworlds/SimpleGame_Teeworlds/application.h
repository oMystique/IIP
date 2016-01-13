#pragma once
#include "menu.h"
#include "world.h"

struct Application {
	RenderWindow *window;
	View view;
	Clock clock;
	Vector2f mousePos;
	float gameSpeed;
	World *world = nullptr;
	int numberLevel;

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
	void CheckWorldState();
	void StartGame();
	void GameOver();
};
