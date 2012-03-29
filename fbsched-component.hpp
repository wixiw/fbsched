#ifndef OROCOS_FBSCHED_COMPONENT_HPP
#define OROCOS_FBSCHED_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <iostream>

class Fbsched
    : public RTT::TaskContext
{
 public:
    Fbsched(string const& name)
        : TaskContext(name)
    {
        std::cout << "Fbsched constructed !" <<std::endl;
    }

    bool configureHook() {
        std::cout << "Fbsched configured !" <<std::endl;
        return true;
    }

    bool startHook() {
        std::cout << "Fbsched started !" <<std::endl;
        return true;
    }

    void updateHook() {
        std::cout << "Fbsched executes updateHook !" <<std::endl;
    }

    void stopHook() {
        std::cout << "Fbsched executes stopping !" <<std::endl;
    }

    void cleanupHook() {
        std::cout << "Fbsched cleaning up !" <<std::endl;
    }
};

#endif
