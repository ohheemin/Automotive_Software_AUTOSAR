// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ad_msgs:msg/VehicleOutput.idl
// generated code does not contain a copyright notice
#include "ad_msgs/msg/detail/vehicle_output__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `id`
#include "rosidl_runtime_c/string_functions.h"

bool
ad_msgs__msg__VehicleOutput__init(ad_msgs__msg__VehicleOutput * msg)
{
  if (!msg) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__init(&msg->id)) {
    ad_msgs__msg__VehicleOutput__fini(msg);
    return false;
  }
  // x
  // y
  // yaw
  // velocity
  // length
  // width
  return true;
}

void
ad_msgs__msg__VehicleOutput__fini(ad_msgs__msg__VehicleOutput * msg)
{
  if (!msg) {
    return;
  }
  // id
  rosidl_runtime_c__String__fini(&msg->id);
  // x
  // y
  // yaw
  // velocity
  // length
  // width
}

bool
ad_msgs__msg__VehicleOutput__are_equal(const ad_msgs__msg__VehicleOutput * lhs, const ad_msgs__msg__VehicleOutput * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->id), &(rhs->id)))
  {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // length
  if (lhs->length != rhs->length) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  return true;
}

bool
ad_msgs__msg__VehicleOutput__copy(
  const ad_msgs__msg__VehicleOutput * input,
  ad_msgs__msg__VehicleOutput * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__copy(
      &(input->id), &(output->id)))
  {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // yaw
  output->yaw = input->yaw;
  // velocity
  output->velocity = input->velocity;
  // length
  output->length = input->length;
  // width
  output->width = input->width;
  return true;
}

ad_msgs__msg__VehicleOutput *
ad_msgs__msg__VehicleOutput__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ad_msgs__msg__VehicleOutput * msg = (ad_msgs__msg__VehicleOutput *)allocator.allocate(sizeof(ad_msgs__msg__VehicleOutput), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ad_msgs__msg__VehicleOutput));
  bool success = ad_msgs__msg__VehicleOutput__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ad_msgs__msg__VehicleOutput__destroy(ad_msgs__msg__VehicleOutput * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ad_msgs__msg__VehicleOutput__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ad_msgs__msg__VehicleOutput__Sequence__init(ad_msgs__msg__VehicleOutput__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ad_msgs__msg__VehicleOutput * data = NULL;

  if (size) {
    data = (ad_msgs__msg__VehicleOutput *)allocator.zero_allocate(size, sizeof(ad_msgs__msg__VehicleOutput), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ad_msgs__msg__VehicleOutput__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ad_msgs__msg__VehicleOutput__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ad_msgs__msg__VehicleOutput__Sequence__fini(ad_msgs__msg__VehicleOutput__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ad_msgs__msg__VehicleOutput__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ad_msgs__msg__VehicleOutput__Sequence *
ad_msgs__msg__VehicleOutput__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ad_msgs__msg__VehicleOutput__Sequence * array = (ad_msgs__msg__VehicleOutput__Sequence *)allocator.allocate(sizeof(ad_msgs__msg__VehicleOutput__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ad_msgs__msg__VehicleOutput__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ad_msgs__msg__VehicleOutput__Sequence__destroy(ad_msgs__msg__VehicleOutput__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ad_msgs__msg__VehicleOutput__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ad_msgs__msg__VehicleOutput__Sequence__are_equal(const ad_msgs__msg__VehicleOutput__Sequence * lhs, const ad_msgs__msg__VehicleOutput__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ad_msgs__msg__VehicleOutput__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ad_msgs__msg__VehicleOutput__Sequence__copy(
  const ad_msgs__msg__VehicleOutput__Sequence * input,
  ad_msgs__msg__VehicleOutput__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ad_msgs__msg__VehicleOutput);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ad_msgs__msg__VehicleOutput * data =
      (ad_msgs__msg__VehicleOutput *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ad_msgs__msg__VehicleOutput__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ad_msgs__msg__VehicleOutput__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ad_msgs__msg__VehicleOutput__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
