#ifndef ENJINCPPSDK_RAPIDJSONUTILS_HPP
#define ENJINCPPSDK_RAPIDJSONUTILS_HPP

#include "rapidjson/document.h"
#include <string>

namespace enjin::sdk::utils {

std::string get_object_as_string(const rapidjson::Document& document, const std::string& key = "");

}

#endif //ENJINCPPSDK_RAPIDJSONUTILS_HPP
