#cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 3.28)
project(cpp)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
include_directories(/home/kali/.vcpkg-clion/vcpkg/installed/x64-linux/include/)
include_directories(/home/kali/CLionProjects/mysql-connector-cpp/driver/)
include_directories(/home/kali/workingDirectory/programs/clion-2024.1.4/jbr/include/linux/ /home/kali/workingDirectory/programs/clion-2024.1.4/jbr/include/)
#include_directories(/usr/include/)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(cpprestsdk REQUIRED)
#target_link_libraries(main PRIVATE cpprestsdk::cpprest)

find_package(httplib CONFIG REQUIRED)
find_package(bson-1.0 CONFIG REQUIRED)
#target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)
add_executable(a1
        tests/llama-3/Task30_Test.cpp
)
