# Blockchain SDK by Enjin for C++

Create blockchain video games and applications using the Java programming language.

[Learn more](https://enjin.io/) about the Enjin blockchain platform.

Sign up to Enjin Cloud: [Kovan (Testnet)](https://kovan.cloud.enjin.io/)
or [Mainnet (Production)](https://cloud.enjin.io/)

### Resources

* [Enjin Docs](https://enjin.io/docs)

### Table of Contents

* [Compatibility](#compatibility)
* [Installation](#installation)
* [Contributing](#contributing)
    * [Issues](#issues)
    * [Pull Requests](#pull-requests)
* [Copyright and Licensing](#copyright-and-licensing)

## Compatibility

The Enjin C++ SDK is developed with cross-platform usage in mind. Platform and compiler combinations tested are as
follows:

* 64bit Linux with GCC 9
* 64bit Linux with Clang 10
* 64bit Windows with MSVC 2019

## Installation

The SDK is a **shared** (dynamic) C++ library.

The following dependencies are used for building the SDK:

* [CMake (3.16+)](https://cmake.org/) as a build tool
* [Git](https://git-scm.com/) for submodule(s)

The following libraries are used by the SDK to create its functionality and must be installed on your machine, but are
not necessary to link to by your own project:

* [RapidJSON (1.1.0+)](https://github.com/Tencent/rapidjson) for processing JSON
* [spdlog (1.8.0+)](https://github.com/gabime/spdlog) for the logger class
* (optional) [cpp-httplib (0.8.5+)](https://github.com/yhirose/cpp-httplib) for a default HTTP client implementation
* (optional) [IXWebSocket (11.0.4+)](https://github.com/machinezone/IXWebSocket) for a default websocket client
  implementation
* [Googletest (1.10.0+)](https://github.com/google/googletest) for testing
    * Is acquired using CMake's `ExternalProject_Add()` function with git.

To have the SDK build its default HTTP and websocket clients use the `ENJINSDK_ALLOW_DEFAULT_HTTP`
and `ENJINSDK_ALLOW_DEFAULT_WEBSOCKET` as CMake arguments and set them to be "on" (off by default).

You may include the SDK in your project by first cloning it into your project hierarchy with:

```commandline
git clone https://github.com/enjin/Enjin-CPP-SDK.git
```

then add the following to your project's CMakeLists file:

```cmake
add_subdirectory(Enjin-CPP-SDK)
target_link_libraries(my_target PRIVATE enjinsdk)
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

```
Copyright 2021 Enjin Pte Ltd.

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