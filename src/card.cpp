#include "card.hpp"

/**
* @brief Prints information about the card.
*/
void CharacterCard::printInfo() override {
	std::cout << "Name: " << type << '\n';
	std::cout << "HEALTH: " << health << '\n';
	std::cout << "DAMAGE: " << damage << '\n';
	std::cout << "HEAL AMOUNT: " << healAmount << '\n';
	std::cout << "DEFENSE BONUS: " << defenseBonus << '\n';
}