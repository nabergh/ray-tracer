#include <math.h>
#include <GL/glut.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition, RayIntersectionInfo &iInfo) {
	float dot = iInfo.normal.dot(direction.negate());
	if (dot > 0) {
		return iInfo.material->diffuse * color * dot;
	}
	return Point3D(0, 0, 0);
}
Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition, RayIntersectionInfo &iInfo) {
	Point3D reflect = (iInfo.normal * iInfo.normal.dot(direction.negate()) * 2 - direction.negate()).unit();
	float dot = reflect.dot((cameraPosition - iInfo.iCoordinate).unit());
	if (dot > 0) {
		return iInfo.material->specular * color * pow(dot, iInfo.material->specularFallOff);
	}
	return Point3D(0, 0, 0);
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo &iInfo, RayShape *shape, int &isectCount) {
	// RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
	Point3D lightDir = direction.negate();
	Point3D origin = iInfo.iCoordinate + (lightDir * 0.0000000001);
	float mx = shape->intersect(Ray3D(origin, lightDir), iInfo, -1);
	return mx > 0;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo &iInfo, RayShape *shape, Point3D cLimit) {
	cLimit = cLimit * iInfo.material->transparent;
	if (cLimit[0] < 1 || cLimit[1] < 1 || cLimit[2] < 1) {
		RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
		int shadow = 0;
		Point3D tran = Point3D(1, 1, 1);
		if (isInShadow(inter, shape, shadow)) {
			tran = transparency(inter, shape, cLimit);
		}
		if (inter.material == iInfo.material) {
			tran = tran / iInfo.material->transparent;
		}
		return iInfo.material->transparent * tran;
	}
	return Point3D(1, 1, 1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index) {
}
