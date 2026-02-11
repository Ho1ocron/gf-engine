cmake_minimum_required(VERSION 3.14)
project(GF_Engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # TODO: move it somewhere


option(GF_LIB_PROVIDED_GLFW "ON if user provide GLFW. OFF for FetchContent" OFF)
option(GF_LIB_PROVIDED_GLM "ON if user provide GLM. OFF for FetchContent" OFF)
option(GF_LIB_PROVIDED_FREETYPE "ON if user provide Freetype. OFF for FetchContent" OFF)
set(_GF_ANY_LIB_PROVIDED (
    GF_LIB_PROVIDED_GLFW
    OR GF_LIB_PROVIDED_GLM
    OR GF_LIB_PROVIDED_FREETYPE
))

# user should define GF_USERINCLUDES to provide headers that
# are used by engine at compile-time (e.g. paths)
if(NOT DEFINED GF_USERINCLUDES)
    message(AUTHOR_WARNING "GF_USERINCLUDES is not defined! Didn't you forget to define it, did you?")
endif()

### third-party
add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include/)
# TODO: add the way for including libraries by user
# FetchContent begin
if(_GF_ANY_LIB_PROVIDED)
    include(FetchContent)

    if(NOT GF_LIB_PROVIDED_GLFW)
        message("glfw is not provided")
        FetchContent_Declare(
            glfw
            GIT_REPOSITORY git@github.com:glfw/glfw.git
            GIT_TAG 3.4
        )
        FetchContent_MakeAvailable(glfw)
    else()
        message("glfw is provided by user")
    endif()

    if(NOT GF_LIB_PROVIDED_GLM)
        message("glm is not provided")
        FetchContent_Declare(
            glm
            GIT_REPOSITORY git@github.com:g-truc/glm.git
            GIT_TAG 1.0.3
        )
        FetchContent_MakeAvailable(glm)
    else()
        message("glm is provided by user")
    endif()

    if(NOT GF_LIB_PROVIDED_FREETYPE)
        message("freetype is not provided")
        FetchContent_Declare(
            freetype
            GIT_REPOSITORY git@github.com:freetype/freetype.git
            GIT_TAG VER-2-13-3
        )
        FetchContent_MakeAvailable(freetype)
    else()
        message("freetype is provided by user")
    endif()

endif()
# FetchContent end

# TODO: consider why not
add_library(glfw::glfw ALIAS glfw)
add_library(glm::glm ALIAS glm)
add_library(freetype::freetype ALIAS freetype)

# our code


### paths to sublibraries (use in sublib's target_include_directories())
# sublibs must perform
# target_include_directories(foolib INTERFACE/PUBLIC ${GF_INCLUDES_PUBLIC})
set(GF_INCLUDES_PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
# GF_INCLUDES_PRIVATE is used to get path to .cpp/.h in add_library()
set(GF_INCLUDES_PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/gfe/")


### actual engine target
add_library(gfe
    ${GF_INCLUDES_PRIVATE}/engine/engine.h
    src/engine/engine.cpp
)
add_library(gfe::gfe ALIAS gfe)
target_include_directories(gfe
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
        ${GF_USERINCLUDES}/
)

target_link_libraries(gfe
    PUBLIC
        # third-party
        glad
        glm::glm
        glfw::glfw
        freetype::freetype
        # user
        gfe_app_constants
        # engine
)

### sublibraries
# interfaces
add_subdirectory(src/core/constants)
add_subdirectory(src/core/utils)
# core
add_subdirectory(src/core/render)
add_subdirectory(src/core/font)
add_subdirectory(src/core/resource_manager)
add_subdirectory(src/core/input)
# nodes (interfaces first)
add_subdirectory(src/nodes/idrawable)
add_subdirectory(src/nodes/camera)
add_subdirectory(src/nodes/label)
add_subdirectory(src/nodes/text)

add_custom_command(TARGET gfe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:gfe>/assets"
    COMMENT "gfe::Copying internal assets..."
)
