#include "player.hpp"

Player::Player(const int& _id) {
	id = _id;
	defCoef = 0;
	// TO DO: random for Characters and Abilities
	for (int i = 0; i < 9; ++i)
		handCharacters.push_back(std::make_unique<CharacterCard>("Chrcter_" + to_string(i)));
	for (int i = 0; i < 5; ++i)
		handAbilities.push_back(std::make_unique<AbilityCard>("Abil_" + to_string(i)));
	field.resize(2);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			field[i].push_back(std::make_unique<CharacterCard>("EmptySlot"));
		}
	}
}

std::unique_ptr<Card> Player::popCharacterFromHand(int index) {
	auto ret = std::move(handCharacters[index]);
	handCharacters.erase(handCharacters.begin() + index);
	return ret;
}

std::unique_ptr<Card> Player::popAbilityFromHand(int index) {
	auto ret = std::move(handAbilities[index]);
	handAbilities.erase(handAbilities.begin() + index);
	return ret;
}

void Player::printField(bool reverse = false) const {
	for (int i = (reverse ? 1 : 0); (reverse ? i >= 0 : i < 2); (reverse ? --i : ++i)) {
		for (int j = 0; j < 4; ++j) {
			switch (field[i][j]->getType()) {
				case "EmptySlot":
					std::cout << "# ";
					break;
				case "Knight":
					std::cout << "K ";
					break;
				case "Archer":
					std::cout << "A ";
					break;
				// TODO: other characters
				default:
					std::cout << "? ";
					break;
			}
		}
		std::cout << '\n';
	}
}

void Player::printHand() const {
	std::cout << "Player " + to_string(id) << " CHARACTERS:\n";
	for (auto character : handCharacters) {
		std::cout << character->getType() << ' ';
	}
	std::cout << "\nABILITIES:\n";
	for (auto ability : handAbilities) {
		std::cout << ability->getType() << ' ';
	}
	std::cout << '\n';
}