target_sources(${PROJECT_NAME}_tests
        PRIVATE
        HttpResponseBuilderTest.cpp
        HttpResponseTest.cpp
        TrustedPlatformHandlerTest.cpp)

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            HttpClientTest.cpp)
endif ()
