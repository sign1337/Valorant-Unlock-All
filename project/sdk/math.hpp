#include <cmath>  
#pragma once
// For acosf, atan2f, sqrtf
#define RAD2DEG(rad) ((rad) * (180.0f / 3.14159265358979323846f))

struct FRotator
{
	double Pitch, Yaw, Roll;

	FRotator()
		: Pitch(0), Yaw(0), Roll(0)
	{
	}

	FRotator(double pitch, double yaw, double roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}

	FRotator operator+ (const FRotator& other) const { return FRotator(Pitch + other.Pitch, Yaw + other.Yaw, Roll + other.Roll); }

	FRotator operator- (const FRotator& other) const { return FRotator(Pitch - other.Pitch, Yaw - other.Yaw, Roll - other.Roll); }

	FRotator operator* (double scalar) const { return FRotator(Pitch * scalar, Yaw * scalar, Roll * scalar); }

	FRotator& operator=  (const FRotator& other) { Pitch = other.Pitch; Yaw = other.Yaw; Roll = other.Roll; return *this; }

	FRotator& operator+= (const FRotator& other) { Pitch += other.Pitch; Yaw += other.Yaw; Roll += other.Roll; return *this; }

	FRotator& operator-= (const FRotator& other) { Pitch -= other.Pitch; Yaw -= other.Yaw; Roll -= other.Roll; return *this; }

	FRotator& operator*= (const double other) { Yaw *= other; Pitch *= other; Roll *= other; return *this; }

	struct fquat Quaternion() const;
};


struct FVector2D
{
	double X, Y;

	FVector2D() : X(0), Y(0) {}

	FVector2D(double x, double y) : X(x), Y(y) {}

	double Size() const;

	FVector2D operator + (const FVector2D& other) const { return FVector2D(X + other.X, Y + other.Y); }

	FVector2D operator- (const FVector2D& other) const { return FVector2D(X - other.X, Y - other.Y); }

	FVector2D operator* (double scalar) const { return FVector2D(X * scalar, Y * scalar); }

	FVector2D& operator=  (const FVector2D& other) { X = other.X; Y = other.Y; return *this; }

	FVector2D& operator+= (const FVector2D& other) { X += other.X; Y += other.Y; return *this; }

	FVector2D& operator-= (const FVector2D& other) { X -= other.X; Y -= other.Y; return *this; }

	FVector2D& operator*= (const double other) { X *= other; Y *= other; return *this; }

	friend bool operator==(const FVector2D& one, const FVector2D& two) { return one.X == two.X && one.Y == two.Y; }

	friend bool operator!=(const FVector2D& one, const FVector2D& two) { return !(one == two); }

	friend bool operator>(const FVector2D& one, const FVector2D& two) { return one.X > two.X && one.Y > two.Y; }

	friend bool operator<(const FVector2D& one, const FVector2D& two) { return one.X < two.X && one.Y < two.Y; }
	bool IsValid()
	{
		if (X == 0 || Y == 0)
			return false;
		else
			return true;
	}
};

struct fvector2d
{
	double x, y;

	fvector2d() : x(0), y(0) {}

	fvector2d(double x, double y) : x(x), y(y) {}

	fvector2d operator + (const fvector2d& other) const { return fvector2d(x + other.x, y + other.y); }

	fvector2d operator- (const fvector2d& other) const { return fvector2d(x - other.x, y - other.y); }

	fvector2d operator* (double scalar) const { return fvector2d(x * scalar, y * scalar); }

	fvector2d& operator=  (const fvector2d& other) { x = other.x; y = other.y; return *this; }

	fvector2d& operator+= (const fvector2d& other) { x += other.x; y += other.y; return *this; }

	fvector2d& operator-= (const fvector2d& other) { x -= other.x; y -= other.y; return *this; }

	fvector2d& operator*= (const double other) { x *= other; y *= other; return *this; }

	friend bool operator==(const fvector2d& one, const fvector2d& two) { return one.x == two.x && one.y == two.y; }

	friend bool operator!=(const fvector2d& one, const fvector2d& two) { return !(one == two); }

	friend bool operator>(const fvector2d& one, const fvector2d& two) { return one.x > two.x && one.y > two.y; }

	friend bool operator<(const fvector2d& one, const fvector2d& two) { return one.x < two.x && one.y < two.y; }

	bool is_valid()
	{
		if (x == 0 || y == 0)
			return false;
		else
			return true;
	}

};


struct FVector
{
	bool is_null() {
		if (X == 0 && Y == 0 && Z == 0)
			return true;

		return false;
	}

	double X, Y, Z;
	FVector GetSafeNormal(double Tolerance = 1e-6) const
	{
		const double squareSum = X * X + Y * Y + Z * Z;
		if (squareSum > Tolerance)
		{
			const double scale = 1 / sqrt(squareSum);
			return FVector(X * scale, Y * scale, Z * scale);
		}
		return FVector(0, 0, 0);
	}

	FVector() : X(0), Y(0), Z(0) {}

	FVector(double X, double Y, double z) : X(X), Y(Y), Z(z) {}

	FVector(double InF) : X(InF), Y(InF), Z(InF) {}

	FVector ClampFVector() {
		while (X < -88) X += 360;
		//    if (X == -89.f) X = !-89;
		while (X > 89) X -= 89;

		//if (X < 0)X >= 0;
		//if (X == -89.f) X != -89.f;
		while (Y < -180) Y += 360;
		while (Y > 180) Y -= 360;
		Z = 0;

		return FVector{ X, Y,Z };

	}
	inline static double Distance2(const FVector& a, const FVector& b)
	{
		double X = a.X - b.X;
		double Y = a.Y - b.Y;
		double Z = a.Z - b.Z;

		return sqrt((X * X) + (Y * Y) + (Z * Z)) * 0.03048; // scale factor applied
	}


	inline double Distance(FVector v)
	{
		double X = this->X - v.X;
		double Y = this->Y - v.Y;
		double z = this->Z - v.Z;

		return sqrt((X * X) + (Y * Y) + (z * z)) * 0.03048;
	}
	bool IsNearlyZero(double Tolerance = 1e-6) const
	{
		return (fabs(X) <= Tolerance) && (fabs(Y) <= Tolerance) && (fabs(Z) <= Tolerance);
	}
	bool IsNormalized(double Tolerance = 1e-4) const
	{
		return fabs(SizeSquared() - 1) <= Tolerance;
	}
	void normalize() {
		double len = sqrt(X * X + Y * Y + Z * Z);
		if (len > 0.0) {
			double inv_len = 1.0 / len;
			X = inv_len; Y = inv_len; Z *= inv_len;
		}
	}
	inline double Dot(const FVector& B) const { return (X * B.X) + (Y * B.Y) + (Z * B.Z); }
	inline double DotProduct(const FVector& a, const FVector& b) { return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }

	inline double MagnitudeSqr() const { return Dot(*this); }

	inline double Magnitude() const { return std::sqrt(MagnitudeSqr()); }

	double Size() const { return sqrt(X * X + Y * Y + Z * Z); }

	double size() const { return sqrt(X * X + Y * Y + Z * Z); }

	double Sum() const { return X + Y + Z; }

	double Size2D() const { return sqrt(X * X + Y * Y); }

	double SizeSquared() const { return X * X + Y * Y + Z * Z; }

	double DistTo(const FVector& V) const { return (*this - V).Size(); }


	FVector operator+(const FVector& other) const { return FVector(X + other.X, Y + other.Y, Z + other.Z); }

	FVector operator-(const FVector& other) const { return FVector(X - other.X, Y - other.Y, Z - other.Z); }

	FVector operator*(const FVector& V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }

	FVector operator/(const FVector& V) const { return FVector(X / V.X, Y / V.Y, Z / V.Z); }

	bool operator==(const FVector& V) const { return X == V.X && Y == V.Y && Z == V.Z; }

	bool operator!=(const FVector& V) const { return X != V.X || Y != V.Y || Z != V.Z; }

	FVector operator-() const { return FVector(-X, -Y, -Z); }

	FVector operator+(double Bias) const { return FVector(X + Bias, Y + Bias, Z + Bias); }

	FVector operator-(double Bias) const { return FVector(X - Bias, Y - Bias, Z - Bias); }

	FVector operator*(double Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); } const

		FVector operator/(double Scale) const { const double RScale = 1 / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }

	FVector operator=(const FVector& V) { X = V.X; Y = V.Y; Z = V.Z; return *this; }

	FVector operator+=(const FVector& V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }

	FVector operator-=(const FVector& V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }

	FVector operator*=(const FVector& V) { X *= V.X; Y *= V.Y; Z *= V.Z; return *this; }

	FVector operator/=(const FVector& V) { X /= V.X; Y /= V.Y; Z /= V.Z; return *this; }

	FVector operator*=(double Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }

	FVector operator/=(double V) { const double RV = 1 / V; X *= RV; Y *= RV; Z *= RV; return *this; }

	double operator|(const FVector& V) const { return X * V.X + Y * V.Y + Z * V.Z; }

	FVector operator^(const FVector& V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }

	bool IsValid()
	{
		if (X == 0 || Y == 0 || Z == 0)
			return false;
		else
			return true;
	}
	static const FVector ZeroVector;

	static const FVector OneVector;
};
float __sqrtf(float _X) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_X))); }
float __fabs(float x)
{
	if (x < 0)
		return -x;

	return x;
}
#define M_PI3 3.14159265358979323846


#define RAD2DEG2(x) x * 180.f / (float)M_PI3


float XM_PI = 3.141592654f;
float XM_2PI = 6.283185307f;
float XM_1DIVPI = 0.318309886f;
float XM_1DIV2PI = 0.159154943f;
float XM_PIDIV2 = 1.570796327f;
float XM_PIDIV4 = 0.785398163f;

inline float __acosf
(
	float Value
)
{
	// Clamp input to [-1,1].
	bool nonnegative = (Value >= 0.0f);
	float x = __fabs(Value);
	float omx = 1.0f - x;
	if (omx < 0.0f)
	{
		omx = 0.0f;
	}
	float root = __sqrtf(omx);

	// 7-degree minimax approximation
	float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + 1.5707963050f;
	result *= root;

	// acos(x) = pi - acos(-x) when x < 0
	return (nonnegative ? result : XM_PI - result);
}
float __atan2f(float y, float x)
{
	float t0, t1, t3, t4;

	t3 = __fabs(x);
	t1 = __fabs(y);
	t0 = max(t3, t1);
	t1 = min(t3, t1);
	t3 = float(1) / t0;
	t3 = t1 * t3;

	t4 = t3 * t3;
	t0 = -float(0.013480470);
	t0 = t0 * t4 + float(0.057477314);
	t0 = t0 * t4 - float(0.121239071);
	t0 = t0 * t4 + float(0.195635925);
	t0 = t0 * t4 - float(0.332994597);
	t0 = t0 * t4 + float(0.999995630);
	t3 = t0 * t3;

	t3 = (__fabs(y) > __fabs(x)) ? float(1.570796327) - t3 : t3;
	t3 = (x < 0) ? float(3.141592654) - t3 : t3;
	t3 = (y < 0) ? -t3 : t3;

	return t3;
}


class frotator {
public:
	frotator() : pitch(0.f), yaw(0.f), roll(0.f) {}
	frotator(double pitch, double yaw) : pitch(pitch), yaw(yaw), roll(0.f) {}
	frotator(double pitch, double yaw, double roll) : pitch(pitch), yaw(yaw), roll(roll) {}

	frotator operator + (const frotator& other) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
	frotator operator - (const frotator& other) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
	frotator operator * (double scalar) const { return { this->pitch * scalar, this->yaw * scalar, this->roll * scalar }; }
	frotator operator / (double divide) const { return { this->pitch / divide, this->yaw / divide, this->roll / divide }; }

	frotator& operator *= (const double other) { this->yaw *= other; this->pitch *= other; this->roll *= other; return *this; }
	frotator& operator /= (const double other) { this->yaw /= other; this->pitch /= other; this->roll /= other; return *this; }

	frotator& operator =  (const frotator& other) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
	frotator& operator += (const frotator& other) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
	frotator& operator -= (const frotator& other) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
	frotator& operator *= (const frotator& other) { this->pitch *= other.pitch; this->yaw *= other.yaw; this->roll *= other.roll; return *this; }
	frotator& operator /= (const frotator& other) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

	operator bool()
	{
		return bool(this->pitch && this->yaw && this->roll);
	}

	friend bool operator==(const frotator& first, const frotator& second)
	{
		return first.pitch == second.pitch && first.yaw == second.yaw && first.roll == second.roll;
	}

	friend bool operator!=(const frotator& first, const frotator& second)
	{
		return !(first == second);
	}

public:

	double pitch;
	double yaw;
	double roll;
};

struct fvector
{
	double x, y, z;

	fvector() : x(0.f), y(0.f), z(0.f) {}
	fvector(double x, double y, double z) : x(x), y(y), z(z) {}
	fvector(double InF) : x(InF), y(InF), z(InF) {}

	fvector operator+(const fvector& other) const { return fvector(x + other.x, y + other.y, z + other.z); }
	fvector operator-(const fvector& other) const { return fvector(x - other.x, y - other.y, z - other.z); }
	fvector operator*(const fvector& V) const { return fvector(x * V.x, y * V.y, z * V.z); }
	fvector operator/(const fvector& V) const { return fvector(x / V.x, y / V.y, z / V.z); }

	bool operator==(const fvector& V) const { return x == V.x && y == V.y && z == V.z; }
	bool operator!=(const fvector& V) const { return x != V.x || y != V.y || z != V.z; }

	fvector operator-() const { return fvector(-x, -y, -z); }
	fvector operator+(double Bias) const { return fvector(x + Bias, y + Bias, z + Bias); }
	fvector operator-(double Bias) const { return fvector(x - Bias, y - Bias, z - Bias); }
	fvector operator*(double Scale) const { return fvector(x * Scale, y * Scale, z * Scale); }
	fvector operator/(double Scale) const { const double RScale = 1.f / Scale; return fvector(x * RScale, y * RScale, z * RScale); }

	fvector operator=(const fvector& V) { x = V.x; y = V.y; z = V.z; return *this; }
	fvector operator+=(const fvector& V) { x += V.x; y += V.y; z += V.z; return *this; }
	fvector operator-=(const fvector& V) { x -= V.x; y -= V.y; z -= V.z; return *this; }
	fvector operator*=(const fvector& V) { x *= V.x; y *= V.y; z *= V.z; return *this; }
	fvector operator/=(const fvector& V) { x /= V.x; y /= V.y; z /= V.z; return *this; }
	fvector operator*=(double Scale) { x *= Scale; y *= Scale; z *= Scale; return *this; }
	fvector operator/=(double V) { const double RV = 1.f / V; x *= RV; y *= RV; z *= RV; return *this; }

	double operator|(const fvector& V) const { return x * V.x + y * V.y + z * V.z; }
	fvector operator^(const fvector& V) const { return fvector(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x); }

	static float DotProduct(const fvector& a, const fvector& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	__forceinline float dot(const fvector& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}



	frotator Rotator() {
		float hyp = __sqrtf(x * x + y * y + z * z);

		frotator r{};

		r.pitch = RAD2DEG2(__acosf(z / hyp));
		r.yaw = RAD2DEG2(__atan2f(y, x)) + 180.f;
		r.roll = 0;

		r.pitch += 270.f;
		if (r.pitch > 360.f) {
			r.pitch -= 360.f;
		}

		if (r.yaw < 0.f) {
			r.yaw += 360.f;
		}

		return r;
	}


	fvector GetSafeNormal(double Tolerance = 1e-6) const
	{
		const double squareSum = x * x + y * y + z * z;
		if (squareSum > Tolerance)
		{
			const double scale = 1 / sqrt(squareSum);
			return fvector(x * scale, y * scale, z * scale);
		}
		return fvector(0, 0, 0);
	}

	bool is_valid() { return x != 0 && y != 0; }
	bool is_finite() const
	{
		return std::isfinite(x) &&
			std::isfinite(y) &&
			std::isfinite(z);
	}

	bool is_zero(float tolerance = 0.001f) const { return fabsf(x) < tolerance && fabsf(y) < tolerance && fabsf(z) < tolerance; }
	fvector normalized() const {
		double len = sqrt(x * x + y * y + z * z);
		if (len > 0.0) {
			double inv_len = 1.0 / len;
			return fvector(x * inv_len, y * inv_len, z * inv_len);
		}
		return fvector(0, 0, 0);
	}
	void normalize() {
		double len = sqrt(x * x + y * y + z * z);
		if (len > 0.0) {
			double inv_len = 1.0 / len;
			x *= inv_len; y *= inv_len; z *= inv_len;
		}
	}
	bool is_null() { return x == 0 && y == 0 && z == 0; }

	inline double distance(fvector v) { double x = this->x - v.x; double y = this->y - v.y; double z = this->z - v.z; return sqrtf((x * x) + (y * y) + (z * z)) * 0.03048f; }

	double size2() const { return x * x + y * y + z * z; }

	double size() const { return sqrt(x * x + y * y + z * z); }

	bool is_valid() const {
		return !std::isnan(x) && !std::isnan(y) && !std::isnan(z) &&
			!std::isinf(x) && !std::isinf(y) && !std::isinf(z);
	}

	// ✅ ADDED LENGTH FUNCTION
	double length() const { return sqrt(x * x + y * y + z * z); }
};


struct alignas(16) fplane : public fvector {
	double w;
};

struct alignas(16) FPlane2 : public FVector {
	double W;
};



static void normalize(fvector& in)
{
	if (in.x > 89.f) in.x -= 360.f;
	else if (in.x < -89.f) in.x += 360.f;

	while (in.y > 180)in.y -= 360;
	while (in.y < -180)in.y += 360;
	in.z = 0;
}

static fvector smooth(fvector target, fvector delta_rotation, double smooth) {

	fvector diff = target - delta_rotation;
	normalize(diff);
	return delta_rotation + diff / smooth;
}

struct linear_values
{
	float h;
	float u;
	float v;
};


struct fquat
{
	double x;
	double y;
	double z;
	double w;
};

struct fmath
{
	static __forceinline void sin_cos(float* ScalarSin, float* ScalarCos, float Value);
	static __forceinline float fmod(float X, float Y);

	template<class T>
	static __forceinline T Abs(const T X)
	{
		return X < (T)0 ? -X : X;
	}

	template<class T>
	static __forceinline T clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : (X > Max ? Max : X);
	}

	template<class T>
	static __forceinline T Min(const T A, const T B)
	{
		return A < B ? A : B;
	}

	template<class T>
	static __forceinline T Max(const T A, const T B)
	{
		return A > B ? A : B;
	}

	template<class T>
	static __forceinline T lerp(const T A, const T B, const float Alpha)
	{
		return A + Alpha * (B - A);
	}

	static __forceinline float Clamp(float Value, float Min, float Max)
	{
		if (Value < Min) return Min;
		if (Value > Max) return Max;
		return Value;
	}
	static __forceinline float DegreesToRadians(float deg)
	{
		return deg * (3.14159265358979323846f / 180.0f);
	}

};

struct FMatrix2 {

	struct FPlane2 XPlane;
	struct FPlane2 YPlane;
	struct FPlane2 ZPlane;
	struct FPlane2 WPlane;

};

struct fmatrix {
	struct fplane xplane;
	struct fplane yplane;
	struct fplane zplane;
	struct fplane wplane;
};

struct fmatrix2 {
	union {
		struct {
			double        _11, _12, _13, _14;
			double        _21, _22, _23, _24;
			double        _31, _32, _33, _34;
			double        _41, _42, _43, _44;

		};
		double m[4][4];
	};		

	float M[4][4];
	fvector Transform(const fvector& v) const {
		return fvector(
			v.x * M[0][0] + v.y * M[1][0] + v.z * M[2][0] + M[3][0],
			v.x * M[0][1] + v.y * M[1][1] + v.z * M[2][1] + M[3][1],
			v.x * M[0][2] + v.y * M[1][2] + v.z * M[2][2] + M[3][2]
		);
	}

};



__forceinline fmatrix2 MatrixMultiplication(fmatrix2 pM1, fmatrix2 pM2) {
	fmatrix2 pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

struct ftransform
{
	fquat rot;
	fvector translation;
	char pad[4];
	fvector scale;
	char pad1[4];

	fmatrix2 ToMatrixWithScale()
	{
		fmatrix2 m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		double x2 = rot.x + rot.x;
		double y2 = rot.y + rot.y;
		double z2 = rot.z + rot.z;

		double xx2 = rot.x * x2;
		double yy2 = rot.y * y2;
		double zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		double yz2 = rot.y * z2;
		double wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		double xy2 = rot.x * y2;
		double wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		double xz2 = rot.x * z2;
		double wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}

};