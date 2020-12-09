file(GLOB HEADERS_ENJINSDK "${PROJECT_SOURCE_DIR}/include/enjinsdk/*.hpp")
source_group("Header Files\\enjinsdk" FILES ${HEADERS_ENJINSDK})

set(SOURCE_FILES
        ${HEADERS_ENJINSDK}
        graphql/TemplateConstants.cpp
        graphql/TemplateConstants.hpp
        utils/EnumUtils.cpp
        utils/EnumUtils.hpp
        utils/StringUtils.cpp
        utils/StringUtils.hpp
)

add_library(enjinsdk ${SOURCE_FILES})
target_include_directories(enjinsdk
        PUBLIC
        $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/graphql
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
