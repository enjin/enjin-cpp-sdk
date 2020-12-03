#ifndef ENJINCPPSDK_ENUMUTILS_HPP
#define ENJINCPPSDK_ENUMUTILS_HPP

#include "GraphqlTemplate.hpp"
#include <string>

namespace enjin {
    namespace sdk {
        namespace utils {
            std::string get_name(enjin::sdk::graphql::TemplateType e);
        }
    }
}

#endif //ENJINCPPSDK_ENUMUTILS_HPP
