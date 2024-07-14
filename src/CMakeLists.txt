# Add raylib headers
include_directories(
    ${RAYLIB_INCLUDE}
)

# Add source files
file(
    GLOB SHOHIH_SRC
    "./board/*.cpp"
    "./piece/*.cpp"
    "./game/*.cpp"
)

# Shohih static library (../output/lib/libshohih.a)
add_library(${SHOHIH_LIB} ${SHOHIH_SRC})

# Main executable (../output/exe/shohih)
add_executable(${SHOHIH_MAIN} main.cpp)

# Link with Shohih library and Raylib
target_link_libraries(
    ${SHOHIH_MAIN}
    ${SHOHIH_LIB}
    raylib
)

# Copy resources/ directory to CMAKE_RUNTIME_OUTPUT_DIRECTORY
file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})