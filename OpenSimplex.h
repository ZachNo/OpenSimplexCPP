#ifndef OPENSIMPLEX_H
#define OPENSIMPLEX_H

#include <cstdint>

//OpenSimplex C++ implementation translated from Java and C#
//Credits: https://gist.github.com/KdotJPG/b1270127455a94ac5d19 https://gist.github.com/digitalshadow/134a3a02b67cecd72181

class OpenSimplex
{
public:
	OpenSimplex(int64_t seed = DEFAULT_SEED);
	OpenSimplex(const OpenSimplex&);
	OpenSimplex(OpenSimplex&&);
	OpenSimplex& operator=(const OpenSimplex&);
	OpenSimplex& operator=(OpenSimplex&&);
	virtual ~OpenSimplex();

    double noise(double x, double y);
    double noise(double x, double y, double z);
    double noise(double x, double y, double z, double w);

private:
    static const double STRETCH_CONSTANT_2D;
    static const double SQUISH_CONSTANT_2D;
    static const double STRETCH_CONSTANT_3D;
    static const double SQUISH_CONSTANT_3D;
    static const double STRETCH_CONSTANT_4D;
    static const double SQUISH_CONSTANT_4D;
    static const int NORM_CONSTANT_2D;
    static const int NORM_CONSTANT_3D;
    static const int NORM_CONSTANT_4D;
    static const int DEFAULT_SEED;
    static const int8_t GRADIENTS_2D[];
    static const int8_t GRADIENTS_3D[];
    static const int8_t GRADIENTS_4D[];

	struct Contribution2
	{
		double dx, dy;
		int xsb, ysb;
		Contribution2 *next;
		Contribution2(double multiplier, int xsb_, int ysb_) :
			dx(-xsb_ - multiplier * SQUISH_CONSTANT_2D),
			dy(-ysb_ - multiplier * SQUISH_CONSTANT_2D),
			xsb(xsb_), ysb(ysb_), next(nullptr)
		{};
	};

	struct Contribution3
	{
		double dx, dy, dz;
		int xsb, ysb, zsb;
		Contribution3 *next;
		Contribution3(double multiplier, int xsb_, int ysb_, int zsb_) :
			dx(-xsb_ - multiplier * SQUISH_CONSTANT_3D),
			dy(-ysb_ - multiplier * SQUISH_CONSTANT_3D),
			dz(-zsb_ - multiplier * SQUISH_CONSTANT_3D),
			xsb(xsb_), ysb(ysb_), zsb(zsb_), next(nullptr)
		{};
	};

	struct Contribution4
	{
		double dx, dy, dz, dw;
		int xsb, ysb, zsb, wsb;
		Contribution4 *next;
		Contribution4(double multiplier, int xsb_, int ysb_, int zsb_, int wsb_) :
			dx(-xsb_ - multiplier * SQUISH_CONSTANT_4D),
			dy(-ysb_ - multiplier * SQUISH_CONSTANT_4D),
			dz(-zsb_ - multiplier * SQUISH_CONSTANT_4D),
			dw(-wsb_ - multiplier * SQUISH_CONSTANT_4D),
			xsb(xsb_), ysb(ysb_), zsb(zsb_), wsb(wsb_), next(nullptr)
		{};
	};

    static Contribution2 **lookup2D;
	static Contribution3 **lookup3D;
	static Contribution4 **lookup4D;
	static bool initialized;

	inline int fastFloor(double x);

	int8_t *perm;
	int8_t *perm2D;
	int8_t *perm3D;
	int8_t *perm4D;
};

#endif
