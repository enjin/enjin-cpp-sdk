#ifndef ENJINCPPSDK_IDESERIALIZABLE_HPP
#define ENJINCPPSDK_IDESERIALIZABLE_HPP

#include "enjinsdk_export.h"
#include <string>

namespace enjin::sdk::serialization {

/// \brief Interface for deserialization.
class ENJINSDK_EXPORT IDeserializable {
public:
    /// \brief Default destructor.
    virtual ~IDeserializable() = default;

    /// \brief Parses the JSON string and assigns valid values to this object's fields.
    /// \param json The JSON string.
    virtual void deserialize(const std::string& json) = 0;
};

}

#endif //ENJINCPPSDK_IDESERIALIZABLE_HPP
