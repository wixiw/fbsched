-- Simple test script for the FBSched component.

tc=rtt.getTC()
dp=tc:getPeer("deployer")

dp:import("fbsched")

--rtt.setLogLevel("Info")

-- this string is the code executed in each slave
comp_str=[[
      i=0
      function startHook()
	 i=0
	 return true
      end

      function updateHook()
	 i=i+1
	 -- print(rtt.getTC():getName())
      end

      function stopHook()
	 print(rtt.getTC():getName().." updateHook executed "..tostring(i).." times")
      end
]]

-- Create num slaves and return them in a table.
function create_slaves(num, master_name)
   local peers={}
   for i=1,num do
      local name="l_"..tostring(i)
      print("creating", name, " component")
      dp:loadComponent(name, "OCL::LuaComponent")
      peers[i]=dp:getPeer(name)
      peers[i]:exec_str(comp_str)
      -- correct
      dp:setMasterSlaveActivity("fbs", name)
      -- wrong (for testing enable this to replace the slave activity
      -- with a regular one:
      -- dp:setActivity(name, 0.0001, 0, rtt.globals.ORO_SCHED_OTHER)
      peers[i]:configure()
      peers[i]:start()
   end
end

dp:loadComponent("fbs", "FBSched")
dp:setActivity("fbs", 0.001, 0, rtt.globals.ORO_SCHED_OTHER)
fbs=dp:getPeer("fbs")

peers=create_slaves(100, "fbs")

sched_order=fbs:getProperty("sched_order")
sched_order:get():resize(10)
sched_order[0]="l_10"
sched_order[1]="l_9"
sched_order[2]="l_8"
sched_order[3]="l_7"
sched_order[4]="l_6"
sched_order[5]="l_5"
sched_order[6]="l_4"
sched_order[7]="l_3"
sched_order[8]="l_2"
sched_order[9]="l_1"

fbs:start()
os.execute("sleep 1")
