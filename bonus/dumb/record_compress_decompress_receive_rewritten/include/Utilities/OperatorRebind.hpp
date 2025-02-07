/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** OperatorRebind.hpp
*/

#pragma once
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <ostream>
#include <unordered_set>
#include <unordered_map>
#include "Recoded/ToString.hpp"

namespace Utilities
{
    /**
     * @brief Outputs a boolean value to the given output stream using a custom string representation.
     *
     * This function uses the custom `Recoded::myToString` function to convert the boolean value
     * to a string ("true" or "false") and then inserts the result into the output stream.
     *
     * @param os The output stream to which the boolean value will be written.
     * @param item The boolean value to output.
     *
     * @return The modified output stream with the boolean's string representation appended.
     */
    inline std::ostream &operator<<(std::ostream &os, const bool &item)
    {
        os << Recoded::myToString(item);
        return os;
    };

    /**
     * @brief Outputs a pair of items to the given output stream using a custom string representation.
     *
     * This function uses the custom `Recoded::myToString` function to convert the pair to a string
     * and then inserts the result into the output stream.
     *
     * @tparam T1 The type of the first element in the pair.
     * @tparam T2 The type of the second element in the pair.
     *
     * @param os The output stream to which the pair will be written.
     * @param item The pair of items to output.
     *
     * @return The modified output stream with the pair's string representation appended.
     */
    template<typename T1, typename T2>
    inline std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &item)
    {
        os << Recoded::myToString(item);
        return os;
    };

    /**
     * @brief Outputs a vector of items to the given output stream using a custom string representation.
     *
     * This function uses the custom `Recoded::myToString` function to convert the vector to a string
     * and then inserts the result into the output stream.
     *
     * @tparam T The type of the elements in the vector.
     *
     * @param os The output stream to which the vector will be written.
     * @param item The vector of items to output.
     *
     * @return The modified output stream with the vector's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::vector<T> &set)
    {
        os << Recoded::myToString(set);
        return os;
    }

    /**
     * @brief Outputs an unordered_map of items to the given output stream using a custom string representation.
     *
     * This function uses the custom `Recoded::myToString` function to convert the unordered_map to a string
     * and then inserts the result into the output stream.
     *
     * @tparam T The type of the elements in the unordered_map.
     *
     * @param os The output stream to which the unordered_map will be written.
     * @param item The unordered_map of items to output.
     *
     * @return The modified output stream with the unordered_map's string representation appended.
     */
    template<typename Key, typename Value>
    inline std::ostream &operator<<(std::ostream &os, const std::unordered_map<Key, Value> &map)
    {
        os << Recoded::myToString(map);
        return os;
    }

    /**
     * @brief Outputs a set of items to the given output stream using a custom string representation.
     *
     * This function uses the custom `Recoded::myToString` function to convert the set to a string
     * and then inserts the result into the output stream.
     *
     * @tparam T The type of the elements in the set.
     *
     * @param os The output stream to which the set will be written.
     * @param item The set of items to output.
     *
     * @return The modified output stream with the set's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::set<T> &set)
    {
        os << Recoded::myToString(set);
        return os;
    }

    /**
     * @brief Outputs an unordered_set of items to the given output stream using a custom string representation.
     *
     * This function uses the custom `Recoded::myToString` function to convert the unordered_set to a string
     * and then inserts the result into the output stream.
     *
     * @tparam T The type of the elements in the unordered_set.
     *
     * @param os The output stream to which the unordered_set will be written.
     * @param item The unordered_set of items to output.
     *
     * @return The modified output stream with the unordered_set's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &set)
    {
        os << Recoded::myToString(set);
        return os;
    }
}

/**
 * @brief Brings the `operator<<` from the `Utilities` namespace into the current scope.
 *
 * This makes the `operator<<` overloads available in the current namespace, allowing direct
 * usage of `operator<<` to output various types (e.g., `bool`, `std::pair`, etc.) with
 * custom string representations via `Recoded::myToString`. This removes the need to fully
 * qualify the operator with `Utilities::` within this file.
 *
 * @see Utilities::operator<<
 */
using Utilities::operator<<;
