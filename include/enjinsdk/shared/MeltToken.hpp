#ifndef ENJINCPPSDK_SHAREDMELTTOKEN_HPP
#define ENJINCPPSDK_SHAREDMELTTOKEN_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Melt.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for melting a item.
class MeltToken : public graphql::AbstractGraphqlRequest,
                  public TransactionRequestArgumentsTemplate<MeltToken> {
public:
    /// \brief Default constructor.
    MeltToken();

    ~MeltToken() override = default;

    std::string serialize() override;

    /// Sets the melts to be performed.
    /// \param melts The melts.
    /// \return This request for chaining.
    MeltToken& set_melts(std::vector<models::Melt> melts);

    bool operator==(const MeltToken& rhs) const;

    bool operator!=(const MeltToken& rhs) const;

private:
    std::optional<std::vector<models::Melt>> melts;
};

}

#endif //ENJINCPPSDK_SHAREDMELTTOKEN_HPP
