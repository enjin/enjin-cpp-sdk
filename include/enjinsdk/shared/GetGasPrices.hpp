#ifndef ENJINCPPSDK_SHAREDGETGASPRICES_HPP
#define ENJINCPPSDK_SHAREDGETGASPRICES_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"

namespace enjin::sdk::shared {

/// \brief Request for getting the latest gas prices.
class ENJINSDK_EXPORT GetGasPrices : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    GetGasPrices();

    ~GetGasPrices() override = default;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const GetGasPrices& rhs) const;

    bool operator!=(const GetGasPrices& rhs) const;
};

}

#endif //ENJINCPPSDK_SHAREDGETGASPRICES_HPP
