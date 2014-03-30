#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.6.3
#
cmake_minimum_required(VERSION 2.8.3)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(fbsched)

set(CMAKE_BUILD_TYPE MinSizeRel)

find_package(catkin REQUIRED COMPONENTS
 rtt_ros
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS rtt_ros
)

include_directories(
	include/fbsched
	${catkin_INCLUDE_DIRS})

add_definitions(-DRTT_COMPONENT)
add_definitions(${catkin_DEFINITIONS})

orocos_generate_package(
  INCLUDE_DIRS include
  DEPENDS rtt_ros
)

orocos_install_headers(
  DIRECTORY include/${PROJECT_NAME}/
)

# Rest of the configuration is in src/
add_subdirectory( src )
