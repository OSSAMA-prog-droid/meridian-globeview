cmake_minimum_required(VERSION 3.15)
project(MeridianGlobeView LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Offline/CI builds use the stub GL layer by default (no GPU/driver needed).
# Set -DGLOBEVIEW_STUB_GL=0 and link a real GL loader for a runnable client.
option(GLOBEVIEW_STUB_GL "Use stub OpenGL entry points" ON)

file(GLOB_RECURSE GLOBEVIEW_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(globeview ${GLOBEVIEW_SOURCES})
target_include_directories(globeview PUBLIC include src)
if(GLOBEVIEW_STUB_GL)
  target_compile_definitions(globeview PUBLIC GLOBEVIEW_STUB_GL=1)
endif()

add_executable(globeview_app src/main.cpp)
target_link_libraries(globeview_app PRIVATE globeview)

if(MSVC)
  target_compile_options(globeview PRIVATE /W4)
else()
  target_compile_options(globeview PRIVATE -Wall -Wextra)
endif()
