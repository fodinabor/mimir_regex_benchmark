#include <cstddef>
#include <cstdio>
#include <cstring>

#define PCRE2_CODE_UNIT_WIDTH 8
#define HAVE_CONFIG_H
#include <pcre2.h>

#ifdef REGEX_DETERMINISTIC
static constexpr const char pattern[]
    = "^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\\-]"
      "+[a-zA-Z0-9])*[a-zA-"
      "Z0-9]*\\.(?:(?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\\.)*[a-zA-Z][a-zA-Z]+$";
#else
static constexpr const char pattern[] = "^[a-zA-Z0-9](?:[a-zA-Z0-9.!#$%&'*+\\/=?^_`{|}~\\-]*[a-zA-Z0-9])?"
                                        "@[a-zA-Z0-9](?:[a-zA-Z0-9\\-]*[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-"
                                        "Z0-9_\\-]*[a-zA-Z0-9])?)*\\.[a-zA-Z][a-zA-Z]+$";
#endif

pcre2_code* prepare_pattern() {
    int errornumber    = 0;
    size_t erroroffset = 0;
    auto re = pcre2_compile((PCRE2_SPTR8)pattern, PCRE2_ZERO_TERMINATED, 0, &errornumber, &erroroffset, NULL);

    if (re == nullptr) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset, buffer);
        return nullptr;
    }
    return re;
}

pcre2_code* prepare_jit_pattern() {
    auto re = prepare_pattern();
    if (pcre2_jit_compile(re, PCRE2_JIT_COMPLETE) == 0) return re;
    return nullptr;
}

pcre2_code* re     = prepare_pattern();
pcre2_code* re_jit = prepare_jit_pattern();

extern "C" bool match_pcre2(const char* mail) {
    size_t len = strlen(mail);
    auto data  = pcre2_match_data_create(1, nullptr);
    int rc     = pcre2_match(re, (PCRE2_SPTR8)mail, len, 0, 0, data, nullptr);
    pcre2_match_data_free(data);
    return rc == 1;
}

extern "C" bool match_jit_pcre2(const char* mail) {
    size_t len = strlen(mail);
    auto data  = pcre2_match_data_create(1, nullptr);
    int rc     = pcre2_jit_match(re_jit, (PCRE2_SPTR8)mail, len, 0, 0, data, nullptr);
    pcre2_match_data_free(data);
    return rc == 1;
}
