#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
	Ray3D oldray = ray;
	ray = getInverseMatrix() * ray;
	for (int i = 0; i < sNum; ++i) {
		if (shapes[i]->intersect(ray, inter, mx) > 0) {
			inter.iCoordinate = getMatrix() * inter.iCoordinate;
			inter.normal = getNormalMatrix().multDirection(inter.normal).unit();
			double t = (inter.iCoordinate - ray.position).length();
			mx = t;
			iInfo.iCoordinate = inter.iCoordinate;
			iInfo.material = inter.material;
			iInfo.normal = inter.normal;
		}
	}
	if (inter.material == NULL) {
		return -1;
	}
	return mx / ray.direction.length();
}

BoundingBox3D RayGroup::setBoundingBox(void) {
	return bBox;
}

int StaticRayGroup::set(void) {
	inverseTransform = localTransform.invert();
	normalTransform = localTransform.transpose().invert();
	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void) {
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex) {
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void) {
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void) {
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void) {
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void) {
	return Matrix4D::IdentityMatrix();
}
