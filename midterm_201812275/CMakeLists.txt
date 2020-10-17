cmake_minimum_required(VERSION 3.0.2)
project(midterm_201812275)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  roscpp
  rospy
  sensor_msgs
  std_msgs
  std_srvs
)

find_package(Boost REQUIRED COMPONENTS system)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  info.msg
  board.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  passenger.srv
  detect.srv
)

## Generate actions in the 'action' folder
add_action_files(
  FILES
  position.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  actionlib_msgs
  sensor_msgs
  std_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES midterm_201812275
 CATKIN_DEPENDS actionlib actionlib_msgs message_runtime roscpp rospy sensor_msgs std_msgs std_srvs
 DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(motor src/motor.cpp)
add_dependencies(motor ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(motor ${catkin_LIBRARIES})

add_executable(information src/information.cpp)
add_dependencies(information ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(information ${catkin_LIBRARIES})

add_executable(judgement_stop src/judgement_stop.cpp)
add_dependencies(judgement_stop ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(judgement_stop ${catkin_LIBRARIES})

add_executable(passenger src/passenger.cpp)
add_dependencies(passenger ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(passenger ${catkin_LIBRARIES})

add_executable(bus_stop src/bus_stop.cpp)
add_dependencies(bus_stop ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(bus_stop ${catkin_LIBRARIES})