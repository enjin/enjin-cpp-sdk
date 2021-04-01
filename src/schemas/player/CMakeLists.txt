target_sources(${PROJECT_NAME}
        PRIVATE
        PlayerSchema.cpp)

add_subdirectory(mutations)
add_subdirectory(queries)
