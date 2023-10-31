#include "ctre.hpp"

#ifdef REGEX_DETERMINISTIC
static constexpr const char pattern[]
    = "^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-"
      "zA-Z0-9]*\\.(?:(?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\\.)*[a-zA-Z][a-zA-Z]+$";
#else
static constexpr const char pattern[] = "^[a-zA-Z0-9](?:[a-zA-Z0-9.!#$%&'*+\\/=?^_`{|}~\\-]*[a-zA-Z0-9])?"
                                        "@[a-zA-Z0-9](?:[a-zA-Z0-9\\-]*[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-"
                                        "Z0-9_\\-]*[a-zA-Z0-9])?)*\\.[a-zA-Z][a-zA-Z]+$";
#endif

extern "C" bool match_ctre(const char* mail) {
    using namespace ctre::literals;
    return {ctre::match<pattern>(mail)};
}
