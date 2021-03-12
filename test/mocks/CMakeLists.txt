#[=[
Double frees exist in MockHttpServer.cpp and MockWebsocketServer.cpp as a result of:
- cpprestsdk (v2.10.18)
- ixwebsocket (v11.0.4)
#]=]

target_sources(${PROJECT_NAME}_tests
        PRIVATE
        MockEventListener.hpp
        MockHttpServer.cpp
        MockHttpServer.hpp
        MockSubscriptionEventListener.hpp
        MockWebSocketClientImpl.cpp
        MockWebSocketClientImpl.hpp
        MockWebsocketServer.cpp
        MockWebsocketServer.hpp)
