add_library(${PROJECT_NAME}_utils STATIC "")
set_property(TARGET ${PROJECT_NAME}_utils PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME}_utils
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)

add_subdirectory(src)
