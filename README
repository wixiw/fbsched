FBSched Component
=================

The FBSched (Function Block Scheduler) component is a simple mechanism
to sequentially execute function blocks (represented as the
functionality within the updateHook of RTT components) within a single
thread. The goal is to minimize overhead introduced by scheduling
latencies.

The basic usage pattern is the following:

1. Create a FBSched component and configure it either with a Activity
   _or_ connect an event source to the FBSched 'trigger' port.

2. Create slave components and configure them as slaves to the FBSched
   component by using the deployer operation:

   	      setMasterSlaveActivity(FBSchedName, SlaveName)

3. First start all slaves and then the FBSched component to begin the
   scheduling. The FBSched component will trigger all of it's peers.


Execution Order
---------------

Per default, the order of executing slave function blocks is
undefined. To configure the order the "order" property can be
used. The order does not have to be completely defined: all peers not
mentioned in the order property will be executed in a undefined (but
consistent in the sense that it will not change between triggers)
after the mentioned ones.


Future work
-----------

It would be nice to extend the component (configurably) to measure the
min/avg/max duration of each slave and the total execution time.


License
-------

Dual LGPL/BSD


Acknowledgement
---------------

Inspired by suggestions from Herman Bruyninckx.