cmake_minimum_required(VERSION 3.10)
project(Laboratorio2Cache CXX)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

add_executable(1anidados 1anidados.cpp)
add_executable(2mutiplicacionmatrices 2mutiplicacionmatrices.cpp)
add_executable(3multiplicacionbloques 3multiplicacionbloques.cpp)
add_executable(4strassen 4strassen.cpp)
add_executable(5winograd 5winograd.cpp)

set(EXPERIMENT_N 2500)
set(LOOP_N 5000)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RESULT_FILES
    ${PROJECT_DIR}/tiempospart1.csv
    ${PROJECT_DIR}/tiempospart2.csv
    ${PROJECT_DIR}/tiempospart3.csv
    ${PROJECT_DIR}/tiempospart4.csv
    ${PROJECT_DIR}/tiempospart5.csv)

add_custom_command(
    OUTPUT ${RESULT_FILES}
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} $<TARGET_FILE:1anidados> ${LOOP_N}
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} $<TARGET_FILE:2mutiplicacionmatrices> ${EXPERIMENT_N}
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} $<TARGET_FILE:3multiplicacionbloques> ${EXPERIMENT_N}
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} $<TARGET_FILE:4strassen> ${EXPERIMENT_N}
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} $<TARGET_FILE:5winograd> ${EXPERIMENT_N}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_DIR}/graficas
    DEPENDS 1anidados 2mutiplicacionmatrices 3multiplicacionbloques 4strassen 5winograd
    VERBATIM)

add_custom_command(
    OUTPUT ${PROJECT_DIR}/graficas/.graficas_generadas
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} ${Python3_EXECUTABLE} 1grafica.py
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} ${Python3_EXECUTABLE} 2grafica.py
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} ${Python3_EXECUTABLE} 3grafica.py
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} ${Python3_EXECUTABLE} 4grafica.py
    COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_DIR}/graficas/.graficas_generadas
    DEPENDS ${RESULT_FILES} 1grafica.py 2grafica.py 3grafica.py 4grafica.py
    VERBATIM)

add_custom_target(laboratorio DEPENDS ${PROJECT_DIR}/graficas/.graficas_generadas)

add_custom_target(perfil_cachegrind
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_DIR} bash perfil_cachegrind.sh
        $<TARGET_FILE:2mutiplicacionmatrices>
        $<TARGET_FILE:3multiplicacionbloques>
    DEPENDS 2mutiplicacionmatrices 3multiplicacionbloques
    USES_TERMINAL)

add_dependencies(laboratorio perfil_cachegrind)
