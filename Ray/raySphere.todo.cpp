#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	double distCenter = (center - ray.position).length();
	double tLength = ray.direction.length();
	Point3D p = ray(distCenter / tLength);
	double a = (p - center).length();
	if (a < radius - 1e-5) {
		double b = sqrt(radius * radius - a * a);
		if (distCenter - b < mx || mx == -1) {
			iInfo.iCoordinate = ray((distCenter - b) / tLength);
			iInfo.material = material;
			iInfo.normal = (iInfo.iCoordinate - center).unit();
			return distCenter - b;
		}
	} else if (a < radius + 1e-5 && (distCenter < mx || mx == -1)) {
		iInfo.iCoordinate = p;
		iInfo.material = material;
		return distCenter;
	}
	return -1;
}
BoundingBox3D RaySphere::setBoundingBox(void) {
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex) {
	return -1;
}
