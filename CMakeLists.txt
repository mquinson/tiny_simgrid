cmake_minimum_required(VERSION 3.5)

set(PROJECT tiny_simgrid)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC src)
set(UNFOLDING ${SRC}/unfolding)
set(APP ${SRC}/app)
set(API ${SRC}/api)

add_executable(${PROJECT} ${SRC}/main.cpp
    ${API}/CheckerSide.hpp
    ${API}/CheckerSide.cpp
    ${API}/ModelChecker.h
    ${API}/ModelChecker.cpp
    ${API}/RemoteSimulation.hpp
    ${API}/RemoteSimulation.cpp

#    ${APP}/app_include.hpp
    ${APP}/AppSide.h
    ${APP}/AppSide.cpp
#    ${APP}/main_include.hpp
    ${APP}/actor.h
    ${APP}/actor.cpp
    ${APP}/mailbox.h
    ${APP}/mailbox.cpp

    ${UNFOLDING}/Checker.hpp
    ${UNFOLDING}/state.h
    ${UNFOLDING}/state.cpp
    ${UNFOLDING}/transition.h
    ${UNFOLDING}/transition.cpp
    ${UNFOLDING}/EventSet.h
    ${UNFOLDING}/EventSet.cpp
    ${UNFOLDING}/UnfoldingEvent.h
    ${UNFOLDING}/UnfoldingEvent.cpp
    ${UNFOLDING}/configuration.h
    ${UNFOLDING}/configuration.cpp
    ${UNFOLDING}/UnfoldingChecker.h
    ${UNFOLDING}/UnfoldingChecker.cpp
    )
