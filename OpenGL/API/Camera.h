#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#endif

#include <gl/glew.h>
#include "../res/vendor/glm/glm.hpp"
#include "../res/vendor/glm/gtc/matrix_transform.hpp"

#include <vector>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;