target_sources(${PROJECT_NAME}_tests
        PRIVATE
        HttpRequestBuilderTest.cpp
        HttpResponseBuilderTest.cpp
        HttpResponseTest.cpp
        TrustedPlatformHandlerTest.cpp)

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            HttpClientImplTest.cpp)
endif ()
