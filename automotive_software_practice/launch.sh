#!/bin/bash
terminator -u -e  " source ~/.bashrc && source install/setup.bash && ros2 launch simulator simulation.launch.xml " &
sleep 3
terminator -u -e  " source ~/.bashrc && source install/setup.bash && ros2 launch scenario_runner scenario_runner.launch.xml " &
sleep 3
terminator -u -e  " source ~/.bashrc && source install/setup.bash && ros2 launch evaluation evaluation.launch.xml " &
sleep 3
terminator -u -e  " source ~/.bashrc && source install/setup.bash && ros2 launch autonomous_driving autonomous_driving.launch.xml use_manual_inputs:=true "