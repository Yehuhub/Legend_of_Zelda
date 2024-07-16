cmake_minimum_required (VERSION 3.26)


project (oop2_project)
set (MY_AUTHORS "Yuval_Hasson-Or_Shain-Yehu_Raccah")

include (cmake/CompilerSettings.cmake)

set(SFML_URL "https://github.com/SFML/SFML.git")
if(APPLE)
    set(SFML_VERSION 2.6.1)
    set(SFML_DIR "/opt/homebrew/Cellar/sfml/${SFML_VERSION}/lib/cmake/SFML")
    add_executable (${CMAKE_PROJECT_NAME})
elseif(WIN32)
    set(SFML_VERSION 2.6.0)
    set(SFML_DIR "C:/SFML/SFML-${SFML_VERSION}/lib/cmake/SFML")
    add_executable (${CMAKE_PROJECT_NAME} WIN32)
endif()

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)

# Attempt to find SFML libraries
find_package (SFML ${SFML_VERSION} COMPONENTS graphics audio QUIET)

# If SFML is not found, download it
if (NOT SFML_FOUND)
    message("SFML not Found!\nDownloading SFML")
    set(SFML_VERSION 2.6.1)
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG ${SFML_VERSION}
        CMAKE_ARGS -DSFML_BUILD_SHARED_LIBS=TRUE
    )
    FetchContent_MakeAvailable(SFML)

    set(SFML_DIR "${sfml_BINARY_DIR}")
else()
    message("SFML found")
endif()

if(APPLE)
    if(NOT SFML_FOUND)
        set(SFML_LOCATION "${sfml_BINARY_DIR}")
    else()
        set(SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
        set(SFML_LOCATION "/opt/homebrew/Cellar/sfml/${SFML_VERSION}")
    endif()
    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio)

elseif(WIN32)
    if(NOT SFML_FOUND)
        set(SFML_LOCATION "${sfml_BINARY_DIR}")
    else()
        set(SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
        set(SFML_LOCATION "C:/SFML/SFML-${SFML_VERSION}")
    endif()
    set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)
    include (cmake/SFML.cmake)

endif()


