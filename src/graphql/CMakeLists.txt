target_sources(${PROJECT_NAME}
        PRIVATE
        AbstractGraphqlRequest.cpp
        AbstractGraphqlResponse.cpp
        GraphqlError.cpp
        GraphqlQueryRegistry.cpp
        GraphqlResponseUtils.cpp
        TemplateConstants.cpp
        TemplateConstants.hpp) # TODO: Move TemplateConstants.hpp to 'src/include' directory.
