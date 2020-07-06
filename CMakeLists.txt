cmake_minimum_required(VERSION 3.5)

set(PROJECT tiny_simgrid)
project(${PROJECT} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC src)
set(UNFOLDING ${SRC}/Unfolding)
set(APP ${SRC}/App)
set(API ${SRC}/Api)

add_executable(${PROJECT}
    # ROOT
    ${SRC}/include.hpp
    ${SRC}/main.cpp

    # API
    ${API}/CheckerSide.hpp
    ${API}/CheckerSide.cpp
    ${API}/ModelChecker.h
    ${API}/ModelChecker.cpp
    ${API}/RemoteSimulation.hpp
    ${API}/RemoteSimulation.cpp

    # APP
    ${APP}/AppSide.h
    ${APP}/AppSide.cpp
    ${APP}/Actor.h
    ${APP}/Actor.cpp
    ${APP}/Mailbox.h
    ${APP}/Mailbox.cpp

    # UNFOLDING
    ${UNFOLDING}/Checker.hpp
    ${UNFOLDING}/EventSet.h
    ${UNFOLDING}/EventSet.cpp
    ${UNFOLDING}/EventSetNew.h
    ${UNFOLDING}/EventSetNew.cpp
    ${UNFOLDING}/UnfoldingChecker.h
    ${UNFOLDING}/UnfoldingChecker.cpp
    ${UNFOLDING}/UnfoldingEvent.h
    ${UNFOLDING}/UnfoldingEvent.cpp
    ${UNFOLDING}/Configuration.h
    ${UNFOLDING}/Configuration.cpp
    ${UNFOLDING}/State.h
    ${UNFOLDING}/State.cpp
    ${UNFOLDING}/Transition.h
    ${UNFOLDING}/Transition.cpp
    )

INCLUDE(CTest)
ENABLE_TESTING()
foreach(tnum 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17)
  add_test(test-${tnum} ./tiny_simgrid ${tnum})
endforeach()

