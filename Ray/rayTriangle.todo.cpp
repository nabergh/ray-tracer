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
	double t = -1 * (ray.position.dot(plane.normal) + plane.distance) / (ray.direction.unit().dot(plane.normal));
	if (t <= 1e-5) {
		return -1;
	}
	Point3D p = ray(t / ray.direction.length());
	Point3D rayVector = p - ray.position;
	if (rayVector.length() / ray.direction.length() > mx && mx > 0) {
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

	iInfo.normal = Point3D(0, 0, 0);
	Point3D side2 = v[1]->position - v[0]->position;
	Point3D side1 = v[2]->position - v[0]->position;
	float totalArea = (side1 ^ side2).length() / 2;
	float gamma = ((p - v[0]->position) ^ side2).length() / (2 * totalArea);
	float beta = ((p - v[0]->position) ^ side1).length() / (2 * totalArea);
	float alpha = 1 - beta - gamma;
	iInfo.normal += v[0]->normal * alpha;
	iInfo.normal += v[1]->normal * beta;
	iInfo.normal += v[2]->normal * gamma;
	iInfo.normal = iInfo.normal.unit();

	iInfo.texCoordinate = v[0]->texCoordinate * alpha + v[1]->texCoordinate * beta + v[2]->texCoordinate * gamma;
	return rayVector.length() / ray.direction.length();
}
BoundingBox3D RayTriangle::setBoundingBox(void) {
	Point3D pts[3] = {v[0]->position, v[1]->position, v[2]->position};
	bBox = BoundingBox3D(pts, 3);
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex) {
	return -1;
}
