cmake_minimum_required(VERSION 3.10)
project(PolyBridgeWaterSimulation LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

find_package(OpenGL REQUIRED)

include_directories(
    ${INCLUDE_DIR}
    ${VENDOR_DIR}/glad/include
)

find_package(glfw3 REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES "${SOURCE_DIR}/*.cpp")

set(GLAD_SOURCE_FILE "${VENDOR_DIR}/glad/src/glad.c")
set_source_files_properties(${GLAD_SOURCE_FILE} PROPERTIES LANGUAGE C)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${GLAD_SOURCE_FILE}
)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
