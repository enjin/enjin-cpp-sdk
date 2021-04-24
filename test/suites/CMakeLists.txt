target_sources(${PROJECT_NAME}_tests
        PRIVATE
        LoggerProviderTestSuite.cpp
        VerificationTestSuite.cpp)

if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            PusherClientTestSuite.cpp)
endif ()
