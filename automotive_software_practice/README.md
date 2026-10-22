# Practice 11: Lane Detection and Lateral Control

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

## Key Messages (`src/rte/msg/ad_msgs/msg`)

| Message | Fields | Description |
|---|---|---|
| `LanePointData` | `frame_id`, `id`, `geometry_msgs/Point[] point` | Lane points in the vehicle frame (`ego/body`). Left and right lane points arrive mixed together |
| `PolyfitLaneData` | `frame_id`, `id`, `a0`~`a3` | Coefficients of the cubic `y = a0 + a1·x + a2·x² + a3·x³` |
| `VehicleInput` | `accel`, `brake`, `steering` | Vehicle command |
| `VehicleOutput` | `x`, `y`, `yaw`, `velocity`, ... | Vehicle state |

Vehicle frame: origin = vehicle, **x = forward**, **y = left** (REP-103).

## Algorithm

### TODO1. `FindDrivingWay()`: Center Line Estimation

1. **Left/right classification**: Substitute each point's x into the previous frame's center line (`previous_middle_lane`) to get `y_center`, then use `center2point = p.y - y_center`.
   - `|center2point| > maximum_distance` → discarded (adjacent lane, noise)
   - `center2point > 0` → left lane, otherwise → right lane
   - In the first frame all coefficients are 0, so this is the same as splitting by `y = 0`. After that, the reference line bends with the road, so classification still works in curves.
2. **Least-squares fit**: For each lane, build `X = [1, x, x², x³]` (N×4) and `Y = [y]` (N×1), then compute `A = (XᵀX)⁻¹XᵀY`. Skipped if a lane has fewer than 4 points.
3. **Center line**: If both lanes are fitted, average their coefficients; otherwise keep the previous center line. The result is stored in `previous_middle_lane` as the reference for the next frame.

### TODO2. `LateralControl()`: Pure Pursuit (not implemented)

1. Look-ahead distance `l_xd = kd + kv · v`
2. Look-ahead point `g_x = l_xd`, `g_y = a0 + a1·g_x + a2·g_x² + a3·g_x³`
3. `l_d = √(g_x² + g_y²)`
4. `steering = atan2(2 · L · g_y, l_d²)` (`L = param_wheel_base_`)

## Parameters

| Location | Name | Value | Meaning |
|---|---|---|---|
| `autonomous_driving.hpp` | `maximum_distance` | 2.5 m | Points farther than this from the previous center line are discarded |
| `autonomous_driving.launch.xml` | `use_manual_inputs` | false | If true, accel/brake/steering come from the keyboard |
| | `pure_pursuit_kd` / `kv` | 5.0 / 0.35 | Look-ahead distance gains |
| `simulation.launch.xml` | `ROIFront` / `ROIRear` | 20 / 5 m | Forward/backward range of lane points |
| | `ROILeft` / `ROIRight` | 4 / 4 m | Left/right range of lane points |

Note: Lanes on the map are 4 m apart (lane lines at y = -2, 2, 6), so each lane line is about 2 m from the center line. If `maximum_distance` is set below 2 m, all points of the ego lane are discarded. About 30 points per lane line are received (spacing about 0.84 m).

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
