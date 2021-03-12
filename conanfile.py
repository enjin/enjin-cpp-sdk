from conans import ConanFile, CMake, tools


class EnjinCPPSDK(ConanFile):
    name = "enjincppsdk"
    version = "2.0.0"
    description = "A C++ SDK for development on the Enjin blockchain platform."
    homepage = "https://enjin.io/"
    url = "https://github.com/enjin/Enjin-CPP-SDK"
    license = ""  # TODO: Add license.
    author = "Enjin PTE LTD"
    topics = ("conan", "enjin", "sdk", "blockchain", "cpp")
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    options = {
        "enable_cpprestsdk": [True, False]
    }
    default_options = {
        "enable_cpprestsdk": True
    }

    def build(self):  # Building just the tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.test()

    def imports(self):
        self.copy("*.lib", "", "bin")

    def package(self):
        self.copy("*.h", dst="include", src="include/enjinsdk")
        self.copy("*enjinsdk.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def requirements(self):
        #  if self.options['include_http']:
        self.requires("cpprestsdk/2.10.18")  # TODO: Make HTTP client optional
        #  if self.options['include_websocket']:
        self.requires("ixwebsocket/11.0.4")  # TODO: Make websocket client optional

        self.requires("gtest/1.10.0")  # TODO: Require gtest only when running tests if possible.
        self.requires("rapidjson/1.1.0")
