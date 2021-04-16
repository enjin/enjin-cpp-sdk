/* Copyright 2021 Enjin Pte Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "enjinsdk_utils/StringUtils.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace enjin::utils {

bool is_empty_or_whitespace(const std::string& str) {
    return str.empty() || std::all_of(str.begin(), str.end(), [](unsigned char c) { return c == ' '; });
}

std::string join(const std::string& separator, const std::vector<std::string>& values) {
    std::stringstream stream;

    size_t count = 0;
    for (const std::string& e : values) {
        stream << e;
        if (count++ < values.size() - 1) {
            stream << separator;
        }
    }

    return stream.str();
}

std::string to_lower(const std::string& str) {
    std::string new_str(str);

    std::transform(new_str.begin(), new_str.end(), new_str.begin(), [](unsigned char c) { return std::tolower(c); });

    return new_str;
}

std::string to_upper(const std::string& str) {
    std::string new_str(str);

    std::transform(new_str.begin(), new_str.end(), new_str.begin(), [](unsigned char c) { return std::toupper(c); });

    return new_str;
}

std::string trim(const std::string& str) {
    if (str.empty()) {
        return "";
    }

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

std::string replace(const std::string& str,
                    const std::string& old_value,
                    const std::string& new_value) {
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

std::vector<std::string> split(const std::string& str, const std::string& separator) {
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

}
