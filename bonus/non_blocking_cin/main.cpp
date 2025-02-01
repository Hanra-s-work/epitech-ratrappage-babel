/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** main.cpp
*/

#include <iostream>

const std::string getResponse()
{
    std::string response;
    char c;
    while (std::cin.get(c)) {
        if (c == '\n') {
            break;
        }
        response += c;
    }
    return response;
}

int main(void)
{
    std::ios_base::sync_with_stdio(true); // Enable synchronization with C stdio
    // std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio
    bool loop = true;
    std::string response;
    while (loop) {
        std::cout << "Enter something or just press enter, enter q and press enter to quit: ";
        response = getResponse();
        std::cout << "You entered: " << response << std::endl;
        if (response == "q") {
            loop = false;
        }
    }
    std::cout << "Goodbye!" << std::endl;
}
