// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

#include <iostream>

const float DEG2RAD = pi/180.00; 

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	const float angle = degrees * DEG2RAD;

	return cos(angle) * mat3(1, 0, 0, 
							 0, 1, 0,
							 0, 0, 1) + 
	       (1 - cos(angle)) * mat3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
	       						   axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
	       						   axis.x*axis.z, axis.y*axis.z, axis.z*axis.z) + 
	       sin(angle) * mat3(      0,  axis.z, -axis.y,
	       					 -axis.z,       0,  axis.x,
	       					  axis.y, -axis.x,       0);

}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	const mat3 r = rotate(degrees, up);
	eye = r * eye;
	up = r * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	const mat3 r = rotate(degrees, glm::cross(glm::normalize(vec3(0,0,0) - eye), up));
	eye = r * eye;
	up = r * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) 
{
 	const vec3 w = glm::normalize(eye - vec3(0, 0, 0));
 	const vec3 u = glm::normalize(glm::cross(up, w));
 	const vec3 v = glm::cross(w, u);

 	return mat4(u.x, v.x, w.x, 0,
 		        u.y, v.y, w.y, 0,
 		        u.z, v.z, w.z, 0,
 		          -u.x*eye.x - u.y*eye.y - u.z*eye.z,   
 		          -v.x*eye.x - v.y*eye.y - v.z*eye.z, 
 		          -w.x*eye.x - w.y*eye.y - w.z*eye.z,
 		          1);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
