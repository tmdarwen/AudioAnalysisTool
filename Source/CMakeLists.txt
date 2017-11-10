cmake_minimum_required(VERSION 2.8.11)

project(AudioAnalysisTool)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

file(GLOB source_files [^.]*.h [^.]*.cpp)

# Tell CMake to create the AudioAnalysisTool executable
if(MSVC)
	add_executable(AudioAnalysisTool WIN32 ${source_files})
else()
	add_executable(AudioAnalysisTool ${source_files})
endif(MSVC)

# Use the Widgets module from Qt 5.
target_link_libraries(AudioAnalysisTool Qt5::Widgets)
