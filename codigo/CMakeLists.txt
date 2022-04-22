cmake_minimum_required(VERSION 3.20.2)
project(logistics-codigo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(include)
add_executable(logistics
    main.cpp
    src/dataset.cpp
    src/entities/delivery.cpp
    src/entities/driver.cpp
    src/interact.cpp
    src/ui.cpp
    src/sparse_hypercube.cpp
    src/scenarios/reward_optimization.cpp
    src/scenarios/driver_optimization.cpp
    src/scenarios/start_optimization.cpp
)