#include "application.h"


Application::Application() :
	window(new RenderWindow(VideoMode(unsigned int(DEFAULT_WINDOW_SIZE.x), unsigned int(DEFAULT_WINDOW_SIZE.y)), "FirstGame. Ildarkin Alexey; PS-22.")) {
	InitMenu();
	appState = startGame;
	Run();
}


void Application::InitMenu() {
	unique_ptr<Image> menuImage = make_unique<Image>();
	menuImage->loadFromFile("images/bgmenu.png");
	menu = make_unique<Menu>(*menuImage, Vector2f(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y));
	menu->DrawMenu(*window);
}

void Application::GameOver() {
	gameOver.setFont(world->interfaceText->font);
	gameOver.setString("GAME OVER");
	gameOver.setColor(Color::Red);
	gameOver.setScale(2, 2);
	gameOver.setPosition(window->getView().getCenter().x - 180, window->getView().getCenter().y - 100);
	restart.setFont(world->interfaceText->font);
	restart.setString("PRESS R TO EXIT TO MENU");
	restart.setColor(Color::Red);
	restart.setPosition(window->getView().getCenter().x - 195, window->getView().getCenter().y);
	plashRect.setFillColor(Color(0, 0, 0, 200));
	plashRect.setSize(DEFAULT_WINDOW_SIZE);
	plashRect.setPosition(window->getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window->getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF);
	window->clear();
	world->DrawObjects(window);
	window->draw(plashRect);
	window->draw(gameOver);
	window->draw(restart);
	window->display();
}

void Application::Run() {
	window->setMouseCursorVisible(false);
	window->setFramerateLimit(60);
	world = new World();
	world->InitWorldObjects();
	view.reset(FloatRect(world->player->rect.left, world->player->rect.top, DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y));
	appState = gaming;
	while ((window->isOpen())) {
		if (appState == startGame) {
			world->DestroyWorldObjects();
			delete world;
			world = new World();
			world->InitWorldObjects();
			appState = gaming;
		}
		else if (appState == gameMenu) {
			InitMenu();
		}
		else if (appState == gaming) {
			float time = float(clock.getElapsedTime().asMicroseconds());
			clock.restart();
			time = time / GAME_SPEED;
			GetMouseCoords();
			ProcessEvents();
			if (!((world->countEnemies == 0) && (world->player->missionComplete)) && (world->player->life)) {
				world->InteractObjects(time);
				Update(time);
				Render();
			}
			else {
				GameOver();
			}
		}
		else if (appState == closeGame) {
			window->close();
		}
	}
}