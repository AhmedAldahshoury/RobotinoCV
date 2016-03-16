    cmake_minimum_required(VERSION 3.3)
    project(RobotinoCV)


    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -std=c++14")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14")

   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_directories(${OpenCV_INCLUDE_DIRS})
    add_definitions(${OpenCV_DEFINITIONS})

    if(WITH_OPENCLAMDFFT)
        find_path(CLAMDFFT_ROOT_DIR
                NAMES include/clAmdFft.h
                PATHS ENV CLAMDFFT_PATH ENV ProgramFiles
                PATH_SUFFIXES clAmdFft AMD/clAmdFft
                DOC "AMD FFT root directory"
                NO_DEFAULT_PATH)

        find_path(CLAMDFFT_INCLUDE_DIR
                NAMES clAmdFft.h
                HINTS ${CLAMDFFT_ROOT_DIR}
                PATH_SUFFIXES include
                DOC "clAmdFft include directory")

        if(CLAMDFFT_INCLUDE_DIR)
            set(HAVE_CLAMDFFT 1)
            list(APPEND OPENCL_INCLUDE_DIRS "${CLAMDFFT_INCLUDE_DIR}")
        endif()
    endif()

    if(WITH_OPENCLAMDBLAS)
        find_path(CLAMDBLAS_ROOT_DIR
                NAMES include/clAmdBlas.h
                PATHS ENV CLAMDBLAS_PATH ENV ProgramFiles
                PATH_SUFFIXES clAmdBlas AMD/clAmdBlas
                DOC "AMD FFT root directory"
                NO_DEFAULT_PATH)

        find_path(CLAMDBLAS_INCLUDE_DIR
                NAMES clAmdBlas.h
                HINTS ${CLAMDBLAS_ROOT_DIR}
                PATH_SUFFIXES include
                DOC "clAmdFft include directory")

        if(CLAMDBLAS_INCLUDE_DIR)
            set(HAVE_CLAMDBLAS 1)
            list(APPEND OPENCL_INCLUDE_DIRS "${CLAMDBLAS_INCLUDE_DIR}")
        endif()
    endif()

    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
    if(NOT OPENGL_FOUND)
        message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)

    find_package(OpenCL REQUIRED)
    include_directories(${OpenCL_INCLUDE_DIRS})
    link_directories(${OpenCL_LIBRARY_DIRS})
    add_definitions(${OpenGCL_DEFINITIONS})
    if(NOT OPENCL_FOUND)
        message(ERROR " OPENCL not found!")
    endif(NOT OPENCL_FOUND)

    include_directories(/usr/local/robotino/api2/include)
    link_directories(/usr/local/robotino/api2/lib)




    set(SOURCE_FILES main.cpp)
    add_executable(RobotinoCV ${SOURCE_FILES})
    target_link_libraries(RobotinoCV ${OpenCV_LIBS} ${OPENGL_LIBRARIES})
    include_directories(${/home/ahmed/RobotinoCV}/opencv)
