add_library(DataProcessor DataProcessor.c++)
set_target_properties(DataProcessor PROPERTIES PUBLIC_HEADER "src/main/data_processor/DataProcessor.h++")
target_include_directories(DataProcessor PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")