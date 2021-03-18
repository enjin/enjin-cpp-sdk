#ifndef ENJINCPPSDK_SHAREDMELTASSET_HPP
#define ENJINCPPSDK_SHAREDMELTASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Melt.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for melting a asset.
class ENJINSDK_EXPORT MeltAsset : public graphql::AbstractGraphqlRequest,
                                  public TransactionRequestArguments<MeltAsset> {
public:
    /// \brief Default constructor.
    MeltAsset();

    ~MeltAsset() override = default;

    std::string serialize() override;

    /// Sets the melts to be performed.
    /// \param melts The melts.
    /// \return This request for chaining.
    MeltAsset& set_melts(std::vector<models::Melt> melts);

    bool operator==(const MeltAsset& rhs) const;

    bool operator!=(const MeltAsset& rhs) const;

private:
    std::optional<std::vector<models::Melt>> melts;
};

}

#endif //ENJINCPPSDK_SHAREDMELTASSET_HPP
