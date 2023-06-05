#include <regex>

const std::regex regex{"^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*\\.(?:(?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\\.)*[a-zA-Z][a-zA-Z]+$"};

extern "C" bool match_std(const char* mail) {
    return std::regex_match(mail, regex);
}
