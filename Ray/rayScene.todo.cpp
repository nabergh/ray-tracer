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
	Point3D dx = (right - left) * (((width - i) + 0.5) / width);
	Point3D dy = (bottom - top) * (((height - j) + 0.5) / height);
	Point3D result = topleft + dx + dy;

	return Ray3D(camera->position, result);
}

Point3D RayScene::GetColor(Ray3D ray, int rDepth, Point3D cLimit) {
	RayIntersectionInfo inter = {NULL, Point3D(0,0,0), Point3D(0,0,0), Point2D(0,0)};
	double result = group->intersect(ray, inter, -1);
	if (result > 0) {
		Point3D color = Point3D(0.0, 0.0, 0.0);
		color += inter.material->ambient * ambient;
		color += inter.material->emissive;
		for (int i = 0; i < 3; ++i) {
			if (color[i] > 1.0) {
				color[i] = 1.0;
			}
		}
		return color;
	} else return background;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void) {
}
void RayTexture::setUpOpenGL(void) {
}



		// printf("%f %f %f   %f %f %f\n", inter.material->ambient[0], inter.material->ambient[1], inter.material->ambient[2], inter.material->emissive[0], inter.material->emissive[1], inter.material->emissive[2]);







