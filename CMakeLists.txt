#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.8.3
#
cmake_minimum_required(VERSION 2.8.3)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(fbsched)

#
# Do setup in case of ros package, If ROS_ROOT is set, it is
# recommended to use RTT/OCL through the ros packages.
#
set (ROS_ROOT $ENV{ROS_ROOT} )
if (ROS_ROOT)
  find_package(catkin REQUIRED)
  include_directories(${catkin_INCLUDE_DIRS})  
  include_directories(${USE_OROCOS_INCLUDE_DIRS})
  set( RTT_HINTS HINTS ${rtt_PACKAGE_PATH}/install )
endif()

set(CMAKE_BUILD_TYPE MinSizeRel)

# Set the CMAKE_PREFIX_PATH in case you're not using Orocos through ROS
# for helping these find commands find RTT.
find_package(OROCOS-RTT REQUIRED ${RTT_HINTS})

# Defines the orocos_* cmake macros. See that file for additional
# documentation.
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)

# Creates a component library libfbsched-<target>.so
# and installs in the directory lib/orocos/fbsched/
#
orocos_component(fbsched fbsched.hpp fbsched.cpp)

#
# Additional headers:
#
# Installs in the include/orocos/fbsched/ directory
#
orocos_install_headers( fbsched.hpp ) 

#
# Generates and installs our package. Must be the last statement such
# that it can pick up all above settings.
#
orocos_generate_package(
  DEPENDS_TARGETS rtt
)
