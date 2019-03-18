cmake_minimum_required(VERSION 2.8)
project(wifiPositioning)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

############### dependencies ######################
# for mlpack
find_package(MLPACK REQUIRED)
include_directories(${MLPACK_INCLUDE_DIRS})

# for eigen
include_directories("/usr/include/eigen3")

# for opencv (OPTIONAL)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

# for boost
find_package(Boost 1.47.0 REQUIRED COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIRS})

set(THIRD_PARTY_LIBS
        ${MLPACK_LIBRARIES}
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES})

################# source and test ##########################
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
