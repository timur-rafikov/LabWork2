#ifndef GAME_H
#define GAME_H

#include <memory>

class Game;

class GameMode {
public:
	virtual void start() = 0;
};

class Game {
private:
	std::unique_ptr<GameMode> mode;
public:
	Game() : mode(nullptr) {};
	void setMode(std::unique_ptr<GameMode> newMode) {
		mode = std::move(newMode);
	}
	void start() {
		if (mode)
			mode->start();
	}
};

#endif