cmake_minimum_required(VERSION 3.10)

project(PacketInspector
    VERSION 0.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(packet_inspector 
    ./src/main.cpp
    ./src/logging.hpp
    ./src/settings.cpp
    ./src/settings.hpp
    ./src/capture_device.hpp
    ./src/capture_device.cpp
    ./src/packet.hpp
    ./src/packet.cpp
    ./src/packet_reader.hpp
    ./src/packet_reader.cpp
    ./src/packet_parser.hpp
    ./src/packet_parser.cpp
    ./src/helper.hpp
    ./src/helper.cpp
)

target_link_libraries(packet_inspector pcap)
