cmake_minimum_required(VERSION 2.8.11)

if(VERSION_NUMBER)
	add_definitions(-DVERSION_NUMBER=${VERSION_NUMBER})
endif(VERSION_NUMBER)

if(BUILD_NUMBER)
	add_definitions(-DBUILD_NUMBER=${BUILD_NUMBER})
endif(BUILD_NUMBER)

project(AudioAnalysisTool)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# "Externals" consists of GoogleTest and AudioLib
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeSupport/CMakeLists.Externals.txt)
include_externals()

include_directories("${PROJECT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/audiolib-src/Source")

file(GLOB source_files [^.]*.h [^.]*.cpp)

# Tell CMake to create the AudioAnalysisTool executable
if(MSVC)
	add_executable(AudioAnalysisTool WIN32 ${source_files})
else()
	add_executable(AudioAnalysisTool ${source_files})
endif(MSVC)

include(${PROJECT_SOURCE_DIR}/CMakeSupport/CMakeLists.CompilerSettings.txt)

# Use the Widgets module from Qt 5.
target_link_libraries(AudioAnalysisTool Qt5::Widgets WaveFile)

set_target_properties(AudioAnalysisTool PROPERTIES FOLDER App)
