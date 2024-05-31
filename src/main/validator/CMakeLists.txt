add_library(Validator Validator.c++)
set_target_properties(Validator PROPERTIES PUBLIC_HEADER "src/main/validator/Validator.h++")
target_include_directories(Validator PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")