/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** toString.hpp
*/

/**
 * @file ToString.hpp
 * @brief Provides custom string conversion functions as alternatives to `std::to_string`.
 *
 * This header defines the `myToString` functions, which extend the capabilities of `std::to_string`.
 * These functions include specialized handling for boolean values and generic handling for
 * `std::pair` objects, making them suitable for more complex use cases.
 */

#pragma once
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>

namespace Recoded
{

    /**
     * @brief Converts a boolean value to its string representation.
     *
     * Unlike `std::to_string`, which converts `true` to "1" and `false` to "0",
     * this function returns "true" for `true` and "false" for `false`.
     *
     * @param value The boolean value to convert.
     *
     * @return A string representation of the boolean ("true" or "false").
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(bool value);

    /**
     * @brief Converts a numeric value to its string representation.
     *
     * This function is a wrapper around `std::to_string` and supports all types
     * for which `std::to_string` is valid. It is intended for general use with
     * numeric types like `int`, `float`, `double`, etc.
     *
     * @tparam T The type of the value to convert. Must be a numeric type.
     *
     * @param value The value to convert.
     *
     * @return A string representation of the numeric value.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template <typename T>
    const std::string myToString(const T &value)
    {
        return std::to_string(value);
    };

    /**
     * @brief Converts a `std::pair` to its string representation.
     *
     * This function formats the `std::pair` as `( x: <first>, y: <second> )`,
     * where `<first>` and `<second>` are the string representations of the pair's elements.
     * The elements' string representations are generated using `myToString`.
     *
     * Example:
     * ```
     * std::pair<int, int> p = {1, 2};
     * std::cout << myToString(p); // Output: ( x: 1, y: 2 )
     * ```
     *
     * @tparam T1 The type of the first element in the pair.
     * @tparam T2 The type of the second element in the pair.
     *
     * @param value The pair to convert.
     *
     * @return A string representation of the pair in the format `( x: <first>, y: <second> )`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template <typename T1, typename T2>
    const std::string myToString(const std::pair<T1, T2> &value)
    {
        return "( x: " + myToString(value.first) + ", y: " + myToString(value.second) + ")";
    };


    /**
     * @brief Converts a std::map to a string representation.
     *
     * This function iterates over the key-value pairs of a `std::map` and generates
     * a string in the format: `{ 'key1' : 'value1', 'key2' : 'value2', ... }`.
     *
     * @tparam Key The type of the keys in the map.
     * @tparam Value The type of the values in the map.
     *
     * @param map The map to be converted to a string.
     *
     * @return A string representing the map.
     *
     * @note Uses `Recoded::myToString` to convert keys and values to strings.
     */
    template<typename Key, typename Value>
    std::string myToString(const std::map<Key, Value> &map)
    {
        std::string result = "{ ";
        typename std::map<Key, Value>::const_iterator it = map.begin();
        for (; it != map.end(); ++it) {
            result += "'" + Recoded::myToString(it->first) + "' : '" + Recoded::myToString(it->second) + "'";
            if (std::next(it) != map.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::set to a string representation.
     *
     * This function iterates over the elements of a `std::set` and generates
     * a string in the format: `{ 'element1', 'element2', ... }`.
     *
     * @tparam T The type of the elements in the set.
     *
     * @param set The set to be converted to a string.
     *
     * @return A string representing the set.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template<typename T>
    std::string myToString(const std::set<T> &set)
    {
        std::string result = "{ ";
        for (typename std::set<T>::const_iterator it = set.begin(); it != set.end();) {
            result += "'" + Recoded::myToString(*it) + "'";
            if (++it != set.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::vector to a string representation.
     *
     * This function iterates over the elements of a `std::vector` and generates
     * a string in the format: `[ 'element1', 'element2', ... ]`.
     *
     * @tparam T The type of the elements in the vector.
     *
     * @param vec The vector to be converted to a string.
     *
     * @return A string representing the vector.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template<typename T>
    const std::string myToString(const std::vector<T> &set)
    {
        std::string result = "[ ";
        typename std::vector<T>::const_iterator it = set.begin();
        for (; it != set.end(); ++it) {
            result += "'" + Recoded::myToString(*it) + "'";
            if (std::next(it) != set.end())
                result += ", ";
        }
        result += " ]";
        return result;
    }

    /**
     * @brief Converts a std::unordered_map to a string representation.
     *
     * This function iterates over the key-value pairs of a `std::unordered_map` and generates
     * a string in the format: `{ 'key1' : 'value1', 'key2' : 'value2', ... }`.
     *
     * @tparam Key The type of the keys in the unordered map.
     * @tparam Value The type of the values in the unordered map.
     *
     * @param map The unordered map to be converted to a string.
     *
     * @return A string representing the unordered map.
     *
     * @note Uses `Recoded::myToString` to convert keys and values to strings.
     */
    template<typename Key, typename Value>
    std::string myToString(const std::unordered_map<Key, Value> &map)
    {
        std::string result = "{ ";
        typename std::unordered_map<Key, Value>::const_iterator it = map.begin(); // Correct variable name
        for (; it != map.end(); ++it) {
            result += "'" + Recoded::myToString(it->first) + "' : '" + Recoded::myToString(it->second) + "'";
            if (std::next(it) != map.end()) // Avoid trailing comma
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::unordered_set to a string representation.
     *
     * This function iterates over the elements of a `std::unordered_set` and generates
     * a string in the format: `{ 'element1', 'element2', ... }`.
     *
     * @tparam T The type of the elements in the unordered set.
     *
     * @param set The unordered set to be converted to a string.
     *
     * @return A string representing the unordered set.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template<typename T>
    const std::string myToString(const std::unordered_set<T> &set)
    {
        std::string result = "{ ";
        typename std::unordered_set<T>::const_iterator it = set.begin();
        for (; it != set.end(); ++it) {
            result += "'" + Recoded::myToString(*it) + "'";
            if (std::next(it) != set.end())
                result += ", ";
        }
        result += " }";
        return result;
    }
}
