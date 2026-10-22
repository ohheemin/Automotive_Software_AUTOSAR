// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ad_msgs:msg/VehicleOutput.idl
// generated code does not contain a copyright notice

#ifndef AD_MSGS__MSG__DETAIL__VEHICLE_OUTPUT__STRUCT_H_
#define AD_MSGS__MSG__DETAIL__VEHICLE_OUTPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/VehicleOutput in the package ad_msgs.
typedef struct ad_msgs__msg__VehicleOutput
{
  rosidl_runtime_c__String id;
  double x;
  double y;
  double yaw;
  double velocity;
  double length;
  double width;
} ad_msgs__msg__VehicleOutput;

// Struct for a sequence of ad_msgs__msg__VehicleOutput.
typedef struct ad_msgs__msg__VehicleOutput__Sequence
{
  ad_msgs__msg__VehicleOutput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ad_msgs__msg__VehicleOutput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AD_MSGS__MSG__DETAIL__VEHICLE_OUTPUT__STRUCT_H_
