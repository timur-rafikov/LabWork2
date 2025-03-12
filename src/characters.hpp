#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "card.hpp"
#include "player.hpp"
#include <ctime>
#include <cstdlib>
#include <string>

class Knight : public CharacterCard {
public:
	Knight() : CharacterCard("Knight", 8, 4, 0, 0) {}

	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "It's a Knight! You can attack the nearest enemy.\n";
		if ((r == 1 && owner.getId() == 2) || (r == 0 && owner.getId() == 1)) {
			std::cout << "Since you have chosen the farthest row, the knight will not be able to attack...\n";
			return;
		}
		int col;
		std::cout << "Choose a column (0-3) to attack melee row: ";
		std::cin >> col;

		if (opponent.getId() == 1) {
			col = 3 - col;
		}
		opponent.takeDamage(0, col, getDamage());
		std::cout << "The knight attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
	}
};

class Archer : public CharacterCard {
public:
	Archer() : CharacterCard("Archer", 5, 3, 0, 0) {}

	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's an Archer! You can attack all enemies.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, getDamage());
		std::cout << "The archer attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
	}
};

class Magician : public CharacterCard {
public:
	Magician() : CharacterCard("Magician", 4, 5, 0, 1) {}

	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Magician! You can attack all enemies.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;

		srand(time(0));

		int critDamage = rand() % 5; // 0-4

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, getDamage() + critDamage);
		std::cout << "The Magician attacked, dealing " + std::to_string(opponent.damageReduction(getDamage() + critDamage)) + " damage!\n";
	}
};

class Engineer : public CharacterCard {
public:
	Engineer() : CharacterCard("Engineer", 2, 0, 0, 2) {}

	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "It's an Engineer! You can't attack, but you are given defense points and taken away from the opponent.\n";

		opponent.decreaseDefense(1);
	}
};

class Healer : public CharacterCard {
public:
	Healer() : CharacterCard("Healer", 2, 0, 4, 1) {}

	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Healer! You can heal a character on the field by 4 points, which you select.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to heal: ";
		std::cin >> row >> col;

		owner.healingCharacter(row, col, getHealAmount());
	}
};

class Nekromancer : public CharacterCard {
public:
	Nekromancer() : CharacterCard("Nekromancer", 4, 2, 1, 0) {}

	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Nekromancer! You can attack any opponent and revive a random character.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, getDamage());
		std::cout << "The Nekromancer attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";

		owner.printDead();
		int cardIndex;
		std::cout << "Choose a card to revive (index): ";
		std::cin >> cardIndex;

		auto characterCard = owner.popDeadCharacter(cardIndex);
		owner.addCharacterToHand(std::move(characterCard));
	}
};

class Berserk : public CharacterCard {
public:
	Berserk() : CharacterCard("Berserk", 8, 5, 0, 0) {}

	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Berserk! You can instantly kill your chosen opponent and inflict damage on neighboring ones.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, 100); // killing

		opponent.takeDamage(1 - row, col, 2);
		if (col > 0) 
			opponent.takeDamage(row, col - 1, 2);
		if (col < 3)
			opponent.takeDamage(row, col + 1, 2);
		std::cout << "The Berserker attacked!\n";
	}
};

#endif