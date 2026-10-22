# Lane Detection and Lateral Control

A ROS2 Humble simulator exercise: estimate the driving path (center line) from lane points, then compute the steering angle with Pure Pursuit.

## Assignment

Only two files in the `autonomous_driving` package are edited.

| File | Task | Status |
|---|---|---|
| `src/app/autonomous_driving/src/autonomous_driving.cpp` | TODO1 `FindDrivingWay()`: lane points → cubic polynomial of the center line | Done |
| | TODO2 `LateralControl()`: center line → steering angle (Pure Pursuit) | Not implemented |
| `src/app/autonomous_driving/include/autonomous_driving.hpp` | Add member variables needed by the algorithm | Added `previous_middle_lane`, `maximum_distance` |

The other packages (`simulator`, `scenario_runner`, `evaluation`, `ad_msgs`) are provided as the exercise environment and are not modified.

## Directory Structure

```
automotive_software_practice/
├── launch.sh                         # Launches simulator, scenario, evaluation and autonomous driving nodes at once
├── resources/
│   ├── csv/simulation_lane/          # Lane coordinates of the simulation map (Lane_0~3.csv)
│   ├── csv/evaluation_lane/          # Lane coordinates for evaluation
│   ├── meshes/                       # Vehicle models for RViz
│   └── rviz/ros2_practice.rviz       # RViz configuration
└── src/
    ├── app/
    │   ├── autonomous_driving/       # ★ Exercise code
    │   │   ├── src/autonomous_driving.cpp
    │   │   ├── include/autonomous_driving.hpp
    │   │   ├── launch/autonomous_driving.launch.xml   # Node + tuning parameters
    │   │   ├── launch/manual_driving.launch.xml       # Keyboard input node
    │   │   └── scripts/simultaneous_inputs.py         # pygame keyboard input
    │   ├── simulator/                # Vehicle dynamics, lane detection, RViz display
    │   │   ├── src/vehicle/          #   Vehicle simulator
    │   │   ├── src/lane_detection/   #   Map lanes → lane points around the vehicle (ROI + noise)
    │   │   └── src/display/          #   Topics → RViz markers
    │   ├── scenario_runner/          # 3 surrounding vehicles (obstacles), speed limit
    │   └── evaluation/               # Driving evaluation result
    ├── bsw/system/interface/         # Shared data types (Lane, Vehicle, etc.)
    └── rte/msg/ad_msgs/              # Custom ROS2 messages
```

## Data Flow

```
[simulator/lane_detection] ──/ego/lane_points──▶ [autonomous_driving]
[simulator/vehicle]        ──/ego/vehicle_state─▶        │
[manual_driving]           ──/manual_input──────▶        │
                                                         ├─ FindDrivingWay()  → /ego/driving_way
                                                         └─ LateralControl()  → /ego/vehicle_command ──▶ [simulator/vehicle]

[simulator/display] : /ego/driving_way → /ego/driving_way_marker (yellow dotted line in RViz)
```

## Custom msgs (`src/rte/msg/ad_msgs/msg`)

| Message | Fields | Description |
|---|---|---|
| `LanePointData` | `frame_id`, `id`, `geometry_msgs/Point[] point` | Lane points in the vehicle frame (`ego/body`). Left and right lane points arrive mixed together |
| `PolyfitLaneData` | `frame_id`, `id`, `a0`~`a3` | Coefficients of the cubic `y = a0 + a1·x + a2·x² + a3·x³` |
| `VehicleInput` | `accel`, `brake`, `steering` | Vehicle command |
| `VehicleOutput` | `x`, `y`, `yaw`, `velocity`, ... | Vehicle state |

Vehicle frame: origin = vehicle, **x = forward**, **y = left** (REP-103).

## Build

**Always build inside `automotive_software_practice/`.** Building from the parent folder puts the output into a different `install/`, and the changes will not be used at runtime.

```bash
cd ~/Practice_11_Lane_Detection_and_Lateral_Control_code/automotive_software_practice
colcon build                                        # All packages
colcon build --packages-select autonomous_driving   # Exercise code only
```

Rebuild after editing any `.cpp`, `.hpp`, `.launch.xml` or `.py` file.

## Run

```bash
# Terminal 1: simulator, scenario, evaluation, autonomous driving node (4 terminator windows)
cd ~/Practice_11_Lane_Detection_and_Lateral_Control_code/automotive_software_practice
source install/setup.bash
./launch.sh

# Terminal 2: keyboard input (manual mode)
source install/setup.bash
ros2 launch autonomous_driving manual_driving.launch.xml
```

`launch.sh` currently runs with `use_manual_inputs:=true`. Remove this option to test automatic steering.

### Keyboard Controls (click the `keyboard` window first)

| Key | Action |
|---|---|
| `↑` / `i` | Accelerate |
| `↓` / `k` | Brake |
| `←` / `j`, `→` / `l` | Steer left / right |
| `Space` | Emergency stop + steering 0 |
| `w` / `x`, `e` / `c` | Accel / steering step ±10% |

### Manual Mode Behavior

When `use_manual_inputs` is true, `Run()` takes accel, brake **and steering** from the keyboard. The original template took only accel and brake from the keyboard and used the `LateralControl()` result for steering. After implementing `LateralControl()`, delete the following line in `Run()` to test "human controls speed, algorithm controls steering":

```cpp
vehicle_command.steering = manual_vehicle_command.steering;
```

## Checking in RViz

| Display | Topic | Color |
|---|---|---|
| DrivingWay | `/ego/driving_way_marker` | Yellow dotted line (estimated center line) |
| LanePoints | `/ego/lane_points_marker` | Cyan (input lane points) |
| Obstacles | `/ego/obstacles_marker` | Green beyond 26 m → red within 13 m |

Inspect topics directly:

```bash
ros2 topic echo /ego/lane_points
ros2 topic echo /ego/driving_way
```
