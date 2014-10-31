#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v, Point3D n) {
	return (n * n.dot(v.negate()) * 2 - v.negate()).unit();
}

int RayScene::Refract(Point3D v, Point3D n, double ir, Point3D &refract) {
	float costheta1 = v.unit().dot(n.negate());
	refract = v * ir + n * (ir * costheta1 - sqrt(1 - ir * ir * (1 - costheta1 * costheta1)));
	if (isnan(refract[0]) || isnan(refract[1]) || isnan(refract[2])) {
		return 0;
	}
	return 1;
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
	Point3D dy = (bottom - top) * (((height - j) + 0.5) / height);
	Point3D result = topleft + dx + dy;

	return Ray3D(camera->position, result);
}

Point3D RayScene::GetColor(Ray3D ray, int rDepth, Point3D cLimit) {
	RayIntersectionInfo inter = {NULL, Point3D(0, 0, 0), Point3D(0, 0, 0), Point2D(0, 0)};
	ray.direction = ray.direction.unit();
	double result = group->intersect(ray, inter, -1);
	if (result > 1e-5) {
		Point3D color = Point3D(0.0, 0.0, 0.0);
		color += inter.material->ambient * ambient;
		color += inter.material->emissive;
		for (int i = 0; i < lightNum; ++i) {
			int shadow = 0;
			RayIntersectionInfo iInfo = inter;
			Point3D transparency = Point3D(1, 1, 1);
			if (lights[i]->isInShadow(iInfo, group, shadow)) {
				transparency = lights[i]->transparency(iInfo, group, cLimit);
			}
			if (transparency[0] > 0 || transparency[1] > 0 || transparency[2] > 0) {
				color += transparency * lights[i]->getDiffuse(ray.position, inter);
				color += transparency * lights[i]->getSpecular(ray.position, inter);
			}
		}
		if (rDepth > 1) {
			Point3D totalSpec = cLimit / inter.material->specular;
			if (totalSpec[0] < 1 || totalSpec[1] < 1 || totalSpec[2] < 1) {
				Point3D c = GetColor(Ray3D(inter.iCoordinate, Reflect(ray.direction, inter.normal) * 1e-5), rDepth - 1, totalSpec);
				if (c[0] != background[0] && c[1] != background[1] && c[2] != background[2]) {
					color += inter.material->specular * c;
				}
			}
			if (inter.material->transparent[0] != 0 || inter.material->transparent[1] != 0 || inter.material->transparent[2] != 0) {
				Point3D dir;
				double ir = inter.material->refind;
				if (ray.direction.dot(inter.normal) < 0) {
					ir = 1 / ir;
				}
				if (Refract(ray.direction, inter.normal, ir, dir)) {
					Point3D c = GetColor(Ray3D(inter.iCoordinate + ray.direction * 1e-5, dir), rDepth - 1, cLimit);
					color += inter.material->transparent * c;
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			if (color[i] > 1.0) {
				color[i] = 1.0;
			}
		}
		return color;
	} return background;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void) {
}
void RayTexture::setUpOpenGL(void) {
}

