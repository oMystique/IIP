#include "interface_text.h"

InterfaceText::InterfaceText() {
	font.loadFromFile(INTERFACE_FONT_PATH);
	countEnemiesText.setFont(font);
	countEnemiesText.setColor(Color::Blue);
	missionTargetText.setFont(font);
	missionTargetText.setColor(Color::Blue);
}


void InterfaceText::UpdateText(RenderWindow &window, int const countEnemies, bool const missionTarget) {
	Vector2f center = window.getView().getCenter();
	if ((countEnemiesText.getColor() == (Color::Red) && (missionTargetText.getColor() == (Color::Red)))) {
		countEnemiesText.setString(TAKE_FLAG_AT_THE_END);
		missionTargetText.setString("");
	}
	else {
		countEnemiesText.setString(COUNT_ENEMIES + to_string(countEnemies));
		if (!countEnemies) {
			countEnemiesText.setColor(Color::Red);
		}
		if (missionTarget) {
			missionTargetText.setString(FLAG_CAPTURED);
			missionTargetText.setColor(Color::Red);
		}
		else {
			missionTargetText.setString(FLAG_NOT_CAPTURED);
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