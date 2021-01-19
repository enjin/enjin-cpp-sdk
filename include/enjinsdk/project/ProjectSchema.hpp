#ifndef ENJINCPPSDK_PROJECTSCHEMA_HPP
#define ENJINCPPSDK_PROJECTSCHEMA_HPP

#include "enjinsdk/BaseSchema.hpp"
#include "enjinsdk/project/IProjectSchema.hpp"
#include <string>

namespace enjin::sdk::project {

class ProjectSchema : public IProjectSchema,
        public BaseSchema {
protected:
    ProjectSchema(const enjin::sdk::TrustedPlatformMiddleware& middleware, const std::string& schema);
};

}

#endif //ENJINCPPSDK_PROJECTSCHEMA_HPP
