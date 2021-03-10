target_sources(${PROJECT_NAME}
        PRIVATE
        PlayerClient.cpp
        ProjectClient.cpp
        TrustedPlatformMiddleware.cpp)

add_subdirectory(events)
add_subdirectory(graphql)
add_subdirectory(http)
add_subdirectory(models)
add_subdirectory(pusher)
add_subdirectory(schemas)
add_subdirectory(utils)
add_subdirectory(websockets)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        events
        graphql
        http
        models
        pusher
        schemas
        utils
        websockets)
