file(GLOB HEADERS_ENJINSDK
        "${PROJECT_SOURCE_DIR}/include/enjinsdk/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/enjinsdk/*/*.hpp")
source_group("Header Files\\enjinsdk" FILES ${HEADERS_ENJINSDK})

set(SOURCE_FILES
        ${HEADERS_ENJINSDK}
        TrustedPlatformMiddleware.cpp
        graphql/AbstractGraphqlResponse.cpp
        graphql/GraphqlError.cpp
        graphql/GraphqlQueryRegistry.cpp
        graphql/TemplateConstants.cpp
        graphql/TemplateConstants.hpp
        http/AbstractHttpClient.cpp
        http/HttpClientImpl.cpp
        http/HttpClientImpl.hpp
        http/HttpRequest.cpp
        http/HttpResponse.cpp
        models/AccessToken.cpp
        models/Balance.cpp
        models/PaginationCursor.cpp
        models/Player.cpp
        models/Project.cpp
        models/Request.cpp
        models/Token.cpp
        models/TokenConfigData.cpp
        models/TokenStateData.cpp
        models/TokenTransferFeeSettings.cpp
        models/TokenVariant.cpp
        models/Wallet.cpp
        schemas/BaseSchema.cpp
        utils/EnumUtils.cpp
        utils/EnumUtils.hpp
        utils/RapidJsonUtils.cpp
        utils/RapidJsonUtils.hpp
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
