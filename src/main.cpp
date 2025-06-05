#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"
#include "modes.hpp"

int main() {
	srand(time(0));
	
	Game game;
	int num;

	std::system("clear");
	std::cout << "Choose the type of game:\n";
	std::cout << "1. PvP (vs other Player)\n";
	std::cout << "2. PvE (AI)\n";
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

	// game.setMode(std::make_unique<PvPMode>());

	// std::system("clear");
	game.start();

	return 0;
}