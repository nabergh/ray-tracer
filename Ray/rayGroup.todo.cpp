#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	RayIntersectionInfo inter;
	for (int i = 0; i < sNum; ++i) {
		if (shapes[i]->intersect(ray, inter, mx) > 0) {
			double t = (inter.iCoordinate - ray.position).length();
			mx = t;
			iInfo.iCoordinate = inter.iCoordinate;
		}
	}
	return mx;
}

BoundingBox3D RayGroup::setBoundingBox(void) {
	return bBox;
}

int StaticRayGroup::set(void) {
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
