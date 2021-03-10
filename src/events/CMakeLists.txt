target_sources(${PROJECT_NAME}
        PRIVATE
        EventListenerRegistration.cpp
        EventTypeDef.cpp
        EventTypeDef.hpp
        PusherEventService.cpp)

add_subdirectory(channels)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        channels)
