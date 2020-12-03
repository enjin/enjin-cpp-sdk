add_library(
        src
        graphql/GraphqlTemplate.cpp
        utils/EnumUtils.cpp
        utils/StringUtils.cpp
)

target_include_directories(
        src
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/graphql
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
