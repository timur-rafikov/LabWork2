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
	virtual void activateAI(Player& owner, Player& opponent, int row) = 0;
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
	bool reflection;
public:
	CharacterCard(const std::string& _type, int _health, int _damage, int _healAmount, int _defenseBonus)
		: Card(_type), health(_health), damage(_damage), healAmount(_healAmount), defenseBonus(_defenseBonus), reflection(false) {}

	virtual void activate(Player& owner, Player& opponent, int row) override {
		std::cout << "Character '" + type + "' has been activated...\n";
	}

	virtual void activateAI(Player& owner, Player& opponent, int row) override {
		std::cout << "AI Character has been activated...\n";
	}

	void setReflection() {
		reflection = true;
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
	bool getReflection() const {
		return reflection;
	}

	void takeDamage(int dmg) {
		if (reflection) {
			reflection = false;
			return;
		}
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
	virtual void activateAI(Player& owner, Player& opponent, int row) {
		std::cout << "AI Ability has been activated...\n";
	}
};

#endif