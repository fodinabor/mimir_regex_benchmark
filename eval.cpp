#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

extern "C" bool match(const char* mail);
extern "C" bool match_ctre(const char* mail);
extern "C" bool match_manual(const char* mail);
extern "C" bool match_std(const char* mail);
extern "C" bool match_pcre2(const char* mail);
extern "C" bool match_jit_pcre2(const char* mail);

bool stob(std::string s, bool throw_on_error = true) {
    auto result = false; // failure to assert is false

    std::istringstream is(s);
    // first try simple integer conversion
    is >> result;

    if (is.fail()) {
        // simple integer failed; try boolean
        is.clear();
        is >> std::boolalpha >> result;
    }

    if (is.fail() && throw_on_error) throw std::invalid_argument(s.append(" is not convertable to bool"));

    return result;
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <mail>";
        return 1;
    }

    using namespace std::literals;

    auto report_result = [](std::string_view engine, bool result) {
        if (result)
            std::cout << engine << ": matched\n";
        else
            std::cout << engine << ": not matched\n";
    };

    report_result("thorin"sv, match(argv[1]));
    report_result("ctre"sv, match_ctre(argv[1]));
    report_result("manual"sv, match_manual(argv[1]));
    report_result("std"sv, match_std(argv[1]));
    report_result("pcre2"sv, match_pcre2(argv[1]));
    report_result("jit_pcre2"sv, match_jit_pcre2(argv[1]));

    return 0;
}
