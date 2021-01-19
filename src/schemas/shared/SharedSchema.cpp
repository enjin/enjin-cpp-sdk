#include <enjinsdk/shared/SharedSchema.hpp>

namespace enjin::sdk::shared {

SharedSchema::SharedSchema(const enjin::sdk::TrustedPlatformMiddleware& middleware, const std::string& schema)
        : BaseSchema(middleware, schema) {
}

}
