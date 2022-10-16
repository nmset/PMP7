cmake_minimum_required(VERSION 3.0)

project(pmp7) 

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake") 

find_package(Boost COMPONENTS program_options CONFIG REQUIRED)
find_package(DBusCpp REQUIRED)

add_executable(pmp7 
    mpris_proxy.hpp  pod_proxy.hpp
    DBusMprisProxy.cpp  DBusPODProxy.cpp  main.cpp)

target_link_libraries(pmp7 ${Boost_LIBRARIES} ${DBUSCPP_LIBRARIES})

install(TARGETS pmp7 RUNTIME DESTINATION bin)


