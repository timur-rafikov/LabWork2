#ifndef CARD_H
#define CARD_H

#include "player.hpp"
#include <string>
#include <memory>
#include <iostream>

class Player;

/**
 * @brief Base class for all cards in the game.
 */
class Card {
protected:
    /// Type of the card (e.g., "Character", "Ability")
    std::string type;

public:
    /**
     * @brief Constructor for Card.
     * @param _type The type of the card.
     */
    Card(const std::string& _type) : type(_type) {}

    /**
     * @brief Pure virtual function to activate the card effect for a human player.
     * @param owner The player who owns the card.
     * @param opponent The opposing player.
     * @param row The row number for targeting (if needed).
     */
    virtual void activate(Player& owner, Player& opponent, int row) = 0;

    /**
     * @brief Pure virtual function to activate the card effect for an AI player.
     * @param owner The AI player who owns the card.
     * @param opponent The opposing player.
     * @param row The row number for targeting (if needed).
     */
    virtual void activateAI(Player& owner, Player& opponent, int row) = 0;

    /**
     * @brief Pure virtual function to print information about the card.
     */
    virtual void printInfo() const = 0;

    /**
     * @brief Returns the type of the card.
     * @return The type string.
     */
    std::string getType() {
        return type;
    }
};

/**
 * @brief Represents a character card that can be placed on the field.
 */
class CharacterCard : public Card {
private:
    int health;          ///< Health points of the character.
    int damage;          ///< Damage value of the character.
    int healAmount;      ///< Healing power of the character.
    int defenseBonus;    ///< Defensive bonus when placed.
    bool reflection;     ///< Indicates if the character reflects incoming damage.

public:
    /**
     * @brief Constructor for CharacterCard.
     * @param _type The type/name of the character.
     * @param _health Initial health points.
     * @param _damage Damage this character can deal.
     * @param _healAmount Amount of health it can heal.
     * @param _defenseBonus Defense bonus granted.
     */
    CharacterCard(const std::string& _type, int _health, int _damage, int _healAmount, int _defenseBonus)
        : Card(_type), health(_health), damage(_damage), healAmount(_healAmount), defenseBonus(_defenseBonus), reflection(false) {}

    /**
     * @brief Activates the card's effect for a human player.
     * @param owner The player who owns this card.
     * @param opponent The opposing player.
     * @param row Targeted row (unused here).
     */
    virtual void activate(Player& owner, Player& opponent, int row) override {
        std::cout << "Character '" + type + "' has been activated...\n";
    }

    /**
     * @brief Activates the card's effect for an AI player.
     * @param owner The AI player who owns this card.
     * @param opponent The opposing player.
     * @param row Targeted row (unused here).
     */
    virtual void activateAI(Player& owner, Player& opponent, int row) override {
        std::cout << "AI Character has been activated...\n";
    }

    /**
     * @brief Enables the reflection ability for the next incoming damage.
     */
    void setReflection() {
        reflection = true;
    }

    /**
     * @brief Prints information about the character card.
     */
    void printInfo() const override {
        std::cout << "Name: " << type << '\n';
        std::cout << "HEALTH: " << health << '\n';
        std::cout << "DAMAGE: " << damage << '\n';
        std::cout << "HEAL AMOUNT: " << healAmount << '\n';
        std::cout << "DEFENSE BONUS: " << defenseBonus << '\n';
    }

    /**
     * @brief Gets the current health of the character.
     * @return Current health points.
     */
    int getHealth() const {
        return health;
    }

    /**
     * @brief Gets the damage value of the character.
     * @return Damage points.
     */
    int getDamage() const {
        return damage;
    }

    /**
     * @brief Gets the healing value of the character.
     * @return Healing amount.
     */
    int getHealAmount() const {
        return healAmount;
    }

    /**
     * @brief Gets the defense bonus of the character.
     * @return Defense bonus points.
     */
    int getDefenseBonus() const {
        return defenseBonus;
    }

    /**
     * @brief Checks whether the reflection ability is active.
     * @return True if active, false otherwise.
     */
    bool getReflection() const {
        return reflection;
    }

    /**
     * @brief Reduces the character's health by the given damage, unless reflection is active.
     * @param dmg Amount of damage to take.
     */
    void takeDamage(int dmg) {
        if (reflection) {
            reflection = false;
            return;
        }
        health -= dmg;
    }

    /**
     * @brief Heals the character by the specified amount.
     * @param amount Amount of health to restore.
     */
    void heal(int amount) {
        health += amount;
    }
};

/**
 * @brief Represents an ability card that performs an effect when activated.
 */
class AbilityCard : public Card {
public:
    /**
     * @brief Constructor for AbilityCard.
     * @param _type The type of ability.
     */
    AbilityCard(const std::string& _type) : Card(_type) {}

    /**
     * @brief Activates the ability for a human player.
     * @param owner The player who owns this card.
     * @param opponent The opposing player.
     * @param row Targeted row (if applicable).
     */
    virtual void activate(Player& owner, Player& opponent, int row) {
        std::cout << "Ability '" + type + "' has been activated...\n";
    }

    /**
     * @brief Activates the ability for an AI player.
     * @param owner The AI player who owns this card.
     * @param opponent The opposing player.
     * @param row Targeted row (if applicable).
     */
    virtual void activateAI(Player& owner, Player& opponent, int row) {
        std::cout << "AI Ability has been activated...\n";
    }
};

#endif
