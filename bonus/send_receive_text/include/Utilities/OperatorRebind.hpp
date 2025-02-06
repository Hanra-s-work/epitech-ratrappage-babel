/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** OperatorRebind.hpp
*/

#pragma once
#include <map>
#include <set>
#include <list>
#include <deque>
#include <array>
#include <vector>
#include <utility>
#include <ostream>
#include <forward_list>
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

    /**
     * @brief Outputs a list of items to the given output stream using a custom string representation.
     *
     * @tparam T The type of the elements in the list.
     *
     * @param os The output stream to which the list will be written.
     * @param item The list of items to output.
     *
     * @return The modified output stream with the list's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::list<T> &list)
    {
        os << Recoded::myToString(list);
        return os;
    }

    /**
     * @brief Outputs a deque of items to the given output stream using a custom string representation.
     *
     * @tparam T The type of the elements in the deque.
     *
     * @param os The output stream to which the deque will be written.
     * @param item The deque of items to output.
     *
     * @return The modified output stream with the deque's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::deque<T> &deque)
    {
        os << Recoded::myToString(deque);
        return os;
    }

    /**
     * @brief Outputs an array of items to the given output stream using a custom string representation.
     *
     * @tparam T The type of the elements in the array.
     * @tparam N The size of the array.
     *
     * @param os The output stream to which the array will be written.
     * @param item The array of items to output.
     *
     * @return The modified output stream with the array's string representation appended.
     */
    template<typename T, std::size_t N>
    inline std::ostream &operator<<(std::ostream &os, const std::array<T, N> &array)
    {
        os << Recoded::myToString(array);
        return os;
    }

    /**
     * @brief Outputs a forward_list of items to the given output stream using a custom string representation.
     *
     * @tparam T The type of the elements in the forward_list.
     *
     * @param os The output stream to which the forward_list will be written.
     * @param item The forward_list of items to output.
     *
     * @return The modified output stream with the forward_list's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::forward_list<T> &flist)
    {
        os << Recoded::myToString(flist);
        return os;
    }

    /**
     * @brief Outputs a multiset of items to the given output stream using a custom string representation.
     *
     * @tparam T The type of the elements in the multiset.
     *
     * @param os The output stream to which the multiset will be written.
     * @param item The multiset of items to output.
     *
     * @return The modified output stream with the multiset's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::multiset<T> &mset)
    {
        os << Recoded::myToString(mset);
        return os;
    }

    /**
     * @brief Outputs an unordered_multiset of items to the given output stream using a custom string representation.
     *
     * @tparam T The type of the elements in the unordered_multiset.
     *
     * @param os The output stream to which the unordered_multiset will be written.
     * @param item The unordered_multiset of items to output.
     *
     * @return The modified output stream with the unordered_multiset's string representation appended.
     */
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const std::unordered_multiset<T> &umset)
    {
        os << Recoded::myToString(umset);
        return os;
    }

    /**
     * @brief Outputs a multimap of items to the given output stream using a custom string representation.
     *
     * @tparam Key The type of the keys in the multimap.
     * @tparam Value The type of the values in the multimap.
     *
     * @param os The output stream to which the multimap will be written.
     * @param item The multimap of items to output.
     *
     * @return The modified output stream with the multimap's string representation appended.
     */
    template<typename Key, typename Value>
    inline std::ostream &operator<<(std::ostream &os, const std::multimap<Key, Value> &mmap)
    {
        os << Recoded::myToString(mmap);
        return os;
    }

    /**
     * @brief Outputs an unordered_multimap of items to the given output stream using a custom string representation.
     *
     * @tparam Key The type of the keys in the unordered_multimap.
     * @tparam Value The type of the values in the unordered_multimap.
     *
     * @param os The output stream to which the unordered_multimap will be written.
     * @param item The unordered_multimap of items to output.
     *
     * @return The modified output stream with the unordered_multimap's string representation appended.
     */
    template<typename Key, typename Value>
    inline std::ostream &operator<<(std::ostream &os, const std::unordered_multimap<Key, Value> &ummap)
    {
        os << Recoded::myToString(ummap);
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
