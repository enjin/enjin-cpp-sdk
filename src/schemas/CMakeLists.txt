target_sources(${PROJECT_NAME}
        PRIVATE
        BaseSchema.cpp)

add_subdirectory(player)
add_subdirectory(project)
add_subdirectory(shared)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        player
        project
        shared)
