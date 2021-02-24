cmake_minimum_required(VERSION 3.17)
project(enjincppsdk CXX)

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    # TODO: Search manually for dependencies.
    message(WARNING "Enjin: The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

if (true) # TODO: Check if cpprestsdk was installed.
    message("-- Enjin: Built-in HTTP client available for platform clients")

    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=1)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_definitions(-D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=1)
    endif ()
else ()
    message(WARNING "Enjin: Built-in HTTP client not available for platform clients")

    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=0)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_definitions(-D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=0)
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
add_test(NAME EnjinSDKTest COMMAND Test)
