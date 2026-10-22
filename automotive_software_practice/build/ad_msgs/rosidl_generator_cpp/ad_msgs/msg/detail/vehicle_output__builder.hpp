// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ad_msgs:msg/VehicleOutput.idl
// generated code does not contain a copyright notice

#ifndef AD_MSGS__MSG__DETAIL__VEHICLE_OUTPUT__BUILDER_HPP_
#define AD_MSGS__MSG__DETAIL__VEHICLE_OUTPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ad_msgs/msg/detail/vehicle_output__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ad_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleOutput_width
{
public:
  explicit Init_VehicleOutput_width(::ad_msgs::msg::VehicleOutput & msg)
  : msg_(msg)
  {}
  ::ad_msgs::msg::VehicleOutput width(::ad_msgs::msg::VehicleOutput::_width_type arg)
  {
    msg_.width = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

class Init_VehicleOutput_length
{
public:
  explicit Init_VehicleOutput_length(::ad_msgs::msg::VehicleOutput & msg)
  : msg_(msg)
  {}
  Init_VehicleOutput_width length(::ad_msgs::msg::VehicleOutput::_length_type arg)
  {
    msg_.length = std::move(arg);
    return Init_VehicleOutput_width(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

class Init_VehicleOutput_velocity
{
public:
  explicit Init_VehicleOutput_velocity(::ad_msgs::msg::VehicleOutput & msg)
  : msg_(msg)
  {}
  Init_VehicleOutput_length velocity(::ad_msgs::msg::VehicleOutput::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_VehicleOutput_length(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

class Init_VehicleOutput_yaw
{
public:
  explicit Init_VehicleOutput_yaw(::ad_msgs::msg::VehicleOutput & msg)
  : msg_(msg)
  {}
  Init_VehicleOutput_velocity yaw(::ad_msgs::msg::VehicleOutput::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_VehicleOutput_velocity(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

class Init_VehicleOutput_y
{
public:
  explicit Init_VehicleOutput_y(::ad_msgs::msg::VehicleOutput & msg)
  : msg_(msg)
  {}
  Init_VehicleOutput_yaw y(::ad_msgs::msg::VehicleOutput::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_VehicleOutput_yaw(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

class Init_VehicleOutput_x
{
public:
  explicit Init_VehicleOutput_x(::ad_msgs::msg::VehicleOutput & msg)
  : msg_(msg)
  {}
  Init_VehicleOutput_y x(::ad_msgs::msg::VehicleOutput::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_VehicleOutput_y(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

class Init_VehicleOutput_id
{
public:
  Init_VehicleOutput_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleOutput_x id(::ad_msgs::msg::VehicleOutput::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_VehicleOutput_x(msg_);
  }

private:
  ::ad_msgs::msg::VehicleOutput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ad_msgs::msg::VehicleOutput>()
{
  return ad_msgs::msg::builder::Init_VehicleOutput_id();
}

}  // namespace ad_msgs

#endif  // AD_MSGS__MSG__DETAIL__VEHICLE_OUTPUT__BUILDER_HPP_
