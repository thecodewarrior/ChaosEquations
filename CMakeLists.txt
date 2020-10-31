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
find_library(OPENGL_LIBRARY OpenGL)

find_package(Boost 1.73.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ChaosEquations src/main.cpp src/Game.cpp src/Game.h src/utils.cpp src/utils.h src/Shader.cpp src/Shader.h src/common_gl.h)

target_link_libraries(ChaosEquations PRIVATE glfw glm::glm ${OPENGL_LIBRARY} ${Boost_LIBRARIES})
