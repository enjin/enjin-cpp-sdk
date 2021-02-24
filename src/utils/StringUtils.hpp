#ifndef ENJINCPPSDK_STRINGUTILS_HPP
#define ENJINCPPSDK_STRINGUTILS_HPP

#include "enjinsdk_export.h"
#include <list>
#include <string>
#include <vector>

namespace enjin::sdk::utils {

ENJINSDK_EXPORT
bool is_empty_or_whitespace(const std::string& str);

ENJINSDK_EXPORT
std::string join(const std::string& separator, const std::list<std::string>& values);

ENJINSDK_EXPORT
std::string to_lower(const std::string& str);

ENJINSDK_EXPORT
std::string to_upper(const std::string& str);

ENJINSDK_EXPORT
std::string trim(const std::string& str);

ENJINSDK_EXPORT
std::string replace(const std::string& str, const std::string& old_value, const std::string& new_value);

ENJINSDK_EXPORT
std::vector<std::string> split(const std::string& str, const std::string& separator);

}

#endif //ENJINCPPSDK_STRINGUTILS_HPP
