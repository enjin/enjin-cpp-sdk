# Blockchain SDK by Enjin for C++

Create blockchain video games and applications using the C++ programming language.

[Learn more](https://enjin.io/) about the Enjin blockchain platform.

Sign up to Enjin Cloud: [Kovan (Testnet)](https://kovan.cloud.enjin.io/),
[Mainnet (Production)](https://cloud.enjin.io/) or [JumpNet](https://jumpnet.cloud.enjin.io/).

### Resources

* [Enjin Docs](https://docs.enjin.io)
* [Doxygen Docs](https://enjin.github.io/enjin-cpp-sdk/sdk/latest/)

### Table of Contents

* [Compatibility](#compatibility)
* [Installation](#installation)
    * [Tests](#tests)
* [Quick Start](#quick-start)
* [Contributing](#contributing)
    * [Issues](#issues)
    * [Pull Requests](#pull-requests)
* [Copyright and Licensing](#copyright-and-licensing)

## Compatibility

The Enjin C++ SDK is a C++17 library and is developed with cross-platform usage in mind. Platform and compiler
combinations tested are as follows:

* GCC 9.3.0 on Linux (64-bit)
* Clang 10.0.0 on Linux (64-bit)
* MSVC 2019 on Windows 10 (64-bit)

## Installation

The SDK may be built as a static or shared (dynamic) library. Use the `ENJINSDK_BUILD_SHARED` CMake argument to build as
a shared library and set it to "on" (off by default).

The following dependencies are used for building the SDK:

* [CMake (3.16+)](https://cmake.org/) as a build tool

The following libraries are used by the SDK for some of its functionality and must be locatable by CMake's
`find_package()` function, however these libraries are not necessary to link to your own target to use this SDK:

* [RapidJSON (1.1.0+)](https://github.com/Tencent/rapidjson) for processing JSON
* [spdlog (1.8.0+)](https://github.com/gabime/spdlog) for the logger class
* (optional) [cpp-httplib (0.8.5+)](https://github.com/yhirose/cpp-httplib) for a default HTTP client implementation
  * [openssl (1.1.1)](https://github.com/openssl/openssl) for HTTPS support
* (optional) [IXWebSocket (11.0.4+)](https://github.com/machinezone/IXWebSocket) for a default websocket client
  implementation

To have the SDK build its default HTTP and websocket clients use the `ENJINSDK_BUILD_DEFAULT_HTTP` and
`ENJINSDK_BUILD_DEFAULT_WEBSOCKET` as CMake arguments and set them to be "on" (off by default).

To utilize this SDK you may clone it into your project tree with:

```console
$ git clone https://github.com/enjin/Enjin-CPP-SDK.git
```

Then use the following in your project's CMakeLists file:

```cmake
add_subdirectory(Enjin-CPP-SDK)
target_link_libraries(my_target PRIVATE enjinsdk::enjinsdk)
```

#### Linux

Alternatively, on Linux you may include the SDK in your project by cloning and building it with the following commands:

```console
$ git clone https://github.com/enjin/Enjin-CPP-SDK.git
$ cmake ./Enjin-CPP-SDK [options] && make -j -C ./Enjin-CPP-SDK
```

From here, you may use CMake's `find_package()` function to find `enjinsdk` and link the library, `enjinsdk::enjinsdk`
to your target.

### Tests

For running unit tests [Git (1.6.5+)](https://git-scm.com/) is required to run CMake's `ExternalProject_Add()` function
to acquire [Googletest (1.10.0+)](https://github.com/google/googletest) to be used as the testing framework.

To have the test executable built, set the CMake argument `ENJINSDK_BUILD_TESTS` to `ON` and leave the `BUILD_TESTING`
option from CTest enabled.

## Quick Start

This example showcases how to quickly create and authenticate a client on the project schema which will then allow us to
make further requests to the platform.

```c++
#include "enjinsdk/EnjinHosts.hpp"
#include "enjinsdk/ProjectClient.hpp"
#include <iostream>

using namespace enjin::sdk;
using namespace enjin::sdk::graphql;
using namespace enjin::sdk::models;
using namespace enjin::sdk::project;

int main() {
    // Builds the project client to run on the Kovan test network.
    // See: https://kovan.cloud.enjin.io to sign up for the test network.
    ProjectClient client = ProjectClient::builder()
        .base_uri(KOVAN) // From EnjinHosts
        .build();

    // Creates the request to authenticate the client.
    // Replace the appropriate strings with the project's UUID and secret.
    AuthProject req = AuthProject()
        .set_uuid("<the-project's-uuid>")
        .set_secret("<the-project's-secret>");

    // Sends the request to the platform and gets the response.
    GraphqlResponse<AccessToken> res = client.auth_project(req).get();

    // Checks if the request was successful.
    if (!res.is_successful()) {
        std::cout << "AuthProject request failed" << std::endl;
        return 0;
    }

    // Authenticates the client with the access token in the response.
    client.auth(res.get_result().value().get_token().value());

    // Checks if the client was authenticated.
    if (client.is_authenticated()) {
        std::cout << "Client is now authenticated" << std::endl;
    } else {
        std::cout << "Client was not authenticated" << std::endl;
    }

    return 0;
}
```

## Contributing

Contributions to the SDK are appreciated!

### Issues

You can open issues for bugs and enhancement requests.

When reporting bugs, please state the OS, compiler, and CMake arguments used as well as reproducible examples if
possible.

### Pull Requests

If you make any changes or improvements to the SDK, which you believe are beneficial to others, consider making a pull
request to merge your changes to be included in the next release.

Ensure that tests are passing when running the target `enjinsdk_tests` and add any necessary test classes or test cases
for your code.

Be sure to include your name in the list of contributors.

## Copyright and Licensing

The license summary below may be copied.

```text
Copyright 2021 Enjin Pte. Ltd.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```