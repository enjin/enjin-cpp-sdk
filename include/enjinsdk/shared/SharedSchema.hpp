#ifndef ENJINCPPSDK_SHAREDSCHEMA_HPP
#define ENJINCPPSDK_SHAREDSCHEMA_HPP

#include "enjinsdk/BaseSchema.hpp"
#include "enjinsdk/shared/ISharedSchema.hpp"
#include <string>

namespace enjin::sdk::shared {

class SharedSchema : public ISharedSchema,
                     public BaseSchema {
protected:
    SharedSchema(const enjin::sdk::TrustedPlatformMiddleware& middleware, const std::string& schema);
};

}

#endif //ENJINCPPSDK_SHAREDSCHEMA_HPP
