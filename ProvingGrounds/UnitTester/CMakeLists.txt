cmake_minimum_required(VERSION 3.28)

add_library(UnitTester STATIC)
target_sources(UnitTester
    PUBLIC FILE_SET CXX_MODULES FILES
        UnitTester.cpp)
target_compile_features(UnitTester PUBLIC cxx_std_20)
target_link_libraries(UnitTester PUBLIC Eqx_Std)

set_target_properties(UnitTester PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
