target_sources(${PROJECT_NAME}_tests
        PRIVATE
        ClientMiddlewareTest.cpp)

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            ProjectClientReauthenticateTest.cpp)
endif ()

add_subdirectory(events)
add_subdirectory(graphql)
add_subdirectory(http)
add_subdirectory(models)
add_subdirectory(pusher)
add_subdirectory(schemas)
add_subdirectory(utils)
add_subdirectory(websockets)
