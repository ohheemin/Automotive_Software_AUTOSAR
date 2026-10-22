// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ad_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#ifndef AD_MSGS__MSG__DETAIL__OBSTACLES__BUILDER_HPP_
#define AD_MSGS__MSG__DETAIL__OBSTACLES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ad_msgs/msg/detail/obstacles__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ad_msgs
{

namespace msg
{

namespace builder
{

class Init_Obstacles_obstacles
{
public:
  Init_Obstacles_obstacles()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ad_msgs::msg::Obstacles obstacles(::ad_msgs::msg::Obstacles::_obstacles_type arg)
  {
    msg_.obstacles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ad_msgs::msg::Obstacles msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ad_msgs::msg::Obstacles>()
{
  return ad_msgs::msg::builder::Init_Obstacles_obstacles();
}

}  // namespace ad_msgs

#endif  // AD_MSGS__MSG__DETAIL__OBSTACLES__BUILDER_HPP_
