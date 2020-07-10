cmake_minimum_required(VERSION 3.5)

set(PROJECT tiny_simgrid)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)

add_executable(${PROJECT} ${SRC_DIR}/test.cpp 
    # APP
    ${SRC_DIR}/App/Actor.cpp
    ${SRC_DIR}/App/Actor.h
    ${SRC_DIR}/App/Mailbox.cpp
    ${SRC_DIR}/App/Mailbox.h
    ${SRC_DIR}/App/Transition.cpp
    ${SRC_DIR}/App/Transition.h

    #Unfolding
    ${SRC_DIR}/Unfolding/Global.cpp
    ${SRC_DIR}/Unfolding/Global.hpp
    ${SRC_DIR}/Unfolding/State.cpp
    ${SRC_DIR}/Unfolding/State.h
    ${SRC_DIR}/Unfolding/UnfoldingChecker.cpp
    ${SRC_DIR}/Unfolding/UnfoldingChecker.h
    )

install(TARGETS ${PROJECTS} DESTINATION bin)
