// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ad_msgs:msg/VehicleInput.idl
// generated code does not contain a copyright notice

#ifndef AD_MSGS__MSG__DETAIL__VEHICLE_INPUT__STRUCT_H_
#define AD_MSGS__MSG__DETAIL__VEHICLE_INPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VehicleInput in the package ad_msgs.
typedef struct ad_msgs__msg__VehicleInput
{
  double steering;
  double accel;
  double brake;
} ad_msgs__msg__VehicleInput;

// Struct for a sequence of ad_msgs__msg__VehicleInput.
typedef struct ad_msgs__msg__VehicleInput__Sequence
{
  ad_msgs__msg__VehicleInput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ad_msgs__msg__VehicleInput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AD_MSGS__MSG__DETAIL__VEHICLE_INPUT__STRUCT_H_
