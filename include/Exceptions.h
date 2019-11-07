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


#endif  // INCLUDE_EXCEPTIONS_H_