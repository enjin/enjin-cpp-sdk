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

#ifndef ENJINSDK_TESTABLESHAREDPAGINATIONARGUMENTS_HPP
#define ENJINSDK_TESTABLESHAREDPAGINATIONARGUMENTS_HPP

#if(ENJINSDK_BUILD_SHARED == 0)

#include "enjinsdk/shared/PaginationArguments.hpp"

namespace enjin::test::utils {

class TestableSharedPaginationArguments : public sdk::shared::PaginationArguments<TestableSharedPaginationArguments> {
public:
    TestableSharedPaginationArguments() = default;

    ~TestableSharedPaginationArguments() override = default;

    bool operator==(const TestableSharedPaginationArguments& rhs) const;

    bool operator!=(const TestableSharedPaginationArguments& rhs) const;
};

}

namespace enjin::sdk::shared {

template test::utils::TestableSharedPaginationArguments&
PaginationArguments<test::utils::TestableSharedPaginationArguments>::set_pagination(
        models::PaginationInput pagination);

template test::utils::TestableSharedPaginationArguments&
PaginationArguments<test::utils::TestableSharedPaginationArguments>::set_pagination(int page, int limit);

}

#endif

#endif //ENJINSDK_TESTABLESHAREDPAGINATIONARGUMENTS_HPP
