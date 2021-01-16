#include "DummyObject.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

namespace enjin::test::utils {

DummyObject::DummyObject(int id) {
    this->id = std::optional<int>(id);
}

void DummyObject::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id = std::optional<int>(document[ID_KEY].GetInt());
        }
    }
}

std::string DummyObject::serialize() {
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    if (id.has_value()) {
        rapidjson::Value v(id.value());
        document.AddMember(ID_KEY, v, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer <rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    const char* json = buffer.GetString();

    return std::string(json);
}

bool DummyObject::operator==(const DummyObject& rhs) const {
    return id == rhs.id;
}

bool DummyObject::operator!=(const DummyObject& rhs) const {
    return !(rhs == *this);
}

DummyObject DummyObject::create_default_dummy_object() {
    return DummyObject(1);
}

}
