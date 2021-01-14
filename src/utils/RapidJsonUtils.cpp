#include "RapidJsonUtils.hpp"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace enjin::sdk::utils {

std::string get_object_as_string(const rapidjson::Document& document, const std::string& key) {
    if (key.empty() && document.IsObject()) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    } else if (!key.empty() && document[key.c_str()].IsObject()) {
        auto& v_value = document[key.c_str()];
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        v_value.Accept(writer);
        return buffer.GetString();
    }

    throw std::exception("JSON element is not an object");
}

}
