
cmake_minimum_required(VERSION 3.20)

project(Minecraft2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(RmlUi CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(minecraft
    ${SOURCES}
    external/glad/src/glad.c
)

target_include_directories(minecraft PRIVATE
    external/glad/include
)

target_link_libraries(minecraft PRIVATE
    glfw
    nlohmann_json::nlohmann_json
    RmlUi::RmlUi
    OpenGL::GL
)
