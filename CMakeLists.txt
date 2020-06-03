cmake_minimum_required(VERSION 3.5)

set(PROJECT prototype_git)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)

add_executable(${PROJECT} ${SRC_DIR}/test.cpp 
	${SRC_DIR}/Simulation.cpp 
	${SRC_DIR}/UnfoldingChecker.cpp
	${SRC_DIR}/UnfoldingChecker.hpp
        ${SRC_DIR}/UnfoldingEvent.cpp

        ${SRC_DIR}/actor/actor.h
        ${SRC_DIR}/actor/actor.cpp
        #${SRC_DIR}/state/.cpp
        ${SRC_DIR}/transition/transition.h
        ${SRC_DIR}/transition/transition.cpp
)


install(TARGETS ${PROJECTS} DESTINATION build)
