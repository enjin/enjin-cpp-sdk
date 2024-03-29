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

#ifndef ENJINSDK_HTTPHEADERS_HPP
#define ENJINSDK_HTTPHEADERS_HPP

namespace enjin::sdk::http {

/// \brief The key for the authorization header.
static constexpr char Authorization[] = "Authorization";

/// \brief The key for the content-type header.
static constexpr char ContentType[] = "Content-Type";

/// \brief The key for the user-agent header.
static constexpr char UserAgent[] = "User-Agent";

}

#endif //ENJINSDK_HTTPHEADERS_HPP
