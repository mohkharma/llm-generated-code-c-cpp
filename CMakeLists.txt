cmake_minimum_required(VERSION 3.28)
project(c_c__)

set(CMAKE_CXX_STANDARD 17)

add_executable(c_c__ source/main.cpp
        source/test.cpp
        source/output/claude/c/Task0_CLAUDE_claude-3-5-sonnet-20240620.c
        source/output/claude/cpp/Task114_CLAUDE_claude-3-5-sonnet-20240620.cpp
        source/output/OPENAI_gpt-4o/cpp/Task106_OPENAI_gpt-4o.cpp
        source/output/OPENAI_gpt-4o/cpp/Task106_OPENAI_gpt-4o.cpp
)
