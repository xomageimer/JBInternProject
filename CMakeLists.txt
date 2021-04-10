cmake_minimum_required(VERSION 3.17)
project(JBInternProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(wxWidgets_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/WXWIN")  # для либы из сабмодуля тут стоит изменить WXWIN на wxWidgets_lib
set(wxWidgets_CONFIGURATION mwsu)
set(wxWidgets_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/WXWIN/lib/gcc_lib") # для либы из сабмодуля тут стоит изменить WXWIN на wxWidgets_lib/lib/gcc_lib

find_package(wxWidgets REQUIRED COMPONENTS core base)

#add_executable(main main.cpp)

add_executable(Application Front/App.cpp Front/App.h Front/Frame.cpp Front/Frame.h Back/ThreadPool.cpp Back/Searcher.cpp)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(Application ${wxWidgets_LIBRARIES})
endif()
