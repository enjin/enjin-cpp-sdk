find_package(cpprestsdk CONFIG)

if (${cpprestsdk_FOUND})
    set(ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL 1)
    message(STATUS "Enjin: Found cpprestsdk package")
else ()
    message(STATUS "Enjin: Did not find cpprestsdk package")
endif ()
