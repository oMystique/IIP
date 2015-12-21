#include "application.h"


Application::Application() : World(),
	window(new RenderWindow(VideoMode(unsigned int(DEFAULT_WINDOW_SIZE.x), unsigned int(DEFAULT_WINDOW_SIZE.y)), "FirstGame. Ildarkin Alexey; PS-22.")) {
	InitMenu();
	Run();
}


void Application::InitMenu() {
	unique_ptr<Image> menuImage = make_unique<Image>();
	menuImage->loadFromFile("images/bgmenu.png");
	menu = make_unique<Menu>(*menuImage, Vector2f(DEFAULT_WINDOW_SIZE.x, DEFAULT_WINDOW_SIZE.y));
	menu->DrawMenu(*window);
}

void Application::GameOver() {
	gameOver.setFont(font);
	gameOver.setString("GAME OVER");
	gameOver.setColor(Color::Red);
	gameOver.setScale(2, 2);
	gameOver.setPosition(window->getView().getCenter().x - 180, window->getView().getCenter().y - 100);
	restart.setFont(font);
	restart.setString("PRESS R TO RESTART GAME");
	restart.setColor(Color::Red);
	restart.setPosition(window->getView().getCenter().x - 200, window->getView().getCenter().y);
	window->clear(Color(0, 0, 0, 255));
	window->draw(gameOver);
	window->draw(restart);
	window->display();
}

void Application::Run() {
	window->setMouseCursorVisible(false);
	InitWorldObjects();
	view.reset(FloatRect(player->rect.left, player->rect.top, DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y));
	while ((window->isOpen())) {
		float time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / GAME_SPEED;
		GetMouseCoords();
		ProcessEvents();
		if (!((countEnemies == 0) && (player->missionComplete))) {
			InteractObjects(time);
			Update(time);
			Render();
		}
		else {
			GameOver();
		}
	}
	entities.clear();
}