cmake_minimum_required(VERSION 3.16)
project(enjinsdk
        LANGUAGES CXX
        VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0)
set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0)
set(ENJINSDK_USING_CONAN 0)

option(ENJINSDK_ALLOW_DEFAULT_HTTP "ENJINSDK_ALLOW_DEFAULT_HTTP" OFF)
option(ENJINSDK_ALLOW_DEFAULT_WEBSOCKET "ENJINSDK_ALLOW_DEFAULT_WEBSOCKET" OFF)

### Setup output directories start
message(STATUS "Setting up output directories")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
### Setup output directories end

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

macro(set_include_http_client_impl_macro)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
    endif ()

    if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
        message(STATUS "Enjin: Built-in HTTP client available for platform clients")
    else ()
        message(STATUS "Enjin: Built-in HTTP client not available for platform clients")
    endif ()
endmacro()

macro(set_include_websocket_client_impl_macro)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
    endif ()

    if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
        message(STATUS "Enjin: Built-in websocket client available for event services")
    else ()
        message(STATUS "Enjin: Built-in websocket client not available for event services")
    endif ()
endmacro()

macro(set_version_macro)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_definitions(/D ENJINSDK_VERSION="\\"${PROJECT_VERSION}\\"")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_definitions(-D ENJINSDK_VERSION="\\"${PROJECT_VERSION}\\"")
    endif ()
endmacro()

function(install_headers_in_rel_path path rel_path)
    file(GLOB _children "${path}/${rel_path}/*")

    foreach (_child ${_children})
        if (IS_DIRECTORY ${_child})
            get_filename_component(_subdir ${_child} NAME)
            install_headers_in_rel_path("${path}" "${rel_path}/${_subdir}")
            continue()
        endif ()

        get_filename_component(_ext ${_child} EXT)
        if (_ext STREQUAL ".h" OR _ext STREQUAL ".hpp")
            install(FILES "${_child}" DESTINATION "${rel_path}") # Install the header file in its relative path
        endif ()
    endforeach ()
endfunction()

# Attempt to setup Conan
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    if ("cpprestsdk" IN_LIST CONAN_DEPENDENCIES)
        set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 1)
    endif ()
    if ("ixwebsocket" IN_LIST CONAN_DEPENDENCIES)
        set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
    endif ()

    set(ENJINSDK_USING_CONAN 1)
endif ()

# Command to generate template constants
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp
        COMMAND template_generator ${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp ${PROJECT_SOURCE_DIR}/src/graphql/templates
        DEPENDS template_generator
        COMMENT "Generating generated file"
)

# Add supporting executables and libraries
add_subdirectory(utils)
add_subdirectory(scripts)

add_library(${PROJECT_NAME} SHARED "")
add_dependencies(${PROJECT_NAME} template_generator)
generate_export_header(${PROJECT_NAME})

# Set SDK properties
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 2)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION 2)
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)

# Dependency setup
if (${ENJINSDK_USING_CONAN})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})
else ()
    include(CheckIncludeFiles)
    include(GNUInstallDirs)

    if (${ENJINSDK_ALLOW_DEFAULT_HTTP})
        include(cmake/enjinsdk_find_cpprestsdk.cmake)
    endif ()
    if (${ENJINSDK_ALLOW_DEFAULT_WEBSOCKET})
        include(cmake/enjinsdk_find_ixwebsocket.cmake)
    endif ()

    include(cmake/enjinsdk_find_rapidjson.cmake)
    include(cmake/enjinsdk_find_spdlog.cmake)

    ###### HTTP client setup
    if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
        target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)
    endif ()
    ######

    ###### Websocket client setup
    if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
        target_link_libraries(${PROJECT_NAME} PRIVATE ixwebsocket::ixwebsocket)
    endif ()
    ######

    ###### RapidJson setup
    target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
    ######

    ###### SpdLog setup
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
    ######
endif ()

# Call macros to set preprocessor directives
set_include_http_client_impl_macro()
set_include_websocket_client_impl_macro()
set_version_macro()

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_utils)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include)

add_subdirectory(src)

# Install and export package
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION include/${PROJECT_NAME})
install_headers_in_rel_path("${PROJECT_SOURCE_DIR}" "include")
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION share/${PROJECT_NAME})
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY SameMajorVersion)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION share/${PROJECT_NAME})
export(EXPORT ${PROJECT_NAME}Targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${PROJECT_NAME}::)

# Setup tests
if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    include(CTest)

    if (${BUILD_TESTING})
        enable_testing()
        add_subdirectory(test)
    endif ()
endif ()

unset(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL)
unset(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL)
unset(ENJINSDK_USING_CONAN)
unset(ENJINSDK_ALLOW_DEFAULT_HTTP CACHE)
unset(ENJINSDK_ALLOW_DEFAULT_WEBSOCKET CACHE)
