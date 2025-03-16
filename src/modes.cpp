#include "modes.hpp"

void PvPMode::displayField() {
	std::cout << "FIELD (Player1 on the top)             First player defence: " << player1.getDefCoef() << " | Second player defence: " << player2.getDefCoef() << '\n';
	std::cout << "  0 1 2 3\n";
	player1.printField(true);

	std::cout << "  _______";
	if (currentPlayer == 1)
		std::cout << " ^^^^\n";
	else std::cout << " vvvv\n";

	player2.printField();
	std::cout << "  0 1 2 3\n";
}

void PvPMode::displayCurrentPlayerHand() {
	if (currentPlayer == 1) {
		player1.printHand(false);
	} else {
		player2.printHand(false);
	}
}

void PvPMode::processPlayerTurn(Player& currentPlayerObj, Player& opponentPlayerObj) {
	int cardIndex, row, col;
	if (!currentPlayerObj.isCharEmpty() && !currentPlayerObj.isFieldFull()) {
		std::cout << "\nChoose a character card to play (index): ";
		std::cin >> cardIndex;

		std::cout << "Choose a row (0-1) and column (0-3) to place card: ";
		std::cin >> row >> col;

		currentPlayerObj.activateCharacterCard(currentPlayerObj, opponentPlayerObj, cardIndex, row, false);

		auto cardChar = currentPlayerObj.popCharacterFromHand(cardIndex);

		if (currentPlayerObj.getId() == 1) {
			row = 1 - row;
			col = 3 - col;
		}
		currentPlayerObj.moveCardToField(std::move(cardChar), row, col);

		//std::cout << "Card played successfully!\n";
	}


	if (!currentPlayerObj.isAbilEmpty()) {
		std::cout << "\nChoose an ability card to play (index from 0): ";
		std::cin >> cardIndex;

		currentPlayerObj.activateAbilityCard(currentPlayerObj, opponentPlayerObj, cardIndex, false);
	}

	if (currentPlayerObj.isCharEmpty() && currentPlayerObj.isAbilEmpty()) {
		std::cout << "Oh no... You're hand is empty\n";
	}
}

bool PvPMode::checkWin() {
	// if ((player1.isCharEmpty() || player1.isFieldFull()) && (player2.isCharEmpty() || player2.isFieldFull()) && player1.isAbilEmpty() && player2.isAbilEmpty()) {
	if ((player1.isCharEmpty() && player1.isFieldFull()) || (player2.isCharEmpty() && player2.isFieldFull())) {
		int sum1 = player1.getSumHealthOnField(), sum2 = player2.getSumHealthOnField();
		if (sum1 > sum2)
			std::cout << "Player 1 win!\n";
		else if (sum1 < sum2)
			std::cout << "Player 2 win!\n";
		else std::cout << "Draw!\n";

		std::cout << "Player 1 summary health: " << sum1 << '\n';
		std::cout << "Player 2 summary health: " << sum2 << '\n';

		return true;
	}
	return false;
}

void PvPMode::start() {
	while (!checkWin()) {
		clearScreen();

		displayField();

		displayCurrentPlayerHand();

		if (currentPlayer == 1)
			processPlayerTurn(player1, player2);
		else
			processPlayerTurn(player2, player1);

		currentPlayer = (currentPlayer == 1) ? 2 : 1;

		std::cout << "Press Enter to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}
}











void PvEMode::displayField() {
	std::cout << "FIELD (AI on the top)             AI defence: " << AIPlayer.getDefCoef() << " | Player defence: " << player.getDefCoef() << '\n';
	std::cout << "  0 1 2 3\n";
	AIPlayer.printField(true);

	std::cout << "  _______";
	if (currentPlayer == 1)
		std::cout << " ^^^^\n";
	else std::cout << " vvvv\n";

	player.printField();
	std::cout << "  0 1 2 3\n";
}

void PvEMode::displayCurrentPlayerHand() {
	if (currentPlayer == 2) 
		player.printHand(true);
}


void PvEMode::processPlayerTurn() {
	int cardIndex, row, col;
	if (!player.isCharEmpty() && !player.isFieldFull()) {
		std::cout << "\nChoose a character card to play (index): ";
		std::cin >> cardIndex;

		std::cout << "Choose a row (0-1) and column (0-3) to place card: ";
		std::cin >> row >> col;

		player.activateCharacterCard(player, AIPlayer, cardIndex, row, false);

		auto cardChar = player.popCharacterFromHand(cardIndex);

		player.moveCardToField(std::move(cardChar), row, col);

		//std::cout << "Card played successfully!\n";
	}


	if (!player.isAbilEmpty()) {
		std::cout << "\nChoose an ability card to play (index from 0): ";
		std::cin >> cardIndex;

		player.activateAbilityCard(player, AIPlayer, cardIndex, false);
	}

	if (player.isCharEmpty() && player.isAbilEmpty()) {
		std::cout << "Oh no... You're hand is empty\n";
	}
}

void PvEMode::makeAITurn() {
	int cardIndex = -1, row = -1, col = -1;
	if (!AIPlayer.isCharEmpty() && !AIPlayer.isFieldFull()) {

		cardIndex = rand() % AIPlayer.getSizeHandChars();

		// std::cout << "Choose a row (0-1) and column (0-3) to place card: ";
		// std::cin >> row >> col;

		if (AIPlayer.getCardHandType(cardIndex) == "Knight") {
			for (int j = 0; j < 4; ++j)
				if (AIPlayer.getCardType(0, j) == "EmptySlot") {
					row = 0;
					col = j;
					break;
				}
		}
		if (row == -1) {
			for (int i = 1; i >= 0; --i) {
				for (int j = 0; j < 4; ++j) {
					if (AIPlayer.getCardType(i, j) == "EmptySlot") {
						row = i;
						col = j;
						break;
					}
				}
				if (row != -1)
					break;
			}
		}

		std::cout << "The AI put the " << AIPlayer.getCardHandType(cardIndex) << " in position " << 1 - row << ' ' << 3 - col << '\n';

		AIPlayer.activateCharacterCard(AIPlayer, player, cardIndex, row, true);

		auto cardChar = AIPlayer.popCharacterFromHand(cardIndex);

		AIPlayer.moveCardToField(std::move(cardChar), row, col);
	}


	if (!AIPlayer.isAbilEmpty()) {
		cardIndex = rand() % AIPlayer.getSizeHandAbils();

		AIPlayer.activateAbilityCard(AIPlayer, player, cardIndex, true);
	}

	if (AIPlayer.isCharEmpty() && AIPlayer.isAbilEmpty()) {
		std::cout << "Oh no... AI hand is empty\n";
	}
}

bool PvEMode::checkWin() {
	// if ((player.isCharEmpty() || player.isFieldFull()) && (AIPlayer.isCharEmpty() || AIPlayer.isFieldFull()) && player.isAbilEmpty() && AIPlayer.isAbilEmpty()) {
	if ((player.isCharEmpty() || player.isFieldFull()) || (AIPlayer.isCharEmpty() || AIPlayer.isFieldFull())) {
		clearScreen();
		
		int sumPlayer = player.getSumHealthOnField();
		int sumAI = AIPlayer.getSumHealthOnField();
		if (sumPlayer > sumAI){
			std::cout << "Congratulations, you've won!\n";
			winnerID = 2;
		}
		else {
			std::cout << "You've lost, try your best...\n";
			winnerID = 1;
		}

		std::cout << "Player summary health: " << sumPlayer << '\n';
		std::cout << "AI summary health: " << sumAI << '\n';

		std::cout << "Press Enter to exit...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();

		return true;
	}
	return false;
}

void PvEMode::start() {
	while (!checkWin()) {
		clearScreen();

		displayField();

		displayCurrentPlayerHand();

		if (currentPlayer == 1)
			makeAITurn();
		else
			processPlayerTurn();

		currentPlayer = (currentPlayer == 1) ? 2 : 1;

		std::cout << "Press Enter to continue...";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}
}












CampaignMode::CampaignMode() {
	for (int i = 0; i < 3; ++i)
		levels.push_back(std::make_unique<PvEMode>());
}

void CampaignMode::printMessage(int level) {
	switch (level) {
		case 0:
			std::cout << "Long ago, in the distant kingdom of Eldaria, magic and chivalry flourished. But one day, dark forces awakened in the ancient ruins on the edge of the forest.\n";
			std::cout << "Locals speak of strange sounds echoing from the depths of the woods and shadows wandering among the trees. You are a wandering knight who has stumbled upon these lands.\n";
			std::cout << "The village elder begs you to investigate the strange occurrences.\n\n";
			std::cout << "You stand at the edge of an ancient forest. The air is thick with the scent of moss and damp earth.\n";
			std::cout << "The wind whispers warnings in your ear, but you decide to press on. Suddenly, shadows emerge from behind the trees—undead creatures, awakened by an ancient curse.\n";
			std::cout << "Your sword is already in hand, and you are ready to face these horrors. Remember: in this forest, every step could be your last...\n\n";
			break;
		case 1:
			std::cout << "After defeating the undead, you find an ancient artifact—a key with mysterious runes.\n";
			std::cout << "A local sage tells you that this key unlocks the gates to the Castle of Forgotten Souls, where the spirits of those who once served the kingdom are trapped, victims of betrayal.\n";
			std::cout << "The castle is shrouded in mist, and no one has ever returned from it alive. But you decide to enter, determined to uncover its secrets and free the lost souls.\n\n";
			std::cout << "You stand before the massive gates of the castle. The key in your hand begins to glow, and the gates slowly creak open.\n";
			std::cout << "Inside, you are met with an icy wind and the whispers of forgotten souls. The shadows of knights, once loyal to the kingdom, now guard these walls.\n";
			std::cout << "They will not let you pass without a fight.\nPrepare to face the ghosts of the past...\n\n";
			break;
		case 2:
			std::cout << "Deep within the castle, you find an ancient altar holding a dark artifact—the Heart of Darkness. It awakens an ancient evil that once nearly destroyed Eldaria.\n";
			std::cout << "Now, this evil threatens the world once more. You must stop it, but to do so, you will have to face its servants and the embodiment of darkness itself.\n\n";
			std::cout << "You enter the castle’s throne room. The air trembles with dark energy. On the altar before you lies the Heart of Darkness, pulsating with a sinister light.\n";
			std::cout << "Suddenly, a figure emerges from the shadows—it is the Archdemon, the ancient evil awakened by the artifact. Its eyes burn with hatred, and its voice booms like thunder.\n";
			std::cout << "'You are too late, mortal,' it says. But you know this is your last chance to save the world.\nPrepare for the final battle...\n\n";
			break;
	}

	std::cout << "Press Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void CampaignMode::start() {
	for (int i = 0; i < 3; ++i) {
		clearScreen();
		printMessage(i);
		levels[i]->start();
		if (levels[i]->getWinner() == 1)
			return;
	}
}