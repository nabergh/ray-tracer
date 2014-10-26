#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getDiffuse(Point3D cameraPosition, RayIntersectionInfo &iInfo) {
	Point3D rayDir = iInfo.iCoordinate - location;
	float rayDirDot = rayDir.unit().dot(direction);
	if (rayDirDot > cos(cutOffAngle)) {
		float dot = iInfo.normal.dot(rayDir.negate().unit());
		if (dot > 0) {
			float d = rayDir.length();
			Point3D attenuation = color / (constAtten + linearAtten * d + quadAtten * d * d);
			return iInfo.material->diffuse * attenuation * pow(rayDirDot, dropOffRate) * dot;
		}
	}
	return Point3D(0, 0, 0);
}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition, RayIntersectionInfo &iInfo) {
	Point3D rayDir = iInfo.iCoordinate - location;
	float rayDirDot = rayDir.unit().dot(direction);
	if (rayDirDot > cos(cutOffAngle)) {
		Point3D lightDir = (location - iInfo.iCoordinate).unit();
		Point3D reflect = (iInfo.normal * iInfo.normal.dot(lightDir) * 2 - lightDir).unit();
		float dot = reflect.dot((cameraPosition - iInfo.iCoordinate).unit());
		if (dot > 0) {
			float d = rayDir.length();
			Point3D attenuation = color / (constAtten + linearAtten * d + quadAtten * d * d);
			return iInfo.material->specular * attenuation * pow(dot, iInfo.material->specularFallOff) * pow(rayDirDot, dropOffRate);
		}
	}
	return Point3D(0, 0, 0);
}
int RaySpotLight::isInShadow(RayIntersectionInfo &iInfo, RayShape *shape, int &isectCount) {
	RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
	Point3D lightDir = (location - iInfo.iCoordinate).unit();
	Point3D origin = iInfo.iCoordinate + (lightDir * 0.0000001);
	float mx = shape->intersect(Ray3D(origin, lightDir), inter, -1);
	return mx > 0;
}
Point3D RaySpotLight::transparency(RayIntersectionInfo &iInfo, RayShape *shape, Point3D cLimit) {
	return Point3D(1, 1, 1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index) {
}
