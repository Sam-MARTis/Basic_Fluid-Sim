cmake_minimum_required(VERSION 3.16)

project(FluidSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(fluid_sim
    main.cpp
    aux-functions.cpp
    initializations.cpp
    display-functions.cpp
    core-sim-functions.cpp
    imgui/imgui.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui-sfml/imgui-SFML.cpp
)

target_include_directories(fluid_sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui-sfml
)

target_link_libraries(fluid_sim PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    OpenGL::GL
)
