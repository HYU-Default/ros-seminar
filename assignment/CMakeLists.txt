cmake_minimum_required(VERSION 2.8.3)
project(assignment)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)

add_message_files(FILES
	Position.msg
    State.msg
)

add_service_files(FILES
    SetPosition.srv
    SetState.srv
)

generate_messages(DEPENDENCIES
    std_msgs
)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES assignment
   CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(position_node src/position_node.cpp)
target_link_libraries(position_node ${catkin_LIBRARIES})

add_executable(assign_state_node src/state_node.cpp)
target_link_libraries(assign_state_node ${catkin_LIBRARIES})

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})