#ifndef ENJINCPPSDK_ASSETSUPPLYMODEL_HPP
#define ENJINCPPSDK_ASSETSUPPLYMODEL_HPP

namespace enjin::sdk::models {

/// \brief Values used to specify the supply model for a asset.
enum class AssetSupplyModel {
    UNKNOWN, ///< SDK value for unknown values from the platform.
    FIXED,
    SETTABLE,
    INFINITE,
    COLLAPSING,
    ANNUAL_VALUE,
    ANNUAL_PERCENTAGE,
};

}

#endif //ENJINCPPSDK_ASSETSUPPLYMODEL_HPP
