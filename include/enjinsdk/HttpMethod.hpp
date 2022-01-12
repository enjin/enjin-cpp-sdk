/* Copyright 2021 Enjin Pte. Ltd.
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

#ifndef ENJINSDK_HTTPMETHOD_HPP
#define ENJINSDK_HTTPMETHOD_HPP

namespace enjin::sdk::http {

/// \brief Enums representing HTTP methods.
enum class HttpMethod {
    GET,
    HEAD,
    POST,
    PUT,
    DEL,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
};

}

#endif //ENJINSDK_HTTPMETHOD_HPP
