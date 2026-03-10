# Micro-Vector Editor (SVG)

**Course:** COP 290 | **Assignment:** Programming Assignment 1  
**Student Entry Number:** [2024CS50855]

## 1. Project Overview
This project is a sophisticated Vector Graphics Editor built from scratch in C++ using the **Qt Framework**. It allows users to create, manipulate, and save vector graphics in SVG format. The application is designed with a strong emphasis on **Object-Oriented Design**, **Smart Pointer memory management**, and **Code Modularity**, ensuring only one file exceeds 100 lines of code.

## 2. Key Features

### A. Geometric Primitives
* **Rectangle**: Standard axis-aligned rectangles.
* **Rounded Rectangle**: Rectangles with adjustable corner radii (implemented similar to Inkscape).
* **Circle**: Center-radius based circles.
* **Line**: Simple two-point connections.
* **Hexagon**: Regular polygons calculated using trigonometry.
* **Freehand Sketch (Polyline)**: Continuous drawing using `QPainterPath`.
* **Text**: Editable text elements with font support.

### B. Core Functionality
* **File I/O**: Custom-built XML/SVG parser (no third-party libraries used). Supports **Open**, **Save**, and **Save As**.
* **Editing Tools**:
    * **Cut/Copy/Paste**: Features "Smart Paste" (staircase offset) and "Paste-Once" logic for Cut operations.
    * **Undo/Redo**: Infinite history stack implemented via the **Command Pattern**.
* **Styling**: Full control over **Stroke Color**, **Fill Color**, and **Stroke Width**.

## 3. Architecture & Design Patterns
To adhere to the **<100 lines per file limit**, the codebase uses a split-file architecture:

* **Core vs. Logic Split**: Complex classes are divided into `_core.cpp` (data/drawing) and `_logic.cpp` (math/interaction).
* **Command Pattern**: All canvas modifications are encapsulated in Command objects (`add_shape_command`, `transform_command`, etc.), enabling robust Undo/Redo.
* **Factory Pattern**: Used in `canvas_factory.cpp` to generate shapes dynamically based on the active tool.
* **Smart Pointers**: Extensive use of `std::unique_ptr` for ownership management, particularly for the Clipboard and Undo Stack.

## 4. File Structure
The project is organized into modular components:

### Canvas Engine
* `canvas.h` / `canvas_core.cpp`: Main canvas initialization.
* `canvas_mouse_logic_1.cpp`: Creation mode (drawing new shapes).
* `canvas_mouse_logic_2.cpp`: Interaction mode (selection, moving, resizing).
* `canvas_clipboard.cpp`: Copy/Cut/Paste logic.
* `canvas_commands.cpp`: Undo/Redo stack interfaces.
* `canvas_transform.cpp`: Transformation math.
* `canvas_factory.cpp`: Shape instantiation factory.
* `canvas_utils.cpp` / `canvas_internals.cpp`: Helper utilities.

### Shapes (Model)
* `graphics_object.h` / `.cpp`: Base abstract class.
* `circle.h`, `circle_core.cpp`, `circle_logic.cpp`
* `hexagon.h`, `hexagon_core.cpp`, `hexagon_logic.cpp`
* `polyline.h`, `polyline_core.cpp`, `polyline_logic.cpp`
* `rectangle.h`, `rectangle.cpp`
* `rounded_rectangle.h`, `rounded_rectangle.cpp`
* `line.h`, `line.cpp`
* `text.h`, `text.cpp`

### Commands (Undo/Redo)
* `commands.h`: Base interface.
* `add_shape_command.h` / `.cpp`
* `delete_shape_command.h` / `.cpp`
* `transform_command.h` / `.cpp`
* `change_color_command.h` / `.cpp`

### SVG Parser (Custom Implementation)
* `parser.h`: Static interface.
* `parser_io.cpp`: Main load/save logic.
* `parser_utils.cpp`: XML attribute parsing helpers.
* `parser_rectangle.cpp`, `parser_circle.cpp`, `parser_line.cpp`, `parser_polyline.cpp`, `parser_hexagon.cpp`, `parser_text.cpp`: Tag-specific parsers.

### User Interface
* `mainwindow.h` / `.cpp`: Main window shell.
* `mainwindow_top_toolbar.cpp`: File and Edit actions.
* `mainwindow_left_toolbar.cpp`: Tool selection palette.
* `tool_type.h`: Tool state definitions.

## 5. Build Instructions
The project uses **CMake** as the build system.

### Prerequisites:
* **CMake** (Version 3.5 or higher)
* **Qt 5** or **Qt 6** (Community Version)
* **C++ Compiler** (GCC/Clang/MSVC) supporting C++17

### Steps to Compile:
1. Navigate to the project root directory:
```bash
   cd project
```
2. Create a build Directory:
 ```bash
    mkdir build
    cd build
```
3. Run CMake:
```bash
    cmake ..
```
4. Compile the project:
```bash
    make
```
5. Run the application:
```bash
    MicroVectorEditor
```

## 6. Submission Details
Format: Tar archive (<2024CS50855>.tar).

Contents: Source code, CMakeLists.txt, and README.md.

Note: No third-party XML parsers were used; a custom parser was implemented as per assignment rules.