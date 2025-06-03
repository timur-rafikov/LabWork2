#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "card.hpp"
#include "player.hpp"
#include <ctime>
#include <cstdlib>
#include <string>


/**
 * @class Knight
 * @brief A melee character that can attack enemies in the front row.
 */
class Knight : public CharacterCard {
public:
	/**
     * @brief Constructs a Knight card.
     */
	Knight() : CharacterCard("Knight", 8, 4, 0, 0) {}

	/**
     * @brief Activates the Knight's ability for a human player.
     * 
     * @param owner The player who owns the Knight.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "It's a Knight! You can attack the nearest enemy.\n";
		if ((r == 1 && owner.getId() == 2) || (r == 0 && owner.getId() == 1)) {
			std::cout << "Since you have chosen the farthest row, the knight will not be able to attack...\n";
			return;
		}
		int col;
		std::cout << "Choose a column (0-3) to attack melee row: ";
		std::cin >> col;
		if (col > 3 || col < 0)
			return;

		if (opponent.getId() == 1) {
			col = 3 - col;
		}

		bool reflected = opponent.getReflection(0, col);
		opponent.takeDamage(0, col, getDamage());
		if (!reflected)
			std::cout << "The knight attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
	}

	/**
     * @brief Activates the Knight's ability for an AI player.
     * 
     * @param owner The AI player who owns the Knight.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		if (r == 1)
			return;

		for (int col = 0; col < 4; ++col) {
			if (opponent.getCardType(0, col) != "EmptySlot") {
				bool reflected = opponent.getReflection(0, col);
				opponent.takeDamage(0, col, getDamage());
				if (!reflected)
					std::cout << "The AI knight attacked you, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
				return;
			}
		}
	}
};

/**
 * @class Archer
 * @brief A ranged character that can attack any cell.
 */
class Archer : public CharacterCard {
public:
	/**
     * @brief Constructs an Archer card.
     */
	Archer() : CharacterCard("Archer", 5, 3, 0, 0) {}

	/**
     * @brief Activates the Archer's ability for a human player.
     * 
     * @param owner The player who owns the Archer.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's an Archer! You can attack all enemies.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;
		if (row > 1 || row < 0 || col > 3 || col < 0)
			return;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}

		bool reflected = opponent.getReflection(row, col);
		opponent.takeDamage(row, col, getDamage());
		if (!reflected)
			std::cout << "The archer attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
	}

	/**
     * @brief Activates the Archer's ability for an AI player.
     * 
     * @param owner The AI player who owns the Archer.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					bool reflected = opponent.getReflection(row, col);
					opponent.takeDamage(row, col, getDamage());
					if (!reflected)
						std::cout << "The AI archer attacked you, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
					return;
				}
			}
		}
	}
};

/**
 * @class Magician
 * @brief A ranged character with a chance to deal critical damage.
 */
class Magician : public CharacterCard {
public:
	/**
     * @brief Constructs a Magician card.
     */
	Magician() : CharacterCard("Magician", 4, 5, 0, 1) {}

	/**
     * @brief Activates the Magician's ability for a human player.
     * 
     * @param owner The player who owns the Magician.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Magician! You can attack all enemies.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;
		if (row > 1 || row < 0 || col > 3 || col < 0)
			return;

		int critDamage = rand() % 5; // 0-4

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}

		bool reflected = opponent.getReflection(row, col);
		opponent.takeDamage(row, col, getDamage() + critDamage);
		if (!reflected)
			std::cout << "The Magician attacked, dealing " + std::to_string(opponent.damageReduction(getDamage() + critDamage)) + " damage!\n";
	}

	/**
     * @brief Activates the Magician's ability for an AI player.
     * 
     * @param owner The AI player who owns the Magician.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					int critDamage = rand() % 5;

					bool reflected = opponent.getReflection(row, col);
					opponent.takeDamage(row, col, getDamage() + critDamage);
					if (!reflected)
						std::cout << "The AI Magician attacked you, dealing " + std::to_string(opponent.damageReduction(getDamage() + critDamage)) + " damage!\n";
					return;
				}
			}
		}
	}
};

/**
 * @class Engineer
 * @brief A support character that reduces the opponent's defense.
 */
class Engineer : public CharacterCard {
public:
	/**
     * @brief Constructs an Engineer card.
     */
	Engineer() : CharacterCard("Engineer", 2, 0, 0, 2) {}

	/**
     * @brief Activates the Engineer's ability for a human player.
     * 
     * @param owner The player who owns the Engineer.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "It's an Engineer! You can't attack, but you are given defense points and taken away from the opponent.\n";

		opponent.addDefence(-1);
	}

	/**
     * @brief Activates the Engineer's ability for an AI player.
     * 
     * @param owner The AI player who owns the Engineer.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		opponent.addDefence(-1);
	}
};

/**
 * @class Healer
 * @brief A support character that heals allies.
 */
class Healer : public CharacterCard {
public:
	/**
     * @brief Constructs a Healer card.
     */
	Healer() : CharacterCard("Healer", 2, 0, 4, 1) {}

	/**
     * @brief Activates the Healer's ability for a human player.
     * 
     * @param owner The player who owns the Healer.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Healer! You can heal a character on the field by 4 points, which you select.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to heal: ";
		std::cin >> row >> col;
		if (row > 1 || row < 0 || col > 3 || col < 0)
			return;

		if (owner.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		owner.healingCharacter(row, col, getHealAmount());
	}

	/**
     * @brief Activates the Healer's ability for an AI player.
     * 
     * @param owner The AI player who owns the Healer.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (owner.getCardType(row, col) != "EmptySlot") {
					owner.healingCharacter(row, col, getHealAmount());
					return;
				}
			}
		}
	}
};

/**
 * @class Nekromancer
 * @brief A hybrid character that deals damage and can revive fallen allies.
 */
class Nekromancer : public CharacterCard {
public:
	/**
     * @brief Constructs a Nekromancer card.
     */
	Nekromancer() : CharacterCard("Nekromancer", 4, 2, 1, 0) {}

	/**
     * @brief Activates the Nekromancer's ability for a human player.
     * 
     * @param owner The player who owns the Nekromancer.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Nekromancer! You can attack any opponent and revive a random character.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;
		if (row > 1 || row < 0 || col > 3 || col < 0)
			return;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}

		bool reflected = opponent.getReflection(row, col);
		opponent.takeDamage(row, col, getDamage());
		if (!reflected)
			std::cout << "The Nekromancer attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";

		if (!owner.isDeadCharEmpty()) {
			owner.printDead();
			int cardIndex;
			std::cout << "Choose a card to revive (index): ";
			std::cin >> cardIndex;
			if (cardIndex < 0 || cardIndex >= owner.getSizeDeadChars())
				return;

			auto characterCard = owner.popDeadCharacter(cardIndex);
			owner.addCharacterToHand(std::move(characterCard));
		}
	}

	/**
     * @brief Activates the Nekromancer's ability for an AI player.
     * 
     * @param owner The AI player who owns the Nekromancer.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					bool reflected = opponent.getReflection(row, col);
					opponent.takeDamage(row, col, getDamage());
					if (!reflected)
						std::cout << "The AI Nekromancer attacked, dealing " + std::to_string(opponent.damageReduction(getDamage())) + " damage!\n";
					
					if (!owner.isDeadCharEmpty()) {
						int cardIndex = 0;
						auto characterCard = owner.popDeadCharacter(cardIndex);
						owner.addCharacterToHand(std::move(characterCard));
					}
					return;
				}
			}
		}
	}
};


/**
 * @class Berserk
 * @brief A powerful melee attacker that can instantly kill a target and damage adjacent cells.
 */
class Berserk : public CharacterCard {
public:
	/**
     * @brief Constructs a Berserk card.
     */
	Berserk() : CharacterCard("Berserk", 8, 5, 0, 0) {}

	/**
     * @brief Activates the Berserk's ability for a human player.
     * 
     * @param owner The player who owns the Berserk.
     * @param opponent The opposing player.
     * @param r The selected row for activation.
     */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "It's a Berserk! You can instantly kill your chosen opponent and inflict damage on neighboring ones.\n";
		std::cout << "Choose a row (0-1) and column (0-3) to attack: ";
		std::cin >> row >> col;
		if (row > 1 || row < 0 || col > 3 || col < 0)
			return;

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

	/**
     * @brief Activates the Berserk's ability for an AI player.
     * 
     * @param owner The AI player who owns the Berserk.
     * @param opponent The human player.
     * @param r The selected row for activation.
     */
	void activateAI(Player& owner, Player& opponent, int r) override {
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					opponent.takeDamage(row, col, 100);

					opponent.takeDamage(1 - row, col, 2);
					if (col > 0) 
						opponent.takeDamage(row, col - 1, 2);
					if (col < 3)
						opponent.takeDamage(row, col + 1, 2);
					return;
				}
			}
		}
	}
};

#endif