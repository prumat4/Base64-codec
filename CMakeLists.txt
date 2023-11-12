cmake_minimum_required(VERSION 3.12)
project(Base64)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(base64)

add_executable(main
    main.cpp
)

target_link_libraries(main
Base64
)