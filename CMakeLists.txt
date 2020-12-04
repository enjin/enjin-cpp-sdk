cmake_minimum_required(VERSION 3.17)
project(enjincppsdk CXX)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_subdirectory(src)

include(GenerateExportHeader)
generate_export_header(enjinsdk)

enable_testing()
add_subdirectory(test)
add_test(NAME EnjinSDKTest COMMAND Test)
