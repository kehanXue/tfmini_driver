cmake_minimum_required(VERSION 2.8.3)
project(sanchi_driver)


add_definitions(-std=c++11)
find_package(catkin REQUIRED roscpp sensor_msgs tf cmake_modules)

find_package(catkin REQUIRED COMPONENTS)


include_directories(${catkin_INCLUDE_DIRS} include)

find_package(Eigen3 REQUIRED)

catkin_package(
)

add_executable(sanchi_driver_node
  src/sanchi_driver_node.cc
  src/utils.cc
  src/BoostSerialCommunicator.cc
  src/SanchiSerialHardware.cc
  src/SanchiRosDriver.cc
)

target_link_libraries(sanchi_driver_node
  ${catkin_LIBRARIES}
)
