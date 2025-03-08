#include <iostream>
#include "game.hpp"

int main() {
	Game game;
	int num;

	std::cout << "Choose the type of game:\n";
	std::cout << "1. PvP (AI)\n";
	std::cout << "2. PvE (vs other Player)\n";
	std::cout << "3. Campaign mode\n";
	std::cout << "Enter the number: ";
	std::cin >> num;

	switch (num) {
		case 1: 
			game.setMode(std::make_unique<PvPMode>());
			break;
		case 2: 
			game.setMode(std::make_unique<PvEMode>());
			break;
		case 3:
			game.setMode(std::make_unique<CampaignMode>());
			break;
		default:
			std::cout << "Incorrect choice. Exiting.\n";
			return 1;
	}

	game.start();

	return 0;
}