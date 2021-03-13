target_sources(${PROJECT_NAME}_tests
        PRIVATE
        PusherEventTest.cpp)

if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            PusherClientReconnectTest.cpp
            PusherClientTest.cpp)
endif ()
