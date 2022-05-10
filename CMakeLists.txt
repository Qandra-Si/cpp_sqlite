cmake_minimum_required(VERSION 3.11 FATAL_ERROR) # need for FetchContent
project(cpp_sqlite)

find_package(Threads)

# see https://www.sqlite.org/howtocompile.html
include(FetchContent)
FetchContent_Declare(sqlite3 URL "https://www.sqlite.org/snapshot/sqlite-snapshot-202205041843.tar.gz")
FetchContent_MakeAvailable(sqlite3)
if (NOT sqlite3_POPULATED)
  FetchContent_Populate(sqlite3)
endif()

add_executable(cpp_sqlite main.cpp "${sqlite3_SOURCE_DIR}/sqlite3.c")
target_include_directories(cpp_sqlite PUBLIC "${sqlite3_SOURCE_DIR}")
set_target_properties(cpp_sqlite PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON)
target_link_libraries(cpp_sqlite ${CMAKE_THREAD_LIBS_INIT} dl)

