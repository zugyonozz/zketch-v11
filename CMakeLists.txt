# Versi CMake minimal, 3.10 sudah lebih dari cukup.
cmake_minimum_required(VERSION 3.10)

# Nama proyekmu, aku ambil dari nama foldernya.
# CXX artinya ini proyek C++.
project(zketch_v11 CXX)

# Atur standar C++ yang dipakai, C++20 itu pilihan yang bagus dan modern.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Hmph. Biar kamu tidak capek-capek menulis semua nama file .cpp satu per satu,
# kita kumpulkan saja semuanya secara otomatis ke dalam variabel bernama SOURCES.
file(GLOB SOURCES "src/*.cpp")

# Beritahu CMake untuk membuat sebuah program (executable).
# Namanya akan sama dengan nama proyek (zketch_v11)
# dan dibuat dari semua file .cpp yang sudah kita kumpulkan tadi.
# add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    src/temp.cpp # Tambahkan file baru kita di sini
)

# Beritahu target kita di mana harus mencari file header (.h).
# Ini akan menyelesaikan masalah 'file not found' mu selamanya.
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

target_compile_options(${PROJECT_NAME} PRIVATE 
    "-IC:/msys64/mingw64/include"
    "-IC:/msys64/mingw64/include/c++/15.2.0"
    "-IC:/msys64/mingw64/include/c++/15.2.0/x86_64-w64-mingw32"
)

# PENTING! Aku lihat kamu punya file zgdiplusinit.h.
# Itu artinya kamu pakai GDI+, kan? Kamu tidak bisa cuma #include,
# kamu harus *link* dengan library-nya! Aku sudah tambahkan ini untukmu.
# Kalau tidak, pasti nanti kamu akan dapat 'linker error' dan datang menangis lagi padaku.
target_link_libraries(${PROJECT_NAME} PRIVATE gdiplus gdi32 user32)

# Oh, dan aku lihat kamu punya folder 'bin' untuk hasil .exe-nya.
# Perintah ini akan mengatur agar CMake menaruh hasil akhirnya di sana,
# biar rapi seperti maumu.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

# Pesan saat proses build selesai. Biar kamu tahu semuanya berjalan lancar.
message(STATUS "Build selesai! Eksekutable ada di folder 'bin/${PROJECT_NAME}.exe'")