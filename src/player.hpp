#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include "card.hpp"

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
	
	std::unique_ptr<Card> popDeadCharacter(int index) {
		return std::move(deadCharacters[index]);
	}

	void activateCharacterCard(Player& owner, Player& opponent, int index, int row) {
		handCharacters[index]->activate(owner, opponent, row);
		auto characterCard = dynamic_cast<CharacterCard*>(handCharacters[index].get());
		if (characterCard) 
			defCoef += characterCard->getDefenseBonus();
		else 
			std::cerr << "Error: Card is not a CharacterCard!\n";
	}

	void activateAbilityCard(Player& owner, Player& opponent, int index) {
		handAbilities[index]->activate(owner, opponent, 0);
	}
	
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
		auto deadChar = std::move(field[row][col]);
		field[row][col] = std::make_unique<CharacterCard>("EmptySlot", 0, 0, 0, 0);
		deadCharacters.push_back(std::move(deadChar));
	}

	int damageReduction(int damage) const {
		return floor((1.0 - (1.0 * defCoef / 100.0)) * damage); 
	}

	void takeDamage(int row, int col, int dmg);

	void healingCharacter(int row, int col, int amount) {
		// field[row][col]->heal(amount);
		auto characterCard = dynamic_cast<CharacterCard*>(field[row][col].get());
		if (characterCard)
			characterCard->heal(amount);
		else
			std::cerr << "Error: No characterCard to heal\n";
	}

	bool isAbilEmpty() const {
		return handAbilities.empty();
	}

	bool isCharEmpty() const {
		return handCharacters.empty();
	}

	bool isFieldFull() const;

	int getSizeHandChars() const {
		return (int)handCharacters.size();
	}

	int getDefCoef() const {
		return defCoef;
	}

	int getId() const {
		return id;
	}

	void decreaseDefense(int count) {
		defCoef -= count;
	}

	int getSumHealthOnField() const;

	void printField(bool reverse = false) const;
	void printHand() const;
	void printDead() const;
};

#endif