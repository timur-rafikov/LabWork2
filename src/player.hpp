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
	std::unique_ptr<Card> popDeadCharacter(int index);
	
	void activateCharacterCard(Player& owner, Player& opponent, int index, int row, bool ai);

	void activateAbilityCard(Player& owner, Player& opponent, int index, bool ai) {
		if (!ai)
			handAbilities[index]->activate(owner, opponent, 0);
		else handAbilities[index]->activateAI(owner, opponent, 0);
		popAbilityFromHand(index);
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

	void moveCharacterToDead(int row, int col);

	int damageReduction(int damage) const {
		return floor((1.0 - (1.0 * defCoef / 100.0)) * damage); 
	}

	void takeDamage(int row, int col, int dmg);

	void healingCharacter(int row, int col, int amount);

	bool isAbilEmpty() const {
		return handAbilities.empty();
	}

	bool isCharEmpty() const {
		return handCharacters.empty();
	}

	bool isDeadCharEmpty() const {
		return deadCharacters.empty();
	}

	bool isFieldFull() const;

	int getSizeHandChars() const {
		return (int)handCharacters.size();
	}

	int getSizeHandAbils() const {
		return (int)handAbilities.size();
	}

	int getDefCoef() const {
		return defCoef;
	}

	bool getReflection(int row, int col);

	void setReflection(int row, int col);

	void addDefence(int defAmount) {
		defCoef += defAmount;
		defCoef = std::max(0, defCoef);
	}

	int getId() const {
		return id;
	}

	int getSumHealthOnField() const;

	std::string getCardType(int row, int col) const {
		return field[row][col]->getType();
	}

	std::string getCardHandType(int index) const {
		return handCharacters[index]->getType();
	}

	void printField(bool reverse = false) const;
	void printHand(bool ai) const;
	void printDead() const;
};

#endif