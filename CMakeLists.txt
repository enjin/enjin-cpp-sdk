cmake_minimum_required(VERSION 3.17)
project(enjincppsdk CXX)

function(SET_INCLUDE_HTTP_CLIENT_IMPL)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${INCLUDE_HTTP_CLIENT_IMPL})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${INCLUDE_HTTP_CLIENT_IMPL})
    endif ()
endfunction()

function(SET_INCLUDE_WEBSOCKET_CLIENT_IMPL)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${INCLUDE_WEBSOCKET_CLIENT_IMPL})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${INCLUDE_WEBSOCKET_CLIENT_IMPL})
    endif ()
endfunction()

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    # TODO: Search manually for dependencies.
    message(WARNING "Enjin: The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

# Checks if HTTP client dependency was installed
if (true) # TODO: Check if cpprestsdk was installed.
    message("-- Enjin: Built-in HTTP client available for platform clients")
    set(INCLUDE_HTTP_CLIENT_IMPL 1)
else ()
    message(WARNING "Enjin: Built-in HTTP client not available for platform clients")
    set(INCLUDE_HTTP_CLIENT_IMPL 0)
endif ()

# Checks if websocket client dependency was installed
if (false) # TODO: Check if ixwebsocket was installed.
    message("-- Enjin: Built-in websocket client available for event services")
    set(INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
else ()
    message(WARNING "Enjin: Built-in websocket client not available for event services")
    set(INCLUDE_WEBSOCKET_CLIENT_IMPL 0)
endif ()

SET_INCLUDE_HTTP_CLIENT_IMPL()
SET_INCLUDE_WEBSOCKET_CLIENT_IMPL()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
add_test(NAME EnjinSDKTest COMMAND Test)
