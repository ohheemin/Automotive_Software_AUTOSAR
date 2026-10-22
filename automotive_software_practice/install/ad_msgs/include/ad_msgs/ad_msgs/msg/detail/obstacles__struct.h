// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ad_msgs:msg/Obstacles.idl
// generated code does not contain a copyright notice

#ifndef AD_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_H_
#define AD_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'obstacles'
#include "ad_msgs/msg/detail/vehicle_output__struct.h"

/// Struct defined in msg/Obstacles in the package ad_msgs.
typedef struct ad_msgs__msg__Obstacles
{
  ad_msgs__msg__VehicleOutput__Sequence obstacles;
} ad_msgs__msg__Obstacles;

// Struct for a sequence of ad_msgs__msg__Obstacles.
typedef struct ad_msgs__msg__Obstacles__Sequence
{
  ad_msgs__msg__Obstacles * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ad_msgs__msg__Obstacles__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AD_MSGS__MSG__DETAIL__OBSTACLES__STRUCT_H_
