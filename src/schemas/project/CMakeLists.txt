target_sources(${PROJECT_NAME}
        PRIVATE
        ProjectSchema.cpp)

add_subdirectory(arguments)
add_subdirectory(mutations)
add_subdirectory(queries)
