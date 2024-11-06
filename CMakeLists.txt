# rm -rf build
# cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# cmake --build build
# for tests:
# cmake --build ./build --target test


cmake_minimum_required (VERSION 3.15)

project (HWMX)

set (EXEC_FILE Matrix.out)
set (SRCS ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/Matrix.cpp)

add_executable (${EXEC_FILE})
# add_library (Matrix STATIC ${CMAKE_SOURCE_DIR}/src/Matrix.cpp ${CMAKE_SOURCE_DIR}/include/Matrix.hpp)
# target_link_libraries (${EXEC_FILE} ${Matrix})
target_include_directories (${EXEC_FILE} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_sources (${EXEC_FILE} PRIVATE ${SRCS})
target_compile_features (${EXEC_FILE} PUBLIC cxx_std_14)

include (Ctest)
enable_testing()
file (GLOB testfiles ${CMAKE_SOURCE_DIR}/test/*.dat)
foreach (file ${testfiles})
    add_test (NAME ${file}
    COMMAND bash ${CMAKE_SOURCE_DIR}/test/test.sh file ${EXEC_FILE} ${CMAKE_SOURCE_DIR}
    )
    set_tests_properties (${file} PROPERTIES DEPENDS ${EXEC_FILE})
endforeach()
