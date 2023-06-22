extern "C" bool match_manual(const char* mail) {
    // ^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*\\.(?:(?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\\.)*[a-zA-Z][a-zA-Z]+$
    char tmp;
    const char* group;
    const char* inner_group;

    // [a-zA-Z0-9]
    tmp = *mail;
    if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) return false;
    ++mail;

    group = mail;
    // (?:[a-zA-Z0-9]*[._\\-]+[a-zA-Z0-9])*
    while (*mail) {
        tmp = *mail;
        while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9')) {
            ++mail;
            tmp = *mail;
        }
        if (!(tmp == '.' || tmp == '_' || tmp == '-')) break;
        ++mail;
        tmp = *mail;
        while (tmp == '.' || tmp == '_' || tmp == '-') {
            ++mail;
            tmp = *mail;
        }
        tmp = *mail;
        if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) break;
        ++mail;
        group = mail;
    }
    mail = group;
    tmp  = *mail;

    // [a-zA-Z0-9]*
    while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9')) {
        ++mail;
        tmp = *mail;
    }

    // @
    if (*mail != '@') return false;
    ++mail;

    // [a-zA-Z0-9]
    tmp = *mail;
    if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) return false;
    ++mail;

    // (?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])
    group = mail;
    while (*mail) {
        tmp = *mail;
        while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9')) {
            ++mail;
            tmp = *mail;
        }
        if (!(tmp == '_' || tmp == '-')) break;
        ++mail;
        tmp = *mail;
        if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) break;
        ++mail;
        group = mail;
    }

    mail = group;

    // [a-zA-Z0-9]*
    tmp = *mail;
    while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9')) {
        ++mail;
        tmp = *mail;
    }

    // \.
    if (*mail != '.') return false;
    ++mail;

    // (?:(?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\\.)*
    group = mail;
    while (*mail) {
        // (?:[a-zA-Z0-9]*[_\\-]+[a-zA-Z0-9])
        inner_group = mail;
        while (*mail) {
            tmp = *mail;
            while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9')) {
                ++mail;
                tmp = *mail;
            }
            if (!(tmp == '_' || tmp == '-')) break;
            ++mail;
            tmp = *mail;
            if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) break;
            ++mail;
            inner_group = mail;
        }
        mail = inner_group;

        // [a-zA-Z0-9]+
        tmp = *mail;
        if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9'))) break;
        ++mail;

        tmp = *mail;
        while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= '0' && tmp <= '9')) {
            ++mail;
            tmp = *mail;
        }

        // \.
        if (*mail != '.') break;
        ++mail;

        group = mail;
    }

    mail = group;

    // [a-zA-Z][a-zA-Z]+$
    tmp = *mail;
    if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z'))) return false;
    ++mail;
    tmp = *mail;
    if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z'))) return false;
    ++mail;
    tmp = *mail;
    while ((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) {
        ++mail;
        tmp = *mail;
    }
    return *mail == '\0';
}
