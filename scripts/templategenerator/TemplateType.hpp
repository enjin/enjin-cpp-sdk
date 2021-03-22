#ifndef ENJINSDK_TEMPLATETYPE_HPP
#define ENJINSDK_TEMPLATETYPE_HPP

#include <ostream>
#include <string>
#include <vector>

namespace enjin::generator {

class TemplateType {
public:
    enum class Value {
        FRAGMENT,
        MUTATION,
        QUERY,
    };

    TemplateType() = delete;

    explicit TemplateType(Value value);

    ~TemplateType() = default;

    [[nodiscard]] Value value() const;

    [[nodiscard]] std::string to_string() const;

    bool operator==(const TemplateType& rhs) const;

    bool operator!=(const TemplateType& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const TemplateType& type);

    [[nodiscard]] static std::vector<TemplateType> values();

private:
    Value m_value;
};

}

#endif //ENJINSDK_TEMPLATETYPE_HPP
