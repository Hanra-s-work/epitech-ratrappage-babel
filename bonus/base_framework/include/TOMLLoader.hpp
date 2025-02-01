/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TOMLLoader.hpp
*/

/**
 * @file TOMLLoader.hpp
 * @brief Contains the `TOMLLoader` class for handling loading and navigation of TOML data.
 */

#pragma once

#include <mutex>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <toml++/toml.hpp>

#include "Logging.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"

 /**
  * @class TOMLLoader
  * @brief A utility class for parsing, navigating, and managing TOML files and data.
  */
class TOMLLoader {
    public:
    /**
     * @brief Default constructor.
     */
    TOMLLoader();

    /**
     * @brief Constructor that initializes the loader with a TOML file path.
     * @param tomlPath The path to the TOML file to be loaded.
     */
    TOMLLoader(const std::string &tomlPath);

    /**
     * @brief Copy constructor.
     * @param tomlInstance The instance to copy.
     */
    TOMLLoader(const TOMLLoader &tomlInstance);

    /**
     * @brief Constructor that initializes the loader with a TOML table.
     * @param tomlTable A TOML table.
     * @param tomlPath The path to the TOML file.
     */
    TOMLLoader(const toml::table &tomlTable, const std::string &tomlPath);

    /**
     * @brief Constructor that initializes the loader with a TOML array.
     * @param tomlArray A TOML array.
     * @param tomlPath The path to the TOML file.
     */
    TOMLLoader(const toml::array &tomlArray, const std::string &tomlPath);

    /**
     * @brief Constructor that initializes the loader with a TOML array under a specific key.
     * @param tomlArray A TOML array.
     * @param key The key associated with the array.
     * @param tomlPath The path to the TOML file.
     */
    TOMLLoader(const toml::array &tomlArray, const std::string &key, const std::string &tomlPath);

    /**
     * @brief Default destructor.
     */
    ~TOMLLoader() = default;

    /**
     * @brief Sets the path of the TOML file to load.
     * @param tomlPath The file path to set.
     */
    void setTOMLPath(const std::string &tomlPath);

    /**
     * @brief Checks if the TOML file is successfully loaded.
     * @return True if loaded, false otherwise.
     */
    const bool isTOMLLoaded() const;

    /**
     * @brief Retrieves the path of the loaded TOML file.
     * @return The path as a string.
     */
    const std::string getTOMLPath() const;

    /**
     * @brief Retrieves the TOML data as a string.
     * @return The TOML data in string format.
     */
    const std::string getTOMLString() const;

    /**
     * @brief Retrieves the raw TOML table.
     * @return The raw TOML table.
     */
    const toml::table getRawTOML() const;

    /**
     * @brief Retrieves a value of type `T` from the TOML table.
     * @tparam T The type of the value to retrieve.
     * @param key The key of the value to retrieve.
     * @return The value of type `T`.
     * @throw CustomExceptions::NoTOMLKey if the key is not found or the value cannot be converted.
     * @warning Do not move the initialisation of this function outside of the header file or compilation issues will arise.
     */
    template <typename T>
    T getValue(const std::string &key) const
    {
        _ensureLoaded();
        if (auto value = _toml[key].value<T>()) {
            return *value;
        }
        throw CustomExceptions::NoTOMLKey(_tomlPath, key);
    };

    /**
     * @brief Retrieves the type of a value for a specific key as a TOML node type.
     * @param key The key to query.
     * @return The TOML node type.
     */
    const toml::node_type getValueType(const std::string &key) const;

    /**
     * @brief Retrieves the type of a value for a specific key as a string.
     * @param key The key to query.
     * @return The type as a string.
     */
    const std::string getValueTypeAsString(const std::string &key) const;

    /**
     * @brief Retrieves the type of a value for a specific key as a string (alias).
     * @param key The key to query.
     * @return The type as a string.
     */
    const std::string getTypeAsString(const std::string &key) const;

    /**
     * @brief Converts a TOML node type to a string representation.
     * @param type The TOML node type.
     * @return The type as a string.
     */
    const std::string getTypeAsString(const toml::node_type &type) const;

    /**
     * @brief Checks if a specific key exists in the TOML data.
     * @param key The key to check.
     * @return True if the key exists, false otherwise.
     */
    const bool hasKey(const std::string &key) const;

    /**
     * @brief Retrieves all keys from the TOML table.
     * @return A vector of all keys.
     */
    std::vector<std::string> getKeys() const;

    /**
     * @brief Retrieves a TOML table for a specific key.
     * @param key The key to retrieve.
     * @return The corresponding TOML table.
     * @throw CustomExceptions::NoTOMLKey if the key does not exist or is not a table.
     */
    toml::table getTable(const std::string &key) const;

    /**
     * @brief Retrieves a TOML array for a specific key.
     * @param key The key to retrieve.
     * @return The corresponding TOML array.
     * @throw CustomExceptions::NoTOMLKey if the key does not exist or is not an array.
     */
    toml::array getArray(const std::string &key) const;

    /**
     * @brief Updates the current loader with another loader's data.
     * @param copy The other loader to copy data from.
     */
    void update(const TOMLLoader &copy);

    /**
     * @brief Updates the current loader with a TOML table.
     * @param copy The TOML table to copy data from.
     */
    void update(const toml::table &copy);

    /**
     * @brief Updates the current loader with a TOML array.
     * @param copy The TOML array to copy data from.
     */
    void update(const toml::array &copy);

    /**
     * @brief Updates the current loader with a TOML array under a specific key.
     * @param copy The TOML array to copy data from.
     * @param key The key associated with the array.
     */
    void update(const toml::array &copy, const std::string &key);

    /**
     * @brief Prints the TOML data to the debug stream.
     */
    void printTOML() const;

    /**
     * @brief Copy assignment operator.
     * @param copy The loader to copy.
     * @return Reference to the current loader.
     */
    TOMLLoader &operator=(const TOMLLoader &copy);

    /**
     * @brief Assignment operator for TOML tables.
     * @param copy The TOML table to assign.
     * @return Reference to the current loader.
     */
    TOMLLoader &operator=(const toml::table &copy);

    /**
     * @brief Assignment operator for TOML arrays.
     * @param copy The TOML array to assign.
     * @return Reference to the current loader.
     */
    TOMLLoader &operator=(const toml::array &copy);

    private:
    /**
     * @brief Loads the TOML file specified by `_tomlPath`.
     */
    void _loadTOML();

    /**
     * @brief Ensures the TOML file is loaded before accessing its data.
     * @throw CustomExceptions::NoTOML if the file is not loaded.
     */
    void _ensureLoaded() const;

    /**
     * @brief Loads the mapping between `toml::node_type` and string representations.
     */
    void _loadNodeTypeEquivalence();

    toml::table _toml;                           ///< The loaded TOML data.
    bool _tomlLoaded = false;                    ///< Indicates whether the TOML file is loaded.
    std::string _tomlPath = "";                  ///< The path to the TOML file.
    std::string _tomlString = "";                ///< The TOML data as a string.
    std::unordered_map<toml::node_type, std::string> _nodeTypeEquivalence; ///< Map of node type to string.
};

/**
 * @brief Overloads the stream insertion operator for TOMLLoader.
 * @param os The output stream.
 * @param node The TOMLLoader instance.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &os, const TOMLLoader &node);
