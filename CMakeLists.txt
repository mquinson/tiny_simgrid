cmake_minimum_required(VERSION 3.5)

set(PROJECT prototype_git)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)

add_executable(${PROJECT} ${SRC_DIR}/main.cpp
        ${SRC_DIR}/actor/actor.h
        ${SRC_DIR}/actor/actor.cpp
        ${SRC_DIR}/state/state.h
        ${SRC_DIR}/state/state.cpp
        ${SRC_DIR}/transition/transition.h
        ${SRC_DIR}/transition/transition.cpp
        ${SRC_DIR}/mailbox/mailbox.h
        ${SRC_DIR}/mailbox/mailbox.cpp
        ${SRC_DIR}/EventSet/EventSet.h
        ${SRC_DIR}/EventSet/EventSet.cpp
        ${SRC_DIR}/UnfoldingEvent/UnfoldingEvent.h
        ${SRC_DIR}/UnfoldingEvent/UnfoldingEvent.cpp
        ${SRC_DIR}/configuration/configuration.h
        ${SRC_DIR}/configuration/configuration.cpp
        ${SRC_DIR}/UnfoldingChecker/UnfoldingChecker.h
        ${SRC_DIR}/UnfoldingChecker/UnfoldingChecker.cpp
)

install(TARGETS ${PROJECTS} DESTINATION build)
