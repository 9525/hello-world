cmake_minimum_required(VERSION 2.6)

project(yolov5_deserialize)

set(OpenCV_DIR "E:/work_project_code/3rdparty/opencv453")    ##1
set(OpenCV_INCLUDE_DIRS "E:/work_project_code/3rdparty/opencv453/include")    ##2
set(OpenCV_LIBS "E:/work_project_code/3rdparty/opencv453/x64/vc14/lib/opencv_world453.lib") 


add_definitions(-std=c++11)
add_definitions(-DAPI_EXPORTS)
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

find_package(CUDA REQUIRED)
message(STATUS "    libraries: ${CUDA_LIBRARIES}")
message(STATUS "    include path: ${CUDA_INCLUDE_DIRS}")

include_directories(${CUDA_INCLUDE_DIRS})
####
#enable_language(CUDA)  # add this line, then no need to setup cuda path in vs
####

include_directories(${PROJECT_SOURCE_DIR}/include)
# include and link dirs of cuda and tensorrt, you need adapt them if yours are different

set(TRT_DIR "E:/TensorRT-7.0.0.11") 
include_directories(${TRT_DIR}\\include)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}\\opencv2)

# -D_MWAITXINTRIN_H_INCLUDED for solving error: identifier "__builtin_ia32_mwaitx" is undefined
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Ofast -D_MWAITXINTRIN_H_INCLUDED")

# setup opencv
find_package(OpenCV QUIET
    NO_MODULE
    NO_DEFAULT_PATH
    NO_CMAKE_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_PACKAGE_REGISTRY
    NO_CMAKE_BUILDS_PATH
    NO_CMAKE_SYSTEM_PATH
    NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${TRT_DIR}\\lib)
link_directories(${OpenCV_DIR}\\x64\\vc14\\lib) #8

#add_executable(yolov5 ${PROJECT_SOURCE_DIR}/calibrator.cpp yolov5 ${PROJECT_SOURCE_DIR}/yolov5.cpp ${PROJECT_SOURCE_DIR}/yololayer.cu ${PROJECT_SOURCE_DIR}/yololayer.h ${PROJECT_SOURCE_DIR}/preprocess.h ${PROJECT_SOURCE_DIR}/preprocess.cu)
add_library(yolov5 SHARED ${PROJECT_SOURCE_DIR}/calibrator.cpp yolov5 ${PROJECT_SOURCE_DIR}/yolov5.cpp ${PROJECT_SOURCE_DIR}/AIDetect.h ${PROJECT_SOURCE_DIR}/yololayer.cu ${PROJECT_SOURCE_DIR}/yololayer.h ${PROJECT_SOURCE_DIR}/preprocess.h ${PROJECT_SOURCE_DIR}/preprocess.cu) 

target_link_libraries(yolov5 "nvinfer" "nvinfer_plugin") #9
target_link_libraries(yolov5 ${OpenCV_LIBS})        #10
target_link_libraries(yolov5 ${CUDA_LIBRARIES}) #11
target_link_libraries(yolov5 Threads::Threads) #12



