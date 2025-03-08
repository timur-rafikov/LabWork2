#ifndef PLAYER_H
#define PLAYER_H

#include "card.hpp"
#include <string>

class Player {
private:
	std::vector<std::unique_ptr<Card>> handCharacters;
	std::vector<std::unique_ptr<Card>> handAbilities;
	std::vector<std::vector<std::unique_ptr<Card>>> field;
	std::vector<std::unique_ptr<Card>> deadCharacters;
	int id;
	int defCoef;
public:
	Player(const int& _id);
	std::unique_ptr<Card> popCharacterFromHand(int index);
	std::unique_ptr<Card> popAbilityFromHand(int index);
	
	void addCharacterToHand(std::unique_ptr<Card> newCharacter) {
		handCharacters.push_back(std::move(newCharacter));
	}

	void addAbilityToHand(std::unique_ptr<Card> newAbility) {
		handAbilities.push_back(std::move(newAbility));
	}

	void moveCardToField(std::unique_ptr<Card> newCard, int row, int col) {
		field[row][col] = std::move(newCard);
	}

	void moveCharacterToDead(int row, int col) {
		deadCharacters.push_back(std::move(field[row][col]));
	}

	void takeDamage(int row, int col, int dmg) {
		field[row][col]->takeDamage(dmg);
	}

	void printField(bool reverse = false) const;
	void printHand() const;
};

#endif