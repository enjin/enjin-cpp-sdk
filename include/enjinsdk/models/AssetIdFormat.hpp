#ifndef ENJINCPPSDK_ASSETIDFORMAT_HPP
#define ENJINCPPSDK_ASSETIDFORMAT_HPP

namespace enjin::sdk::models {

/// \brief Values used to specify the format to render an asset's ID in.
enum class AssetIdFormat {
    HEX64,
    HEX256,
    UINT256,
};

}

#endif //ENJINCPPSDK_ASSETIDFORMAT_HPP
