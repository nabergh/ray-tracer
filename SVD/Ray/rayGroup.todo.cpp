#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	printf("%s\n", "RayGroup intersect");
	RayIntersectionInfo inter;
	double minT = -1;
	for (int i = 0; i < sNum; ++i) {
		if (result > shapes[i].intersect(ray, inter, mx)) {
			double t = (inter.iCoordinate - ray.position).length();
			if (t < minT || (t < mx && minT == -1)) {
				minT = t;
				iInfo.iCoordinate = inter.iCoordinate;
			}
		}
	}
	return minT;
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
