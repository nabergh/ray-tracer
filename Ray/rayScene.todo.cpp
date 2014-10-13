#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v, Point3D n) {
	return Point3D();
}

int RayScene::Refract(Point3D v, Point3D n, double ir, Point3D &refract) {
	return 0;
}

Ray3D RayScene::GetRay(RayCamera *camera, int i, int j, int width, int height) {

	double hTan = tan(camera->heightAngle / 2);
	Point3D top = camera->direction + camera->up * hTan;
	Point3D bottom = camera->direction - camera->up * hTan;
	double wTan = hTan * camera->aspectRatio;
	Point3D right = camera->direction + camera->right * wTan;
	Point3D left = camera->direction - camera->right * wTan;

	Point3D topleft = left + camera->up * hTan;
	Point3D dx = (right - left) * ((i + 0.5) / width);
	Point3D dy = (bottom - top) * ((j + 0.5) / height);
	Point3D result = topleft + dx + dy;

	return Ray3D(camera->position, result);
}

Point3D RayScene::GetColor(Ray3D ray, int rDepth, Point3D cLimit) {
	Point3D behind = ray(-1);
	RayIntersectionInfo inter = {NULL, behind, Point3D(), Point2D()};
	double result = group->intersect(ray, inter, -1);
	if (result > 0) {
		return Point3D(1.0, 1.0, 1.0);
	} else
		return Point3D(0.0, 0.0, 0.0);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void) {
}
void RayTexture::setUpOpenGL(void) {
}
