#include "application.h"


bool StartGame() {
	unique_ptr<Application> application(new Application());
	return(application->player->missionComplete);
}

void GameRunning() {
	bool game = StartGame();
	if (game) {
		GameRunning();
	}
}


int main() {
	GameRunning();
	return 0;
}