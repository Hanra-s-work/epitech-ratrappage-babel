/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** BootScreen.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <random>
#include <iostream>

class BootScreen {
    public:
    BootScreen();
    ~BootScreen();
    void display() const;
    void displayAllScreens() const;
    void displayScreen(const unsigned int screen) const;
    int getAvailableScreens() const;
    private:
    void _addScreen(const std::vector<std::string> &screen);
    int _getRandomNumber(int min = 0, int max = 1) const;

    std::vector<std::vector<std::string>> _screens;
    unsigned int _availableScreens = 0;
};
