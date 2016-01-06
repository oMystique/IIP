#include "menu.h"

Menu::Menu(Image &image, Vector2f bounds): Interface(image, bounds) {
	sprite.setTextureRect(IntRect(0, 0, int(bounds.x), int(bounds.y)));
	menuMusic.openFromFile("sounds/menuMusic(avicii).ogg");
	menuMusic.play();
	menuMusic.setVolume(SOUND_VOLUME);
	menuMusic.setLoop(true);
	isMenu = true;
}


void Menu::Choose(RenderWindow &window) {
	if (menuNum == 1) {
		isMenu = false;
		menuMusic.stop();
	}
	else if (menuNum == 2) {
		window.draw(aboutProgram);
		window.display();
		while (!Keyboard::isKeyPressed(Keyboard::Escape));
	}
	else  if (menuNum == 3) {
		window.close();
		isMenu = false;
		menuMusic.stop();
	}
}


void Menu::GetChoose(RenderWindow &window) {
	menuNum = 0;
	if (newGame.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		newGame.setColor(Color::Blue);
		menuNum = 1; 
	}
	else if (aboutProgram.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		aboutProgram.setColor(Color::Blue);
		menuNum = 2; 
	}
	else if (exit.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		exit.setColor(Color::Blue);
		menuNum = 3; 
	}

	if (Mouse::isButtonPressed(Mouse::Left)) {
		Choose(window);
	}
}



void Menu::DrawMenu(RenderWindow &window) {
	Font font;
	font.loadFromFile("font.ttf");
	newGame.setFont(font);
	newGame.setString("NEW GAME");
	newGame.setPosition(30, 30);
	aboutProgram.setFont(font);
	aboutProgram.setString("ABOUT PROGRAM");
	aboutProgram.setPosition(30, 60);
	exit.setFont(font);
	exit.setString("EXIT");
	exit.setPosition(30, 90);
	while (isMenu) {
		newGame.setColor(Color::Red);
		aboutProgram.setColor(Color::Red);
		exit.setColor(Color::Red);
		GetChoose(window);
		window.clear();
		window.draw(sprite);
		window.draw(newGame);
		window.draw(aboutProgram);
		window.draw(exit);
		window.display();
	}
}