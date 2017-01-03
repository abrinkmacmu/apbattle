cmake_minimum_required(VERSION 2.8)

project(apbattle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_BUILD_TYPE Release)

message("Binary directory was ${PROJECT_BINARY_DIR}")
set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")
message("Binary directory is ${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

find_package(Boost 1.54.0 REQUIRED system)
find_package(Threads)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(SFML 2 REQUIRED system window graphics)

include_directories("${PROJECT_SOURCE_DIR}/include")

##set(NOVEL_PRINTER_SOURCES 
## "${cpp_project_SRC_DIR}/novel_printer.cpp"
## "${cpp_project_INCLUDE_DIR}/novel_printer.h")


add_executable(dummy_server src/test/dummy_server.cpp)
target_link_libraries(dummy_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(dummy_client src/test/dummy_client.cpp)
target_link_libraries(dummy_client ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(test_socket src/test/test_socket.cpp)
target_link_libraries(test_socket ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(manual_gui src/manual_gui.cpp src/battleship_gui.cpp src/battle_board.cpp)
target_link_libraries(manual_gui ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${SFML_LIBRARIES})



### Doxygen autogen ####

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${PROJECT_SOURCE_DIR}/Doxyfile ${PROJECT_SOURCE_DIR}/Doxyfile @ONLY)
	add_custom_target(all
	${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)