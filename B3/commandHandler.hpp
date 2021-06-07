#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>
#include <functional>
#include "phoneBookInterface.hpp"

using commandFunction = std::function<void(PhoneBookInterface & book)>;
commandFunction handler(const std::string & input);

#endif
