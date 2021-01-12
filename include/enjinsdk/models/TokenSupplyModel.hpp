#ifndef ENJINCPPSDK_TOKENSUPPLYMODEL_HPP
#define ENJINCPPSDK_TOKENSUPPLYMODEL_HPP

namespace enjin::sdk::models {

/// \brief Values used to specify the token supply model.
enum class TokenSupplyModel {
    FIXED,
    SETTABLE,
    INFINITE,
    COLLAPSING,
    ANNUAL_VALUE,
    ANNUAL_PERCENTAGE,
};

}

#endif //ENJINCPPSDK_TOKENSUPPLYMODEL_HPP
