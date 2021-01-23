#ifndef ENJINCPPSDK_BALANCEFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_BALANCEFRAGMENTARGUMENTS_HPP

#include "enjinsdk/models/TokenIdFormat.hpp"
#include "enjinsdk/models/TokenIndexFormat.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Balance fragment.
class BalanceFragmentArguments : serialization::ISerializable {
public:
    /// \brief Default constructor.
    BalanceFragmentArguments() = default; // TODO: Consider making this constructor private and friend to its implementing template class.

    ~BalanceFragmentArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param bal_id_format The ID format.
    void set_bal_id_format(models::TokenIdFormat bal_id_format);

    /// \brief Sets the value for the associated field to the passed value.
    /// \param bal_index_format The index format.
    void set_bal_index_format(models::TokenIndexFormat bal_index_format);

    /// \brief Sets the value for the associated field to true.
    void set_with_bal_project_id();

    /// \brief Sets the value for the associated field to true.
    void set_with_bal_wallet_address();

    bool operator==(const BalanceFragmentArguments& rhs) const;

    bool operator!=(const BalanceFragmentArguments& rhs) const;

private:
    std::optional<models::TokenIdFormat> bal_id_format;
    std::optional<models::TokenIndexFormat> bal_index_format;
    std::optional<bool> with_bal_project_id;
    std::optional<bool> with_bal_wallet_address;
};

}

#endif //ENJINCPPSDK_BALANCEFRAGMENTARGUMENTS_HPP
