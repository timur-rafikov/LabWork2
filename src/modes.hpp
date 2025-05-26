#ifndef MODES_H
#define MODES_H

#include "game.hpp"
#include "player.hpp"
#include <limits>
#include <cstdlib>
#include <iostream>

class PvPMode : public GameMode {
private:
	Player player1;
	Player player2;
	int currentPlayer;

	void displayField();
	void displayCurrentPlayerHand();

	void processPlayerTurn(Player& currentPlayerObj, Player& opponentPlayerObj);
	bool checkWin();
public:
	PvPMode() : player1(1), player2(2), currentPlayer(1) {}

	void start() override;
};

class PvEMode : public GameMode {
private:
	Player AIPlayer;
	Player player;
	int currentPlayer;
	int winnerID;

	void displayField();
	void displayCurrentPlayerHand();

	void processPlayerTurn();
	void makeAITurn();
	bool checkWin();
public:
	PvEMode() :  AIPlayer(1), player(2), currentPlayer(1), winnerID(0) {}

	void start() override;

	int getWinner() {
		return winnerID;
	}
};

class CampaignMode : public GameMode {
private:
	std::vector<std::unique_ptr<PvEMode>> levels;

	void printMessage(int level);

public:
	CampaignMode();

	void start() override;
};

#endif