#!/bin/bash

set -x

rm *.ll *.o

time mimir/build/bin/mim match_mail.mim --output-ll mim_match.ll --aggr-lam-spec
time /usr/bin/clang++ -O3 mim_match.ll -c -o mim_match.o
time /usr/bin/clang++ -std=c++20 -O3 ctre_match_mail.cpp -c -o ctre_match.o -I../compile-time-regular-expressions/include
time /usr/bin/clang++ -std=c++20 -O3 std_match_mail.cpp -c -o std_match.o
time /usr/bin/clang++ -std=c++20 -O3 pcre2_match_mail.cpp -c -o pcre2_match.o
time /usr/bin/clang++ -std=c++20 -O3 manual_match_mail.cpp -c -o manual_match_mail.o
clang++ -std=c++20 -O3 benchmark_mail.cpp mim_match.o ctre_match.o std_match.o pcre2_match.o manual_match_mail.o -lpcre2-8 -o benchmark_mail

# shows signs of measuring code loading or sth weird like that, so execute twice..
./benchmark_mail &> /dev/null
./benchmark_mail
