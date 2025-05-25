cmake_minimum_required(VERSION 3.29)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Project VERSION 0.0.1)
include(CMakeDependencies)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

message(NOTICE "🔷 load SDL3")
FetchContent_MakeAvailable(SDL3)
message(NOTICE "✅ SDL3 loaded")

message(NOTICE "🔷 load glm")
FetchContent_MakeAvailable(glm)
message(NOTICE "✅ glm loaded")

message(NOTICE "🔷 load spdlog")
FetchContent_MakeAvailable(spdlog)
message(NOTICE "✅ spdlog loaded")

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADER_DIRS "src/*.h")

set(INCLUDE_DIRS "")
foreach(HEADER ${PROJECT_HEADER_DIRS})
    get_filename_component(DIR ${HEADER} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

add_executable(Project ${PROJECT_SOURCE_FILES})
target_include_directories(Project PRIVATE ${INCLUDE_DIRS})

target_link_libraries(Project PRIVATE
    Vulkan::Vulkan
    SDL3::SDL3-static
    glm
    spdlog
)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
    set_target_properties(Project PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

target_compile_definitions(Project PRIVATE
    PROJECT_NAME="${CMAKE_PROJECT_NAME}"
    PROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    PROJECT_VK_VERSION_MAJOR=1
    PROJECT_VK_VERSION_MINOR=3
    PROJECT_VK_VERSION_PATCH=204

    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<NOT:$<CONFIG:Debug>>:RELEASE_BUILD>
    $<$<BOOL:${WIN32}>:OS_WINDOWS>
    $<$<BOOL:${APPLE}>:OS_MACOS>
    $<$<BOOL:${UNIX}>:OS_LINUX>
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
    RESULT_VARIABLE result
    ERROR_VARIABLE error
)