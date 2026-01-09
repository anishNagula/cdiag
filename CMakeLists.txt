cmake_minimum_required(VERSION 3.16)
project(cdiag LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cdiag
    src/main.cpp
    src/cli/explain.cpp
    src/diagnostics/Parser.cpp
    src/diagnostics/Normalizer.cpp
    src/diagnostics/Grouping.cpp
    src/rules/BuiltinRules.cpp
    src/rules/RootCauseEngine.cpp
    src/output/Formatter.cpp
)

target_include_directories(cdiag PRIVATE src)
