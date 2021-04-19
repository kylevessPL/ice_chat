#ifndef PROJECT_CHARACTERS_NOT_ALLOWED_EXCEPTION_HPP
#define PROJECT_CHARACTERS_NOT_ALLOWED_EXCEPTION_HPP

#include <stdexcept>

class CharactersNotAllowedException : public std::runtime_error
{
    public:
        CharactersNotAllowedException(std::string message) : runtime_error(message) {};
};

#endif //PROJECT_CHARACTERS_NOT_ALLOWED_EXCEPTION_HPP
