cmake_minimum_required(VERSION 3.28)

add_library(Tests STATIC)
target_sources(Tests
    PUBLIC FILE_SET CXX_MODULES FILES
        ClientServer/ClientServer.cpp
        Math/Math.cpp
            Math/Core.cpp
            Math/Modulator.cpp
            Math/Range.cpp
            Math/Trig.cpp
        Misc/Misc.cpp
            Misc/Core.cpp
        Point/Point.cpp
            Point/Core.cpp
        Random/Random.cpp
        Rectangle/Rectangle.cpp
            Rectangle/Core.cpp
        StopWatch/StopWatch.cpp
        Tests.cpp)
target_compile_features(Tests PUBLIC cxx_std_20)
target_link_libraries(Tests PUBLIC Eqx_Lib UnitTester)

set_target_properties(Tests PROPERTIES
    CXX_STANDARD_REQUIRED On
    CXX_EXTENSIONS Off
    EXPORT_COMPILE_COMMANDS On)
