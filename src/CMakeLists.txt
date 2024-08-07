# Add third-party library headers
include_directories(
    ${RAYLIB_INCLUDE}
    ${HTTPLIB_INCLUDE}
)

# Add source files
file(
    GLOB SHOHIH_SRC
    "./game/*.cpp"
    "./board/*.cpp"
    "./piece/*.cpp"
    "./network/*.cpp"
)

# Shohih static library (../output/lib/libshohih.a)
add_library(${SHOHIH_LIB} ${SHOHIH_SRC})

# Main executable (../output/exe/shohih_main)
add_executable(${SHOHIH_MAIN} main.cpp)

# Link with Shohih and third-party libraries
target_link_libraries(
    ${SHOHIH_MAIN}
    ${SHOHIH_LIB}
    raylib
)

# Server executable (../output/exe/shohih_server)
add_executable(${SHOHIH_SERVER} shohih_server.cpp)

# Link with Shohih and third-party libraries
target_link_libraries(
    ${SHOHIH_SERVER}
    ${SHOHIH_LIB}
)

# Copy resources/ directory to CMAKE_RUNTIME_OUTPUT_DIRECTORY
file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})