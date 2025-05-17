cmake_minimum_required(VERSION 3.10)

project(ImageLoader CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather source files
file(GLOB SRC_FILES "Source/*.cpp")

# Add ImGui source files
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(IMGUI_SRC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    # Optional demo:
    # ${IMGUI_DIR}/imgui_demo.cpp
)

# Add the executable
add_executable(image_loader ${SRC_FILES} ${IMGUI_SRC})

# Add the ImGui include directory
target_include_directories(image_loader PRIVATE ${IMGUI_DIR} $(GLFW_INCLUDE_DIR))

target_link_directories(image_loader PRIVATE $(GLFW_LIB_DIR))

target_link_libraries(image_loader PRIVATE glfw3)