cmake_minimum_required(VERSION 4.0)

add_executable(scratch)

target_sources(scratch PRIVATE
    main.cpp
    curlWrappers/curlRequestWrapper.cpp

    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS curlWrappers
)

target_compile_options(scratch PRIVATE
    -O0
    -g3
    -fsanitize=address
    -fsanitize=undefined
)

target_link_options(scratch PRIVATE
    -fsanitize=address
    -fsanitize=undefined
)

find_package(CURL)

target_link_libraries(scratch PRIVATE CURL::libcurl)

