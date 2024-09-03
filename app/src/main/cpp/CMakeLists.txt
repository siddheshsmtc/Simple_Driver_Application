cmake_minimum_required(VERSION 3.4.1)

add_library( # Specifies the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp )

find_library( # Sets the path of the NDK library needed for your library.
        log-lib

        # Specifies the NDK library you want to link.
        log )

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the log library to the target library.
        ${log-lib} )
