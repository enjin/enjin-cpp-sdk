if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            BaseSchemaTest.cpp)
endif ()

add_subdirectory(project)
add_subdirectory(shared)
