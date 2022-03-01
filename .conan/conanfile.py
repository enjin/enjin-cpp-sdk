from conans import ConanFile, CMake, tools


class EnjinCPPSDK(ConanFile):
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    options = {
        "with_default_http_client": [True, False],
        "with_default_ws_client": [True, False],
    }
    default_options = {
        "with_default_http_client": False,
        "with_default_ws_client": False,
    }

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.test()

    def requirements(self):
        if self.options.with_default_http_client:
            self.requires("cpp-httplib/0.8.5")
            self.options["cpp-httplib"].with_openssl = True

        if self.options.with_default_ws_client:
            self.requires("ixwebsocket/11.0.4")

        self.requires("gtest/1.10.0")
        self.requires("rapidjson/1.1.0")
        self.requires("spdlog/1.8.2")
        self.options["spdlog"].header_only = True
