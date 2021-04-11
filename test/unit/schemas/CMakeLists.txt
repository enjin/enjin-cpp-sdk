target_sources(${PROJECT_NAME}_tests
        PRIVATE
        BaseSchemaTest.cpp)

if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            BaseSchemaHttpTest.cpp)
endif ()

add_subdirectory(player)
add_subdirectory(project)
add_subdirectory(shared)
