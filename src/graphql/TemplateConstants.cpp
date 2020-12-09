#include "TemplateConstants.hpp"

namespace enjin {
namespace sdk {
namespace graphql {

const std::map<std::string, std::string> TemplateConstants::templates = [] {
    std::map<std::string, std::string> templates;

    // BEGINNING OF GENERATED CONTENT
    /*[[[cog
    from templategenerator import generate


    templates = generate()
    for t in templates:
        cog.outl('templates.emplace("%s", "%s");' % (t[0], t[1]))
    ]]]*/
    //[[[end]]]
    // END OF GENERATED CONTENT

    return templates;
}();

} // namespace graphql
} // namespace sdk
} // namespace enjin
