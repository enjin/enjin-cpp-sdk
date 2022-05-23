target_sources(${PROJECT_NAME}_tests
        PRIVATE
        DummyObject.cpp
        TestableBaseSchema.cpp)

if (NOT ${ENJINSDK_BUILD_SHARED})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            TestableProjectTransactionRequestArguments.cpp
            TestableSharedAssetFragmentArguments.cpp
            TestableSharedBalanceFragmentArguments.cpp
            TestableSharedPaginationArguments.cpp
            TestableSharedPlayerFragmentArguments.cpp
            TestableSharedTransactionFragmentArguments.cpp
            TestableWalletFragmentArguments.cpp)
endif ()
