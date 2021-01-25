#ifndef ENJINCPPSDK_GETGASPRICES_HPP
#define ENJINCPPSDK_GETGASPRICES_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"

namespace enjin::sdk::shared {

/// \brief Request for getting the latest gas prices.
class GetGasPrices : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    GetGasPrices();

    ~GetGasPrices() override = default;

    std::string serialize() override;

    bool operator==(const GetGasPrices& rhs) const;

    bool operator!=(const GetGasPrices& rhs) const;
};

}

#endif //ENJINCPPSDK_GETGASPRICES_HPP
