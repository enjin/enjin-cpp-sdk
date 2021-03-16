find_package(share CONFIG NAMES ixwebsocket)

if (${share_FOUND})
    set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
    message(STATUS "Enjin: Found ixwebsocket package")
else ()
    message(STATUS "Enjin: Did not find ixwebsocket package")
endif ()
