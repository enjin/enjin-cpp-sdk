target_sources(${PROJECT_NAME}
        PRIVATE
        EventListenerRegistration.cpp
        EventTypeDef.cpp
        PusherEventListener.cpp
        PusherEventService.cpp)

add_subdirectory(channels)
