/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** unCast.hpp
*/

#pragma once

#include <any>
#include <string>
#include <optional>
#include <type_traits>

#include "Logging/Log.hpp"
#include "CustomExceptions.hpp"

namespace Utilities
{
    /**
     * @brief Casts the content of a `std::any` back to its original type.
     *
     * This function attempts to safely cast the value stored in a `std::any` object to the specified type `T`.
     * If the casting fails due to a type mismatch, an exception of type `Exception` may be thrown, or
     * a warning may be logged based on the `raiseOnError` parameter.
     *
     * @tparam T The expected type of the value contained in the `std::any` object.
     * @tparam Exception The type of exception to throw in case of a failure.
     *                   Defaults to `CustomExceptions::InvalidType`. The exception must be constructible
     *                   with a single string parameter, as this is the only argument passed when thrown.
     *
     * @param classNode The `std::any` object containing the value to be cast.
     * @param raiseOnError Whether to throw an exception if the casting fails. Defaults to `true`.
     * @param customErrorMessage An optional custom message prepended to the error description if an exception
     *                           is thrown or a warning is logged.
     *
     * @return std::optional<T> The successfully cast value wrapped in a `std::optional`, or `std::nullopt` if the
     *                          casting fails and exceptions are not raised.
     *
     * @throws Exception If `raiseOnError` is `true` and:
     * - The type stored in the `std::any` object does not match the expected type `T`.
     * - The `std::any` object does not contain a value.
     * - A `std::bad_any_cast` is encountered during the casting attempt.
     *
     * @note If `raiseOnError` is `false` and an error occurs, a warning is logged using `PRETTY_WARNING`,
     *       and `std::nullopt` is returned instead of throwing an exception.
     *
     * Example usage:
     * @code
     * try {
     *     std::any data = 42;
     *     auto value = Utilities::unCast<int>(data);
     *     if (value.has_value()) {
     *         std::cout << "Uncast value: " << value.value() << std::endl;
     *     } else {
     *         std::cout << "Failed to cast value." << std::endl;
     *     }
     * } catch (const CustomExceptions::InvalidType& e) {
     *     std::cerr << "Error: " << e.what() << std::endl;
     * }
     * @endcode
     */
    template<typename T, typename Exception = CustomExceptions::InvalidType>
    std::optional<T> unCast(const std::any &classNode, const bool raiseOnError = true, const std::string customErrorMessage = "")
    {
        PRETTY_DEBUG << "custom error message: '" << customErrorMessage << "'" << std::endl;
        if (classNode.type() != typeid(T)) {
            if (raiseOnError) {
                std::string errMsg = "The type contained in std::any does not";
                errMsg += " match the expected type, Custom error message: '";
                errMsg += customErrorMessage;
                errMsg += "'.";
                throw Exception(errMsg);
            } else {
                PRETTY_WARNING << "The type contained in std::any does"
                    << " not match the expected type, Custom error message: '"
                    << customErrorMessage
                    << "'." << std::endl;
                return std::nullopt;
            }
        }
        if (!classNode.has_value()) {
            if (raiseOnError) {
                throw Exception(customErrorMessage + " : " + classNode.type().name());
            } else {
                PRETTY_WARNING << "There is no content in '"
                    << std::string(classNode.type().name())
                    << "' , Custom error message : '"
                    << customErrorMessage
                    << "'" << std::endl;
                return std::nullopt;
            }
        }
        try {
            return std::optional(std::any_cast<T>(classNode));
        }
        catch (std::bad_any_cast &e) {
            if (raiseOnError) {
                throw Exception(customErrorMessage + std::string(e.what()));
            } else {
                PRETTY_WARNING << "Any cast failed, Custom error message: '"
                    << customErrorMessage
                    << "', system error: " << std::string(e.what())
                    << std::endl;
                return std::nullopt;
            }
        }
    };
}
