include_directories(${ENJINCPPSDK_SOURCE_DIRECTORY}/src)

set(TEST_FILES
        graphql/GraphqlQueryRegistryTest.cpp
        graphql/GraphqlRequestTest.cpp
        utils/EnumUtilsTest.cpp
        utils/StringUtilsTest.cpp
)
add_executable(unittests ${TEST_FILES})
target_link_libraries(unittests
        PUBLIC
        enjinsdk
        PRIVATE
        ${CONAN_LIBS}
)
target_include_directories(
        unittests
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src/graphql
        ${PROJECT_SOURCE_DIR}/src/utils
)
