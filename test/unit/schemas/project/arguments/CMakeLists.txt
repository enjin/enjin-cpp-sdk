target_sources(${PROJECT_NAME}_tests
        PRIVATE
        ProjectTransactionRequestArgumentsImplTest.cpp)

if (NOT ${ENJINSDK_BUILD_SHARED})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            ProjectTransactionRequestArgumentsTest.cpp)
endif ()
