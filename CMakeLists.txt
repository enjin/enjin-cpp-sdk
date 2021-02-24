cmake_minimum_required(VERSION 3.17)
project(enjincppsdk CXX)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    # TODO: Search manually for dependencies.
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

if(true) # TODO: Check if cpprestsdk was installed.
    # TODO: Set preprocessor macro to 'true'.
    add_compile_definitions(WITH_CPPRESTSDK=true)
else()
    # TODO: Set preprocessor macro to 'false'.
    message(WARNING "CPP-Rest-SDK not found")
    add_compile_definitions(WITH_CPPRESTSDK=false)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
add_test(NAME EnjinSDKTest COMMAND Test)
