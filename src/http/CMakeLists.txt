target_sources(${PROJECT_NAME}
        PRIVATE
        HttpRequest.cpp
        HttpResponse.cpp
        TrustedPlatformHandler.cpp)

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}
            PRIVATE
            HttpClient.cpp)
endif ()
