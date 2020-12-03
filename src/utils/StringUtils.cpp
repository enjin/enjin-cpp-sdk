#include "StringUtils.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

bool enjin::sdk::utils::is_empty_or_whitespace(const std::string &str) {
    return str.empty() || std::all_of(str.begin(), str.end(), [](unsigned char c) { return c == ' '; });
}

std::string enjin::sdk::utils::join(const std::string &separator, const std::list<std::string> &values) {
    std::stringstream stream;

    size_t count = 0;
    for (const std::string &e : values) {
        stream << e;
        if (count++ < values.size() - 1) {
            stream << separator;
        }
    }

    return stream.str();
}

std::string enjin::sdk::utils::to_lower(const std::string &str) {
    std::string new_str(str);

    std::transform(new_str.begin(), new_str.end(), new_str.begin(), [](unsigned char c) { return std::tolower(c); });

    return new_str;
}

std::string enjin::sdk::utils::to_upper(const std::string &str) {
    std::string new_str(str);

    std::transform(new_str.begin(), new_str.end(), new_str.begin(), [](unsigned char c) { return std::toupper(c); });

    return new_str;
}

std::string enjin::sdk::utils::trim(const std::string &str) {
    size_t left = 0;
    size_t right = str.size() - 1;

    while (str[left] == ' ') {
        left++;
    }

    while (str[right] == ' ' && right > left) {
        right--;
    }

    return str.substr(left, right - left + 1);
}

std::string enjin::sdk::utils::replace(const std::string &str,
                                       const std::string &old_value,
                                       const std::string &new_value) {
    std::stringstream stream;
    size_t offset = old_value.size();
    size_t beginIdx = 0;
    while (true) {
        size_t endIdx = str.find(old_value, beginIdx);
        if (endIdx == std::string::npos) {
            stream << str.substr(beginIdx);
            return stream.str();
        }

        stream << str.substr(beginIdx, endIdx - beginIdx) << new_value;
        beginIdx = endIdx + offset;
    }
}

std::vector<std::string> enjin::sdk::utils::split(const std::string &str, const std::string &separator) {
    std::vector<std::string> tokens;
    size_t offset = separator.size();
    size_t beginIdx = 0;
    while (true) {
        size_t endIdx = str.find(separator, beginIdx);
        if (endIdx == std::string::npos) {
            tokens.push_back(str.substr(beginIdx));
            return tokens;
        }

        tokens.push_back(str.substr(beginIdx, endIdx - beginIdx));
        beginIdx = endIdx + offset;
    }
}
