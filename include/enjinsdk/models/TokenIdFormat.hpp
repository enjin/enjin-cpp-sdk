#ifndef ENJINCPPSDK_TOKENIDFORMAT_HPP
#define ENJINCPPSDK_TOKENIDFORMAT_HPP

namespace enjin::sdk::models {

/// \brief Values used to specify the format to render an item's ID in.
enum class TokenIdFormat {
    HEX64,
    HEX256,
    UINT256,
};

}

#endif //ENJINCPPSDK_TOKENIDFORMAT_HPP
