#[=[
Double frees exist in MockHttpServer.cpp and MockWebsocketServer.cpp as a result of:
- cpprestsdk (v2.10.18)
- ixwebsocket (v11.0.4)
#]=]

target_sources(${PROJECT_NAME}_tests
        PRIVATE
        MockHttpServer.cpp
        MockWebSocketClientImpl.cpp
        MockWebsocketServer.cpp)
