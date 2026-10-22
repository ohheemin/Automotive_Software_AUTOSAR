// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ad_msgs:msg/VehicleInput.idl
// generated code does not contain a copyright notice

#ifndef AD_MSGS__MSG__DETAIL__VEHICLE_INPUT__BUILDER_HPP_
#define AD_MSGS__MSG__DETAIL__VEHICLE_INPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ad_msgs/msg/detail/vehicle_input__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ad_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleInput_brake
{
public:
  explicit Init_VehicleInput_brake(::ad_msgs::msg::VehicleInput & msg)
  : msg_(msg)
  {}
  ::ad_msgs::msg::VehicleInput brake(::ad_msgs::msg::VehicleInput::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ad_msgs::msg::VehicleInput msg_;
};

class Init_VehicleInput_accel
{
public:
  explicit Init_VehicleInput_accel(::ad_msgs::msg::VehicleInput & msg)
  : msg_(msg)
  {}
  Init_VehicleInput_brake accel(::ad_msgs::msg::VehicleInput::_accel_type arg)
  {
    msg_.accel = std::move(arg);
    return Init_VehicleInput_brake(msg_);
  }

private:
  ::ad_msgs::msg::VehicleInput msg_;
};

class Init_VehicleInput_steering
{
public:
  Init_VehicleInput_steering()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleInput_accel steering(::ad_msgs::msg::VehicleInput::_steering_type arg)
  {
    msg_.steering = std::move(arg);
    return Init_VehicleInput_accel(msg_);
  }

private:
  ::ad_msgs::msg::VehicleInput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ad_msgs::msg::VehicleInput>()
{
  return ad_msgs::msg::builder::Init_VehicleInput_steering();
}

}  // namespace ad_msgs

#endif  // AD_MSGS__MSG__DETAIL__VEHICLE_INPUT__BUILDER_HPP_
