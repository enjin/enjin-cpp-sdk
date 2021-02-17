from conans import ConanFile, CMake, tools


class EnjinCPPSDK(ConanFile):
    name = "enjincppsdk"
    version = "0.1.0"
    description = "A C++ SDK for development on the Enjin blockchain platform."
    homepage = "https://enjin.io/"
    url = "https://github.com/enjin/Enjin-CPP-SDK"
    license = ""  # TODO: Add license.
    author = "Enjin PTE LTD"
    topics = ("conan", "enjin", "sdk", "blockchain", "cpp")
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    build_policy = "always"
    export_sources = "include/*", "test/*", "CMakeLists.txt"
    no_copy_source = True

    def build(self):  # Building just the tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.test()

    def imports(self):
        self.copy("*.lib", "", "bin")

    def package(self):
        self.copy("*.hpp")

    def requirements(self):
        self.requires("cpprestsdk/2.10.16")
        self.requires("gtest/1.10.0")  # TODO: Require gtest only when running tests if possible.
        self.requires("ixwebsocket/11.0.4")
        self.requires("rapidjson/1.1.0")

    def package_id(self):
        self.info.header_only()
