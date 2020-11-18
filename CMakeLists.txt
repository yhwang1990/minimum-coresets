cmake_minimum_required(VERSION 3.5)
project(GRMR)

set(CMAKE_CXX_STANDARD 11)

include_directories(graph exact_grmr heuristic_grmr utils)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/module_path")

find_package(GLPK REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable(ExactGRMR
        graph/Digraph.hpp
        exact_grmr/ExactGRMR.cpp
        exact_grmr/ExactGRMR.h
        exact_grmr/runExactGRMR.cpp
        utils/IOUtil.hpp
        utils/Point2D.hpp
        utils/Validation.hpp)

add_executable(ExactGRMRLoss
        graph/Digraph.hpp
        exact_grmr/ExactGRMR.cpp
        exact_grmr/ExactGRMR.h
        exact_grmr/runExactGRMRLoss.cpp
        utils/IOUtil.hpp
        utils/Point2D.hpp
        utils/Validation.hpp)

add_executable(Example2D
        graph/Digraph.hpp
        exact_grmr/ExactGRMR.cpp
        exact_grmr/ExactGRMR.h
        exact_grmr/runExample2D.cpp
        utils/IOUtil.hpp
        utils/Point2D.hpp
        utils/Validation.hpp)

add_executable(HeurGRMR
        graph/DelaunayGraph.hpp
        graph/DominanceGraph.hpp
        heuristic_grmr/HeuristicGRMR.h
        heuristic_grmr/HeuristicGRMR.cpp
        heuristic_grmr/runGRMR.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp
        utils/Validation.hpp)

add_executable(HeurGRMRLoss
        graph/DelaunayGraph.hpp
        graph/DominanceGraph.hpp
        heuristic_grmr/HeuristicGRMR.h
        heuristic_grmr/HeuristicGRMR.cpp
        heuristic_grmr/runGRMRLoss.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp
        utils/Validation.hpp)

add_executable(DualGRMR
        graph/DelaunayGraph.hpp
        graph/DominanceGraph.hpp
        heuristic_grmr/HeuristicGRMR.h
        heuristic_grmr/HeuristicGRMR.cpp
        heuristic_grmr/runDualGRMR.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp
        utils/Validation.hpp)

add_executable(ExampleHD
        graph/DelaunayGraph.hpp
        graph/DominanceGraph.hpp
        heuristic_grmr/HeuristicGRMR.h
        heuristic_grmr/HeuristicGRMR.cpp
        heuristic_grmr/runExampleHD.cpp
        utils/IOUtil.hpp
        utils/Point.hpp
        utils/SetCover.hpp
        utils/Validation.hpp)

target_link_libraries(HeurGRMR PUBLIC glpk)
target_link_libraries(HeurGRMRLoss PUBLIC glpk)
target_link_libraries(DualGRMR PUBLIC glpk)
target_link_libraries(ExampleHD PUBLIC glpk)
