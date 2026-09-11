cmake_minimum_required(VERSION 3.10)

project(BinaryMorphology)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(BinaryMorphology
    src/main.cpp
    src/BinaryImage.cpp
    src/StructuringElement.cpp
    src/Morphology.cpp
)

add_executable(test_morphology
    test/test_morphology.cpp
    src/BinaryImage.cpp
    src/StructuringElement.cpp
    src/Morphology.cpp
)

target_include_directories(BinaryMorphology PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(test_morphology PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)