project(manager)
cmake_minimum_required(VERSION 3.21.1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(INSTALL_DIR "C:/dev/manager")

file(GLOB SOURCES "src/*.cpp")
add_executable(manager ${SOURCES})


target_include_directories(manager PRIVATE include)
target_link_directories(manager PUBLIC "./lib/shared")
target_link_libraries(manager libcryptopp)


install(DIRECTORY "${PROJECT_SOURCE_DIR}/lib/shared/" DESTINATION "${INSTALL_DIR}/bin")
install(TARGETS manager RUNTIME DESTINATION "${INSTALL_DIR}/bin")