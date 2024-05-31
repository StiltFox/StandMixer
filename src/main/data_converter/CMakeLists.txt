add_library(DataConverter DataConverter.c++
        ../validator/Validator.c++
        ../validator/Validator.h++)
set_target_properties(DataConverter PROPERTIES PUBLIC_HEADER "src/main/data_converter/DataConverter.h++")
target_include_directories(DataConverter PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")