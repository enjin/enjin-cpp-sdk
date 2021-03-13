#[=[
Double frees exist in MockHttpServer.cpp and MockWebsocketServer.cpp as a result of:
- cpprestsdk (v2.10.18)
- ixwebsocket (v11.0.4)
#]=]

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            MockHttpServer.cpp)
endif ()

if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            MockWebSocketClientImpl.cpp
            MockWebsocketServer.cpp)
endif ()
