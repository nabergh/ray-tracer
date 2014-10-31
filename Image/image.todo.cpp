#include "image.h"
#include <stdlib.h>
#include <math.h>

////////////////////////////
// Image processing stuff //
////////////////////////////
Pixel::Pixel(const Pixel32 &p) {
	r = p.r / 255.0;
	g = p.g / 255.0;
	b = p.b / 255.0;
	a = p.a / 255.0;
}

Pixel32::Pixel32(const Pixel &p) {
	r = p.r <= 1 ? (p.r >= 0 ? p.r * 255 : 0) : 255;
	g = p.g <= 1 ? (p.g >= 0 ? p.g * 255 : 0) : 255;
	b = p.b <= 1 ? (p.b >= 0 ? p.b * 255 : 0) : 255;
	a = p.a <= 1 ? (p.a >= 0 ? p.a * 255 : 0) : 255;
}

int Image32::AddRandomNoise(const float &noise, Image32 &outputImage) const {
	return 0;
}
int Image32::Brighten(const float &brightness, Image32 &outputImage) const {
	return 0;
}

int Image32::Luminance(Image32 &outputImage) const {
	return 0;
}

int Image32::Contrast(const float &contrast, Image32 &outputImage) const {
	return 0;
}

int Image32::Saturate(const float &saturation, Image32 &outputImage) const {
	return 0;
}

int Image32::Quantize(const int &bits, Image32 &outputImage) const {
	return 0;
}

int Image32::RandomDither(const int &bits, Image32 &outputImage) const {
	return 0;
}
int Image32::OrderedDither2X2(const int &bits, Image32 &outputImage) const {
	return 0;
}

int Image32::FloydSteinbergDither(const int &bits, Image32 &outputImage) const {
	return 0;
}

int Image32::Blur3X3(Image32 &outputImage) const {
	return 0;
}

int Image32::EdgeDetect3X3(Image32 &outputImage) const {
	return 0;
}
int Image32::ScaleNearest(const float &scaleFactor, Image32 &outputImage) const {
	return 0;
}

int Image32::ScaleBilinear(const float &scaleFactor, Image32 &outputImage) const {
	return 0;
}

int Image32::ScaleGaussian(const float &scaleFactor, Image32 &outputImage) const {
	return 0;
}

int Image32::RotateNearest(const float &angle, Image32 &outputImage) const {
	return 0;
}

int Image32::RotateBilinear(const float &angle, Image32 &outputImage) const {
	return 0;
}

int Image32::RotateGaussian(const float &angle, Image32 &outputImage) const {
	return 0;
}


int Image32::SetAlpha(const Image32 &matte) {
	return 0;
}

int Image32::Composite(const Image32 &overlay, Image32 &outputImage) const {
	return 0;
}

int Image32::CrossDissolve(const Image32 &source, const Image32 &destination, const float &blendWeight, Image32 &ouputImage) {
	return 0;
}
int Image32::Warp(const OrientedLineSegmentPairs &olsp, Image32 &outputImage) const {
	return 0;
}

int Image32::FunFilter(Image32 &outputImage) const {
	return 0;
}
int Image32::Crop(const int &x1, const int &y1, const int &x2, const int &y2, Image32 &outputImage) const {
	return 0;
}


Pixel32 Image32::NearestSample(const float &x, const float &y) const {
	return Pixel32();
}
Pixel32 Image32::BilinearSample(const float &x, const float &y) const {
	int i = (int) x;
	int j = (int) y;

	float a = x - i;
	float b = y - j;

	float q1 = a * b;
	float q2 = (1 - a) * b;
	float q3 = a * (1 - b);
	float q4 = (1 - a) * (1 - b);

	Pixel p1 = Pixel(pixel(i, j));
	Pixel p2 = i + 1 >= w ? p1 : Pixel(pixel(i + 1, j));
	Pixel p3 = j + 1 >= h ? p1 : Pixel(pixel(i, j + 1));
	Pixel p4 = i + 1 >= w || j + 1 >= h ? p1 : Pixel(pixel(i + 1, j + 1));

	Pixel p = Pixel();

	p.r = q4 * p1.r + q3 * p2.r + q2 * p3.r + q1 * p4.r;
	p.g = q4 * p1.g + q3 * p2.g + q2 * p3.g + q1 * p4.g;
	p.b = q4 * p1.b + q3 * p2.b + q2 * p3.b + q1 * p4.b;

	return Pixel32(p);
}
Pixel32 Image32::GaussianSample(const float &x, const float &y, const float &variance, const float &radius) const {
	return Pixel32();
}
