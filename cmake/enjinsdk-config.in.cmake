include(CMakeFindDependencyMacro)

get_filename_component(ENJINSDK_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(ENJINSDK_INCLUDE_DIRS @CONF_INCLUDE_DIRS@)

if (@ENJINSDK_USES_CPPRESTSDK@)
    find_dependency(cpprest)
endif ()

if (@ENJINSDK_USES_IXWEBSOCKET@)
    find_dependency(ixwebsocket)
endif ()

if (@ENJINSDK_USES_RAPIDJSON@)
    find_dependency(rapidjson)
endif ()

if (NOT TARGET enjinsdk AND NOT ENJINSDK_BINARY_DIR)
    include("${CMAKE_CURRENT_LIST_DIR}/enjinsdk-targets.cmake/enjinsdk-targets.cmake")
endif ()
