macro(set_include_http_client_impl_macro)
    target_compile_definitions(${PROJECT_NAME}
            PUBLIC
            ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL=${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})

    if (${ENJINSDK_INCLUDE_HTTP_CLIENT_IMPL})
        message(STATUS "Enjin: Built-in HTTP client available for platform clients")
    else ()
        message(STATUS "Enjin: Built-in HTTP client not available for platform clients")
    endif ()
endmacro()

macro(set_include_websocket_client_impl_macro)
    target_compile_definitions(${PROJECT_NAME}
            PUBLIC
            ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL=${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})

    if (${ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL})
        message(STATUS "Enjin: Built-in websocket client available for event services")
    else ()
        message(STATUS "Enjin: Built-in websocket client not available for event services")
    endif ()
endmacro()

macro(set_version_macro)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENJINSDK_VERSION="${PROJECT_VERSION}")
endmacro()

macro(setup_output_directories)
    if (NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        message(STATUS "Enjin: Setting up runtime output directories")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif ()

    if (NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
        message(STATUS "Enjin: Setting up library output directories")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    endif ()

    if (NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
        message(STATUS "Enjin: Setting up archive output directories")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    endif ()
endmacro()
