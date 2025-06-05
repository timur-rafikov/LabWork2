#include "player.hpp"
#include "characters.hpp"
#include "abilities.hpp"

/**
 * @brief Constructs a new Player and initializes the hand and field.
 *        Randomly fills hand with character and ability cards.
 * @param _id ID of the player.
 */
Player::Player(const int& _id) {
	id = _id;
	defCoef = 0;
	skipCount = 0;

	// Generate character hand
	for (int i = 0; i < 9; ++i) {
		int el = rand() % 13 + 1;
		if (el <= 3)
			handCharacters.push_back(std::make_unique<Knight>());
		else if (el <= 6)
			handCharacters.push_back(std::make_unique<Archer>());
		else if (el <= 8)
			handCharacters.push_back(std::make_unique<Magician>());
		else if (el <= 10)
			handCharacters.push_back(std::make_unique<Healer>());
		else if (el == 11)
			handCharacters.push_back(std::make_unique<Engineer>());
		else if (el == 12)
			handCharacters.push_back(std::make_unique<Nekromancer>());
		else
			handCharacters.push_back(std::make_unique<Berserk>());
	}

	// Generate ability hand
	for (int i = 0; i < 5; ++i) {
		int el = rand() % 9 + 1;
		switch (el) {
			case 1:
				handAbilities.push_back(std::make_unique<HealthBonus>(rand() % 4 + 1));
				break;
			case 2:
				handAbilities.push_back(std::make_unique<DamageBonus>(rand() % 4 + 1));
				break;
			case 3:
				handAbilities.push_back(std::make_unique<CommonHealthBonus>(rand() % 4 + 1));
				break;
			case 4:
				handAbilities.push_back(std::make_unique<DefenceBonus>(rand() % 2 + 1));
				break;
			case 5:
				handAbilities.push_back(std::make_unique<ReflectionDamage>());
				break;
			case 6:
				handAbilities.push_back(std::make_unique<CardTheft>());
				break;
			case 7:
				handAbilities.push_back(std::make_unique<FireBall>(rand() % 3 + 4, rand() % 3 + 1));
				break;
			case 8:
				handAbilities.push_back(std::make_unique<ShieldRowBonus>());
				break;
			case 9:
				handAbilities.push_back(std::make_unique<RageBonus>());
				break;
			default:
				break;
		}
	}

	// Initialize field with empty slots
	field.resize(2);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			field[i].push_back(std::make_unique<CharacterCard>("EmptySlot", 0, 0, 0, 0));
		}
	}
}

/**
 * @brief Removes and returns a character card from hand.
 * @param index Index of the character card.
 * @return std::unique_ptr<Card> The removed card.
 */
std::unique_ptr<Card> Player::popCharacterFromHand(int index) {
	if (isCharEmpty())
		throw std::out_of_range("handCharacters is empty");
	auto ret = std::move(handCharacters[index]);
	handCharacters.erase(handCharacters.begin() + index);
	return ret;
}

/**
 * @brief Removes and returns an ability card from hand.
 * @param index Index of the ability card.
 * @return std::unique_ptr<Card> The removed card.
 */
std::unique_ptr<Card> Player::popAbilityFromHand(int index) {
	if (isAbilEmpty())
		throw std::out_of_range("handAbilities is empty");
	auto ret = std::move(handAbilities[index]);
	handAbilities.erase(handAbilities.begin() + index);
	return ret;
}

/**
 * @brief Removes and returns a dead character.
 * @param index Index of the dead character.
 * @return std::unique_ptr<Card> The removed card.
 */
std::unique_ptr<Card> Player::popDeadCharacter(int index) {
	if (isDeadCharEmpty())
		throw std::out_of_range("deadCharacters is empty");
	auto ret = std::move(deadCharacters[index]);
	deadCharacters.erase(deadCharacters.begin() + index);
	return ret;
}

/**
 * @brief Activates a character card from hand.
 * @param owner Owner player (usually this).
 * @param opponent Opponent player.
 * @param index Index of the card.
 * @param row Row to activate the card into.
 * @param ai Whether to use AI activation.
 */
void Player::activateCharacterCard(Player& owner, Player& opponent, int index, int row, bool ai) {
	if (!ai)
		handCharacters[index]->activate(owner, opponent, row);
	else
		handCharacters[index]->activateAI(owner, opponent, row);

	auto characterCard = dynamic_cast<CharacterCard*>(handCharacters[index].get());
	if (characterCard) 
		defCoef += characterCard->getDefenseBonus();
	else 
		std::cerr << "Error: Card is not a CharacterCard!\n";
}

/**
 * @brief Moves a character card from field to dead pile.
 * @param row Field row.
 * @param col Field column.
 */
void Player::moveCharacterToDead(int row, int col) {
	auto deadChar = std::move(field[row][col]);
	field[row][col] = std::make_unique<CharacterCard>("EmptySlot", 0, 0, 0, 0);
	deadCharacters.push_back(std::move(deadChar));
}

/**
 * @brief Applies damage to a character on the field.
 * @param row Field row.
 * @param col Field column.
 * @param dmg Incoming damage.
 */
void Player::takeDamage(int row, int col, int dmg) {
	if (field[row][col]->getType() == "EmptySlot") {
		std::cout << "Miss!\n";
		return;
	}
	dmg = damageReduction(dmg);

	auto characterCard = dynamic_cast<CharacterCard*>(field[row][col].get());
	if (!characterCard) {
		std::cerr << "Error: no CharacterCard\n";
	}

	bool reflected = characterCard->getReflection();
	std::cout << (reflected ? "The damage was reflected!\n" : "Striked!\n");
	characterCard->takeDamage(dmg);
	std::cout << "Current Health attacked character: " << characterCard->getHealth() << '\n';
	if (characterCard->getHealth() <= 0)
		moveCharacterToDead(row, col);
}

/**
 * @brief Heals a character on the field.
 * @param row Field row.
 * @param col Field column.
 * @param amount Amount to heal.
 */
void Player::healingCharacter(int row, int col, int amount) {
	auto characterCard = dynamic_cast<CharacterCard*>(field[row][col].get());
	if (characterCard) {
		if (characterCard->getType() == "EmptySlot")
			return;
		characterCard->heal(amount);
	}
	else
		std::cerr << "Error: No characterCard to heal\n";
}

/**
 * @brief Checks if the field is full.
 * @return true if full, false otherwise.
 */
bool Player::isFieldFull() const {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (field[i][j]->getType() == "EmptySlot")
				return false;
		}
	}
	return true;
}

/**
 * @brief Gets reflection status of a card on the field.
 * @param row Field row.
 * @param col Field column.
 * @return true if reflected, false otherwise.
 */
bool Player::getReflection(int row, int col) {
	auto characterCard = dynamic_cast<CharacterCard*>(field[row][col].get());
	if (characterCard)
		return characterCard->getReflection();
	else std::cerr << "Error: No characterCard to getReflection\n";
	return false;
}

/**
 * @brief Enables reflection for a card on the field.
 * @param row Field row.
 * @param col Field column.
 */
void Player::setReflection(int row, int col) {
	auto characterCard = dynamic_cast<CharacterCard*>(field[row][col].get());
	if (characterCard)
		characterCard->setReflection();
	else std::cerr << "Error: No characterCard to setReflection\n";
}

/**
 * @brief Gets the total health of all characters on the field.
 * @return int Sum of health values.
 */
int Player::getSumHealthOnField() const {
	int sum = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			auto characterCard = dynamic_cast<CharacterCard*>(field[i][j].get());
			if (!characterCard) {
				std::cerr << "Error: no CharacterCard\n";
			}
			sum += std::max(0, characterCard->getHealth());
		}
	}
	return sum;
}

/**
 * @brief Prints the current state of the field.
 * @param reverse Whether to print from the opponent's perspective.
 */
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

/**
 * @brief Prints the cards in the player's hand.
 * @param ai If true, prints without player ID.
 */
void Player::printHand(bool ai) const {
	std::cout << "Player " + (ai ? "" : std::to_string(id)) << " CHARACTERS:\n";
	for (int i = 0; i < (int)handCharacters.size(); ++i) {
		std::cout << handCharacters[i]->getType() << ' ';
	}
	std::cout << "\nABILITIES:\n";
	for (int i = 0; i < (int)handAbilities.size(); ++i) {
		std::cout << handAbilities[i]->getType() << ' ';
	}
	std::cout << '\n';
}

/**
 * @brief Prints the player's dead characters.
 */
void Player::printDead() const {
	std::cout << "Player " + std::to_string(id) << " dead characters:\n";
	for (int i = 0; i < (int)deadCharacters.size(); ++i) {
		std::cout << deadCharacters[i]->getType() << ' ';
	}
	std::cout << '\n';
}
