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


