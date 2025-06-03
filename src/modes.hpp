#ifndef MODES_H
#define MODES_H

#include "game.hpp"
#include "player.hpp"
#include <limits>
#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * @class PvPMode
 * @brief Player vs Player game mode implementation.
 *
 * Handles gameplay between two human players.
 */
class PvPMode : public GameMode {
private:
    Player player1;              /**< First player instance (ID = 1). */
    Player player2;              /**< Second player instance (ID = 2). */
    int currentPlayer;           /**< Tracks which player's turn it is (1 or 2). */

    /**
     * @brief Displays the current game field.
     */
    void displayField();

    /**
     * @brief Displays the current player's hand.
     */
    void displayCurrentPlayerHand();

    /**
     * @brief Processes the turn logic for a human player.
     * 
     * @param currentPlayerObj The player currently taking their turn.
     * @param opponentPlayerObj The opponent player.
     */
    void processPlayerTurn(Player& currentPlayerObj, Player& opponentPlayerObj);

    /**
     * @brief Checks whether the game has been won.
     * 
     * @return true if there is a winner, false otherwise.
     */
    bool checkWin();

public:
    /**
     * @brief Constructs a PvPMode object with initialized players.
     */
    PvPMode() : player1(1), player2(2), currentPlayer(1) {}

    /**
     * @brief Starts the PvP game mode.
     */
    void start() override;
};

/**
 * @class PvEMode
 * @brief Player vs AI game mode implementation.
 *
 * Handles gameplay between a human player and an AI-controlled opponent.
 */
class PvEMode : public GameMode {
private:
    Player AIPlayer;             /**< AI-controlled player (ID = 1). */
    Player player;               /**< Human player (ID = 2). */
    int currentPlayer;           /**< Tracks which player's turn it is (1 or 2). */
    int winnerID;                /**< Stores the ID of the winning player. */

    /**
     * @brief Displays the current game field.
     */
    void displayField();

    /**
     * @brief Displays the current player's hand.
     */
    void displayCurrentPlayerHand();

    /**
     * @brief Processes the human player's turn.
     */
    void processPlayerTurn();

    /**
     * @brief Executes a turn for the AI player.
     */
    void makeAITurn();

    /**
     * @brief Checks whether the game has been won.
     * 
     * @return true if there is a winner, false otherwise.
     */
    bool checkWin();

public:
    /**
     * @brief Constructs a PvEMode object with initialized AI and human player.
     */
    PvEMode() : AIPlayer(1), player(2), currentPlayer(1), winnerID(0) {}

    /**
     * @brief Starts the PvE game mode.
     */
    void start() override;

    /**
     * @brief Gets the ID of the winner.
     * 
     * @return The ID of the winning player.
     */
    int getWinner() {
        return winnerID;
    }
};

/**
 * @class CampaignMode
 * @brief Campaign-style mode with multiple sequential PvE levels.
 *
 * Players advance through a series of increasingly difficult AI opponents.
 */
class CampaignMode : public GameMode {
private:
    std::vector<std::unique_ptr<PvEMode>> levels; /**< Vector of levels (each a PvE match). */

    /**
     * @brief Prints a custom message for the given level number.
     * 
     * @param level The current campaign level.
     */
    void printMessage(int level);

public:
    /**
     * @brief Constructs the CampaignMode and sets up the levels.
     */
    CampaignMode();

    /**
     * @brief Starts the campaign mode.
     */
    void start() override;
};

#endif // MODES_H
