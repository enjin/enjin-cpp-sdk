#ifndef ENJINCPPSDK_RAPIDJSONUTILS_HPP
#define ENJINCPPSDK_RAPIDJSONUTILS_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <string>
#include <type_traits>
#include <vector>

namespace enjin::sdk::utils {

std::vector<std::string> get_array_as_serialized_vector(const rapidjson::Document& document,
                                                        const std::string& key = "");

template<class T>
std::vector<T> get_array_as_type_vector(const rapidjson::Document& document,
                                        const std::string& key = "") {
    static_assert(std::is_base_of<enjin::sdk::serialization::IDeserializable, T>::value,
                  "Class T does not inherit from IDeserializable.");

    if (key.empty() && document.IsArray()) {
        std::vector<T> v;
        for (auto& arr_el : document.GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            arr_el.Accept(writer);
            T t;
            t.deserialize(buffer.GetString());
            v.push_back(t);
        }
        return v;
    } else if (!key.empty() && document[key.c_str()].IsArray()) {
        std::vector<T> v;
        for (auto& arr_el : document[key.c_str()].GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            arr_el.Accept(writer);
            T t;
            t.deserialize(buffer.GetString());
            v.push_back(t);
        }
        return v;
    }

    throw std::exception("JSON element is not an array");
}

std::string get_object_as_string(const rapidjson::Document& document, const std::string& key = "");

template<class T>
T get_object_as_type(const rapidjson::Document& document, const std::string& key = "") {
    static_assert(std::is_base_of<enjin::sdk::serialization::IDeserializable, T>::value,
                  "Class T does not inherit from IDeserializable.");

    T t;
    t.deserialize(get_object_as_string(document, key));
    return t;
}

}

#endif //ENJINCPPSDK_RAPIDJSONUTILS_HPP
