target_sources(${PROJECT_NAME}
        PRIVATE
        SharedSchema.cpp)

add_subdirectory(arguments)
add_subdirectory(mutations)
add_subdirectory(queries)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        arguments
        mutations
        queries)
