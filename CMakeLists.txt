cmake_minimum_required(VERSION 3.17)
project(ChaosEquations)

set(CMAKE_CXX_STANDARD 17)

IF(APPLE)
    # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
    list(APPEND CMAKE_PREFIX_PATH "/usr/local")
    include_directories("/usr/local/include")
    add_definitions(-DGL_SILENCE_DEPRECATION)
ENDIF()

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(fmt REQUIRED)
find_library(OPENGL_LIBRARY OpenGL)

find_package(Boost 1.73.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ChaosEquations src/main.cpp src/Game.cpp src/Game.h src/utils.cpp src/utils.h src/albedo/Shader.cpp src/albedo/Shader.h src/common_gl.h src/albedo/ShaderPreprocessor.cpp src/albedo/ShaderPreprocessor.h src/albedo/VertexBuffer.cpp src/albedo/VertexBuffer.h src/albedo/VertexAttribute.cpp src/albedo/VertexAttribute.h src/albedo/RenderType.cpp src/albedo/RenderType.h src/SimpleRenderType.cpp src/SimpleRenderType.h src/albedo/VertexAttributeImpl.h src/albedo/vertex_attributes.h)

target_link_libraries(ChaosEquations PRIVATE glfw glm::glm fmt::fmt ${OPENGL_LIBRARY} ${Boost_LIBRARIES})
