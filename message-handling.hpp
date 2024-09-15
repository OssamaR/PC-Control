#ifndef MESSAGE_HANDLING_HPP
#define MESSAGE_HANDLING_HPP

#include "socket-setup.hpp"
#include "database.hpp"

#include <algorithm> // For std::transform
#include <cctype>    // For std::tolower

extern int Continue_Flag;
void Message_Handle(std::string message);

#endif