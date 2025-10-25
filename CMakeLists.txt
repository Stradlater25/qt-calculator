cmake_minimum_required(VERSION 3.16)
project(Calc)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(calc backend.cpp ${SOURCES} ${HEADERS})

target_link_libraries(calc Qt6::Core Qt6::Widgets)
  
