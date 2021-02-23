#ifndef ENJINCPPSDK_ASSETVARIANTMODE_HPP
#define ENJINCPPSDK_ASSETVARIANTMODE_HPP

namespace enjin::sdk::models {

/// \brief Represents the mode that determines variant behavior.
enum class AssetVariantMode {
    UNKNOWN, ///< SDK value for unknown values from the platform.
    NONE,
    BEAM,
    ONCE,
    ALWAYS,
};

}

#endif //ENJINCPPSDK_ASSETVARIANTMODE_HPP
