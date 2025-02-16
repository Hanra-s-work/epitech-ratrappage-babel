/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** BootScreen.hpp
*/

/**
 * @file BootScreen.hpp
 * @brief Defines the BootScreen class for displaying boot screens.
 */

#pragma once

#include <vector>
#include <string>
#include <random>
#include <iostream>

 /**
  * @class BootScreen
  * @brief Manages and displays boot screens.
  */
class BootScreen {
    public:
    /**
     * @brief Construct a new BootScreen object.
     */
    BootScreen();

    /**
     * @brief Destroy the BootScreen object.
     */
    ~BootScreen();

    /**
     * @brief Display a random boot screen.
     */
    void display() const;

    /**
     * @brief Display all available boot screens.
     */
    void displayAllScreens() const;

    /**
     * @brief Display a specific boot screen.
     * @param screen The index of the screen to display.
     */
    void displayScreen(const unsigned int screen) const;

    /**
     * @brief Get the number of available boot screens.
     * @return int The number of available boot screens.
     */
    int getAvailableScreens() const;

    private:
    /**
     * @brief Add a new screen to the list of available screens.
     * @param screen The screen to add.
     */
    void _addScreen(const std::vector<std::string> &screen);

    /**
     * @brief Generate a random number within a specified range.
     * @param min The minimum value (inclusive).
     * @param max The maximum value (inclusive).
     * @return int The generated random number.
     */
    int _getRandomNumber(int min = 0, int max = 1) const;

    std::vector<std::vector<std::string>> _screens; ///< List of boot screens.
    unsigned int _availableScreens = 0; ///< Number of available boot screens.
};
