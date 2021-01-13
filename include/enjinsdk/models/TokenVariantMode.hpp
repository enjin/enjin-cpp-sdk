#ifndef ENJINCPPSDK_TOKENVARIANTMODE_HPP
#define ENJINCPPSDK_TOKENVARIANTMODE_HPP

namespace enjin::sdk::models {

/// \brief Represents the mode that determines variant behavior.
enum class TokenVariantMode {
    UNKNOWN, ///< SDK value for unknown values.
    NONE,
    BEAM,
    ONCE,
    ALWAYS,
};

}

#endif //ENJINCPPSDK_TOKENVARIANTMODE_HPP
