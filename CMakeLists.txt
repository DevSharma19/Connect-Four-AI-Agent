cmake_minimum_required(VERSION 3.26)
project(Connect_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Connect_4 main.cpp
        BoardState.cpp
        BoardState.h
        AgentHuman.cpp
        AgentHuman.h
        AgentMinimaxBase.cpp
        AgentMinimaxBase.h
        AgentMinimaxAB.cpp
        AgentMinimaxAB.h
        AgentMinimaxABH.cpp
        AgentMinimaxABH.h
        AgentMinimaxTT.cpp
        AgentMinimaxTT.h
        GridBoardState.cpp
        GridBoardState.h
)

SET(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.6.0 COMPONENTS system window graphics audio REQUIRED)
file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")
target_link_libraries(Connect_4 sfml-system sfml-window sfml-graphics sfml-audio)