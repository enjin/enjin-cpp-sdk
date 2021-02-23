#ifndef ENJINCPPSDK_ASSETFIELD_HPP
#define ENJINCPPSDK_ASSETFIELD_HPP

namespace enjin::sdk::models {

/// \brief The fields of a Asset type for sorting.
enum class AssetField {
    ID,
    NAME,
    CIRCULATING_SUPPLY,
    NON_FUNGIBLE,
    RESERVE,
    TOTAL_SUPPLY,
    CREATED_AT,
};

}

#endif //ENJINCPPSDK_ASSETFIELD_HPP
