#ifndef CARD_H
#define CARD_H

#include "player.hpp"
#include <string>
#include <memory>
#include <iostream>

class Player;

class Card {
protected:
	std::string type;
public:
	Card(const std::string& _type) : type(_type) {}
	virtual void activate(Player& owner, Player& opponent, int row) = 0;
	virtual void printInfo() const = 0;

	std::string getType() {
		return type;
	}
};

class CharacterCard : public Card {
private:
	int health;			// Health
	int damage;			// Damage
	int healAmount;		// The amount of healing
	int defenseBonus;	// Bonus for defCoef
public:
	CharacterCard(const std::string& _type, int _health, int _damage, int _healAmount, int _defenseBonus)
		: Card(_type), health(_health), damage(_damage), healAmount(_healAmount), defenseBonus(_defenseBonus) {}

	virtual void activate(Player& owner, Player& opponent, int row) override {
		std::cout << "Character '" + type + "' has been activated...\n";
	}

	void printInfo() const override {
		std::cout << "Name: " << type << '\n';
		std::cout << "HEALTH: " << health << '\n';
		std::cout << "DAMAGE: " << damage << '\n';
		std::cout << "HEAL AMOUNT: " << healAmount << '\n';
		std::cout << "DEFENSE BONUS: " << defenseBonus << '\n';
	}

	int getHealth() const {
		return health;
	}
	int getDamage() const {
		return damage;
	}
	int getHealAmount() const {
		return healAmount;
	}
	int getDefenseBonus() const {
		return defenseBonus;
	}

	void takeDamage(int dmg) {
		health -= dmg;
	}
	void heal(int amount) {
		health += amount;
	}
};

class AbilityCard : public Card {
public:
	AbilityCard(const std::string& _type) : Card(_type) {}

	virtual void activate(Player& owner, Player& opponent, int row) {
		std::cout << "Ability '" + type + "' has been activated...\n";
	}
	virtual void printInfo() const {
		std::cout << "Ability type: " << type << '\n';
	}
};

#endif