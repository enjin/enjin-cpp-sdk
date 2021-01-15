#include "enjinsdk/models/PusherOptions.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void PusherOptions::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(CLUSTER_KEY) && document[CLUSTER_KEY].IsString()) {
            cluster.emplace(document[CLUSTER_KEY].GetString());
        }
        if (document.HasMember(ENCRYPTED_KEY) && document[ENCRYPTED_KEY].IsBool()) {
            encrypted.emplace(document[ENCRYPTED_KEY].GetBool());
        }
    }
}

const std::optional<std::string>& PusherOptions::get_cluster() const {
    return cluster;
}

const std::optional<bool>& PusherOptions::get_encrypted() const {
    return encrypted;
}

bool PusherOptions::operator==(const PusherOptions& rhs) const {
    return cluster == rhs.cluster &&
           encrypted == rhs.encrypted;
}

bool PusherOptions::operator!=(const PusherOptions& rhs) const {
    return !(rhs == *this);
}

}
