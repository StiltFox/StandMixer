cmake_minimum_required(VERSION 3.28)
project(StandMixer VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_subdirectory(src)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/StandMixerConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StandMixer
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/StandMixerConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/StandMixerConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StandMixer
)

install(
        TARGETS Hash DataConverter Validator DataProcessor
        EXPORT StandMixer
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/Stilt_Fox/StandMixer
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/Stilt_Fox/StandMixer
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/Stilt_Fox/StandMixer
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Stilt_Fox/StandMixer
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Stilt_Fox/StandMixer
)

install(EXPORT StandMixer
        FILE StandMixerTargets.cmake
        NAMESPACE StiltFox::StandMixer::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StandMixer
)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/StandMixerConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)