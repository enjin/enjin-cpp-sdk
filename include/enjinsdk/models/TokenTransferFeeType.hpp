#ifndef ENJINCPPSDK_TOKENTRANSFERFEETYPE_HPP
#define ENJINCPPSDK_TOKENTRANSFERFEETYPE_HPP

namespace enjin::sdk::models {

/// \brief Represents the different transfer types for tokens.
enum class TokenTransferFeeType {
    NONE,
    PER_TRANSFER,
    PER_CRYPTO_ITEM,
    RATIO_CUT,
    RATIO_EXTRA,
};

}

#endif //ENJINCPPSDK_TOKENTRANSFERFEETYPE_HPP
