#[=[
Double frees exist in MockWebsocketServer.cpp as a result of:
- ixwebsocket (v11.0.4)
#]=]

target_sources(${PROJECT_NAME}_tests
        PRIVATE
        FakeGraphqlRequest.cpp)

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            MockHttpServer.cpp)
endif ()

if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            FakeWebSocketClient.cpp
            MockWebsocketServer.cpp)
endif ()
