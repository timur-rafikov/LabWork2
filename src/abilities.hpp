/**
 * @file abilities.hpp
 * @brief Contains declarations of various AbilityCard subclasses representing different ability effects.
 */

#ifndef ABILITIES_H
#define ABILITIES_H

#include "card.hpp"
#include "player.hpp"


/**
 * @class HealthBonus
 * @brief Ability card that heals a selected character on the field.
 */
class HealthBonus : public AbilityCard {
private:
	int hpBonus; ///< Amount of health to restore
public:
	/**
	 * @brief Constructs a HealthBonus card with a specified healing amount.
	 * @param _hpBonus The amount of health to restore.
	 */
	HealthBonus(int _hpBonus) : AbilityCard("HealthBonus"), hpBonus(_hpBonus) {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "You have activated the health bonus!\n";
		std::cout << "Choose a row (0-1) and col (0-3) to heal: ";
		std::cin >> row >> col;

		if (owner.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		owner.healingCharacter(row, col, hpBonus);
		std::cout << "HealthBonus has been activated...\n";
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the HealthBonus...\n";
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (owner.getCardType(row, col) != "EmptySlot") {
					owner.healingCharacter(row, col, hpBonus);
					return;
				}
			}
		}
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "HealthBonus\n";
		std::cout << "This ability card can heal a certain number of hp of the selected character.\n";
	}
};

/**
 * @class DamageBonus
 * @brief Ability card that deals damage to a selected opponent's character.
 */
class DamageBonus : public AbilityCard {
private:
	int dmgBonus; ///< Amount of damage to deal
public:
	/**
	 * @brief Constructs a DamageBonus card with a specified damage amount.
	 * @param _dmgBonus The amount of damage.
	 */
	DamageBonus(int _dmgBonus) : AbilityCard("DamageBonus"), dmgBonus(_dmgBonus) {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "You have activated the damage bonus!\n";
		std::cout << "Choose a row (0-1) and col (0-3) to attack: ";
		std::cin >> row >> col;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, dmgBonus);
		std::cout << "DamageBonus has been activated...\n";
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the DamageBonus...\n";
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					opponent.takeDamage(row, col, dmgBonus);
					return;
				}
			}
		}
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "DamageBonus\n";
		std::cout << "You can use this card to inflict damage on your chosen opponent.\n";
	}
};

class CommonHealthBonus : public AbilityCard {
private:
	int commonHpBonus;
public:
	CommonHealthBonus(int _commonHpBonus) : AbilityCard("CommonHealthBonus"), commonHpBonus(_commonHpBonus) {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "You have activated the Common Health Bonus!\n";

		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 4; ++j)
				owner.healingCharacter(i, j, commonHpBonus);
		}
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the CommonHealthBonus...\n";
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 4; ++j)
				owner.healingCharacter(i, j, commonHpBonus);
		}
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "CommonHealthBonus\n";
		std::cout << "Heals all the characters on the field for a certain amount of hp.\n";
	}
};

class DefenceBonus : public AbilityCard {
private:
	int defB;
public:
	DefenceBonus(int _defB) : AbilityCard("DefenceBonus"), defB(_defB) {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "You have activated the DefenceBonus!\n";

		owner.addDefence(defB);
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the DefenceBonus...\n";

		owner.addDefence(defB);
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "DefenceBonus\n";
		std::cout << "Gives extra defence points\n";
	}
};

class ReflectionDamage : public AbilityCard {
public:
	ReflectionDamage() : AbilityCard("ReflectionDamage") {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "You have activated the Reflection Damage!\n";
		std::cout << "Choose a row (0-1) and col (0-3) to set reflection: ";
		std::cin >> row >> col;

		if (owner.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		owner.setReflection(row, col);
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the ReflectionDamage...\n";

		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (owner.getCardType(row, col) != "EmptySlot") {
					owner.setReflection(row, col);
				}
			}
		}
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "ReflectionDamage\n";
		std::cout << "Grants the selected character the ability to reflect the next damage done\n";
	}
};

class CardTheft : public AbilityCard {
public:
	CardTheft() : AbilityCard("CardTheft") {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "You have activated the Card Theft Bonus!\n";

		if (opponent.getSizeHandChars() == 0) 
			return;
		owner.addCharacterToHand(opponent.popCharacterFromHand(0));
		std::cout << "Ha-ha-ha! The card has been stolen...\n";
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the CardTheft...\n";

		if (opponent.getSizeHandChars() == 0) 
			return;
		owner.addCharacterToHand(opponent.popCharacterFromHand(0));
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "CardTheft\n";
		std::cout << "Steals the first card in the opponent's hand\n";
	}
};

class FireBall : public AbilityCard {
private:
	int centerDmg;
	int envirDmg;
public:
	FireBall(int _centerDmg, int _envirDmg) : AbilityCard("FireBall"), centerDmg(_centerDmg), envirDmg(_envirDmg) {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "You have activated the Fire Ball!\n";
		std::cout << "Choose a row (0-1) and col (0-3) to throw: ";
		std::cin >> row >> col;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, centerDmg); 

		opponent.takeDamage(1 - row, col, envirDmg);
		if (col > 0) 
			opponent.takeDamage(row, col - 1, envirDmg);
		if (col < 3)
			opponent.takeDamage(row, col + 1, envirDmg);
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the FireBall...\n";

		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					opponent.takeDamage(row, col, centerDmg); 

					opponent.takeDamage(1 - row, col, envirDmg);
					if (col > 0) 
						opponent.takeDamage(row, col - 1, envirDmg);
					if (col < 3)
						opponent.takeDamage(row, col + 1, envirDmg);
					return;
				}
			}
		}
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "FireBall\n";
		std::cout << "Deals damage to the chosen opponent and those around him\n";
	}
};

class ShieldRowBonus : public AbilityCard {
public:
	ShieldRowBonus() : AbilityCard("ShieldRowBonus") {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		std::cout << "You have activated the Row Shield!\n";
		for (int j = 0; j < 4; ++j)
			owner.setReflection(0, j);
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the ShieldRowBonus...\n";

		for (int j = 0; j < 4; ++j)
			owner.setReflection(0, j);
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "ShieldRowBonus\n";
		std::cout << "Reflects damage to the entire near row\n";
	}
};

class RageBonus : public AbilityCard {
public:
	RageBonus() : AbilityCard("RageBonus") {}

	/**
	 * @brief Activates the ability in a player-controlled game.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activate(Player& owner, Player& opponent, int r) override {
		int row, col;
		std::cout << "You have activated the Rage Bonus!\n";
		std::cout << "Choose a row (0-1) and col (0-3) to throw: ";
		std::cin >> row >> col;

		if (opponent.getId() == 1) {
			row = 1 - row; // reversing coordinates
			col = 3 - col;
		}
		opponent.takeDamage(row, col, 100);
	}

	/**
	 * @brief Activates the ability in an AI-controlled scenario.
	 * @param owner The player who owns the card.
	 * @param opponent The opponent player.
	 * @param r The row index (unused).
	 */
	void activateAI(Player& owner, Player& opponent, int r) override {
		std::cout << "The AI has activated the RageBonus...\n";

		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < 4; ++col) {
				if (opponent.getCardType(row, col) != "EmptySlot") {
					opponent.takeDamage(row, col, 100);
					return;
				}
			}
		}
	}

	/**
	 * @brief Prints information about the card.
	 */
	void printInfo() const override {
		std::cout << "RageBonus\n";
		std::cout << "Instantly kills the selected opponent\n";
	}
};

#endif