add_executable(${PROJECT_NAME}_tests "")

### Setup dependencies
if (${ENJINSDK_USING_CONAN})
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${CONAN_LIBS})
else ()
    include(CheckIncludeFiles)
    include(GNUInstallDirs)

    ###### GoogleTest setup start
    # Download and unpack GoogleTest at configure time
    configure_file(CMakeLists.txt.in "${CMAKE_CURRENT_BINARY_DIR}/googletest-download/CMakeLists.txt")
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download")
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download")
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add GoogleTest directly to the build
    add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
            "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
            EXCLUDE_FROM_ALL)

    target_link_libraries(${PROJECT_NAME}_tests
            PRIVATE
            gtest
            gmock
            gtest_main
            gmock_main)
    ###### GoogleTest setup end

    ###### HTTP client setup
    if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
        target_include_directories(${PROJECT_NAME}_tests PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})
    endif ()
    ######

    ###### Websocket client setup
    if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
        target_link_libraries(${PROJECT_NAME}_tests PRIVATE ixwebsocket::ixwebsocket)
    endif ()
    ######

    ###### RapidJson setup
    target_include_directories(${PROJECT_NAME}_tests PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
    ######
endif ()
### Dependencies setup done

target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
        ${PROJECT_NAME}
        ${PROJECT_NAME}_utils)
target_include_directories(${PROJECT_NAME}_tests
        PRIVATE
        "${PROJECT_BINARY_DIR}"
        "$<INSTALL_INTERFACE:include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include"
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/src/include")

add_subdirectory(mocks)
add_subdirectory(suites)
add_subdirectory(unit)
add_subdirectory(utils)

add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}_tests)
