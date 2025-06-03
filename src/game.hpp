#ifndef GAME_H
#define GAME_H

#include <memory>
#include <cstdlib>

/**
 * @brief Forward declaration of the Game class.
 */
class Game;

/**
 * @class GameMode
 * @brief Abstract base class representing a game mode.
 *
 * Defines the interface for various game modes (e.g., single-player, multiplayer, AI).
 */
class GameMode {
public:
	/**
     * @brief Starts the game mode.
     * 
     * This is a pure virtual function that must be implemented by derived classes.
     */
	virtual void start() = 0;

	/**
     * @brief Clears the terminal screen.
     *
     * Uses the `clear` system command to reset the screen.
     */
	void clearScreen() {
		std::system("clear");
	}
};

/**
 * @class Game
 * @brief Represents the main game context.
 *
 * Manages the currently selected game mode and initiates gameplay.
 */
class Game {
private:
	std::unique_ptr<GameMode> mode; /**< The current game mode in use. */
public:
	/**
     * @brief Constructs an empty Game object.
     *
     * The game is initialized without an active mode.
     */
	Game() : mode(nullptr) {};

	/**
     * @brief Sets the game mode.
     * 
     * @param newMode A unique pointer to the new game mode.
     *
     * Transfers ownership of the passed mode to the Game instance.
     */
	void setMode(std::unique_ptr<GameMode> newMode) {
		mode = std::move(newMode);
	}

	/**
     * @brief Starts the game by invoking the current mode's start method.
     *
     * If no mode is set, this function does nothing.
     */
	void start() {
		if (mode)
			mode->start();
	}
};

#endif