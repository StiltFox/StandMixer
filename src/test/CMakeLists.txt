if(NOT SFSkipTesting)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()

    add_executable(Tests
            HashTest.c++
            DataConverterTest.c++
            ValidatorTest.c++
            DataProcessorTest.c++
    )
    target_link_libraries(Tests
            GTest::gtest_main
            Hash
            DataConverter
            Validator
            DataProcessor
    )
endif()