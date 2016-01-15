#include "menu.h"
#include <iostream>

Menu::Menu(Image &image, Vector2f bounds): Interface(image, bounds) {
	sprite.setTextureRect(IntRect(0, 0, int(bounds.x), int(bounds.y)));
	menuMusic.openFromFile(MENU_MUSIC_PATH);
	menuMusic.play();
	menuMusic.setVolume(SOUND_VOLUME);
	menuMusic.setLoop(true);
	isMenu = true;
}

void Menu::ChooseLevel(RenderWindow &window) {
	if (numberLevel == 1 || numberLevel == 2 || numberLevel == 3) {
		isMenu = false;
	}
}

void Menu::PreviewAnimation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > ANIMATION_FRAME / int(GET_THIRD)) {
		currentImage++;
		currentFrame -= ANIMATION_FRAME / int(GET_THIRD);
	}
	if (currentImage >= 110) {
		currentImage = 0;
	}
	if (numberLevel == 1) {
		firstLvlPreviewTexture.loadFromFile("lvlPreview/" + to_string(numberLevel) + "lvl/lvl_" + to_string(currentImage) + ".png");
	}
	else if (numberLevel == 2) {
		secondLvlPreviewTexture.loadFromFile("lvlPreview/" + to_string(numberLevel) + "lvl/lvl_" + to_string(currentImage) + ".png");
	}
	else if (numberLevel == 3) {
		thirdLvlPreviewTexture.loadFromFile("lvlPreview/" + to_string(numberLevel) + "lvl/lvl_" + to_string(currentImage) + ".png");
	}
}

void Menu::GetChooseLevel(RenderWindow &window) {
	float time = float(clock.getElapsedTime().asMicroseconds());
	clock.restart();
	time = time / DEFAULT_GAME_SPEED;
	numberLevel = 0;
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		isPreview = false;
	}
	if (firstLvlPreviewSprite.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		numberLevel = 1;
		PreviewAnimation(time);
	}
	else if (secondLvlPreviewSprite.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		numberLevel = 2;
		PreviewAnimation(time);
	}
	else if (thirdLvlPreviewSprite.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		numberLevel = 3;
		PreviewAnimation(time);
	}
	if (Mouse::isButtonPressed(Mouse::Left)) {
		ChooseLevel(window);
	}
}


void Menu::DrawLvlPreview(RenderWindow &window) {
	GetChooseLevel(window);
	window.draw(chooseLevelSprite);
	window.draw(firstLvlPreviewSprite);
	window.draw(secondLvlPreviewSprite);
	window.draw(thirdLvlPreviewSprite);
}

void Menu::Choose(RenderWindow &window) {
	currentFrame = 0;
	if (menuNum == 1) {
		isMenu = false;
		numberLevel = 1;
	}
	else if (menuNum == 2) {
		isPreview = true;
	}
	else if (menuNum == 3) {
		window.draw(aboutProgramSprite);
		window.display();
		while (!Keyboard::isKeyPressed(Keyboard::Escape));
	}
	else  if (menuNum == 4) {
		window.close();
		isMenu = false;
	}
}


void Menu::GetChoose(RenderWindow &window) {
	menuNum = 0;
	isPreview = false;
	if (newGame.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		newGame.setColor(Color::Red);
		menuNum = 1; 
	}
	else if (chooseLevel.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		chooseLevel.setColor(Color::Red);
		menuNum = 2;
	}
	else if (aboutProgram.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		aboutProgram.setColor(Color::Red);
		menuNum = 3; 
	}
	else if (exit.getGlobalBounds().contains(float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y))) {
		exit.setColor(Color::Red);
		menuNum = 4; 
	}

	if (Mouse::isButtonPressed(Mouse::Left)) {
		Choose(window);
	}
}

void MenuEvents(RenderWindow &window, bool &isMenu) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			isMenu = false;
		}
	}
}

int Menu::DrawMenu(RenderWindow &window) {
	Font font;
	font.loadFromFile(INTERFACE_FONT_PATH);
	newGame.setFont(font);
	newGame.setString("NEW GAME");
	newGame.setPosition(30, 30);
	chooseLevel.setFont(font);
	chooseLevel.setString("CHOOSE LEVEL");
	chooseLevel.setPosition(30, 60);
	aboutProgram.setFont(font);
	aboutProgram.setString("ABOUT PROGRAM");
	aboutProgram.setPosition(30, 90);
	exit.setFont(font);
	exit.setString("EXIT");
	exit.setPosition(30, 120);
	aboutProgramTexture.loadFromFile("images/aboutProgram.png");
	aboutProgramSprite.setTexture(aboutProgramTexture);
	aboutProgramSprite.setPosition(window.getSize().x / GET_HALF, 30);
	firstLvlPreviewTexture.loadFromFile("lvlPreview/1lvl/lvl_0.png");
	firstLvlPreviewSprite.setTexture(firstLvlPreviewTexture);
	firstLvlPreviewSprite.setPosition(800, 72);
	secondLvlPreviewTexture.loadFromFile("lvlPreview/2lvl/lvl_0.png");
	secondLvlPreviewSprite.setTexture(secondLvlPreviewTexture);
	secondLvlPreviewSprite.setPosition(800, 253);
	thirdLvlPreviewTexture.loadFromFile("lvlPreview/3lvl/lvl_0.png");
	thirdLvlPreviewSprite.setTexture(thirdLvlPreviewTexture);
	thirdLvlPreviewSprite.setPosition(800, 434);
	chooseLevelTexture.loadFromFile("images/plashPreview.png");
	chooseLevelSprite.setTexture(chooseLevelTexture);
	chooseLevelSprite.setPosition(window.getSize().x / GET_HALF, 30);
	currentFrame = 0;
	currentImage = 0;
	isPreview = false;
	while (isMenu) {
		if (!isPreview) {
			newGame.setColor(Color::Yellow);
			chooseLevel.setColor(Color::Yellow);
			aboutProgram.setColor(Color::Yellow);
			exit.setColor(Color::Yellow);
			GetChoose(window);
			window.clear();
		}
		MenuEvents(window, isMenu);
		window.draw(sprite);
		window.draw(newGame);
		window.draw(chooseLevel);
		window.draw(aboutProgram);
		window.draw(exit);
		if (isPreview) {
			DrawLvlPreview(window);
		}
		window.display();
	}
	menuMusic.stop();
	return numberLevel;;
}