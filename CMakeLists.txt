cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME birdAI)
project(${PROJECT_NAME})
find_package(OpenGL)

file(GLOB Sources
        "src/*.cpp"
)

add_subdirectory("NEFT")

set(SOURCES ${Sources})

# detect and add SFML
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

# detect and add ImGui for SFML
set(ImGui-SFML_DIR "C:/Program Files (x86)/imgui_sfml/lib/cmake/ImGui-SFML")
find_package(ImGui-SFML REQUIRED)


add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
set(SFML_LIBS sfml-system sfml-window sfml-graphics)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS} NEFT ImGui-SFML::ImGui-SFML)

# Copy resources dir to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)