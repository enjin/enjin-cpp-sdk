#include "enjinsdk/player/PlayerSchema.hpp"

namespace enjin::sdk::player {

PlayerSchema::PlayerSchema(const TrustedPlatformMiddleware& middleware, const std::string& schema)
        : BaseSchema(middleware, schema) {
}

}
