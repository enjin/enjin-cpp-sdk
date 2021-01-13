#ifndef ENJINCPPSDK_TOKENTRANSFERABLE_HPP
#define ENJINCPPSDK_TOKENTRANSFERABLE_HPP

namespace enjin::sdk::models {

/// \brief Represents the transferable types of a token.
enum class TokenTransferable {
    UNKNOWN, ///< SDK value for unknown values.
    PERMANENT,
    TEMPORARY,
    BOUND,
};

}

#endif //ENJINCPPSDK_TOKENTRANSFERABLE_HPP
