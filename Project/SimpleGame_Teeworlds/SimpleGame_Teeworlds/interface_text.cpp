#include "interface_text.h"

InterfaceText::InterfaceText() {
	font.loadFromFile("font.ttf");
	countEnemiesText.setFont(font);
	countEnemiesText.setColor(Color::Blue);
	missionTargetText.setFont(font);
	missionTargetText.setColor(Color::Blue);
}


void InterfaceText::UpdateText(RenderWindow &window, int const countEnemies, bool const missionTarget) {
	Vector2f center = window.getView().getCenter();
	if ((countEnemiesText.getColor() == (Color::Red) && (missionTargetText.getColor() == (Color::Red)))) {
		countEnemiesText.setString("TAKE FLAG AT THE END.");
		missionTargetText.setString("");
	}
	else {
		countEnemiesText.setString("Count enemies: " + to_string(countEnemies));
		if (countEnemies == 0) {
			countEnemiesText.setColor(Color::Red);
		}
		if (missionTarget) {
			missionTargetText.setString("Flag captured");
			missionTargetText.setColor(Color::Red);
		}
		else {
			missionTargetText.setString("Flag is not captured");
		}
	}
	missionTargetText.setPosition(center.x - MISSION_TEXT_CORRECTION.x, center.y - MISSION_TEXT_CORRECTION.y);
	countEnemiesText.setPosition(center.x - MISSION_TEXT_CORRECTION.x, center.y - COUNT_ENEMIES_TEXT_CORRECTION);
	DrawText(window);
}



void InterfaceText::DrawText(RenderWindow &window) {
	window.draw(missionTargetText);
	window.draw(countEnemiesText);
}