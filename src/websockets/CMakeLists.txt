if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}
            PRIVATE
            WebsocketClient.cpp)
endif ()
