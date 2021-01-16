#ifndef ENJINCPPSDK_SUPPLYMODELS_HPP
#define ENJINCPPSDK_SUPPLYMODELS_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the supply models used by the platform.
class SupplyModels : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    SupplyModels() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the fixed model.
    /// \return The fixed model.
    [[nodiscard]] const std::optional<std::string>& get_fixed() const;

    /// \brief Returns the settable model.
    /// \return The settable model.
    [[nodiscard]] const std::optional<std::string>& get_settable() const;

    /// \brief Returns the infinite model.
    /// \return The infinite model.
    [[nodiscard]] const std::optional<std::string>& get_infinite() const;

    /// \brief Returns the collapsing model.
    /// \return The collapsing model.
    [[nodiscard]] const std::optional<std::string>& get_collapsing() const;

    /// \brief Returns the annual value model.
    /// \return The annual value model.
    [[nodiscard]] const std::optional<std::string>& get_annual_value() const;

    /// \brief Returns the annual percentage model.
    /// \return The annual percentage model.
    [[nodiscard]] const std::optional<std::string>& get_annual_percentage() const;

    bool operator==(const SupplyModels& rhs) const;

    bool operator!=(const SupplyModels& rhs) const;

private:
    std::optional<std::string> fixed;
    std::optional<std::string> settable;
    std::optional<std::string> infinite;
    std::optional<std::string> collapsing;
    std::optional<std::string> annual_value;
    std::optional<std::string> annual_percentage;

    constexpr static char FIXED_KEY[] = "fixed";
    constexpr static char SETTABLE_KEY[] = "settable";
    constexpr static char INFINITE_KEY[] = "infinite";
    constexpr static char COLLAPSING_KEY[] = "collapsing";
    constexpr static char ANNUAL_VALUE_KEY[] = "annualValue";
    constexpr static char ANNUAL_PERCENTAGE_KEY[] = "annualPercentage";
};

}

#endif //ENJINCPPSDK_SUPPLYMODELS_HPP
