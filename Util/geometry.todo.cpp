#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D &ray) const {
	double xmin, xmax, ymin, ymax, zmin, zmax;
	Point3D minPoint = (p[0] - ray.position) / ray.direction;
	Point3D maxPoint = (p[1] - ray.position) / ray.direction;
	xmin = fmin(minPoint[0], maxPoint[0]);
	ymin = fmin(minPoint[1], maxPoint[1]);
	xmax = fmax(minPoint[0], maxPoint[0]);
	ymax = fmax(minPoint[1], maxPoint[1]);
	if (xmin > ymax || ymin > xmax || xmax < 0 || ymax < 0) {
		return -1;
	}
	double tmin = fmax(xmin, ymin);
	zmin = fmin(minPoint[2], maxPoint[2]);
	zmax = fmax(minPoint[2], maxPoint[2]);
	if (zmin > fmin(xmax, ymax) || tmin > zmax || zmax < 0) {
		return -1;
	}
	tmin = fmin(tmin, zmin);
	if (tmin < 0) {
		return 0;
	}
	return tmin / ray.direction.length();
	// if (ray.direction[0] > 0) {
	// 	xmin = (p[0][0] - ray.position[0]) / ray.direction[0];
	// 	xmax = (p[1][0] - ray.position[0]) / ray.direction[0];
	// } else {
	// 	xmin = (p[1][0] - ray.position[0]) / ray.direction[0];
	// 	xmax = (p[0][0] - ray.position[0]) / ray.direction[0];
	// }
	// if (ray.direction[1] > 0) {
	// 	ymin = (p[0][1] - ray.position[1]) / ray.direction[1];
	// 	ymax = (p[1][1] - ray.position[1]) / ray.direction[1];
	// } else {
	// 	ymin = (p[1][1] - ray.position[1]) / ray.direction[1];
	// 	ymax = (p[0][1] - ray.position[1]) / ray.direction[1];
	// }
	// if (xmin > ymax || ymin > xmax || xmax < 0 || ymax < 0) {
	// 	return -1;
	// }
	// if (ray.direction[2] > 0) {
	// 	zmin = (p[0][2] - ray.position[2]) / ray.direction[2];
	// 	zmax = (p[1][2] - ray.position[2]) / ray.direction[2];
	// } else {
	// 	zmin = (p[1][2] - ray.position[2]) / ray.direction[2];
	// 	zmax = (p[0][2] - ray.position[2]) / ray.direction[2];
	// }
	// double tmin = fmax(xmin, ymin);
	// if (zmin > fmin(xmax, ymax) || tmin > zmax || zmax < 0) {
	// 	return -1;
	// }
	// tmin = fmin(tmin, zmin);
	// if (tmin < 0) {
	// 	return 0;
	// }
	// return tmin / ray.direction.length();
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D &e) {
	(*this) = Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion &q) {
	(*this) = Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D &m, int iter) {
	return m;
}
