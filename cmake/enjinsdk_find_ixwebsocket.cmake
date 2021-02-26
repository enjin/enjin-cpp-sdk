find_package(share CONFIG NAMES ixwebsocket)

if (${share_FOUND})
    list(APPEND ENJINSDK_TARGET_LIBRARIES ixwebsocket::ixwebsocket)
    set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
    message(STATUS "Enjin: Found ixwebsocket package")
else ()
    message(STATUS "Enjin: Did not find ixwebsocket package")
endif ()
