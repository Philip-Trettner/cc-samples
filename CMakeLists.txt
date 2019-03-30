cmake_minimum_required(VERSION 3.8)
project(CleanCoreSamples)


# ===============================================
# Global settings

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(CC_BUILD_TESTS "Build clean-core tests" ON)

# ===============================================
# Dependencies

# clean core
add_subdirectory(extern/clean-core)


# ===============================================
# Compile flags

if (MSVC)
    set(SAMPLE_FLAGS 
        /MP
    )
else()
    set(SAMPLE_FLAGS 
        -Wall
        -Wno-unused-variable
        -Wpedantic
        -Wextra
        -Werror
    )
endif()


# ===============================================
# Build tests

if (CC_BUILD_TESTS)

    # doctest test library
    option(DOCTEST_WITH_TESTS "" OFF)
    option(DOCTEST_WITH_MAIN_IN_STATIC_LIB  "" OFF)
    add_subdirectory(extern/doctest)

    file(GLOB_RECURSE SOURCES
        "tests/*.cc"
        "tests/*.hh"
    )

    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

    add_executable(cc-tests ${SOURCES})

    target_link_libraries(cc-tests PUBLIC
        clean-core
        doctest
    )

    target_include_directories(cc-tests PUBLIC "tests")

    target_compile_options(cc-tests PUBLIC ${SAMPLE_FLAGS})

endif()


# ===============================================
# Folder grouping

foreach(TARGET_NAME
    clean-core
)
    if (TARGET ${TARGET_NAME}) 
        set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Extern") 
    endif()
endforeach()