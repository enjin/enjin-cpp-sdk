#ifndef ENJINCPPSDK_ASSETTRANSFERABLE_HPP
#define ENJINCPPSDK_ASSETTRANSFERABLE_HPP

namespace enjin::sdk::models {

/// \brief Represents the transferable types of a asset.
enum class AssetTransferable {
    UNKNOWN, ///< SDK value for unknown values from the platform.
    PERMANENT,
    TEMPORARY,
    BOUND,
};

}

#endif //ENJINCPPSDK_ASSETTRANSFERABLE_HPP
