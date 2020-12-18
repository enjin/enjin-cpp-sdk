#include "enjinsdk/GraphqlError.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace enjin::sdk::graphql {

void GraphqlError::deserialize(const char* json) {
    rapidjson::Document document;
    document.Parse(json);

    if (document.IsObject()) {
        if (document.HasMember(MESSAGE) && document[MESSAGE].IsString()) {
            message.emplace(document[MESSAGE].GetString());
        }
        if (document.HasMember(CODE) && document[CODE].IsInt()) {
            code.emplace(document[CODE].GetInt());
        }
        if (document.HasMember(DETAILS) && document[DETAILS].IsString()) {
            details.emplace(document[DETAILS].GetString());
        }
        if (document.HasMember(LOCATIONS) && document[LOCATIONS].IsArray()) {
            locations.emplace(std::vector<std::map<std::string, int>>());

            for (auto& l : document[LOCATIONS].GetArray()) {
                if (!l.IsObject()) {
                    continue;
                }

                std::map<std::string, int> location;
                for (auto& m : l.GetObject()) {
                    location[m.name.GetString()] = m.value.GetInt();
                }
                locations.value().emplace_back(location);
            }
        }
    }
}

std::string GraphqlError::serialize() {
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType & allocator = document.GetAllocator();

    if (message.has_value()) {
        rapidjson::Value v;
        v.SetString(message.value().c_str(), document.GetAllocator());
        document.AddMember(MESSAGE, v, allocator);
    }
    if (code.has_value()) {
        rapidjson::Value v(code.value());
        document.AddMember(CODE, v, allocator);
    }
    if (details.has_value()) {
        rapidjson::Value v;
        v.SetString(details.value().c_str(), allocator);
        document.AddMember(DETAILS, v, allocator);
    }
    if (locations.has_value()) {
        rapidjson::Value v_locations(rapidjson::kArrayType);
        for (auto& location : locations.value()) { // Iterates over each location in the array
            rapidjson::Value v_location(rapidjson::kObjectType);
            for (auto const& entry : location) { // Iterates over each entry in the map (JSON object)
                rapidjson::Value name;
                name.SetString(entry.first.c_str(), allocator);
                rapidjson::Value v(entry.second);
                v_location.AddMember(name, v, allocator);
            }
            v_locations.PushBack(v_location, allocator);
        }
        document.AddMember(LOCATIONS, v_locations, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    const char* json = buffer.GetString();

    return std::string(json);
}

std::optional<std::string> GraphqlError::get_message() {
    return message;
}

std::optional<int> GraphqlError::get_code() {
    return code;
}

std::optional<std::vector<std::map<std::string, int>>> GraphqlError::get_locations() {
    return locations;
}

std::optional<std::string> GraphqlError::get_details() {
    return details;
}

}
