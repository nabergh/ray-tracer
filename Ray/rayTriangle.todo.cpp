#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void) {
	plane = Plane3D(v[0]->position, v[1]->position, v[2]->position);
}
double RayTriangle::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	double t = -1 * plane(ray.position) / (ray.direction.dot(plane.normal));
	Point3D p = ray(t);
	Point3D rayVector = p - ray.position;
	if (rayVector.length() > mx && mx > 0) {
		return -1;
	}

	Plane3D plane1 = Plane3D(v[0]->position, v[1]->position, ray.position);
	plane1.makePositive(v[2]->position);
	if (rayVector.dot(plane1.normal) < 0) {
		return -1;
	}
	plane1 = Plane3D(v[1]->position, v[2]->position, ray.position);
	plane1.makePositive(v[0]->position);
	if (rayVector.dot(plane1.normal) < 0) {
		return -1;
	}
	plane1 = Plane3D(v[2]->position, v[0]->position, ray.position);
	plane1.makePositive(v[1]->position);
	if (rayVector.dot(plane1.normal) < 0) {
		return -1;
	}
	iInfo.iCoordinate = p;
	iInfo.material = material;
	plane.makePositive(ray.position);
	iInfo.normal = plane.normal;
	return rayVector.length();
}
BoundingBox3D RayTriangle::setBoundingBox(void) {
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex) {
	return -1;
}
