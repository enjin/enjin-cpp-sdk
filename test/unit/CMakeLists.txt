target_sources(${PROJECT_NAME}_tests
        PRIVATE
        TrustedPlatformMiddlewareTest.cpp)

add_subdirectory(events)
add_subdirectory(graphql)
add_subdirectory(http)
add_subdirectory(models)
add_subdirectory(pusher)
add_subdirectory(schemas)
add_subdirectory(utils)
add_subdirectory(websockets)
