#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
struct BBoxIntersection {
	RayShape *shape;
	BoundingBox3D *bBox;
	double distance;
};

bool compareBBoxIntersection(BBoxIntersection b1, BBoxIntersection b2) {
	return b1.distance < b2.distance;
}

double RayGroup::intersect(Ray3D ray, RayIntersectionInfo &iInfo, double mx) {
	RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
	Ray3D oldray = ray;
	ray = getInverseMatrix() * ray;
	vector<BBoxIntersection> bBoxes(sNum);
	int intNo = 0;
	for (int i = 0; i < sNum; ++i) {
		double distance = shapes[i]->bBox.intersect(ray);
		if (distance != -1 && (mx == -1 || distance < mx)) {
			BBoxIntersection b = {shapes[i], &shapes[i]->bBox, distance};
			bBoxes[intNo] = b;
			intNo++;
		}
	}
	bBoxes.resize(intNo);
	sort(bBoxes.begin(), bBoxes.end(), compareBBoxIntersection);
	for (int i = 0; i < intNo; ++i) {
		if (bBoxes[i].distance > mx && mx != -1) {
			break;
		}
		if (bBoxes[i].shape->intersect(ray, inter, mx) > 0) {
			inter.iCoordinate = getMatrix() * inter.iCoordinate;
			inter.normal = getNormalMatrix().multDirection(inter.normal).unit();
			double t = (inter.iCoordinate - ray.position).length();
			mx = t;
			iInfo.iCoordinate = inter.iCoordinate;
			iInfo.material = inter.material;
			iInfo.normal = inter.normal;
			iInfo.texCoordinate = inter.texCoordinate;
		}
	}
	if (inter.material == NULL) {
		return -1;
	}
	return mx;
}

BoundingBox3D RayGroup::setBoundingBox(void) {
	bBox = BoundingBox3D();
	for (int i = 0; i < sNum; ++i) {
		shapes[i]->setBoundingBox();
		bBox += shapes[i]->bBox.transform(getMatrix());
	}
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
