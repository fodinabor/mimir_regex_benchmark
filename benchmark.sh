#!/bin/bash

set -x

rm *.ll *.o

time thorin2/build/bin/thorin match_mail.thorin --output-ll thorin_match.ll --aggr-lam-spec
time /usr/bin/clang++ -O3 thorin_match.ll -c -o thorin_match.o
time /usr/bin/clang++ -std=c++20 -O3 ctre_match_mail.cpp -c -o ctre_match.o -I../compile-time-regular-expressions/include
time /usr/bin/clang++ -std=c++20 -O3 std_match_mail.cpp -c -o std_match.o -I../compile-time-regular-expressions/include
time /usr/bin/clang++ -std=c++20 -O3 pcre2_match_mail.cpp -c -o pcre2_match.o -I../compile-time-regular-expressions/include
clang++ -std=c++20 -O3 benchmark_mail.cpp thorin_match.o ctre_match.o std_match.o pcre2_match.o -lpcre2-8 -o benchmark_mail

# shows signs of measuring code loading or sth weird like that, so execute twice..
./benchmark_mail &> /dev/null
./benchmark_mail
