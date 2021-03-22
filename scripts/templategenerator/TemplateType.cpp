#include "TemplateType.hpp"

#include <stdexcept>

namespace enjin::generator {

TemplateType::TemplateType(TemplateType::Value value) : m_value(value) {
}

TemplateType::Value TemplateType::value() const {
    return m_value;
}

std::string TemplateType::to_string() const {
    switch (m_value) {
        case TemplateType::Value::FRAGMENT:
            return "FRAGMENT";
        case TemplateType::Value::MUTATION:
            return "MUTATION";
        case TemplateType::Value::QUERY:
            return "QUERY";
        default:
            throw std::runtime_error("Unknown template type");
    }
}

bool TemplateType::operator==(const TemplateType& rhs) const {
    return m_value == rhs.m_value;
}

bool TemplateType::operator!=(const TemplateType& rhs) const {
    return !(rhs == *this);
}

std::ostream& operator<<(std::ostream& os, const TemplateType& type) {
    os << type.to_string();
    return os;
}

std::vector<TemplateType> TemplateType::values() {
    return std::vector<TemplateType>({
        TemplateType(TemplateType::Value::FRAGMENT),
        TemplateType(TemplateType::Value::MUTATION),
        TemplateType(TemplateType::Value::QUERY),
    });
}

}
