add_library(Hash Hash.c++)
target_link_libraries(Hash
        cryptopp
        DataConverter
)
set_target_properties(Hash PROPERTIES PUBLIC_HEADER "src/main/hash/Hash.h++")
target_include_directories(Hash PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")