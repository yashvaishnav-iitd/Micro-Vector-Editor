cmake_minimum_required(VERSION 3.15)

# Project Definition
project(MicroVectorEditor VERSION 1.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt Setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Required Packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Create the Executable Target
add_executable(MicroVectorEditor
    #Core & UI
    "src/main.cpp"

    "src/ui/mainwindow.h"
    "src/ui/mainwindow.cpp"
    "src/ui/mainwindow_left_toolbar.cpp"
    "src/ui/mainwindow_top_toolbar.cpp"

    "src/tools/tool_type.h"

    # Canvas Engine
    "src/canvas/canvas.h"
    "src/canvas/canvas_core.cpp"
    "src/canvas/canvas_commands.cpp"
    "src/canvas/canvas_clipboard.cpp"
    "src/canvas/canvas_internals.cpp"
    "src/canvas/canvas_factory.cpp"
    "src/canvas/canvas_transform.cpp"
    "src/canvas/canvas_utils.cpp"
    "src/canvas/canvas_mouse_logic_1.cpp"
    "src/canvas/canvas_mouse_logic_2.cpp"

    # Shapes
    "src/graphics/graphics_object.h"
    "src/graphics/graphics_object.cpp"

    "src/shapes/circle.h"
    "src/shapes/circle_core.cpp"
    "src/shapes/circle_logic.cpp"

    "src/shapes/hexagon.h"
    "src/shapes/hexagon_core.cpp"
    "src/shapes/hexagon_logic.cpp"

    "src/shapes/line.h"
    "src/shapes/line.cpp"

    "src/shapes/polyline.h"
    "src/shapes/polyline_core.cpp"
    "src/shapes/polyline_logic.cpp"

    "src/shapes/rectangle.h"
    "src/shapes/rectangle.cpp"

    "src/shapes/rounded_rectangle.h"
    "src/shapes/rounded_rectangle.cpp"

    "srcshapes//text.h"
    "src/shapes/text.cpp"

    # Commands (Undo/Redo)
    "src/commands/commands.h"

    "src/commands/add_shape_command.h"
    "src/commands/add_shape_command.cpp"

    "src/commands/change_color_command.h"
    "src/commands/change_color_command.cpp"

    "src/commands/transform_command.h"
    "src/commands/transform_command.cpp"

    "src/commands/delete_shape_command.h"
    "src/commands/delete_shape_command.cpp"

    #Parser (File I/O)
    "src/parser/parser.h"
    "src/parser/parser_io.cpp"
    "src/parser/parser_utils.cpp"

    "src/parser/parser_circle.cpp"
    "src/parser/parser_hexagon.cpp"
    "src/parser/parser_line.cpp"
    "src/parser/parser_polyline.cpp"
    "src/parser/parser_rectangle.cpp"
    "src/parser/parser_text.cpp"
)

# Target-Based Include Directories
# "PRIVATE" means only this target needs these headers.
target_include_directories(MicroVectorEditor PRIVATE
    src
    src/shapes
    src/canvas
    src/parser
    src/ui
    src/commands
)

# Link Libraries
target_link_libraries(MicroVectorEditor PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

# Compile Options / Warnings
# Adds useful warnings for GCC/Clang and MSVC
target_compile_options(MicroVectorEditor PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

