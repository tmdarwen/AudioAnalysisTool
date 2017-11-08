cmake_minimum_required(VERSION 2.8.11)

project(AudioAnalysisTool)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the AudioAnalysisTool executable
add_executable(AudioAnalysisTool WIN32 main.cpp MainWindow.cpp MainWindow.h)

# Use the Widgets module from Qt 5.
target_link_libraries(AudioAnalysisTool Qt5::Widgets)
