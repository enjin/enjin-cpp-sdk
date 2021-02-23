#ifndef ENJINCPPSDK_ASSETTRANSFERFEETYPE_HPP
#define ENJINCPPSDK_ASSETTRANSFERFEETYPE_HPP

namespace enjin::sdk::models {

/// \brief Represents the different transfer types for assets.
enum class AssetTransferFeeType {
    UNKNOWN, ///< SDK value for unknown values from the platform.
    NONE,
    PER_TRANSFER,
    PER_CRYPTO_ITEM,
    RATIO_CUT,
    RATIO_EXTRA,
};

}

#endif //ENJINCPPSDK_ASSETTRANSFERFEETYPE_HPP
