if(NOT SFSkipTesting)
    find_package(GTest REQUIRED)
    find_package(Scribe REQUIRED)
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
            StiltFox::Scribe::File
            Hash
            DataConverter
            Validator
            DataProcessor
    )
endif()