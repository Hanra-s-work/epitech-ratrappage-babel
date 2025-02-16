/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** LogMacros.hpp
*/


/**
 * @file LogMacros.hpp
 * @brief Macro definitions for logging messages with varying levels of detail and formatting.
 * 
 * This file defines macros for logging purposes, including various log levels (e.g., DEBUG, INFO, SUCCESS, etc.),
 * optional colourized output, and detailed output with file, line, and function information.
 * 
 * @details
 * @li **Log Levels**:
 *   @li DEBUG: Used for debugging information.
 *   @li INFO: General informational messages.
 *   @li SUCCESS: Indicates successful operations.
 *   @li WARNING: Highlights warnings requiring attention.
 *   @li ERROR: Non-critical errors.
 *   @li CRITICAL: Critical errors requiring program termination.
 * 
 * @li **Optional Features**:
 *   @li Colorized output for better visibility.
 *   @li Enhanced logging with detailed file, line, and function information.
 *   @li Variants with and without colour and detailed information.
 * 
 * @note Customize the log macros by defining or omitting certain preprocessor variables:
 * @li `NO_LOG_COLOURS`: Disables colourized output.
 * @li `_MY_FILE_GETTER`: Customizes how file, line, and function information is displayed.
 */

#ifndef _LOG_MACROS
    #define _LOG_MACROS

    #include "Logging/Log.hpp"

    #define COLOUR_LOG_DISABLED Logging::isRedirected()

    // Core log level definitions
    #ifndef _LOG_CORE
        #define _LOG_CORE
        #define _DEBUG_STR    " DEBUG: "                                                                                                                                                        //!< Debug log level string.
        #define _INFO_STR     " INFO: "                                                                                                                                                         //!< Info log level string.
        #define _SUCCESS_STR  " SUCCESS: "                                                                                                                                                      //!< Success log level string.
        #define _WARNING_STR  " WARNING: "                                                                                                                                                      //!< Warning log level string.
        #define _ERROR_STR    " ERROR: "                                                                                                                                                        //!< Error log level string.
        #define _CRITICAL_STR " CRITICAL: "                                                                                                                                                     //!< Critical log level string.
    #endif

    // Color definitions for supported platforms
    #ifndef _LOG_COLOURS
        #define _LOG_COLOURS
        #ifndef NO_LOG_COLOURS
            #if defined(__linux__) || defined(MACOSX) || defined(__APPLE__) || defined(__MACH__)
                /**
                 * @brief Color codes for Unix-like systems.
                 */
                #define BACKGROUND_COL (COLOUR_LOG_DISABLED ? "" : "\033[48;5;16m")                                                                                                             //!< Background colour: GREY0 (according to colors.sh), it's basically the colour black.
                #define DEFAULT_FG     (COLOUR_LOG_DISABLED ? "" : "\033[38;5;15m")                                                                                                             //!< Default foreground colour: WHITE (according to colors.sh), it's the colour white.
                #define RESET_COL      (COLOUR_LOG_DISABLED ? "" : "\033[0m")                                                                                                                   //!< Reset colour to system default.
                #define DEBUG_COL      (COLOUR_LOG_DISABLED ? "" : "\033[38;5;200m")                                                                                                            //!< Debug colour: MAGENTA2 (according to colors.sh), it's basically the colour pink.
                #define SUCCESS_COL    (COLOUR_LOG_DISABLED ? "" : "\033[38;5;10m")                                                                                                             //!< Success colour: LIME (according to colors.sh), it's a very vibrant green.
                #define INFO_COL       (COLOUR_LOG_DISABLED ? "" : "\033[38;5;14m")                                                                                                             //!< Info colour: AQUA (according to colors.sh), it's a very light blue.
                #define WARNING_COL    (COLOUR_LOG_DISABLED ? "" : "\033[38;5;11m")                                                                                                             //!< Warning colour: YELLOW (according to colors.sh), it's the colour yellow.
                #define ERROR_COL      (COLOUR_LOG_DISABLED ? "" : "\033[38;5;9m")                                                                                                              //!< Error colour: RED (according to colors.sh), it's the colour red.
                #define CRITICAL_COL   (COLOUR_LOG_DISABLED ? "" : "\033[1m\033[38;5;232m\033[48;5;9m")                                                                                         //!< Critical colour: BOLD GREY0 (black) on a RED background.
            #else
                /**
                 * @brief Empty colour codes for unsupported platforms.
                 */
                #define BACKGROUND_COL ""
                #define DEFAULT_FG     ""
                #define RESET_COL      ""
                #define DEBUG_COL      ""
                #define SUCCESS_COL    ""
                #define INFO_COL       ""
                #define WARNING_COL    ""
                #define ERROR_COL      ""
                #define CRITICAL_COL   ""
            #endif
        #else
            /**
             * @brief Empty colour codes when `NO_LOG_COLOURS` is defined.
             */
            #define BACKGROUND_COL ""
            #define DEFAULT_FG     ""
            #define RESET_COL      ""
            #define DEBUG_COL      ""
            #define SUCCESS_COL    ""
            #define INFO_COL       ""
            #define WARNING_COL    ""
            #define ERROR_COL      ""
            #define CRITICAL_COL   ""
        #endif
    #endif

    /**
     * @brief Get the name of the function based on the compiler version.
     */
    #ifndef _FUNC_NAME
        #if defined(__GNUG__) || defined(__GNUC__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__)
            #define _FUNC_NAME __PRETTY_FUNCTION__
        #else
            #define _FUNC_NAME "Function name: (" << __func__ << ')' 
        #endif
    #endif

    /**
     * @brief Formats detailed logging information with file, line, and function details.
     */
    #ifndef _MY_FILE_GETTER
        #define _MY_FILE_GETTER " " << __FILE__ << ":" << __LINE__ << " " << _FUNC_NAME << ": "
    #endif

    /**
     * @brief Formats detailed logging information with file, line, and function details in a colourized form.
     */
    #ifndef _MY_COLOURED_FILE_GETTER
        #define _MY_COLOURED_FILE_GETTER BACKGROUND_COL << DEFAULT_FG << " " << SUCCESS_COL << __FILE__ << DEFAULT_FG << ":" << INFO_COL << __LINE__ << DEFAULT_FG << " " << WARNING_COL << _FUNC_NAME << DEFAULT_FG << ": "
    #endif

    /**
     * @defgroup LogLevels Log Levels
     * 
     * @brief Defines macros for logging messages with different severity levels.
     * 
     * @note {
     */
    #ifndef _LOG_LEVELS
        #define _LOG_LEVELS
        #define LOG_DEBUG    Logging::Log::getInstance(true)  << _DEBUG_STR                                                                                                                                    //!< Debug log level.
        #define LOG_SUCCESS  Logging::Log::getInstance(false) << _SUCCESS_STR                                                                                                                                  //!< Success log level.
        #define LOG_INFO     Logging::Log::getInstance(false) << _INFO_STR                                                                                                                                     //!< Info log level.
        #define LOG_WARNING  Logging::Log::getInstance(false) << _WARNING_STR                                                                                                                                  //!< Warning log level.
        #define LOG_ERROR    Logging::Log::getInstance(false) << _ERROR_STR                                                                                                                                    //!< Error log level.
        #define LOG_CRITICAL Logging::Log::getInstance(false) << _CRITICAL_STR                                                                                                                                 //!< Critical log level.
    #endif
    /** @note } */

    /**
     * @defgroup PreciseLog Precise Logs
     * 
     * @brief Similar to pretty logs, intended for extended formatting.
     * 
     * @note {
     */
    #ifndef _PRECISE_LOG
        #define _PRECISE_LOG
            #define PRECISE_DEBUG    Logging::Log::getInstance(true) << _DEBUG_STR    << _MY_FILE_GETTER                                                                                                      //!< Debug log with precise details.
            #define PRECISE_SUCCESS  Logging::Log::getInstance(false) << _SUCCESS_STR  << _MY_FILE_GETTER                                                                                                      //!< Success log with precise details.
            #define PRECISE_INFO     Logging::Log::getInstance(false) << _INFO_STR     << _MY_FILE_GETTER                                                                                                      //!< Info log with precise details.
            #define PRECISE_WARNING  Logging::Log::getInstance(false) << _WARNING_STR  << _MY_FILE_GETTER                                                                                                      //!< Warning log with precise details.
            #define PRECISE_ERROR    Logging::Log::getInstance(false) << _ERROR_STR    << _MY_FILE_GETTER                                                                                                      //!< Error log with precise details.
            #define PRECISE_CRITICAL Logging::Log::getInstance(false) << _CRITICAL_STR << _MY_FILE_GETTER                                                                                                      //!< Critical log with precise details.
    #endif
    /** @note } */

    /**
     * @defgroup ColourLog Colorized Logs
     * 
     * @brief Macros for logging messages with colour.
     * 
     * @note {
     */
    #ifndef _COLOUR_LOG
        #define _COLOUR_LOG
        #define COLOUR_DEBUG    Logging::Log::getInstance(true) << RESET_COL << BACKGROUND_COL << DEBUG_COL    << _DEBUG_STR    << RESET_COL << BACKGROUND_COL << DEFAULT_FG                                  //!< Debug log with colour.
        #define COLOUR_SUCCESS  Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << SUCCESS_COL  << _SUCCESS_STR  << RESET_COL << BACKGROUND_COL << DEFAULT_FG                                  //!< Success log with colour.
        #define COLOUR_INFO     Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << INFO_COL     << _INFO_STR     << RESET_COL << BACKGROUND_COL << DEFAULT_FG                                  //!< Info log with colour.
        #define COLOUR_WARNING  Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << WARNING_COL  << _WARNING_STR  << RESET_COL << BACKGROUND_COL << DEFAULT_FG                                  //!< Warning log with colour.
        #define COLOUR_ERROR    Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << ERROR_COL    << _ERROR_STR    << RESET_COL << BACKGROUND_COL << DEFAULT_FG                                  //!< Error log with colour.
        #define COLOUR_CRITICAL Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << CRITICAL_COL << _CRITICAL_STR << RESET_COL << BACKGROUND_COL << DEFAULT_FG                                  //!< Critical log with colour.
    #endif
    /** @note } */

    /**
     * @defgroup PrettyLog Pretty Logs
     * 
     * @brief Macros for logging messages with file, line, and function information.
     * 
     * @note {
     */
    #ifndef _PRETTY_LOG
        #define _PRETTY_LOG
        #define PRETTY_DEBUG    Logging::Log::getInstance(true) << RESET_COL << BACKGROUND_COL << DEBUG_COL    << _DEBUG_STR    << RESET_COL << BACKGROUND_COL << DEFAULT_FG  << _MY_COLOURED_FILE_GETTER      //!< Debug log with details and colour.
        #define PRETTY_SUCCESS  Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << SUCCESS_COL  << _SUCCESS_STR  << RESET_COL << BACKGROUND_COL << DEFAULT_FG  << _MY_COLOURED_FILE_GETTER      //!< Success log with details and colour.
        #define PRETTY_INFO     Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << INFO_COL     << _INFO_STR     << RESET_COL << BACKGROUND_COL << DEFAULT_FG  << _MY_COLOURED_FILE_GETTER      //!< Info log with details and colour.
        #define PRETTY_WARNING  Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << WARNING_COL  << _WARNING_STR  << RESET_COL << BACKGROUND_COL << DEFAULT_FG  << _MY_COLOURED_FILE_GETTER      //!< Warning log with details and colour.
        #define PRETTY_ERROR    Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << ERROR_COL    << _ERROR_STR    << RESET_COL << BACKGROUND_COL << DEFAULT_FG  << _MY_COLOURED_FILE_GETTER      //!< Error log with details and colour.
        #define PRETTY_CRITICAL Logging::Log::getInstance(false) << RESET_COL << BACKGROUND_COL << CRITICAL_COL << _CRITICAL_STR << RESET_COL << BACKGROUND_COL << DEFAULT_FG  << _MY_COLOURED_FILE_GETTER      //!< Critical log with details and colour.
    #endif
    /** @note } */

#endif // _LOG_MACROS
