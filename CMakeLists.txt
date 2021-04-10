cmake_minimum_required(VERSION 3.17)
project(JBInternProject)

set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/WXWIN")
set(wxWidgets_CONFIGURATION mwsu)
set(wxWidgets_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/WXWIN/lib/gcc_lib")

find_package(wxWidgets REQUIRED COMPONENTS core base)

#add_executable(JBInternProject main.cpp)

add_executable(UI_elements Front/App.cpp Front/App.h Front/Frame.cpp Front/Frame.h)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(UI_elements ${wxWidgets_LIBRARIES})
endif()
