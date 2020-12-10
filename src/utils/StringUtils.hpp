#ifndef ENJINCPPSDK_STRINGUTILS_HPP
#define ENJINCPPSDK_STRINGUTILS_HPP

#include <list>
#include <string>
#include <vector>

namespace enjin {
namespace sdk {
namespace utils {

bool is_empty_or_whitespace(const std::string& str);

std::string join(const std::string& separator, const std::list<std::string>& values);

std::string to_lower(const std::string& str);

std::string to_upper(const std::string& str);

std::string trim(const std::string& str);

std::string replace(const std::string& str, const std::string& old_value, const std::string& new_value);

std::vector<std::string> split(const std::string& str, const std::string& separator);

} // namespace utils
} // namespace sdk
} // enjin

#endif //ENJINCPPSDK_STRINGUTILS_HPP
