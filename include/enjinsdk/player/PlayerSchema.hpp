#ifndef ENJINCPPSDK_PLAYERSCHEMA_HPP
#define ENJINCPPSDK_PLAYERSCHEMA_HPP

#include "enjinsdk/BaseSchema.hpp"
#include "enjinsdk/player/IPlayerSchema.hpp"
#include <string>

namespace enjin::sdk::player {

class PlayerSchema : public IPlayerSchema,
                     public BaseSchema {
protected:
    PlayerSchema(const enjin::sdk::TrustedPlatformMiddleware& middleware, const std::string& schema);
};

}

#endif //ENJINCPPSDK_PLAYERSCHEMA_HPP
