#include "enjinsdk/project/ProjectSchema.hpp"

namespace enjin::sdk::project {

ProjectSchema::ProjectSchema(const TrustedPlatformMiddleware& middleware, const std::string& schema)
        : BaseSchema(middleware, schema) {
}

}
