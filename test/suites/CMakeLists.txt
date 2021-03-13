target_sources(${PROJECT_NAME}_tests
        PRIVATE
        VerificationTestSuite.cpp)

if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            PusherClientTestSuite.cpp)
endif ()
