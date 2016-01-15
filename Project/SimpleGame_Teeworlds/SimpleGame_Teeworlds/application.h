#pragma once
#include "menu.h"
#include "world.h"

struct Application {
	Application();
	~Application();
private:
	RenderWindow *window = nullptr;
	World *world = nullptr;
	View view;
	Clock clock;
	Vector2f mousePos;
	float gameSpeed;
	int numberLevel;
	enum {
		startGame,
		gaming,
		gameMenu,
		closeGame
	} appState;

	unique_ptr<Menu> menu = nullptr;
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
