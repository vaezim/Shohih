file(
    GLOB shohih_SRC
    "./board/*.cpp"
    "./piece/*.cpp"
)

# Shohih static library (../output/lib/libshohih.a)
add_library(${SHOHIH_LIB} ${shohih_SRC})

# Executable path: ../output/exe/shohih
set(SHOHIH_MAIN shohih_main)
add_executable(${SHOHIH_MAIN} main.cpp)

target_link_libraries(
    ${SHOHIH_MAIN}
    ${SHOHIH_LIB}
)