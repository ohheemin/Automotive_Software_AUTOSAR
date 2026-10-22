/**
 * @copyright Hanyang University, Department of Automotive Engineering, 2024. All rights reserved.
 *            Subject to limited distribution and restricted disclosure only.
 *
 * @file      autonomous_driving.cpp
 * @brief     autonomous driving algorithm
 *
 * @date      2018-11-20 created by Kichun Jo (kichunjo@hanyang.ac.kr)
 *            2023-08-07 updated by Yuseung Na (yuseungna@hanyang.ac.kr)
 *              : adapt new template
 *            2023-08-20 updated by Yuseung Na (yuseungna@hanyang.ac.kr)
 *              : change to ROS2
 *            2024-10-21 updated by Seongjae Jeong (sjeong99@hanyang.ac.kr)
 *              : add the missions
 */

#include "autonomous_driving.hpp"
#include <Eigen/Dense>

AutonomousDriving::AutonomousDriving(const std::string &node_name, const double &loop_rate,
                                     const rclcpp::NodeOptions &options)
    : Node(node_name, options) {

    RCLCPP_WARN(this->get_logger(), "Initialize node...");

    // QoS init
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));

    // Parameters
    this->declare_parameter("autonomous_driving/ns", "");
    if (!this->get_parameter("autonomous_driving/ns", param_vehicle_namespace_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get vehicle_namespace");
        param_vehicle_namespace_ = "";
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_vehicle_namespace_: %s", param_vehicle_namespace_.c_str());
    }
    this->declare_parameter("autonomous_driving/use_manual_inputs", false);
    if (!this->get_parameter("autonomous_driving/use_manual_inputs", param_use_manual_inputs_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get use_manual_inputs");
        param_use_manual_inputs_ = true;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_use_manual_inputs_: %d", param_use_manual_inputs_);
    }
    this->declare_parameter("autonomous_driving/pure_pursuit_kd", 1.0);
    if (!this->get_parameter("autonomous_driving/pure_pursuit_kd", param_pp_kd_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get pure_pursuit_kd");
        param_pp_kd_ = 1.0;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_pp_kd_: %f", param_pp_kd_);
    }
    this->declare_parameter("autonomous_driving/pure_pursuit_kv", 0.0);
    if (!this->get_parameter("autonomous_driving/pure_pursuit_kv", param_pp_kv_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get pure_pursuit_kv");
        param_pp_kv_ = 0.0;
    }
    this->declare_parameter("autonomous_driving/pure_pursuit_kc", 0.0);
    if (!this->get_parameter("autonomous_driving/pure_pursuit_kc", param_pp_kc_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get pure_pursuit_kc");
        param_pp_kc_ = 0.0;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_pp_kv_: %f", param_pp_kv_);
    }
    this->declare_parameter("autonomous_driving/pid_kp", 0.0);
    if (!this->get_parameter("autonomous_driving/pid_kp", param_pid_kp_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get pid_kp");
        param_pid_kp_ = 0.0;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_pid_kp_: %f", param_pid_kp_);
    }
    this->declare_parameter("autonomous_driving/pid_ki", 0.0);
    if (!this->get_parameter("autonomous_driving/pid_ki", param_pid_ki_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get pid_ki");
        param_pid_ki_ = 0.0;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_pid_ki_: %f", param_pid_ki_);
    }
    this->declare_parameter("autonomous_driving/pid_kd", 0.0);
    if (!this->get_parameter("autonomous_driving/pid_kd", param_pid_kd_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get pid_kd");
        param_pid_kd_ = 0.0;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_pid_kd_: %f", param_pid_kd_);
    }
    this->declare_parameter("autonomous_driving/brake_ratio", 1.0);
    if (!this->get_parameter("autonomous_driving/brake_ratio", param_brake_ratio_)) {
        RCLCPP_ERROR(this->get_logger(), "Failed to get brake_ratio");
        param_brake_ratio_ = 0.0;
    }
    else {
        RCLCPP_INFO(this->get_logger(), "param_brake_ratio_: %f", param_brake_ratio_);
    }

    // Subscribers
    s_manual_input_ = this->create_subscription<ad_msgs::msg::VehicleInput>(
        "/manual_input", qos_profile, std::bind(&AutonomousDriving::CallbackManualInput, this, std::placeholders::_1));
    s_vehicle_state_ = this->create_subscription<ad_msgs::msg::VehicleOutput>(
        "vehicle_state", qos_profile, std::bind(&AutonomousDriving::CallbackVehicleState, this, std::placeholders::_1));
    s_limit_speed_ = this->create_subscription<std_msgs::msg::Float32>(
        "limit_speed", qos_profile, std::bind(&AutonomousDriving::CallbackLimitSpeed, this, std::placeholders::_1));
    s_lane_points_ = this->create_subscription<ad_msgs::msg::LanePointData>(
        "lane_points", qos_profile, std::bind(&AutonomousDriving::CallbackLanePoints, this, std::placeholders::_1));
    s_obstacles_ = this->create_subscription<ad_msgs::msg::Obstacles>(
        "obstacles", qos_profile, std::bind(&AutonomousDriving::CallbackObstacles, this, std::placeholders::_1));

    // Publishers
    p_vehicle_command_ = this->create_publisher<ad_msgs::msg::VehicleInput>(
        "vehicle_command", qos_profile);
    p_driving_way_ = this->create_publisher<ad_msgs::msg::PolyfitLaneData>(
        "driving_way", qos_profile);
    p_poly_lanes_ = this->create_publisher<ad_msgs::msg::PolyfitLaneDataArray>(
        "poly_lanes", qos_profile);

    // Initialize
    Init(this->now());

    // Timer init
    t_run_node_ = this->create_wall_timer(
        std::chrono::milliseconds((int64_t)(1000 / loop_rate)),
        [this]()
        { this->Run(this->now()); });
}

AutonomousDriving::~AutonomousDriving() {}

void AutonomousDriving::Init(const rclcpp::Time &current_time) {
}

void AutonomousDriving::UpdateParameter() {
}

void AutonomousDriving::Run(const rclcpp::Time &current_time) {
    UpdateParameter();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    // Get subscribe variables
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    mutex_vehicle_state_.lock();
    ad_msgs::msg::VehicleOutput vehicle_state = i_vehicle_state_;
    mutex_vehicle_state_.unlock();

    mutex_obstacles_.lock();
    ad_msgs::msg::Obstacles obstacles = i_obstacles_;
    mutex_obstacles_.unlock();

    mutex_limit_speed_.lock();
    double limit_speed = i_limit_speed_;
    mutex_limit_speed_.unlock();

    mutex_lane_points_.lock();
    ad_msgs::msg::LanePointData lane_points = i_lane_points_;
    mutex_lane_points_.unlock();

    mutex_vehicle_command_.lock();
    ad_msgs::msg::VehicleInput manual_vehicle_command = i_vehicle_command_;
    mutex_vehicle_command_.unlock();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    // Output variables
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    ad_msgs::msg::PolyfitLaneData driving_way;
    ad_msgs::msg::PolyfitLaneDataArray poly_lanes;
    ad_msgs::msg::VehicleInput vehicle_command;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    // Algorithm
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    /**
     * @brief Calculate the vehicle comamnd using given inputs
     * 
     * inputs
     *      vehicle_state, limit_speed, obstacles, lane_points
     * outputs
     *      driving_way, poly_lanes, vehicle_command
     * 
     * TODO1. Find the driving way from the lane points
     * TODO2. Calculate the steering angle using lateral control
     */

    /* TODO1. Complete FindDrivingWay function*/
    driving_way = FindDrivingWay(vehicle_state, lane_points); //====>> 이건 함수를 실행하고, 그 결괏값을 변수에 넣음.
    // 관측할 수 있는 샘플들의 수가 많음. 거꾸로 구하기
    // 피피티 10페이지에 있는 내용 참고. 근데 왜 driving way는 double이 아닌지?
    // 
    
    /* TODO2. Complete LateralControl function*/
    double steering = LateralControl(vehicle_state, driving_way);


    // Update vehicle command
    vehicle_command.steering = steering;
    if (param_use_manual_inputs_) {
        vehicle_command.accel = manual_vehicle_command.accel;
        vehicle_command.brake = manual_vehicle_command.brake;
        vehicle_command.steering = manual_vehicle_command.steering;
        std::cout << "[MODE] Manual Longitudinal Input Mode" << std::endl;
    } else {
        vehicle_command.accel = 0.08;
        vehicle_command.brake = 0.0;
        std::cout << "[MODE] Constant Longitudinal Input Mode" << std::endl;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    // Update output
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    o_driving_way_ = driving_way;
    o_poly_lanes_ = poly_lanes;
    o_vehicle_command_ = vehicle_command;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    // Publish output
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
    Publish(current_time);
}

ad_msgs::msg::PolyfitLaneData AutonomousDriving::FindDrivingWay(const ad_msgs::msg::VehicleOutput &vehicle_state,
                                                                const ad_msgs::msg::LanePointData &lane_points) {
    ad_msgs::msg::PolyfitLaneData driving_way;
    driving_way.frame_id = param_vehicle_namespace_ + "/body";

    /**
     * @brief Find the driving way from the lane points
     * inputs: vehicle_state, lane_points
     * outputs: driving_way
     * Purpose: Implement lane fitting algorithm to find the driving way (center line) from the given lane points
     */

    ////////////////////// TODO //////////////////////
    // driving way가 double이 아닌 이유? 3차 다항식으로, 계수를 담는 메시지.


    /**********   Step 1: Separate lane points into left and right lanes ***********/
    // Classify each point by its offset (dy) from the previous center line
    // 1-1 Check and initialize the number of points
    int num_points = lane_points.point.size();
    std::vector<geometry_msgs::msg::Point> left_points, right_points;

    for (int i = 0; i < num_points; i++) {
        const auto &p = lane_points.point[i];
        // 점 하나는 작아서 복사해도 큰 차이는 없음. 그대로 반복문을 수십번 돌고, 더 큰 데이터 다루면
        // 복사비용 커져서 습관적 참조 사용.
        double y_center = previous_middle_lane.a0 + previous_middle_lane.a1 * p.x
                        + previous_middle_lane.a2 * p.x * p.x + previous_middle_lane.a3 * p.x * p.x * p.x;
        // 이전 프레임에서 구한 3차 함수에 현재 점의 x좌표를 대입. 그 위치의 중앙선 y값을 계산.
        double center2point = p.y - y_center;
        // 그 후에 중앙선으로부터의 거리 구해줌. y좌표에서만.
 
        if (std::fabs(center2point) > maximum_distance) 
            continue;
        // std::fabs는 

        if (center2point > 0.0) left_points.push_back(p);
        else          right_points.push_back(p);
    }

    // 1-2 Count left and right points
    int left_point_count  = left_points.size();
    int right_point_count = right_points.size();

    // 1-3 Initialize X, Y, and A matrices for left and right lanes with correct sizes
    Eigen::MatrixXd X_left(left_point_count, 4), X_right(right_point_count, 4);
    Eigen::VectorXd Y_left(left_point_count),    Y_right(right_point_count);
    Eigen::VectorXd A_left  = Eigen::VectorXd::Zero(4);
    Eigen::VectorXd A_right = Eigen::VectorXd::Zero(4);

    for (int i = 0; i < left_point_count; i++) {
        double x = left_points[i].x;
        X_left.row(i) << 1.0, x, x * x, x * x * x;
        Y_left(i) = left_points[i].y;
    }
    for (int i = 0; i < right_point_count; i++) {
        double x = right_points[i].x;
        X_right.row(i) << 1.0, x, x * x, x * x * x;
        Y_right(i) = right_points[i].y;
    }

    /**********   Step 2: Fit a polynomial to each lane's points *******************/
    // Least squares: A = (X^T X)^-1 X^T Y, at least 4 points needed for 4 coefficients
    // 2-1 Get optimized left lane coefficients A_left
    if (left_point_count >= 4) {
        A_left = (X_left.transpose() * X_left).inverse() * X_left.transpose() * Y_left;
    }

    // 2-2 Get optimized right lane coefficients A_right
    if (right_point_count >= 4) {
        A_right = (X_right.transpose() * X_right).inverse() * X_right.transpose() * Y_right;
    }

    // Step 3: Determine the driving way as the center line between the left and right lane
    // If either lane fails to fit, keep the previous center line
    if (left_point_count >= 4 && right_point_count >= 4) {
        driving_way.a0 = (A_left(0) + A_right(0)) / 2.0;
        driving_way.a1 = (A_left(1) + A_right(1)) / 2.0;
        driving_way.a2 = (A_left(2) + A_right(2)) / 2.0;
        driving_way.a3 = (A_left(3) + A_right(3)) / 2.0;
    }
    else {
        driving_way.a0 = previous_middle_lane.a0;
        driving_way.a1 = previous_middle_lane.a1;
        driving_way.a2 = previous_middle_lane.a2;
        driving_way.a3 = previous_middle_lane.a3;
    }
    previous_middle_lane = driving_way;


    ////////////////////////////////////////////////////
    return driving_way;
}

double AutonomousDriving::LateralControl(const ad_msgs::msg::VehicleOutput &vehicle_state,
                                          const ad_msgs::msg::PolyfitLaneData &driving_way) {
    /**
     * @brief Calculate the steering angle using pure pursuit or PID control
     * inputs: vehicle_state, driving_way
     * outputs: steering_angle
     * Purpose: Implement Pure Pursuit Control to calculate the steering angle based on the look-ahead point on the driving way
     */
                                              
    ////////////////////// TODO //////////////////////

    /***** Initialize variables */
    // Initialize Inputs
    double l_xd; // look-ahead distance [m]
    double g_x, g_y; // look-ahead point coordinates [m]
    double l_d; // distance between vehicle and look-ahead point [m]
    // Initialize Outputs
    double steering_angle = 0.0;


    // Step 0: Set look-ahead distance

    // Step 1: Get look-ahead point using look-ahead distance
    // (g_x g_y) = (x, ax^3 + bx^2 + cx + d)|x=l_xd

    // Step 2: The distance between vehicle position and look-ahead point

    // Step 3: Calculate steering angle using Pure Pursuit formula
    // steering_angle = atan2(2 * L * e_ld / l_d^2)

    ////////////////////////////////////////////////////
   
    return steering_angle;
}

void AutonomousDriving::Publish(const rclcpp::Time &current_time) {
    p_vehicle_command_->publish(o_vehicle_command_);
    p_driving_way_->publish(o_driving_way_);
    p_poly_lanes_->publish(o_poly_lanes_);
}

int main(int argc, char **argv) {
    std::string node_name = "autonomous_driving";
    double loop_rate = 100.0;

    // Initialize node
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AutonomousDriving>(node_name, loop_rate));
    rclcpp::shutdown();
    return 0;
}
