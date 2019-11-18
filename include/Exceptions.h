/*
*Copyright 2019 Fafnir
*/

#ifndef INCLUDE_EXCEPTIONS_H_
#define INCLUDE_EXCEPTIONS_H_

#include <stdexcept>

/**
* Exception for when you try to create a non-square amount of rooms
*/
class room_count_not_square_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit room_count_not_square_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* Exception for when you try to create a too many of rooms
*/
class room_count_too_large_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit room_count_too_large_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* Exception for when you try to do anything invalid
*/
class invalid_operation_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit invalid_operation_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* Exception for if you somehow reach a game state that is unhandled
*/
class game_state_error: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit game_state_error(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

#endif  // INCLUDE_EXCEPTIONS_H_
