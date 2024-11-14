# rm -rf build
# cmake -B build && cmake --build build
# for tests:
# cmake --build build --target test


cmake_minimum_required (VERSION 3.11)

project (HWMX)

set (EXEC_FILE Matrix.out)
# set (SRCS src/main.cpp src/Matrix.cpp)

add_library (lMatrix STATIC ${CMAKE_SOURCE_DIR}/src/Matrix.cpp)
target_compile_features (lMatrix PUBLIC cxx_std_11)

add_executable (${EXEC_FILE})
target_link_libraries (${EXEC_FILE} PUBLIC lMatrix)
target_include_directories (${EXEC_FILE} PUBLIC "include")
target_sources (${EXEC_FILE} PRIVATE ${CMAKE_SOURCE_DIR}/src/main.cpp)
# target_sources (${EXEC_FILE} PRIVATE ${SRCS})
target_compile_features (${EXEC_FILE} PUBLIC cxx_std_11)

include (Ctest)
enable_testing()
file(GLOB testfiles "${CMAKE_SOURCE_DIR}/test/*.dat")
foreach(file ${testfiles})
    add_test (NAME ${file}
        COMMAND bash ${CMAKE_SOURCE_DIR}/test/test.sh ${CMAKE_SOURCE_DIR} ${file})
    set_tests_properties(${file} PROPERTIES DEPENDS ${EXEC_FILE})
endforeach()
