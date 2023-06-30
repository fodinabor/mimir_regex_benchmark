# Thorin2 E-Mail Address RegEx Benchmark

This repo contains benchmarks comparing Thorin2's regex dialect performance against, [CTRE](https://github.com/hanickadot/compile-time-regular-expressions), [PCRE2](pcre.org) and `std::regex`.

The common theme is to match e-mail addresses harvested from a spam e-mail dataset (https://www.kaggle.com/datasets/rtatman/fraudulent-email-corpus).
The to-be-matched regex is:
`^[a-zA-Z0-9](?:[a-zA-Z0-9]*[._\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*@[a-zA-Z0-9](?:[a-zA-Z0-9]*[_\-]+[a-zA-Z0-9])*[a-zA-Z0-9]*\.(?:(?:[a-zA-Z0-9]*[_\-]+[a-zA-Z0-9])*[a-zA-Z0-9]+\.)*[a-zA-Z][a-zA-Z]+$`

## Setup
### Requirements
- GCC >=11
- Clang
- PCRE2 (8-bit lib, tested with version 10.42)

### Init Submodules & Build
```sh
git submodule update --init --recursive
mkdir -p build && mkdir -p thorin2/build && cd thorin2/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DTHORIN_BUILD_TESTING=OFF -DTHORIN_INSTALL_DEPENDENCIES=ON -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=`pwd`/install
make -j`nproc` install
cd ../../build
cmake .. -DCMAKE_BUILD_TYPE=Release -DThorin_DIR=`pwd`/../thorin2/build/install/lib/cmake/thorin -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
make -j`nproc`
```

### Dataset
To prepare the dataset, run the following in the project root:
```sh
grep -oE "[a-zA-Z0-9_.\-]+@[a-zA-Z0-9_.\-]+" fradulent_emails.txt > addresses.txt
python3 annotate_matched.py
```

## Benchmark
To run the benchmark, provide the benchmark executable with the path to the dataset file:
```sh
./build/benchmark_mail annotated.txt 2> full_results.csv
```

## Compile-time benchmark
For compile-time benchmarking, add `-DREGEX_COMPILE_TIME_BENCHMARK=ON` and ensure that you do not hit any caches, such as `ccache`.
One way to do so is using the full path to your clang, usually: `/usr/bin/clang++`.
Also note, that with CMake, there's a rather high overhead. You might want to run `make clean; make -n | grep -E "(clang++|bin/thorin)" | sed "s/^/time /" | bash --verbose` instead.
Note, for some reason, this unnecessarily compiles the Thorin2 thing twice. That's a build-system issue, not a Thorin limitation.
