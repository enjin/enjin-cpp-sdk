find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")

if (${CPP_HTTPLIB_INCLUDE_DIRS} STREQUAL "CPP_HTTPLIB_INCLUDE_DIRS-NOTFOUND")
    message(STATUS "Enjin: Did not find path for cpp-httplib")
else ()
    set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 1)
    message(STATUS "Enjin: Found path for cpp-httplib")
endif ()
