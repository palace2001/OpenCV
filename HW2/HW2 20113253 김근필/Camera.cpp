#include <iostream>
#include "Camera.h"
#include "math.h"
#include <glm/ext.hpp>

const glm::vec3 Camera::center_position() const
{
  return  glm::vec3(position_.x + front_dir_.x,
                 position_.y + front_dir_.y, 
                 position_.z + front_dir_.z);
}

// TODO: fill up the following functions properly 
void Camera::move_forward(float delta)
{
	position_.z += delta * front_dir_.z;
	position_.x += delta * front_dir_.x;
}

void Camera::move_backward(float delta)
{	
	position_.z -= delta * front_dir_.z;
	position_.x -= delta * front_dir_.x;
}

void Camera::move_left(float delta)
{	
	position_.z -= delta * right_direction().z;
	position_.x -= delta * right_direction().x;
}

void Camera::move_right(float delta)
{
	position_.z += delta * right_direction().z;
	position_.x += delta * right_direction().x;
}

void Camera::rotate_left(float delta)
{
	yaw_ -= delta;
	front_dir_.x = (FRONT_DIR)*-sin(yaw_);
	front_dir_.z = (FRONT_DIR)*cos(yaw_);
}

void Camera::rotate_right(float delta)
{
	yaw_ += delta;
	front_dir_.x = (FRONT_DIR)*-sin(yaw_);
	front_dir_.z = (FRONT_DIR)*cos(yaw_);
	
}
