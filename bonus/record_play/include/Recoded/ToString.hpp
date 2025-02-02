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
#include <list>
#include <deque>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

#include "Audio/StreamData.hpp"

namespace Recoded
{

    /**
     * @brief Converts a boolean value to its string representation.
     *
     * @param value The boolean value to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the boolean ("true" or "false").
     */
    const std::string myToString(bool value, const unsigned int indent = 0);

    /**
     * @brief Converts a string value to its string representation.
     *
     * @param value The string value to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the string.
     */
    const std::string myToString(const std::string &value, const unsigned int indent = 0);

    /**
     * @brief Converts a numeric value to its string representation.
     *
     * @tparam T The type of the value to convert. Must be a numeric type.
     * @param value The value to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the numeric value.
     */
    template <typename T>
    const std::string myToString(const T &value, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        return indentation + std::to_string(value);
    };

    /**
     * @brief Converts a std::pair to its string representation.
     *
     * @tparam T1 The type of the first element in the pair.
     * @tparam T2 The type of the second element in the pair.
     * @param value The pair to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the pair.
     */
    template <typename T1, typename T2>
    const std::string myToString(const std::pair<T1, T2> &value, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        return indentation + "( x: " + myToString(value.first, 0) + ", y: " + myToString(value.second, 0) + ")";
    };

    /**
     * @brief Converts a std::map to its string representation.
     *
     * @tparam Key The type of the keys in the map.
     * @tparam Value The type of the values in the map.
     * @param map The map to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the map.
     */
    template<typename Key, typename Value>
    std::string myToString(const std::map<Key, Value> &map, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = indentation + "{";
            typename std::map<Key, Value>::const_iterator it = map.begin();
            for (; it != map.end(); ++it) {
                result += +"'" + Recoded::myToString(it->first, 0) + "' : '" + Recoded::myToString(it->second, 0) + "'";
                if (std::next(it) != map.end())
                    result += ", ";
            }
            result += " }";
        } else {
            result = indentation + "{\n";
            typename std::map<Key, Value>::const_iterator it = map.begin();
            for (; it != map.end(); ++it) {
                result += indentation + "\t'" + Recoded::myToString(it->first, 0) + "' : '";
                result += Recoded::myToString(it->second, 0) + "'";
                if (std::next(it) != map.end()) {
                    result += ",";
                }
                result += "\n";
            }
            result += indentation + "}";
        }
        return result;
    }

    /**
     * @brief Converts a std::set to its string representation.
     *
     * @tparam T The type of the elements in the set.
     * @param set The set to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the set.
     */
    template<typename T>
    std::string myToString(const std::set<T> &set, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "{ ";
            for (typename std::set<T>::const_iterator it = set.begin(); it != set.end();) {
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (++it != set.end())
                    result += ", ";
            }
            result += " }";
        } else {
            result = indentation + "{ \n";
            for (typename std::set<T>::const_iterator it = set.begin(); it != set.end();) {
                result += indentation;
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (++it != set.end()) {
                    result += ", ";
                }
                result += "\n";
            }
            result += indentation + " }";
        }
        return result;
    }

    /**
     * @brief Converts a std::vector to its string representation.
     *
     * @tparam T The type of the elements in the vector.
     * @param vec The vector to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the vector.
     */
    template<typename T>
    const std::string myToString(const std::vector<T> &vec, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "[ ";
            typename std::vector<T>::const_iterator it = vec.begin();
            for (; it != vec.end(); ++it) {
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != vec.end())
                    result += ", ";
            }
            result += " ]";
        } else {
            result = indentation + "[ \n";
            typename std::vector<T>::const_iterator it = vec.begin();
            for (; it != vec.end(); ++it) {
                result += indentation;
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != vec.end()) {
                    result += ", ";
                }
                result += "\n";
            }
            result += indentation + " ]";
        }
        return result;
    }

    /**
     * @brief Converts a std::unordered_map to its string representation.
     *
     * @tparam Key The type of the keys in the unordered map.
     * @tparam Value The type of the values in the unordered map.
     * @param map The unordered map to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the unordered map.
     */
    template<typename Key, typename Value>
    std::string myToString(const std::unordered_map<Key, Value> &map, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = indentation + "{";
            typename std::unordered_map<Key, Value>::const_iterator it = map.begin();
            for (; it != map.end(); ++it) {
                result += "'" + Recoded::myToString(it->first, 0) + "' : '";
                result += Recoded::myToString(it->second, 0) + "'";
                if (std::next(it) != map.end())
                    result += ", ";
            }
            result += " }";
        } else {
            result = indentation + "{\n";
            typename std::unordered_map<Key, Value>::const_iterator it = map.begin();
            for (; it != map.end(); ++it) {
                result += indentation + "\t'" + Recoded::myToString(it->first, 0) + "' : '";
                result += Recoded::myToString(it->second, 0) + "'";
                if (std::next(it) != map.end())
                    result += ",";
                result += "\n";
            }
            result += indentation + "}";
        }
        return result;
    }

    /**
     * @brief Converts a std::unordered_set to its string representation.
     *
     * @tparam T The type of the elements in the unordered set.
     * @param set The unordered set to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the unordered set.
     */
    template<typename T>
    const std::string myToString(const std::unordered_set<T> &set, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "{ ";
            for (typename std::unordered_set<T>::const_iterator it = set.begin(); it != set.end();) {
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (++it != set.end())
                    result += ", ";
            }
            result += " }";
        } else {
            result = indentation + "{ \n";
            for (typename std::unordered_set<T>::const_iterator it = set.begin(); it != set.end();) {
                result += indentation;
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (++it != set.end())
                    result += ", ";
                result += "\n";
            }
            result += indentation + " }";
        }
        return result;
    }

    /**
     * @brief Converts a std::list to its string representation.
     *
     * @tparam T The type of the elements in the list.
     * @param lst The list to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the list.
     */
    template<typename T>
    const std::string myToString(const std::list<T> &lst, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "[ ";
            typename std::list<T>::const_iterator it = lst.begin();
            for (; it != lst.end(); ++it) {
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != lst.end())
                    result += ", ";
            }
            result += " ]";
        } else {
            result = indentation + "[ \n";
            typename std::list<T>::const_iterator it = lst.begin();
            for (; it != lst.end(); ++it) {
                result += indentation;
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != lst.end())
                    result += ", ";
                result += "\n";
            }
            result += indentation + " ]";
        }
        return result;
    }

    /**
     * @brief Converts a std::deque to its string representation.
     *
     * @tparam T The type of the elements in the deque.
     * @param deq The deque to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the deque.
     */
    template<typename T>
    const std::string myToString(const std::deque<T> &deq, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "[ ";
            typename std::deque<T>::const_iterator it = deq.begin();
            for (; it != deq.end(); ++it) {
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != deq.end())
                    result += ", ";
            }
            result += " ]";
        } else {
            result = indentation + "[ \n";
            typename std::deque<T>::const_iterator it = deq.begin();
            for (; it != deq.end(); ++it) {
                result += indentation;
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != deq.end())
                    result += ", ";
                result += "\n";
            }
            result += indentation + " ]";
        }
        return result;
    }

    /**
     * @brief Converts a std::array to its string representation.
     *
     * @tparam T The type of the elements in the array.
     * @tparam N The size of the array.
     * @param arr The array to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the array.
     */
    template<typename T, std::size_t N>
    const std::string myToString(const std::array<T, N> &arr, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "[ ";
            for (std::size_t i = 0; i < N; ++i) {
                result += "'" + Recoded::myToString(arr[i], 0) + "'";
                if (i != N - 1)
                    result += ", ";
            }
            result += " ]";
        } else {
            result = indentation + "[ \n";
            for (std::size_t i = 0; i < N; ++i) {
                result += indentation + "\t";
                result += "'" + Recoded::myToString(arr[i], 0) + "'";
                if (i != N - 1)
                    result += ", ";
                result += "\n";
            }
            result += indentation + " ]";
        }
        return result;
    }

    /**
     * @brief Converts a std::forward_list to its string representation.
     *
     * @tparam T The type of the elements in the forward list.
     * @param flist The forward list to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the forward list.
     */
    template<typename T>
    const std::string myToString(const std::forward_list<T> &flist, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result;
        if (indent == 0) {
            result = "[ ";
            for (typename std::forward_list<T>::const_iterator it = flist.begin(); it != flist.end(); ++it) {
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != flist.end())
                    result += ", ";
            }
            result += " ]";
        } else {
            result = indentation + "[ \n";
            for (typename std::forward_list<T>::const_iterator it = flist.begin(); it != flist.end(); ++it) {
                result += indentation + "\t";
                result += "'" + Recoded::myToString(*it, 0) + "'";
                if (std::next(it) != flist.end())
                    result += ", ";
                result += "\n";
            }
            result += indentation + " ]";
        }
        return result;
    }

    /**
     * @brief Converts a std::multiset to its string representation.
     *
     * @tparam T The type of the elements in the multiset.
     * @param mset The multiset to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the multiset.
     */
    template<typename T>
    const std::string myToString(const std::multiset<T> &mset, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result = indentation + "{ ";
        for (typename std::multiset<T>::const_iterator it = mset.begin(); it != mset.end();) {
            result += "'" + Recoded::myToString(*it, 0) + "'";
            if (++it != mset.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::unordered_multiset to its string representation.
     *
     * @tparam T The type of the elements in the unordered multiset.
     * @param umset The unordered multiset to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the unordered multiset.
     */
    template<typename T>
    const std::string myToString(const std::unordered_multiset<T> &umset, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result = indentation + "{ ";
        for (typename std::unordered_multiset<T>::const_iterator it = umset.begin(); it != umset.end();) {
            result += "'" + Recoded::myToString(*it, 0) + "'";
            if (++it != umset.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::multimap to its string representation.
     *
     * @tparam Key The type of the keys in the multimap.
     * @tparam Value The type of the values in the multimap.
     * @param mmap The multimap to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the multimap.
     */
    template<typename Key, typename Value>
    const std::string myToString(const std::multimap<Key, Value> &mmap, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result = indentation + "{ ";
        for (typename std::multimap<Key, Value>::const_iterator it = mmap.begin(); it != mmap.end(); ++it) {
            result += "'" + Recoded::myToString(it->first, 0) + "' : '" + Recoded::myToString(it->second, 0) + "'";
            if (std::next(it) != mmap.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::unordered_multimap to its string representation.
     *
     * @tparam Key The type of the keys in the unordered multimap.
     * @tparam Value The type of the values in the unordered multimap.
     * @param ummap The unordered multimap to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the unordered multimap.
     */
    template<typename Key, typename Value>
    const std::string myToString(const std::unordered_multimap<Key, Value> &ummap, const unsigned int indent = 0)
    {
        std::string indentation(indent, '\t');
        std::string result = indentation + "{ ";
        for (typename std::unordered_multimap<Key, Value>::const_iterator it = ummap.begin(); it != ummap.end(); ++it) {
            result += "'" + Recoded::myToString(it->first, 0) + "' : '" + Recoded::myToString(it->second, 0) + "'";
            if (std::next(it) != ummap.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts an Audio::StreamData object to its string representation.
     *
     * @param data The Audio::StreamData object to convert.
     * @param indent The indentation level for the output string.
     * @return A string representation of the Audio::StreamData object.
     */
    const std::string myToString(const Audio::StreamData &data, const unsigned int indent = 0);
}
