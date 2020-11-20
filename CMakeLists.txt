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

include_directories(include)
add_executable(ChaosEquations src/main.cpp src/Window.cpp src/Window.h src/utils.cpp src/utils.h src/albedo/Shader.cpp include/albedo/Shader.h include/albedo/opengl.h src/albedo/ShaderPreprocessor.cpp include/albedo/ShaderPreprocessor.h src/albedo/VertexBuffer.cpp include/albedo/VertexBuffer.h src/albedo/VertexAttribute.cpp include/albedo/VertexAttribute.h src/albedo/RenderBuffer.cpp include/albedo/RenderBuffer.h src/SimpleRenderBuffer.cpp src/SimpleRenderBuffer.h include/albedo/vertex_attributes.h src/albedo/Uniform.cpp include/albedo/Uniform.h include/albedo/uniforms.h include/albedo/uniform_type.h src/facade/FacadeRenderer.cpp include/facade/FacadeRenderer.h src/facade/Facade.cpp include/facade/Facade.h src/facade/GuiLayer.cpp include/facade/GuiLayer.h src/facade/layer/RectLayer.cpp include/facade/layer/RectLayer.h src/facade/FacadeEnvironment.cpp include/facade/FacadeEnvironment.h include/liblib/Math.h src/liblib/Math.cpp include/liblib/Colors.h src/TestScreen.cpp src/TestScreen.h src/Screen.cpp src/Screen.h include/facade/layer/layers.h include/facade/core.h)

target_link_libraries(ChaosEquations PRIVATE glfw glm::glm fmt::fmt ${OPENGL_LIBRARY} ${Boost_LIBRARIES})
