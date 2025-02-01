/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** MainClass.hpp
*/

/**
 * @file MainClass.hpp
 *
 * @brief File in charge of containing the main class of the program (in other words the orchestrator of the program, the brain)
 */

#include <string>
#include <cctype>
#include <memory>
#include <algorithm>

#include "Network.hpp"
#include "Logging.hpp"
#include "TOMLLoader.hpp"

class Main {
    public:
    Main();
    Main(const std::string &ip, const unsigned int port);
    Main(const std::string &ip, const unsigned int port, const bool log = false, const bool debug = false);
    Main(const std::string &ip, const unsigned int port, const std::string &name, const bool log = false, const bool debug = false);

    ~Main() = default;

    void setLog(const bool log);
    void setDebug(const bool debug);
    void setIp(const std::string &ip);
    void setPort(const unsigned int port);
    void setUserName(const std::string &username);
    void setConfigFile(const std::string &path);

    void takeOff();

    const bool getLog() const;
    const bool getDebug() const;
    const std::string getIp() const;
    const unsigned int getPort() const;
    const std::string getUserName() const;
    const std::string getConfigFilePath() const;
    const TOMLLoader getTOMLInstance() const;

    /**
     * @brief Updates the AddressHolder by copying another AddressHolder.
     *
     * @param copy The AddressHolder to copy data from.
     */
    void update(const Main &copy);

    /**
     * @brief Dumps the current state of the variables for debugging purposes.
     * It will dump them for itself and any of its underlying classes.
     *
     * @param indent The level to which the class should be indented in the dump.
     * @return The formatted output.
     */
    const std::string getInfo(const unsigned int indent = 0) const;

    /**
     * @brief Overloads the assignment operator to copy from another AddressHolder.
     *
     * @param copy The AddressHolder to copy data from.
     * @return A reference to the updated instance.
     */
    Main &operator =(const Main &copy);

    private:

    const bool _isOnlyWhitespaces(const std::string &string) const;
    void _checkUsernameValidity(const std::string &username) const;

    std::string _username = "John Doe";
    TOMLLoader _toml;
    Network::AddressHolder _addresses;
};
