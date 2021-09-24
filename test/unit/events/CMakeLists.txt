target_sources(${PROJECT_NAME}_tests
        PRIVATE
        AssetChannelTest.cpp
        EventListenerRegistrationTest.cpp
        EventTypeDefTest.cpp
        PlayerChannelTest.cpp
        ProjectChannelTest.cpp
        PusherEventListenerTest.cpp
        PusherEventServiceTest.cpp
        RegistrationListenerConfigurationTest.cpp
        WalletChannelTest.cpp)

if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            PusherEventServiceWebsocketTest.cpp)
endif ()
