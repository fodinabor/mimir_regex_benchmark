cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project("benchmark_mail" CXX)

find_package(Thorin REQUIRED CONFIG)

if(NOT THORIN_TARGET_NAMESPACE)
    set(THORIN_TARGET_NAMESPACE "")
endif()

option(REGEX_COMPILE_TIME_BENCHMARK "Enable to run the relevant compilation commands with 'time' - see ReadMe.md" OFF)

if(REGEX_COMPILE_TIME_BENCHMARK)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_CUSTOM "${CMAKE_COMMAND} -E time")
endif()

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/thorin_match.o
                   COMMAND $<TARGET_FILE:${THORIN_TARGET_NAMESPACE}thorin> "${CMAKE_SOURCE_DIR}/match_mail.thorin" --output-ll "${CMAKE_BINARY_DIR}/thorin_match.ll" --aggr-lam-spec
                   COMMAND ${CMAKE_CXX_COMPILER} -O3 "${CMAKE_BINARY_DIR}/thorin_match.ll" -c -o "${CMAKE_BINARY_DIR}/thorin_match.o"
                   MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/match_mail.thorin"
                   BYPRODUCTS ${CMAKE_BINARY_DIR}/thorin_match.ll)

add_executable(${PROJECT_NAME}
    benchmark_mail.cpp
    ctre_match_mail.cpp
    pcre2_match_mail.cpp
    std_match_mail.cpp
    manual_match_mail.cpp
    ${CMAKE_BINARY_DIR}/thorin_match.o
)

target_include_directories(${PROJECT_NAME} PRIVATE compile-time-regular-expressions/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pcre2-8
)
