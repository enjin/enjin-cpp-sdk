#ifndef ENJINCPPSDK_PLAYERFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_PLAYERFRAGMENTARGUMENTS_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Player fragment.
class PlayerFragmentArguments : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    PlayerFragmentArguments() = default;

    ~PlayerFragmentArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to true.
    void set_with_linking_info();

    /// \brief Sets the value for the associated field to the passed value.
    /// \param size The size.
    void set_qr_size(int size);

    /// \brief Sets the value for the associated field to true.
    void set_with_wallet();

    bool operator==(const PlayerFragmentArguments& rhs) const;

    bool operator!=(const PlayerFragmentArguments& rhs) const;

private:
    std::optional<bool> with_linking_info;
    std::optional<int> qr_size;
    std::optional<bool> with_wallet;
};

}

#endif //ENJINCPPSDK_PLAYERFRAGMENTARGUMENTS_HPP
