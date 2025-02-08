/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Constants.hpp
*/

/**
 * @file Constants.hpp
 * @brief Defines various constants used throughout the project.
 */

#pragma once

 /**
  * @brief The version of the application.
  */
static const char VERSION[] = "1.1.0";

/**
 * @brief The error code returned by the program on failure.
 */
static const unsigned int PROGRAM_ERROR = 84;

/**
 * @brief The success code returned by the program on success.
 */
static const unsigned int PROGRAM_SUCCESS = 0;

/**
 * @brief The sample rate used for audio processing.
 */
static const unsigned int SAMPLE_RATE = 48000;

/**
 * @brief The number of frames per buffer for audio processing.
 */
static const unsigned int FRAMES_PER_BUFFER = 480;

/**
 * @brief The minimum length of a username in characters.
 */
static const unsigned int USERNAME_MIN_LENGTH = 0; // Characters

/**
 * @brief The maximum length of a username in characters.
 */
static const unsigned int USERNAME_MAX_LENGTH = 40; // Characters
