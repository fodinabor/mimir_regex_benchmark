#include "ctre.hpp"

extern "C" bool match_ctre(const char* mail) {
    using namespace ctre::literals;
    return {ctre::match<"^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*\\.(?:(?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\\.)*[a-zA-Z][a-zA-Z]+$">(mail)};
}
