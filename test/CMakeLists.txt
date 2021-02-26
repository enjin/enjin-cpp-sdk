### Setup GoogleTest
if (NOT ENJINSDK_USING_CONAN)
    find_package(GTest CONFIG REQUIRED)
    if (${GTest_FOUND})
        list(APPEND ENJINSDK_TARGET_LIBRARIES
                GTest::gmock
                GTest::gtest
                GTest::gmock_main
                GTest::gtest_main)
        message(STATUS "Enjin: Gtest found")
    else ()
        configure_file(CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/googletest-download/CMakeLists.txt)
        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
        if (result)
            message(FATAL_ERROR "CMake step for googletest failed: ${result}")
        endif ()
        execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
        if (result)
            message(FATAL_ERROR "Build step for googletest failed: ${result}")
        endif ()

        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                EXCLUDE_FROM_ALL)

        list(APPEND ENJINSDK_TARGET_LIBRARIES gmock gtest gmock_main gtest_main)
    endif ()
endif ()
### GoogleTest setup done

add_subdirectory(mocks)
add_subdirectory(suites)
add_subdirectory(utils)
add_subdirectory(unit)
