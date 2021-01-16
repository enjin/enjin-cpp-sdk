#include "enjinsdk/models/LinkingInfo.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void enjin::sdk::models::LinkingInfo::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(CODE_KEY) && document[CODE_KEY].IsString()) {
            code.emplace(document[CODE_KEY].GetString());
        }
        if (document.HasMember(QR_KEY) && document[QR_KEY].IsString()) {
            qr.emplace(document[QR_KEY].GetString());
        }
    }
}

const std::optional<std::string>& LinkingInfo::get_code() const {
    return code;
}

const std::optional<std::string>& LinkingInfo::get_qr() const {
    return qr;
}

bool LinkingInfo::operator==(const LinkingInfo& rhs) const {
    return code == rhs.code &&
           qr == rhs.qr;
}

bool LinkingInfo::operator!=(const LinkingInfo& rhs) const {
    return !(rhs == *this);
}

}
