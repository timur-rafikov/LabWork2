#include "player.hpp"
#include "characters.hpp"
#include "abilities.hpp"

Player::Player(const int& _id) {
	id = _id;
	defCoef = 0;
	// TO DO: random for Characters and Abilities

	for (int i = 0; i < 3; ++i) {
		handCharacters.push_back(std::make_unique<Knight>());
		handCharacters.push_back(std::make_unique<Archer>());
	}
	handCharacters.push_back(std::make_unique<Engineer>());
	handCharacters.push_back(std::make_unique<Healer>());
	handCharacters.push_back(std::make_unique<Berserk>());

	for (int i = 0; i < 5; ++i) 
		handAbilities.push_back(std::make_unique<HealthBonus>());

	field.resize(2);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			field[i].push_back(std::make_unique<CharacterCard>("EmptySlot", 0, 0, 0, 0));
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


void Player::takeDamage(int row, int col, int dmg) {
	if (field[row][col]->getType() == "EmptySlot") {
		std::cout << "You missed!\n";
		return;
	}
	std::cout << "You striked!\n";
	dmg = damageReduction(dmg);

	auto characterCard = dynamic_cast<CharacterCard*>(field[row][col].get());
	if (!characterCard) {
		std::cerr << "Error: no CharacterCard\n";
	}

	characterCard->takeDamage(dmg);
	std::cout << "Current Health attacked character: " << characterCard->getHealth() << '\n';
	if (characterCard->getHealth() <= 0) // death
		moveCharacterToDead(row, col);
}

bool Player::isFieldFull() const {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (field[i][j]->getType() == "EmptySlot")
				return false;
		}
	}
	return true;
}

int Player::getSumHealthOnField() const {
	int sum = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			auto characterCard = dynamic_cast<CharacterCard*>(field[i][j].get());
			if (!characterCard) {
				std::cerr << "Error: no CharacterCard\n";
			}
			sum += characterCard->getHealth();
		}
	}
	return sum;
}

void Player::printField(bool reverse) const {
	for (int i = (reverse ? 1 : 0); (reverse ? i >= 0 : i < 2); (reverse ? --i : ++i)) {
		std::cout << (reverse ? 1 - i : i) << ' ';
		for (int j = (reverse ? 3 : 0); (reverse ? j >= 0 : j < 4); (reverse ? --j : ++j)) {
			switch (field[i][j]->getType()[0]) {
				case 'E':
					if (field[i][j]->getType()[1] == 'm')
						std::cout << ". ";
					else std::cout << "E ";
					break;
				case 'K':
					std::cout << "K ";
					break;
				case 'A':
					std::cout << "A ";
					break;
				case 'M':
					std::cout << "M ";
					break;
				case 'N':
					std::cout << "N ";
					break;
				case 'H':
					std::cout << "H ";
					break;
				case 'B':
					std::cout << "B ";
					break;
				default:
					std::cout << "? ";
					break;
			}
		}
		std::cout << '\n';
	}
}

void Player::printHand() const {
	std::cout << "Player " + std::to_string(id) << " CHARACTERS:\n";
	for (int i = 0; i < (int)handCharacters.size(); ++i) {
		std::cout << handCharacters[i]->getType() << ' ';
	}
	std::cout << "\nABILITIES:\n";
	for (int i = 0; i < (int)handAbilities.size(); ++i) {
		std::cout << handAbilities[i]->getType() << ' ';
	}
	std::cout << '\n';
}

void Player::printDead() const {
	std::cout << "Player " + std::to_string(id) << " dead characters:\n";
	for (int i = 0; i < (int)deadCharacters.size(); ++i) {
		std::cout << deadCharacters[i]->getType() << ' ';
	}
	std::cout << '\n';
}