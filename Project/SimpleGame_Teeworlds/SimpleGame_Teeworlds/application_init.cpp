#include "application.h"


Application::Application() :
	window(new RenderWindow(VideoMode(unsigned int(DEFAULT_WINDOW_SIZE.x), unsigned int(DEFAULT_WINDOW_SIZE.y)), "FirstGame. Ildarkin Alexey; PS-22.")) {
	InitMenu();
	Run();
}


void Application::InitMenu() {
	unique_ptr<Image> menuImage = make_unique<Image>();
	menuImage->loadFromFile("images/bgmenu.png");
	menu = make_unique<Menu>(*menuImage, Vector2f(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y));
	numberLevel = menu->DrawMenu(*window);
}

void Application::GameOver() {
	Text gameOver;
	Text restart;
	RectangleShape plashRect;
	gameOver.setFont(world->interfaceText->font);
	gameOver.setString("GAME STOPPED");
	gameOver.setColor(Color::Red);
	gameOver.setScale(2, 2);
	gameOver.setPosition(window->getView().getCenter().x - 225, window->getView().getCenter().y - 100);
	restart.setFont(world->interfaceText->font);
	restart.setString("PRESS R TO EXIT TO RESTART");
	restart.setColor(Color::Red);
	restart.setPosition(window->getView().getCenter().x - 210, window->getView().getCenter().y);
	plashRect.setFillColor(Color(0, 0, 0, 200));
	plashRect.setSize(DEFAULT_WINDOW_SIZE);
	plashRect.setPosition(window->getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window->getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF);
	window->clear();
	world->DrawObjects(window);
	window->draw(plashRect);
	window->draw(restart);
	if (!((world->countEnemies == 0) && (world->player->missionComplete)) && (world->player->life)) {
		restart.setString("OR PRESS PAUSE TO CONTINUE");
		restart.setColor(Color::Yellow);
		restart.setPosition(window->getView().getCenter().x - 220, window->getView().getCenter().y + 30);
	}
	else {
		gameOver.setString("   GAME OVER");
	}
	window->draw(gameOver);
	window->draw(restart);
	window->display();
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
		}
	}
}

void DestructWorld(World *world) {
	if (world != nullptr) {
		world->DestroyWorldObjects();
		delete world;
	}
}


void Application::StartGame() {
	DestructWorld(world);
	world = new World;
	world->numberLvl = numberLevel;
	world->InitWorldObjects();
	view.reset(FloatRect(world->player->rect.left, world->player->rect.top, DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y));
	appState = gaming;
}

void Application::Run() {
	window->setMouseCursorVisible(false);
	window->setVerticalSyncEnabled(false);
	window->setFramerateLimit(60);
	gameSpeed = DEFAULT_GAME_SPEED;
	appState = startGame;
	while ((window->isOpen())) {
		float time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / gameSpeed;
		GetMouseCoords();
		ProcessEvents();
		if (appState == startGame) {
			StartGame();
		}
		else if (appState == gaming) {
				world->InteractObjects(time);
				Update(time);
				Render();
		}
		else if (appState == gameMenu) {
			GameOver();
		}
		else if (appState == closeGame) {
			window->close();
		}
		CheckWorldState();
	}
	DestructWorld(world);
	delete window;
}