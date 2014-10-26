#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	double tLength = ray.direction.length();
	Point3D toCenter = center - ray.position;
	double pLength = ray.direction.unit().dot(toCenter);
	Point3D p = ray(pLength / tLength);
	double a = (p - center).length();
	if (a < radius - 1e-5) {
		double b = sqrt(radius * radius - a * a);
		if ((pLength - b) / tLength < mx || mx == -1) {
			iInfo.iCoordinate = ray((pLength - b) / tLength);
			iInfo.material = material;
			iInfo.normal = (iInfo.iCoordinate - center).unit();
			return (pLength - b) / tLength;
		}
	} else if (a < radius + 1e-5 && (pLength / tLength < mx || mx == -1)) {
		iInfo.iCoordinate = p;
		iInfo.material = material;
		iInfo.normal = (iInfo.iCoordinate - center).unit();
		return pLength / tLength;
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
