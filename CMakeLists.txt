cmake_minimum_required (VERSION 3.12)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED true)

project ("Othello Demo")

include (${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup (NO_OUTPUT_DIRS)

aux_source_directory (${PROJECT_SOURCE_DIR}/src PROJECT_SOURCE_FILES)
add_executable (OthelloDemo ${PROJECT_SOURCE_FILES})
target_link_libraries (OthelloDemo ${CONAN_LIBS})

file (GENERATE OUTPUT "${PROJECT_BINARY_DIR}/$<$<BOOL:${PROP_GENERATOR_IS_MULTI_CONFIG}>:$<CONFIG>/>lark.config" CONTENT "SdkPath=${CONAN_LARKSDK_ROOT}")

file (COPY "${PROJECT_SOURCE_DIR}/res" DESTINATION ${PROJECT_BINARY_DIR})
