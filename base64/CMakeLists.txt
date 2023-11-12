add_library(Base64
    base64.cpp
    coder.cpp
    decoder.cpp
)

target_include_directories(Base64
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)