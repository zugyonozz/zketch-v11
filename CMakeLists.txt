# Versi CMake minimal
cmake_minimum_required(VERSION 3.10)

# Nama proyek
project(zketch_v11 CXX)

# Standard C++ yang dipakai
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Kumpulkan semua file cpp
file(GLOB SOURCES "src/*.cpp")

# Buat executable
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    src/temp.cpp
)

# Tambahkan include path
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    "C:/msys64/mingw64/include"
    "C:/msys64/mingw64/include/c++/15.2.0"
    "C:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32"
)

# Tambahkan flag compile
target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
    # -Werror
)

# Link ke library Windows
target_link_libraries(${PROJECT_NAME} PRIVATE 
    gdiplus
    gdi32
    user32
	ole32 
	oleaut32
)

# Atur output executable ke folder bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

# Pesan build
message(STATUS "Build selesai! Eksekutable ada di folder 'bin/${PROJECT_NAME}.exe'")