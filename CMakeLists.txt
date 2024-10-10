cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project("benchmark_mail" CXX)

find_package(Mim REQUIRED CONFIG)

if(NOT MIM_TARGET_NAMESPACE)
    set(MIM_TARGET_NAMESPACE "")
endif()

option(REGEX_COMPILE_TIME_BENCHMARK "Enable to run the relevant compilation commands with 'time' - see ReadMe.md" OFF)

if(REGEX_COMPILE_TIME_BENCHMARK)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_CUSTOM "${CMAKE_COMMAND} -E time")
endif()

option(REGEX_DETERMINISTIC "Enable to select the deterministic benchmark regex" ON)

if(REGEX_DETERMINISTIC)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mim_match.o
                    COMMAND $<TARGET_FILE:${MIM_TARGET_NAMESPACE}mim> "${CMAKE_SOURCE_DIR}/match_mail.mim" --output-ll "${CMAKE_CURRENT_BINARY_DIR}/mim_match.ll" --aggr-lam-spec
                    COMMAND ${CMAKE_CXX_COMPILER} -O3 -c "${CMAKE_CURRENT_BINARY_DIR}/mim_match.ll" -o "${CMAKE_CURRENT_BINARY_DIR}/mim_match.o"
                    MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/match_mail.mim"
                    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/mim_match.ll)
    set(MIM_MATCH_FILE ${CMAKE_CURRENT_BINARY_DIR}/mim_match.o)
else()
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mim_match_nondet.o
                    COMMAND $<TARGET_FILE:${MIM_TARGET_NAMESPACE}mim> "${CMAKE_SOURCE_DIR}/match_mail_nondet.mim" --output-ll "${CMAKE_CURRENT_BINARY_DIR}/mim_match_nondet.ll" --aggr-lam-spec
                    COMMAND ${CMAKE_CXX_COMPILER} -O3 -c "${CMAKE_CURRENT_BINARY_DIR}/mim_match_nondet.ll" -o "${CMAKE_CURRENT_BINARY_DIR}/mim_match_nondet.o"
                    MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/match_mail_nondet.mim"
                    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/mim_match_nondet.ll)
    set(MIM_MATCH_FILE ${CMAKE_CURRENT_BINARY_DIR}/mim_match_nondet.o)
endif()

add_library(matchers STATIC
    ctre_match_mail.cpp
    pcre2_match_mail.cpp
    std_match_mail.cpp
    manual_match_mail.cpp
    ${MIM_MATCH_FILE}
)
target_include_directories(matchers PRIVATE compile-time-regular-expressions/include)

add_executable(${PROJECT_NAME}
    benchmark_mail.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pcre2-8
    matchers
)

if(REGEX_DETERMINISTIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DREGEX_DETERMINISTIC
    )
endif()

add_executable(eval
    eval.cpp
)

target_link_libraries(eval PRIVATE
    pcre2-8
    matchers
)

if(REGEX_DETERMINISTIC)
    target_compile_definitions(eval PRIVATE
        -DREGEX_DETERMINISTIC
    )
endif()

set_target_properties(eval PROPERTIES COMPILE_FLAGS "-fno-omit-frame-pointer -fsanitize=address")
set_target_properties(eval PROPERTIES LINK_FLAGS " -fno-omit-frame-pointer -fsanitize=address")
