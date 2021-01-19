#ifndef ENJINCPPSDK_TOKENFIELD_HPP
#define ENJINCPPSDK_TOKENFIELD_HPP

namespace enjin::sdk::models {

/// \brief The fields of a Token type for sorting.
enum class TokenField {
    ID,
    NAME,
    CIRCULATING_SUPPLY,
    NON_FUNGIBLE,
    RESERVE,
    TOTAL_SUPPLY,
    CREATED_AT,
};

}

#endif //ENJINCPPSDK_TOKENFIELD_HPP
