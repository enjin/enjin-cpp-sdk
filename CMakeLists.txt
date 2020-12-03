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
add_subdirectory(include)

enable_testing()
set(TEST_FILES ./test/unit/graphql/GraphqlTemplateTest.cpp ./test/unit/utils/EnumUtilsTest.cpp ./test/unit/utils/StringUtilsTest.cpp)
add_executable(tests ${TEST_FILES})
target_link_libraries(tests PRIVATE src ${CONAN_LIBS})
target_include_directories(
        tests
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/graphql
        ${CMAKE_CURRENT_LIST_DIR}/src/utils
)
add_test(NAME tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND tests
)
