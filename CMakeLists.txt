cmake_minimum_required(VERSION 3.5)

set(PROJECT tiny_simgrid)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)

add_executable(${PROJECT}
    ${SRC_DIR}/test.cpp
    ${SRC_DIR}/main_include.hpp

    # APP
    ${SRC_DIR}/App/Actor.cpp
    ${SRC_DIR}/App/Actor.h
    ${SRC_DIR}/App/AppSide.cpp
    ${SRC_DIR}/App/AppSide.h
    ${SRC_DIR}/App/AppState.cpp
    ${SRC_DIR}/App/AppState.h
    ${SRC_DIR}/App/Mailbox.cpp
    ${SRC_DIR}/App/Mailbox.h
    ${SRC_DIR}/App/StateManager.cpp
    ${SRC_DIR}/App/StateManager.h
    ${SRC_DIR}/App/Transition.cpp
    ${SRC_DIR}/App/Transition.h

    #Unfolding
    ${SRC_DIR}/Unfolding/CheckerSide.cpp
    ${SRC_DIR}/Unfolding/CheckerSide.h
    ${SRC_DIR}/Unfolding/Global.cpp
    ${SRC_DIR}/Unfolding/Global.hpp
    ${SRC_DIR}/Unfolding/UnfoldingChecker.cpp
    ${SRC_DIR}/Unfolding/UnfoldingChecker.h
    )

install(TARGETS ${PROJECTS} DESTINATION bin)

INCLUDE(CTest)
ENABLE_TESTING()
foreach(tnum 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 17 23)
  add_test(test-${tnum} ./tiny_simgrid ${tnum})
endforeach()
