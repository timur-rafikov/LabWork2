#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include "card.hpp"

/**
 * @class Player
 * @brief Represents a player in the card game.
 */
class Player {
private:
    std::vector<std::unique_ptr<Card>> handCharacters; ///< Character cards in player's hand.
    std::vector<std::unique_ptr<Card>> handAbilities;  ///< Ability cards in player's hand.
    std::vector<std::vector<std::unique_ptr<Card>>> field; ///< Field: 2 rows of 4 card slots.
    std::vector<std::unique_ptr<Card>> deadCharacters; ///< Dead character cards.
    int id; ///< Unique identifier of the player.
    int defCoef; ///< Defense coefficient in percentage.
    int skipCount; ///< Number of skipped turns.

public:
    /**
     * @brief Constructs a new Player object with a specified ID.
     * @param _id Player's ID.
     */
    Player(const int& _id);

    /**
     * @brief Removes and returns a character card from the player's hand.
     * @param index Index of the character card in hand.
     * @return std::unique_ptr<Card> Pointer to the removed character card.
     */
    std::unique_ptr<Card> popCharacterFromHand(int index);

    /**
     * @brief Removes and returns an ability card from the player's hand.
     * @param index Index of the ability card in hand.
     * @return std::unique_ptr<Card> Pointer to the removed ability card.
     */
    std::unique_ptr<Card> popAbilityFromHand(int index);

    /**
     * @brief Removes and returns a character card from the dead pile.
     * @param index Index of the dead character card.
     * @return std::unique_ptr<Card> Pointer to the removed dead character.
     */
    std::unique_ptr<Card> popDeadCharacter(int index);

    /**
     * @brief Activates a character card from hand and places it on the field.
     * @param owner The owning player (this).
     * @param opponent The opponent player.
     * @param index Index of the card in hand.
     * @param row Field row to place the card.
     * @param ai If true, AI logic is used.
     */
    void activateCharacterCard(Player& owner, Player& opponent, int index, int row, bool ai);

    /**
     * @brief Activates an ability card.
     * @param owner The owning player.
     * @param opponent The opponent player.
     * @param index Index of the card in hand.
     * @param ai If true, AI logic is used.
     */
    void activateAbilityCard(Player& owner, Player& opponent, int index, bool ai) {
        if (!ai)
            handAbilities[index]->activate(owner, opponent, 0);
        else
            handAbilities[index]->activateAI(owner, opponent, 0);
        popAbilityFromHand(index);
    }

    /**
     * @brief Adds a character card to the player's hand.
     * @param newCharacter The new character card.
     */
    void addCharacterToHand(std::unique_ptr<Card> newCharacter) {
        handCharacters.push_back(std::move(newCharacter));
    }

    /**
     * @brief Adds an ability card to the player's hand.
     * @param newAbility The new ability card.
     */
    void addAbilityToHand(std::unique_ptr<Card> newAbility) {
        handAbilities.push_back(std::move(newAbility));
    }

    /**
     * @brief Places a card on the field at the given position.
     * @param newCard The card to place.
     * @param row Field row index.
     * @param col Field column index.
     */
    void moveCardToField(std::unique_ptr<Card> newCard, int row, int col) {
        field[row][col] = std::move(newCard);
    }

    /**
     * @brief Moves a character card from the field to the dead pile.
     * @param row Row index of the card on the field.
     * @param col Column index of the card on the field.
     */
    void moveCharacterToDead(int row, int col);

    /**
     * @brief Calculates the reduced damage after applying defense.
     * @param damage Original damage amount.
     * @return int Reduced damage.
     */
    int damageReduction(int damage) const {
        return floor((1.0 - (1.0 * defCoef / 100.0)) * damage); 
    }

    /**
     * @brief Applies damage to a character on the field.
     * @param row Row index.
     * @param col Column index.
     * @param dmg Damage amount.
     */
    void takeDamage(int row, int col, int dmg);

    /**
     * @brief Heals a character on the field.
     * @param row Row index.
     * @param col Column index.
     * @param amount Amount to heal.
     */
    void healingCharacter(int row, int col, int amount);

    /**
     * @brief Checks if the ability hand is empty.
     * @return true if empty, false otherwise.
     */
    bool isAbilEmpty() const {
        return handAbilities.empty();
    }

    /**
     * @brief Checks if the character hand is empty.
     * @return true if empty, false otherwise.
     */
    bool isCharEmpty() const {
        return handCharacters.empty();
    }

    /**
     * @brief Checks if there are dead characters.
     * @return true if none, false otherwise.
     */
    bool isDeadCharEmpty() const {
        return deadCharacters.empty();
    }

    /**
     * @brief Checks if the field is full.
     * @return true if all slots are occupied, false otherwise.
     */
    bool isFieldFull() const;

    /**
     * @brief Increments the skip turn counter.
     */
    void addSkip() {
        skipCount++;
    }

    /**
     * @brief Gets the number of skipped turns.
     * @return int Number of skipped turns.
     */
    int getSkipCount() const {
        return skipCount;
    }

    /**
     * @brief Gets the number of character cards in hand.
     * @return int Size of handCharacters.
     */
    int getSizeHandChars() const {
        return (int)handCharacters.size();
    }

    /**
     * @brief Gets the number of ability cards in hand.
     * @return int Size of handAbilities.
     */
    int getSizeHandAbils() const {
        return (int)handAbilities.size();
    }

    /**
     * @brief Gets the number of dead character cards.
     * @return int Size of deadCharacters.
     */
    int getSizeDeadChars() const {
        return (int)deadCharacters.size();
    }

    /**
     * @brief Gets the current defense coefficient.
     * @return int Defense value.
     */
    int getDefCoef() const {
        return defCoef;
    }

    /**
     * @brief Gets the reflection status of a card on the field.
     * @param row Row index.
     * @param col Column index.
     * @return true if card has reflection, false otherwise.
     */
    bool getReflection(int row, int col);

    /**
     * @brief Enables reflection status on a card.
     * @param row Row index.
     * @param col Column index.
     */
    void setReflection(int row, int col);

    /**
     * @brief Increases the defense coefficient.
     * @param defAmount Amount to add.
     */
    void addDefence(int defAmount) {
        defCoef += defAmount;
        defCoef = std::max(0, defCoef);
    }

    /**
     * @brief Gets the player's ID.
     * @return int Player ID.
     */
    int getId() const {
        return id;
    }

    /**
     * @brief Calculates total health of all characters on the field.
     * @return int Total health.
     */
    int getSumHealthOnField() const;

    /**
     * @brief Gets the type of a card on the field.
     * @param row Row index.
     * @param col Column index.
     * @return std::string Card type.
     */
    std::string getCardType(int row, int col) const {
        return field[row][col]->getType();
    }

    /**
     * @brief Gets the health of a character on the field.
     * @param row Row index.
     * @param col Column index.
     * @return int Character's health.
     */
    int getCardHealth(int row, int col) const {
        return dynamic_cast<CharacterCard*>(field[row][col].get())->getHealth();
    }

    /**
     * @brief Checks if the specified field slot is empty.
     * @param row Row index.
     * @param col Column index.
     * @return true if the slot is empty, false otherwise.
     */
    bool isEmptySlot(int row, int col) const {
        if ((row == 0 || row == 1) && (col >= 0 && col <= 3))
            return (getCardType(row, col) == "EmptySlot");
        else return false;
    }

    /**
     * @brief Gets the type of a character card in hand.
     * @param index Index in the handCharacters vector.
     * @return std::string Card type.
     */
    std::string getCardHandType(int index) const {
        return handCharacters[index]->getType();
    }

    /**
     * @brief Prints the current state of the field.
     * @param reverse If true, prints in reverse (for the opponent's perspective).
     */
    void printField(bool reverse = false) const;

    /**
     * @brief Prints the hand cards.
     * @param ai If true, prints in AI-mode (limited info).
     */
    void printHand(bool ai) const;

    /**
     * @brief Prints the list of dead characters.
     */
    void printDead() const;
};

#endif
