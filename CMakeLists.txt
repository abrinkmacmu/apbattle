cmake_minimum_required(VERSION 2.8)

project(apbattle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_BUILD_TYPE Release)

message("Binary directory was ${PROJECT_BINARY_DIR}")
set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")
message("Binary directory is ${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(Boost 1.54.0 REQUIRED system)
find_package(Threads)
find_package(SFML 2 REQUIRED system window graphics)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	)

set(SOURCE_FILES 
	src/counting_agent.cpp
	src/manual_agent.cpp 
	src/battleship_agent.cpp 
	src/socket_connection.cpp
	src/battle_board.cpp
	src/player_battle_board.cpp
	src/enemy_battle_board.cpp
	)

add_executable(run_random_agent
	src/run_random_agent.cpp 
	${SOURCE_FILES})
target_link_libraries(run_random_agent 
	${Boost_LIBRARIES} 
	${CMAKE_THREAD_LIBS_INIT} 
	${SFML_LIBRARIES} 
	)

add_executable(run_manual_agent
  src/run_manual_agent.cpp 
	${SOURCE_FILES})
target_link_libraries(run_manual_agent 
	${Boost_LIBRARIES} 
	${CMAKE_THREAD_LIBS_INIT} 
	${SFML_LIBRARIES} 
	)

add_executable(run_counting_agent
  src/run_counting_agent.cpp 
	${SOURCE_FILES})
target_link_libraries(run_counting_agent 
	${Boost_LIBRARIES} 
	${CMAKE_THREAD_LIBS_INIT} 
	${SFML_LIBRARIES} 
	)


########################
### Doxygen autogen ####
########################

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${PROJECT_SOURCE_DIR}/Doxyfile ${PROJECT_SOURCE_DIR}/Doxyfile @ONLY)
	add_custom_target(all
	${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)







##########
## Testing
##########


##set(NOVEL_PRINTER_SOURCES 
## "${cpp_project_SRC_DIR}/novel_printer.cpp"
## "${cpp_project_INCLUDE_DIR}/novel_printer.h")


#add_executable(dummy_server src/test/dummy_server.cpp)
#target_link_libraries(dummy_server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

#add_executable(dummy_client src/test/dummy_client.cpp)
#target_link_libraries(dummy_client ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

#add_executable(test_socket src/test/test_socket.cpp)
#target_link_libraries(test_socket ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

#add_executable(manual_gui src/manual_gui.cpp src/battleship_gui.cpp src/battle_board.cpp)
#target_link_libraries(manual_gui 
#	${Boost_LIBRARIES} 
#	${CMAKE_THREAD_LIBS_INIT} 
#	${SFML_LIBRARIES} 
#	)

#add_executable(test_msgs src/test/test_msgs.cpp)


# add_executable(test_board
	# src/test/test_board.cpp 
	# src/battleship_agent.cpp 
	# src/socket_connection.cpp
	# src/battle_board.cpp
	# src/player_battle_board.cpp
	# src/enemy_battle_board.cpp)
# target_link_libraries(test_board
	# ${Boost_LIBRARIES} 
	# ${CMAKE_THREAD_LIBS_INIT} 
	# ${SFML_LIBRARIES} 
	# )