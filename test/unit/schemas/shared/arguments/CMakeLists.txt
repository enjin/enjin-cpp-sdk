if (NOT ${ENJINSDK_BUILD_SHARED})
    target_sources(${PROJECT_NAME}_tests
            PRIVATE
            SharedAssetFragmentArgumentsTest.cpp
            SharedBalanceFragmentArgumentsTest.cpp
            SharedPaginationArgumentsTest.cpp
            SharedPlayerFragmentArgumentsTest.cpp
            SharedTransactionFragmentArgumentsTest.cpp
            SharedWalletFragmentArgumentsTest.cpp)
endif ()
