#ifndef ENJINCPPSDK_RAPIDJSONUTILS_HPP
#define ENJINCPPSDK_RAPIDJSONUTILS_HPP

#include "rapidjson/document.h"
#include <string>
#include <vector>

namespace enjin::sdk::utils {

std::vector<std::string> get_array_as_serialized_vector(const rapidjson::Document& document,
                                                        const std::string& key = "");

std::string get_object_as_string(const rapidjson::Document& document, const std::string& key = "");

}

#endif //ENJINCPPSDK_RAPIDJSONUTILS_HPP
