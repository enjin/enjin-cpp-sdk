cmake_minimum_required(VERSION 3.16)

include("cmake/enjinsdk_git_submodules.cmake")
include("cmake/enjinsdk_macros.cmake")
include(GenerateExportHeader)

####################################################################################################################
### Define project and set properties
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

# Attempt to setup Conan
if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup()

    if ("cpprestsdk" IN_LIST CONAN_DEPENDENCIES)
        set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 1)
    endif ()
    if ("ixwebsocket" IN_LIST CONAN_DEPENDENCIES)
        set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 1)
    endif ()

    set(ENJINSDK_USING_CONAN 1)
endif ()

# Setup output directories before creating any targets
setup_output_directories()

# Command to generate template constants
add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp"
        COMMAND template_generator "${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp" "${PROJECT_SOURCE_DIR}/src/graphql/templates"
        DEPENDS template_generator
        COMMENT "Generating TemplateConstants source file"
)

# Add supporting submodules, executables, and libraries
init_git_submodules()
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

    if (${ENJINSDK_ALLOW_DEFAULT_HTTP})
        include("cmake/enjinsdk_find_cpp_httplib.cmake")
    endif ()
    if (${ENJINSDK_ALLOW_DEFAULT_WEBSOCKET})
        include("cmake/enjinsdk_find_ixwebsocket.cmake")
    endif ()

    include("cmake/enjinsdk_find_rapidjson.cmake")
    include("cmake/enjinsdk_find_spdlog.cmake")

    ###### HTTP client setup
    if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
        target_include_directories(${PROJECT_NAME} PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})
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

target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_utils)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "$<INSTALL_INTERFACE:include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include")

add_subdirectory(src)

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
