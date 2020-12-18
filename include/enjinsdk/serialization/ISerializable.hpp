#ifndef ENJINCPPSDK_SERIALIZABLE_HPP
#define ENJINCPPSDK_SERIALIZABLE_HPP

#include <string>

namespace enjin::sdk::serialization {

/// \brief Interface for serialization.
class ISerializable {
public:
    /// \brief Default destructor.
    virtual ~ISerializable() = default;

    /// \brief Parses the JSON string and assigns valid values to this object's fields.
    /// \param json The JSON string.
    virtual void deserialize(const char* json) = 0;

    /// \brief Returns a JSON string with this object's data.
    /// \return This object as a JSON string.
    /// \remark Null fields are to be omitted from the JSON string.
    virtual std::string serialize() = 0;
};

}

#endif //ENJINCPPSDK_SERIALIZABLE_HPP
