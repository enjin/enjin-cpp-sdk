#ifndef ENJINCPPSDK_GASPRICES_HPP
#define ENJINCPPSDK_GASPRICES_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models gas prices on the platform.
class ENJINSDK_EXPORT GasPrices : enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    GasPrices() = default;

    ~GasPrices() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the recommended safe gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 30 minutes.
    [[nodiscard]] const std::optional<float>& get_safe_low() const;

    /// \brief Returns the recommended average gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 5 minutes.
    [[nodiscard]] const std::optional<float>& get_average() const;

    /// \brief Returns the recommended fast gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 2 minutes.
    [[nodiscard]] const std::optional<float>& get_fast() const;

    /// \brief Returns the recommended fastest gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 30 seconds.
    [[nodiscard]] const std::optional<float>& get_fastest() const;

    bool operator==(const GasPrices& rhs) const;

    bool operator!=(const GasPrices& rhs) const;

private:
    std::optional<float> safe_low;
    std::optional<float> average;
    std::optional<float> fast;
    std::optional<float> fastest;

    constexpr static char SAFE_LOW_KEY[] = "safeLow";
    constexpr static char AVERAGE_KEY[] = "average";
    constexpr static char FAST_KEY[] = "fast";
    constexpr static char FASTEST_KEY[] = "fastest";
};

}

#endif //ENJINCPPSDK_GASPRICES_HPP
