cmake_minimum_required(VERSION 3.16)

include("cmake/enjinsdk_macros.cmake")
include(GenerateExportHeader)

####################################################################################################################
### Define project and set properties
project(enjinsdk
        LANGUAGES CXX
        VERSION 1.0.0.1001)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 0)
set(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0)
set(ENJINSDK_USING_CONAN 0)

option(ENJINSDK_BUILD_SHARED "ENJINSDK_BUILD_SHARED" OFF)
option(ENJINSDK_BUILD_TESTS "ENJINSDK_BUILD_TESTS" OFF)
option(ENJINSDK_BUILD_DEFAULT_HTTP "ENJINSDK_BUILD_DEFAULT_HTTP" OFF)
option(ENJINSDK_BUILD_DEFAULT_WEBSOCKET "ENJINSDK_BUILD_DEFAULT_WEBSOCKET" OFF)

# Attempt to setup Conan
if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup()

    if ("cpp-httplib" IN_LIST CONAN_DEPENDENCIES)
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

# Add supporting executables and libraries
add_subdirectory(utils)
add_subdirectory(scripts)

# Create the SDK target
if (${ENJINSDK_BUILD_SHARED})
    message(STATUS "Enjin: Building SDK as shared library")
    add_library(${PROJECT_NAME} SHARED "")
else ()
    message(STATUS "Enjin: Building SDK as static library")
    add_library(${PROJECT_NAME} STATIC "")
endif ()

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} template_generator)
generate_export_header(${PROJECT_NAME})

# Sets compiler specific flags
if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
    elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
        target_compile_options(${PROJECT_NAME} PRIVATE
                /EHsc /MTd /W2 /c /D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
        target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_EXPORTS)
    endif ()
endif ()

# Set SDK properties
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 2)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION 2)
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)

####################################################################################################################
### Link dependencies
if (${ENJINSDK_USING_CONAN})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})
else ()
    include(CheckIncludeFiles)

    ###### HTTP client setup
    if (${ENJINSDK_BUILD_DEFAULT_HTTP})
        include("cmake/enjinsdk_find_openssl.cmake")
        include("cmake/enjinsdk_find_cpp_httplib.cmake")
        if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
            target_link_libraries(${PROJECT_NAME} PRIVATE
                    OpenSSL::SSL
                    OpenSSL::Crypto)
            target_include_directories(${PROJECT_NAME} PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})
        endif ()
    endif ()
    ######

    ###### Websocket client setup
    if (${ENJINSDK_BUILD_DEFAULT_WEBSOCKET})
        include("cmake/enjinsdk_find_ixwebsocket.cmake")
        if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
            target_link_libraries(${PROJECT_NAME} PRIVATE ixwebsocket::ixwebsocket)
        endif ()
    endif ()
    ######

    ###### RapidJson setup
    include("cmake/enjinsdk_find_rapidjson.cmake")
    target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
    ######

    ###### SpdLog setup
    include("cmake/enjinsdk_find_spdlog.cmake")
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
    ######
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_utils)

# Call macros to set preprocessor directives
set_include_http_client_impl_macro()
set_include_websocket_client_impl_macro()
set_version_macro()

####################################################################################################################
### Target sources
target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/TemplateConstants.cpp")
target_include_directories(${PROJECT_NAME}
        PUBLIC
        "$<INSTALL_INTERFACE:include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include")

add_subdirectory(src)

####################################################################################################################
### Install library and export package
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_utils
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}")

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}")

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}")

# Exports target from build tree
export(EXPORT ${PROJECT_NAME}
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.cmake"
        NAMESPACE ${PROJECT_NAME}::)

####################################################################################################################
### Setup tests
include(CTest)

if (${BUILD_TESTING} AND ${ENJINSDK_BUILD_TESTS})
    message(STATUS "Enjin: Building tests")

    enable_testing()
    add_subdirectory(test)
endif ()

####################################################################################################################
### Unset variables
unset(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL)
unset(ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL)
unset(ENJINSDK_USING_CONAN)
unset(ENJINSDK_BUILD_SHARED CACHE)
unset(ENJINSDK_BUILD_TESTS CACHE)
unset(ENJINSDK_BUILD_DEFAULT_HTTP CACHE)
unset(ENJINSDK_BUILD_DEFAULT_WEBSOCKET CACHE)
