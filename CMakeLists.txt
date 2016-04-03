    cmake_minimum_required(VERSION 3.3)
    project(RobotinoCV)


    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -std=c++14")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14")

   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_directories(${OpenCV_INCLUDE_DIRS})
    add_definitions(${OpenCV_DEFINITIONS})

    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
    if(NOT OPENGL_FOUND)
        message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)

#    find_package(OpenCL REQUIRED)
#    include_directories(${OpenCL_INCLUDE_DIRS})
#    link_directories(${OpenCL_LIBRARY_DIRS})
#    add_definitions(${OpenGCL_DEFINITIONS})
#    if(NOT OPENCL_FOUND)
#        message(ERROR " OPENCL not found!")
#    endif(NOT OPENCL_FOUND)

    include_directories(/usr/local/robotino/api2/include)
    link_directories(/usr/local/robotino/api2/lib)


    set(SOURCE_FILES main.cpp)
    add_executable(RobotinoCV ${SOURCE_FILES})
    target_link_libraries(RobotinoCV ${OpenCV_LIBS} ${OPENGL_LIBRARIES})
    include_directories(${/home/ahmed/RobotinoCV}/opencv)
