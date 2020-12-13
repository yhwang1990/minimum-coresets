cmake_minimum_required(VERSION 3.5)
project(minimum-coresets)

set(CMAKE_CXX_STANDARD 11)

include_directories(graph approximate optimal heuristic utils)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/module_path")

find_package(GLPK REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable(approx
        approximate/runApprox.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp)

add_executable(approx-r
        approximate/runApproxFixedSize.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp)

add_executable(opt
        graph/Digraph.hpp
        optimal/OptimalCoreset.cpp
        optimal/OptimalCoreset.h
        optimal/runOpt.cpp
        utils/IOUtil.hpp
        utils/Point2D.hpp
        utils/Validation.hpp)

add_executable(opt-r
        graph/Digraph.hpp
        optimal/OptimalCoreset.cpp
        optimal/OptimalCoreset.h
        optimal/runOptFixSize.cpp
        utils/IOUtil.hpp
        utils/Point2D.hpp
        utils/Validation.hpp)

add_executable(heur
        graph/DelaunayGraph.hpp
        graph/DominanceGraph.hpp
        heuristic/HeurCoreset.h
        heuristic/HeurCoreset.cpp
        heuristic/runHeur.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp
        utils/Validation.hpp)

add_executable(heur-r
        graph/DelaunayGraph.hpp
        graph/DominanceGraph.hpp
        heuristic/HeurCoreset.h
        heuristic/HeurCoreset.cpp
        heuristic/runHeurFixedSize.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp
        utils/Validation.hpp)

target_link_libraries(approx PUBLIC ann)
target_link_libraries(approx-r PUBLIC ann)
target_link_libraries(heur PUBLIC glpk)
target_link_libraries(heur-r PUBLIC glpk)
