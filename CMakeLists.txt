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
        ${SRC_DIR}/actor/actor.h
        ${SRC_DIR}/actor/actor.cpp
        ${SRC_DIR}/state/state.h
        ${SRC_DIR}/state/state.cpp
        ${SRC_DIR}/transition/transition.h
        ${SRC_DIR}/transition/transition.cpp
        ${SRC_DIR}/mailbox/mailbox.h
        ${SRC_DIR}/mailbox/mailbox.cpp
        ${SRC_DIR}/EventSet/eventset.h
        ${SRC_DIR}/EventSet/eventset.cpp
        ${SRC_DIR}/UnfoldingEvent/unfoldingevent.h
        ${SRC_DIR}/UnfoldingEvent/unfoldingevent.cpp
        ${SRC_DIR}/configuration/configuration.h
        ${SRC_DIR}/configuration/configuration.cpp
)

install(TARGETS ${PROJECTS} DESTINATION build)
