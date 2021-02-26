cmake_minimum_required(VERSION 3.17)
project(enjincppsdk CXX)

set(ENJINSDK_VERSION_MAJOR 1)
set(ENJINSDK_VERSION_MINOR 0)
set(ENJINSDK_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(ENJINSDK_TARGET_DIRECTORIES)
set(ENJINSDK_TARGET_LIBRARIES)
set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0)
set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0)

function(set_include_http_client_impl)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    endif ()

    if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
        message(STATUS "Enjin: Built-in HTTP client available for platform clients")
    else ()
        message(STATUS "Enjin: Built-in HTTP client not available for platform clients")
    endif ()
endfunction()

function(set_include_websocket_client_impl)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    endif ()

    if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
        message(STATUS "Enjin: Built-in websocket client available for event services")
        set(INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
    else ()
        message(STATUS "Enjin: Built-in websocket client not available for event services")
        set(INCLUDE_WEBSOCKET_CLIENT_IMPL 0)
    endif ()
endfunction()

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
    set(ENJINSDK_USING_CONAN 1)
    set(ENJINSDK_TARGET_LIBRARIES ${CONAN_LIBS})

    # TODO: Check if these dependencies were included.
    set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 1)
    set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
else ()
    set(ENJINSDK_USING_CONAN 0)
    include(cmake/enjinsdk_find_cpprestsdk.cmake)
    include(cmake/enjinsdk_find_ixwebsocket.cmake)
    include(cmake/enjinsdk_find_rapidjson.cmake)
    include(CheckIncludeFiles)
    include(GNUInstallDirs)
endif ()

set_include_http_client_impl()
set_include_websocket_client_impl()

add_subdirectory(src)

# TODO: Until issues with linking GTest manually are resolved, only allow unit tests if GTest is imported using conan.
if (ENJINSDK_USING_CONAN) # TODO: Check if tests should be enabled.
    enable_testing()
    add_subdirectory(test)
endif ()
