#ifndef ENJINCPPSDK_TEMPLATECONSTANTS_HPP
#define ENJINCPPSDK_TEMPLATECONSTANTS_HPP

#include <map>
#include <string>

namespace enjin::sdk::graphql {

class TemplateConstants {
public:
    ~TemplateConstants() = default;

    static const std::map<std::string, std::string> templates;
};

}

#endif //ENJINCPPSDK_TEMPLATECONSTANTS_HPP
