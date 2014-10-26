#include <math.h>
#include <GL/glut.h>
#include "rayPointLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition, RayIntersectionInfo &iInfo) {
	float d = (iInfo.iCoordinate - location).length();
	Point3D attenuation = color / (constAtten + linearAtten * d + quadAtten * d * d);
	float dot = iInfo.normal.dot((location - iInfo.iCoordinate).unit());
	if (dot > 0) {
		return iInfo.material->diffuse * attenuation * dot;
	}
	return Point3D(0, 0, 0);
}
Point3D RayPointLight::getSpecular(Point3D cameraPosition, RayIntersectionInfo &iInfo) {
	float d = (iInfo.iCoordinate - location).length();
	Point3D attenuation = color / (constAtten + linearAtten * d + quadAtten * d * d);
	Point3D lightDir = (location - iInfo.iCoordinate).unit();
	Point3D reflect = (iInfo.normal * iInfo.normal.dot(lightDir) * 2 - lightDir).unit();
	float dot = reflect.dot((cameraPosition - iInfo.iCoordinate).unit());
	if (dot > 0) {
		return iInfo.material->specular * attenuation * pow(dot, iInfo.material->specularFallOff);
	}
	return Point3D(0, 0, 0);
}
int RayPointLight::isInShadow(RayIntersectionInfo &iInfo, RayShape *shape, int &isectCount) {
	RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
	Point3D lightDir = (location - iInfo.iCoordinate).unit();
	Point3D origin = iInfo.iCoordinate + (lightDir * 0.0000001);
	float mx = shape->intersect(Ray3D(origin, lightDir), inter, -1);
	return mx > 0;
}
Point3D RayPointLight::transparency(RayIntersectionInfo &iInfo, RayShape *shape, Point3D cLimit) {
	return Point3D(1, 1, 1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL(int index) {
}
